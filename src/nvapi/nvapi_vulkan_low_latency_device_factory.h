#pragma once

#include "../nvapi_private.h"
#include "./nvapi_resource_factory.h"
#include "./nvapi_vulkan_low_latency_device.h"

namespace dxvk {
    class NvapiVulkanLowLatencyDeviceFactory {

      public:
        static bool Initialize(NvapiResourceFactory& resourceFactory);
        static void Reset();

        [[nodiscard]] static std::pair<NvapiVulkanLowLatencyDevice*, VkResult> GetOrCreate(VkDevice device);
        [[nodiscard]] static NvapiVulkanLowLatencyDevice* Get(VkDevice device);
        static bool Destroy(VkDevice device);

      private:
        static std::unique_ptr<Vk> m_vk;
        static std::unordered_map<VkDevice, std::unique_ptr<NvapiVulkanLowLatencyDevice>> m_nvapiDeviceMap;
        static std::mutex m_mutex;
    };
}
