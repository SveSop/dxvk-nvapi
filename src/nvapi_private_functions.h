#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Non documented functions

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

#ifdef __cplusplus
}
#endif
