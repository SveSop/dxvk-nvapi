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

#ifdef __cplusplus
}
#endif
