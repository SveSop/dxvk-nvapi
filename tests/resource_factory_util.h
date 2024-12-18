#pragma once

#include "nvapi_tests_private.h"
#include "nvapi_d3d_mocks.h"
#include "nvapi_sysinfo_mocks.h"
#include "mock_factory.h"

DXGIDxvkAdapterMock* CreateDXGIDxvkAdapterMock();
DXGIOutput6Mock* CreateDXGIOutput6Mock();

void SetupResourceFactory(
    std::unique_ptr<DXGIDxvkFactoryMock> dxgiFactory,
    std::unique_ptr<VulkanMock> vulkan,
    std::unique_ptr<NvmlMock> nvml,
    std::unique_ptr<LfxMock> lfx);

void ResetGlobals();

[[nodiscard]] std::array<std::unique_ptr<trompeloeil::expectation>, 23> ConfigureDefaultTestEnvironment(
    DXGIDxvkFactoryMock& dxgiFactory,
    VulkanMock& vulkan,
    NvmlMock& nvml,
    LfxMock& lfx,
    DXGIDxvkAdapterMock& adapter,
    DXGIOutput6Mock& output);

[[nodiscard]] std::array<std::unique_ptr<trompeloeil::expectation>, 40> ConfigureExtendedTestEnvironment(
    DXGIDxvkFactoryMock& dxgiFactory,
    VulkanMock& vulkan,
    NvmlMock& nvml,
    LfxMock& lfx,
    DXGIDxvkAdapterMock& adapter1,
    DXGIDxvkAdapterMock& adapter2,
    DXGIOutput6Mock& output1,
    DXGIOutput6Mock& output2,
    DXGIOutput6Mock& output3);

void ConfigureGetPhysicalDeviceProperties2(
    VkPhysicalDeviceProperties2* props,
    std::function<void(
        VkPhysicalDeviceProperties*,
        VkPhysicalDeviceIDProperties*,
        VkPhysicalDevicePCIBusInfoPropertiesEXT*,
        VkPhysicalDeviceDriverPropertiesKHR*,
        VkPhysicalDeviceFragmentShadingRatePropertiesKHR*)>
        configure);
