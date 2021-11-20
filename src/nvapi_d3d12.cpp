#include "nvapi_private.h"
#include "nvapi_static.h"
#include "d3d12/nvapi_d3d12_device.h"
#include "util/util_statuscode.h"
#include "util/util_op_code.h"
#include "util/util_pso_extension.h"
#include "util/util_string.h"

extern "C" {
    using namespace dxvk;

    NvAPI_Status __cdecl NvAPI_D3D12_IsNvShaderExtnOpCodeSupported(ID3D12Device *pDevice, NvU32 opCode, bool *pSupported) {
        constexpr auto n = __func__;

        if (pDevice == nullptr || pSupported == nullptr)
                return InvalidArgument(n);

        // VKD3D does not know any NVIDIA intrinsics
        *pSupported = false;

        return Ok(str::format(n, " ", opCode, " (", fromCode(opCode), ")"));
    }

    NvAPI_Status __cdecl NvAPI_D3D12_CreateCubinComputeShaderWithName(ID3D12Device* pDevice, const void* cubinData, NvU32 cubinSize, NvU32 blockX, NvU32 blockY, NvU32 blockZ, const char* shaderName, NVDX_ObjectHandle* pShader) {
        constexpr auto n = __func__;
        static bool alreadyLoggedError = false;
        static bool alreadyLoggedOk = false;

        if (pDevice == nullptr)
            return InvalidArgument(n);

        if (!NvapiD3d12Device::CreateCubinComputeShaderWithName(pDevice, cubinData, cubinSize, blockX, blockY, blockZ, shaderName, pShader))
            return Error(n, alreadyLoggedError);

        return Ok(n, alreadyLoggedOk);
    }

    NvAPI_Status __cdecl NvAPI_D3D12_CreateCubinComputeShader(ID3D12Device* pDevice, const void* cubinData, NvU32 cubinSize, NvU32 blockX, NvU32 blockY, NvU32 blockZ, NVDX_ObjectHandle* pShader) {
        constexpr auto n = __func__;
        static bool alreadyLoggedError = false;
        static bool alreadyLoggedOk = false;

        if (pDevice == nullptr)
            return InvalidArgument(n);

        if (!NvapiD3d12Device::CreateCubinComputeShaderWithName(pDevice, cubinData, cubinSize, blockX, blockY, blockZ, "", pShader))
            return Error(n, alreadyLoggedError);

        return Ok(n, alreadyLoggedOk);
    }

    NvAPI_Status __cdecl NvAPI_D3D12_DestroyCubinComputeShader(ID3D12Device* pDevice, NVDX_ObjectHandle pShader) {
        constexpr auto n = __func__;
        static bool alreadyLoggedError = false;
        static bool alreadyLoggedOk = false;

        if (pDevice == nullptr)
            return InvalidArgument(n);

        if (!NvapiD3d12Device::DestroyCubinComputeShader(pDevice, pShader))
            return Error(n, alreadyLoggedError);

        return Ok(n, alreadyLoggedOk);
    }

    NvAPI_Status __cdecl NvAPI_D3D12_GetCudaTextureObject(ID3D12Device* pDevice, D3D12_CPU_DESCRIPTOR_HANDLE srvHandle, D3D12_CPU_DESCRIPTOR_HANDLE samplerHandle, NvU32* cudaTextureHandle) {
        constexpr auto n = __func__;
        static bool alreadyLoggedError = false;
        static bool alreadyLoggedOk = false;

        if (pDevice == nullptr)
            return InvalidArgument(n);

        if (!NvapiD3d12Device::GetCudaTextureObject(pDevice, srvHandle, samplerHandle, cudaTextureHandle))
            return Error(n, alreadyLoggedError);

        return Ok(n, alreadyLoggedOk);
    }

    NvAPI_Status __cdecl NvAPI_D3D12_GetCudaSurfaceObject(ID3D12Device* pDevice, D3D12_CPU_DESCRIPTOR_HANDLE uavHandle, NvU32* cudaSurfaceHandle) {
        constexpr auto n = __func__;
        static bool alreadyLoggedError = false;
        static bool alreadyLoggedOk = false;

        if (pDevice == nullptr)
            return InvalidArgument(n);

        if (!NvapiD3d12Device::GetCudaSurfaceObject(pDevice, uavHandle, cudaSurfaceHandle))
            return Error(n, alreadyLoggedError);

        return Ok(n, alreadyLoggedOk);
    }

    NvAPI_Status __cdecl NvAPI_D3D12_LaunchCubinShader(ID3D12GraphicsCommandList* pCmdList, NVDX_ObjectHandle pShader, NvU32 blockX, NvU32 blockY, NvU32 blockZ, const void* params, NvU32 paramSize) {
        constexpr auto n = __func__;
        static bool alreadyLoggedError = false;
        static bool alreadyLoggedOk = false;

        if (pCmdList == nullptr)
            return InvalidArgument(n);

        if (!NvapiD3d12Device::LaunchCubinShader(pCmdList, pShader, blockX, blockY, blockZ, params, paramSize))
            return Error(n, alreadyLoggedError);

        return Ok(n, alreadyLoggedOk);
    }

    NvAPI_Status __cdecl NvAPI_D3D12_CaptureUAVInfo(ID3D12Device* pDevice, NVAPI_UAV_INFO* pUAVInfo) {
        constexpr auto n = __func__;
        static bool alreadyLoggedError = false;
        static bool alreadyLoggedOk = false;

        if (pDevice == nullptr)
            return InvalidArgument(n);

        if (!NvapiD3d12Device::CaptureUAVInfo(pDevice, pUAVInfo))
            return Error(n, alreadyLoggedError);

        return Ok(n, alreadyLoggedOk);
    }

    NvAPI_Status __cdecl NvAPI_D3D12_GetGraphicsCapabilities(IUnknown* pDevice, NvU32 structVersion, NV_D3D12_GRAPHICS_CAPS* pGraphicsCaps) {
        constexpr auto n = __func__;

        if (nvapiAdapterRegistry == nullptr)
            return ApiNotInitialized(n);

        if (pDevice == nullptr || structVersion != NV_D3D12_GRAPHICS_CAPS_VER1)
            return InvalidArgument(n);

        pGraphicsCaps->majorSMVersion = 0;
        pGraphicsCaps->minorSMVersion = 0;
        // all Vulkan drivers are expected to support ZBC clear without padding
        pGraphicsCaps->bFastUAVClearSupported = true;

        NvapiAdapter* adapter = nullptr;
        auto luid = NvapiD3d12Device::GetLuid(pDevice);
        if (luid.has_value())
            adapter = nvapiAdapterRegistry->GetAdapter(luid.value());

        if (adapter == nullptr || adapter->GetDriverId() != VK_DRIVER_ID_NVIDIA_PROPRIETARY)
            return Ok(str::format(n, " (sm_0)"));

        // From https://arnon.dk/matching-sm-architectures-arch-and-gencode-for-various-nvidia-cards/
        // Note: One might think that SM here is D3D12 Shader Model, in fact it is the "Streaming Multiprocessor" architecture name
        switch (adapter->GetArchitectureId()) {
            case NV_GPU_ARCHITECTURE_GA100:
                pGraphicsCaps->majorSMVersion = 8;
                pGraphicsCaps->minorSMVersion = 6; // Take the risk that no one uses an NVIDIA A100 with this implementation
                break;
            case NV_GPU_ARCHITECTURE_TU100:
                pGraphicsCaps->majorSMVersion = 7;
                pGraphicsCaps->minorSMVersion = 5;
                break;
            case NV_GPU_ARCHITECTURE_GV100:
                pGraphicsCaps->majorSMVersion = 7;
                pGraphicsCaps->minorSMVersion = 0;
                break;
            case NV_GPU_ARCHITECTURE_GP100:
                pGraphicsCaps->majorSMVersion = 6;
                pGraphicsCaps->minorSMVersion = 0;
                break;
            case NV_GPU_ARCHITECTURE_GM200:
                pGraphicsCaps->majorSMVersion = 5;
                pGraphicsCaps->minorSMVersion = 0;
                break;
            default:
                break;
        }

        // These fields should be derivable from architecture, but not sure yet what the consequences are
        // Currently we do not require these fields, we can implement them later.
        // pGraphicsCaps->bExclusiveScissorRectsSupported = ;
        // pGraphicsCaps->bVariablePixelRateShadingSupported = ; // Should be supported on Turing and newer

        return Ok(str::format(n, " (sm_", pGraphicsCaps->majorSMVersion, pGraphicsCaps->minorSMVersion, ")"));
    }

    NvAPI_Status __cdecl NvAPI_D3D12_IsFatbinPTXSupported(ID3D12Device* pDevice, bool* isSupported) {
        constexpr auto n = __func__;
        static bool alreadyLoggedError = false;
        static bool alreadyLoggedOk = false;

        if (pDevice == nullptr)
            return InvalidArgument(n);

        *isSupported = NvapiD3d12Device::IsFatbinPTXSupported(pDevice);
        if (!*isSupported)
            return Error(n, alreadyLoggedError);

        return Ok(n, alreadyLoggedOk);
    }

    NvAPI_Status __cdecl NvAPI_D3D12_CreateGraphicsPipelineState(ID3D12Device *pDevice, const D3D12_GRAPHICS_PIPELINE_STATE_DESC *pPSODesc, NvU32 numExtensions, const NVAPI_D3D12_PSO_EXTENSION_DESC** ppExtensions, ID3D12PipelineState **ppPSO) {
        constexpr auto n = __func__;
        static bool alreadyLoggedOk = false;

        if (pDevice == nullptr)
            return InvalidArgument(n);

        if (numExtensions == 0)
            return InvalidArgument(n);

        if (ppExtensions[0]->baseVersion != NV_PSO_EXTENSION_DESC_VER_1)
            return IncompatibleStructVersion(n);

        std::string extensionNames;
        for(auto i = 0U; i < numExtensions;i++)
            extensionNames += str::format(fromPsoExtension(ppExtensions[i]->psoExtension), ",");

        extensionNames.pop_back();

        if (!NvapiD3d12Device::CreateGraphicsPipelineState(pDevice, pPSODesc, numExtensions, ppExtensions, ppPSO))
            return NotSupported(str::format(n, " ", numExtensions, " (", extensionNames, ")"));

        return Ok(str::format(n, " ", numExtensions, " (", extensionNames, ")"), alreadyLoggedOk);
    }

    NvAPI_Status __cdecl NvAPI_D3D12_SetDepthBoundsTestValues(ID3D12GraphicsCommandList *pCommandList, const float minDepth, const float maxDepth) {
        constexpr auto n = __func__;
        static bool alreadyLoggedError = false;
        static bool alreadyLoggedOk = false;

        if (pCommandList == nullptr)
            return InvalidArgument(n);

        if(!NvapiD3d12Device::SetDepthBoundsTestValues(pCommandList, minDepth, maxDepth))
            return Error(n, alreadyLoggedError);

        return Ok(n, alreadyLoggedOk);
    }
}
