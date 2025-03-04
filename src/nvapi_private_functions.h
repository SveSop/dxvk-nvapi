#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Non documented functions

typedef struct
{
    NvPhysicalGpuHandle hPhysicalGpu;
    NvU8 data0 : 4;
    NvU8 data1 : 4;
} NODE_INFO;

typedef struct _NV_CUDA_COMPUTE
{
    NvU32   version;        //structure version
    NvU32   count;
    NODE_INFO* nodeInfo;
} NV_CUDA_COMPUTE_V2;

typedef NV_CUDA_COMPUTE_V2         NV_CUDA_COMPUTE;
#define NV_CUDA_COMPUTE_VER2       MAKE_NVAPI_VERSION(NV_CUDA_COMPUTE_V2, 2)
#define NV_CUDA_COMPUTE_VER        NV_CUDA_COMPUTE_VER2

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
///////////////////////////////////////////////////////////////////////////////
NVAPI_INTERFACE NvAPI_GPU_GetGPCMask(NvPhysicalGpuHandle hPhysicalGpu, NvU32 *pSupport);

///////////////////////////////////////////////////////////////////////////////
// FUNCTION NAME:   NvAPI_GPU_GetTPCMaskOnGPC
//
//! DESCRIPTION:     This API is unknown and experimental
///////////////////////////////////////////////////////////////////////////////
NVAPI_INTERFACE NvAPI_GPU_GetTPCMaskOnGPC(NvPhysicalGpuHandle hPhysicalGpu, NvU32 Info, NvU32 *pSupport);

///////////////////////////////////////////////////////////////////////////////
// FUNCTION NAME:   NvAPI_CUDA_EnumComputeCapableByTopology
//
//! DESCRIPTION:     This API is unknown and experimental
///////////////////////////////////////////////////////////////////////////////
NVAPI_INTERFACE NvAPI_CUDA_EnumComputeCapableByTopology(NV_CUDA_COMPUTE* computeInfo, NvU32 flags);

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
