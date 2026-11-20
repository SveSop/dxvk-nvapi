#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Non documented functions

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

#ifdef __cplusplus
}
#endif
