/*
 * Copyright (C) 2020-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "level_zero/core/source/driver/driver.h"
#include "level_zero/core/source/driver/driver_handle.h"

#include "zex_api.h"

ZE_APIEXPORT ze_result_t ZE_APICALL
zexDriverImportExternalPointer(
    ze_driver_handle_t hDriver,
    void *ptr,
    size_t size) {
    return L0::DriverHandle::fromHandle(hDriver)->importExternalPointer(ptr, size);
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zexDriverReleaseImportedPointer(
    ze_driver_handle_t hDriver,
    void *ptr) {
    return L0::DriverHandle::fromHandle(hDriver)->releaseImportedPointer(ptr);
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zexDriverGetHostPointerBaseAddress(
    ze_driver_handle_t hDriver,
    void *ptr,
    void **baseAddress) {
    return L0::DriverHandle::fromHandle(hDriver)->getHostPointerBaseAddress(ptr, baseAddress);
}
