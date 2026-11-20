#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Non documented functions

#define MAX_NUMBER_OF_FAN_COOLER_STATUS_ENTRIES 32
typedef struct {
        NvU32 coolerId;
        NvU32 currentRPM;
        NvU32 minimumLevel;
        NvU32 maximumLevel;
        NvU32 currentLevel;
        NvU32 Reserved[8];
} NV_GPU_FANCOOLERSTATUS_ENTRY;

typedef struct {
        NvU32 version;
        NvU32 fanCount;
        NvU32 reserved[8];
        NV_GPU_FANCOOLERSTATUS_ENTRY fanCoolersStatusEntries[MAX_NUMBER_OF_FAN_COOLER_STATUS_ENTRIES];
} NV_GPU_FANCOOLERSTATUS_V1;

typedef NV_GPU_FANCOOLERSTATUS_V1 NV_GPU_FANCOOLERSTATUS;

#define NV_GPU_FANCOOLERSTATUS_VER1 MAKE_NVAPI_VERSION(NV_GPU_FANCOOLERSTATUS_V1,1)
#define NV_GPU_FANCOOLERSTATUS_VER NV_GPU_FANCOOLERSTATUS_VER1

///////////////////////////////////////////////////////////////////////////////
// FUNCTION NAME:   NvAPI_GPU_GetGPCMask
//
//! DESCRIPTION:     This API is unknown and experimental
//
// Returns:  a bitmask of the GPC's available on the GPU. This can vary between different cards, so use X080 type values
// Eg. a 4080 has 7 GPC's - 0x01111111 = 127
///////////////////////////////////////////////////////////////////////////////
NVAPI_INTERFACE NvAPI_GPU_GetGPCMask(NvPhysicalGpuHandle hPhysicalGpu, NvU32 *pGPCMask, NvU32 flags);

///////////////////////////////////////////////////////////////////////////////
// FUNCTION NAME:   NvAPI_GPU_GetTPCMaskOnGPC
//
//! DESCRIPTION:     This API is unknown and experimental
//
// Returns:  a bitmask of the TPC's available on the GPC. This can vary between different cards, so use X080 type values.
// This will be an approximation depending on the GPU arch, and the layout will not be "correct".
// This call should be done with gpcIndex being the GPU's GPC index at the callers responsibility.
///////////////////////////////////////////////////////////////////////////////
NVAPI_INTERFACE NvAPI_GPU_GetTPCMaskOnGPC(NvPhysicalGpuHandle hPhysicalGpu, NvU32 gpcIndex, NvU32 *pTPCMask);

///////////////////////////////////////////////////////////////////////////////
// FUNCTION NAME:   NvAPI_CUDA_EnumComputeCapableByTopology
//
//! DESCRIPTION:     This API is unknown and experimental
///////////////////////////////////////////////////////////////////////////////
NVAPI_INTERFACE NvAPI_CUDA_EnumComputeCapableByTopology(NV_COMPUTE_GPU_TOPOLOGY* computeInfo, NvU32* displayId, NvU32 param0, NvU32 param1);

///////////////////////////////////////////////////////////////////////////////
// FUNCTION NAME:   NvAPI_GPU_GetPstatesInfo
//
//! DESCRIPTION:     This API is unknown and experimental - Deprecated
///////////////////////////////////////////////////////////////////////////////
NVAPI_INTERFACE NvAPI_GPU_GetPstatesInfo(NvPhysicalGpuHandle hPhysicalGpu, NV_GPU_PERF_PSTATES_INFO *pPstatesInfo);

///////////////////////////////////////////////////////////////////////////////
// FUNCTION NAME:   NvAPI_GPU_ClientFanCoolersGetStatus
//
//! DESCRIPTION:     This API is unknown and experimental
///////////////////////////////////////////////////////////////////////////////
NVAPI_INTERFACE NvAPI_GPU_ClientFanCoolersGetStatus(NvPhysicalGpuHandle hPhysicalGpu, NV_GPU_FANCOOLERSTATUS* pFanCoolerStatus);

#ifdef __cplusplus
}
#endif
