/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/test/common/test_macros/hw_test_base.h"

HWTEST_EXCLUDE_PRODUCT(ProductHelperTest, WhenAllowCompressionIsCalledThenTrueIsReturned, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(ProductHelperTest, givenHardwareInfoWhenCallingIsAdditionalStateBaseAddressWARequiredThenFalseIsReturned, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(ProductHelperTest, givenHardwareInfoWhenCallingIsMaxThreadsForWorkgroupWARequiredThenFalseIsReturned, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(ProductHelperTest, givenProductHelperWhenAskedForDefaultEngineTypeAdjustmentThenFalseIsReturned, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(ProductHelperTest, givenProductHelperWhenAskedIfAllocationSizeAdjustmentIsRequiredThenFalseIsReturned, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(ProductHelperTest, givenProductHelperWhenAskedIfPrefetchDisablingIsRequiredThenFalseIsReturned, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(ProductHelperTest, givenProductHelperWhenAskedIfPipeControlPriorToNonPipelinedStateCommandsWARequiredThenFalseIsReturned, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(ProductHelperTest, givenProductHelperWhenAskedIfTile64With3DSurfaceOnBCSIsSupportedThenTrueIsReturned, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(ProductHelperTest, WhenAllowRenderCompressionIsCalledThenTrueIsReturned, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(ProductHelperTest, whenConvertingTimestampsToCsDomainThenNothingIsChanged, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(ProductHelperTest, givenProductHelperWhenAskedIfStorageInfoAdjustmentIsRequiredThenFalseIsReturned, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(CompilerProductHelperFixture, givenAtLeastXeHpgCoreWhenGetCachingPolicyOptionsThenReturnWriteByPassPolicyOption_IsAtLeastXeHpgCore, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(ProductHelperTest, givenProductHelperWhenGetL1CachePolicyThenReturnWriteByPass_IsAtLeastXeHpgCore, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(HwInfoConfigTest, givenAtLeastXeHpgCoreWhenGetL1CachePolicyThenReturnCorrectValue_IsAtLeastXeHpgCore, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(HwInfoConfigTest, givenDebugFlagWhenCheckingIsResolveDependenciesByPipeControlsSupportedThenCorrectValueIsReturned, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(AILTests, whenModifyKernelIfRequiredIsCalledThenDontChangeKernelSources, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(CommandEncodeStatesTest, givenSlmTotalSizeEqualZeroWhenDispatchingKernelThenSharedMemorySizeIsSetCorrectly, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(MemoryManagerTests, givenEnabledLocalMemoryWhenAllocateInternalAllocationInDevicePoolThen32BitAllocationIsCreated, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(MemoryManagerTests, givenEnabledLocalMemoryWhenLinearStreamIsAllocatedInDevicePoolThenLocalMemoryPoolIsUsed, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(MemoryManagerTests, givenEnabledLocalMemoryWhenAllocateKernelIsaInDevicePoolThenLocalMemoryPoolIsUsed, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(SbaTest, givenStateBaseAddressAndDebugFlagSetWhenAppendExtraCacheSettingsThenProgramCorrectL1CachePolicy_IsAtLeastXeHpgCore, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(XeHpgSbaTest, givenSpecificProductFamilyWhenAppendingSbaThenProgramWBPL1CachePolicy, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(GfxCoreHelperTest, GivenZeroSlmSizeWhenComputeSlmSizeIsCalledThenCorrectValueIsReturned, IGFX_DG2);
HWTEST_EXCLUDE_PRODUCT(ProductHelperTestXeHpgCore, givenProductHelperWhenCheckTimestampWaitSupportForEventsThenReturnFalse, IGFX_DG2);
