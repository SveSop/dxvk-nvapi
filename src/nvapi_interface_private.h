#pragma once

struct NVAPI_INTERFACE_TABLE nvapi_interface_private_table[] = {
    // Non documented function pointers
    { "NvAPI_GPU_GetGPCMask", 0x7dbe90ab },
    { "NvAPI_GPU_GetTPCMaskOnGPC", 0xed74af30 },
    { "NvAPI_GPU_GetTPCMask", 0x4a35df54 },
};
