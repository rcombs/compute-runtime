/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "opencl/source/sharings/gl/linux/gl_sharing_linux.h"

#include "opencl/source/context/context.inl"
#include "opencl/source/helpers/gl_helper.h"
#include "opencl/source/sharings/gl/gl_arb_sync_event.h"

namespace Os {
extern const char *eglDllName;
extern const char *openglDllName;
} // namespace Os

namespace NEO {
GLSharingFunctionsLinux::GLSharingFunctionsLinux(GLType glhdcType, GLContext glhglrcHandle, GLContext glhglrcHandleBkpCtx, GLDisplay glhdcHandle)
    : glHDCType(glhdcType), glHGLRCHandle(glhglrcHandle), glHGLRCHandleBkpCtx(glhglrcHandleBkpCtx), glHDCHandle(glhdcHandle) {
    GLSharingFunctionsLinux::initGLFunctions();
    updateOpenGLContext();
}
GLSharingFunctionsLinux::~GLSharingFunctionsLinux() = default;

bool GLSharingFunctionsLinux::isGlSharingEnabled() {
    static bool oglLibAvailable = std::unique_ptr<OsLibrary>(OsLibrary::load(Os::eglDllName)).get() != nullptr;
    return oglLibAvailable;
}

void GLSharingFunctionsLinux::createBackupContext() {
    if (pfnEglCreateContext) {
        glHGLRCHandleBkpCtx = pfnEglCreateContext(glHDCHandle);
        pfnEglShareLists(glHGLRCHandle, glHGLRCHandleBkpCtx);
    }
}

GLboolean GLSharingFunctionsLinux::setSharedOCLContextState() {
    ContextInfo contextInfo{};
    GLboolean retVal = glSetSharedOCLContextState(glHDCHandle, glHGLRCHandle, CL_TRUE, &contextInfo);
    if (retVal == GL_FALSE) {
        return GL_FALSE;
    }
    glContextHandle = contextInfo.ContextHandle;
    glDeviceHandle = contextInfo.DeviceHandle;

    return retVal;
}

bool GLSharingFunctionsLinux::isOpenGlExtensionSupported(const unsigned char *pExtensionString) {
    if (glGetStringi == nullptr || glGetIntegerv == nullptr) {
        return false;
    }

    cl_int numberOfExtensions = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &numberOfExtensions);
    for (cl_int i = 0; i < numberOfExtensions; i++) {
        std::basic_string<unsigned char> pString = glGetStringi(GL_EXTENSIONS, i);
        if (pString == pExtensionString) {
            return true;
        }
    }
    return false;
}

bool GLSharingFunctionsLinux::isOpenGlSharingSupported() {

    std::basic_string<unsigned char> vendor = glGetString(GL_VENDOR);
    const unsigned char intelVendor[] = "Intel";

    if ((vendor.empty()) || (vendor != intelVendor)) {
        return false;
    }
    std::basic_string<unsigned char> version = glGetString(GL_VERSION);
    if (version.empty()) {
        return false;
    }

    bool isOpenGLES = false;
    const unsigned char versionES[] = "OpenGL ES";
    if (version.find(versionES) != std::string::npos) {
        isOpenGLES = true;
    }

    if (isOpenGLES == true) {
        const unsigned char versionES1[] = "OpenGL ES 1.";
        if (version.find(versionES1) != std::string::npos) {
            const unsigned char supportGLOES[] = "GL_OES_framebuffer_object";
            if (isOpenGlExtensionSupported(supportGLOES) == false) {
                return false;
            }
        }
    } else {
        if (version[0] < '3') {
            const unsigned char supportGLEXT[] = "GL_EXT_framebuffer_object";
            if (isOpenGlExtensionSupported(supportGLEXT) == false) {
                return false;
            }
        }
    }

    return true;
}

GlArbSyncEvent *GLSharingFunctionsLinux::getGlArbSyncEvent(Event &baseEvent) {
    std::lock_guard<std::mutex> lock{glArbEventMutex};
    auto it = glArbEventMapping.find(&baseEvent);
    if (it != glArbEventMapping.end()) {
        return it->second;
    }
    return nullptr;
}

void GLSharingFunctionsLinux::removeGlArbSyncEventMapping(Event &baseEvent) {
    std::lock_guard<std::mutex> lock{glArbEventMutex};
    auto it = glArbEventMapping.find(&baseEvent);
    if (it == glArbEventMapping.end()) {
        DEBUG_BREAK_IF(it == glArbEventMapping.end());
        return;
    }
    glArbEventMapping.erase(it);
}

GLboolean GLSharingFunctionsLinux::initGLFunctions() {
    eglLibrary.reset(OsLibrary::load(Os::eglDllName));
    glLibrary.reset(OsLibrary::load(Os::openglDllName));

    if (eglLibrary->isLoaded()) {
        GlFunctionHelper eglGetProc(eglLibrary.get(), "eglGetProcAddress");
        glGetCurrentContext = eglGetProc["eglGetCurrentContext"];
        glGetCurrentDisplay = eglGetProc["eglGetCurrentDisplay"];
        pfnEglCreateContext = eglGetProc["eglCreateContext"];
        pfnEglDeleteContext = eglGetProc["eglDestroyContext"];
        eglMakeCurrent = eglGetProc["eglMakeCurrent"];
        eglCreateImage = eglGetProc["eglCreateImage"];
        eglDestroyImage = eglGetProc["eglDestroyImage"];
        glAcquireSharedTexture = eglGetProc["eglExportDMABUFImageMESA"];
    }
    if (glLibrary->isLoaded()) {
        glGetString = (*glLibrary)["glGetString"];
        glGetStringi = (*glLibrary)["glGetStringi"];
        glGetIntegerv = (*glLibrary)["glGetIntegerv"];
        glGetTexLevelParameteriv = (*glLibrary)["glGetTexLevelParameteriv"];
    }
    this->pfnGlArbSyncObjectCleanup = cleanupArbSyncObject;
    this->pfnGlArbSyncObjectSetup = setupArbSyncObject;
    this->pfnGlArbSyncObjectSignal = signalArbSyncObject;
    this->pfnGlArbSyncObjectWaitServer = serverWaitForArbSyncObject;

    return 1;
}

template GLSharingFunctionsLinux *Context::getSharing<GLSharingFunctionsLinux>();

} // namespace NEO
