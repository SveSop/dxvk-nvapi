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

#ifdef __cplusplus
}
#endif
