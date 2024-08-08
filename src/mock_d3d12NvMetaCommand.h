#pragma once

#include <guiddef.h> // For GUID definitions
#include <unknwnbase.h> // For IUnknown
#include <d3d12.h> // For ID3D12NvMetaCommand

// Define the GUID for ID3D12NvMetaCommand_V1
const GUID IID_ID3D12NvMetaCommand_V1 = { 0x00BF193A, 0x117B, 0x42BC, { 0xBB, 0xCD, 0xE9, 0x64, 0xA0, 0xEA, 0x4F, 0x2B } };

// Custom __mingw_uuidof implementation
template <typename T>
constexpr const GUID& __mingw_uuidof();

template <>
constexpr const GUID& __mingw_uuidof<ID3D12NvMetaCommand_V1>() {
    return IID_ID3D12NvMetaCommand_V1;
}

// MockD3D12NvMetaCommand definition
class MockD3D12NvMetaCommand : public ID3D12NvMetaCommand {
public:
    // IUnknown methods
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppv) override {
        if (riid == __uuidof(ID3D12NvMetaCommand_V1) || riid == __uuidof(IUnknown)) {
            *ppv = static_cast<ID3D12NvMetaCommand*>(this);
            AddRef();
            return S_OK;
        }
        return E_NOINTERFACE;
    }

    STDMETHOD_(ULONG, AddRef)(THIS) override {
        return ++m_refCount;
    }

    STDMETHOD_(ULONG, Release)(THIS) override {
        ULONG refCount = --m_refCount;
        if (refCount == 0) {
            delete this;
        }
        return refCount;
    }

    // ID3D12NvMetaCommand methods
    STDMETHOD(GetRequiredParameterResourceSize)(THIS_ NV_META_COMMAND_RESOURCE_TYPE ResourceType, NvU64* SizeInBytes) const override {
        // Implementation here
        return S_OK;
    }

protected:
    virtual ~MockD3D12NvMetaCommand() {}

private:
    ULONG m_refCount = 1;
};
