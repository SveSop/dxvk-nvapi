#pragma once

#include "../nvapi_private.h"
#include "./nvapi_resource_factory.h"

namespace dxvk {

    enum class LowLatencyDeviceImplementation : uint8_t {
        LowLatency2,
        VkReflexFake
    };

    struct NvapiVulkanLowLatencyDevice {
        NvapiVulkanLowLatencyDevice(LowLatencyDeviceImplementation implementation) : m_implementation(implementation) {}
        [[nodiscard]] LowLatencyDeviceImplementation GetImplementation() const { return m_implementation; }

      private:
        LowLatencyDeviceImplementation m_implementation;
    };

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

    class NvapiVulkanLowLatency2LayerDevice final : public NvapiVulkanLowLatencyDevice {
      public:
        [[nodiscard]] static std::pair<std::unique_ptr<NvapiVulkanLowLatency2LayerDevice>, VkResult> TryCreate(Vk* vk, VkDevice device);

#define PFN_PARAM(proc) PFN_##proc proc
        [[nodiscard]] explicit NvapiVulkanLowLatency2LayerDevice(
            VkDevice device,
            VkSemaphore semaphore,
            PFN_PARAM(vkDestroySemaphore),
            PFN_PARAM(vkSetLatencySleepModeNV),
            PFN_PARAM(vkLatencySleepNV),
            PFN_PARAM(vkGetLatencyTimingsNV),
            PFN_PARAM(vkSetLatencyMarkerNV),
            PFN_PARAM(vkQueueNotifyOutOfBandNV));
#undef PFN_PARAM

        [[nodiscard]] VkSemaphore GetSemaphore() const;
        [[nodiscard]] NvBool GetLowLatencyMode() const;
        [[nodiscard]] VkResult SetLatencySleepMode(std::nullptr_t);
        [[nodiscard]] VkResult SetLatencySleepMode(bool lowLatencyMode, bool lowLatencyBoost, uint32_t minimumIntervalUs);
        [[nodiscard]] VkResult LatencySleep(uint64_t value);
        void GetLatencyTimings(std::span<NV_VULKAN_LATENCY_RESULT_PARAMS_V1::vkFrameReport, 64> frameReports);
        [[nodiscard]] bool SetLatencyMarker(uint64_t frameID, NV_VULKAN_LATENCY_MARKER_TYPE marker);
        void QueueNotifyOutOfBand(VkQueue queue, NV_VULKAN_OUT_OF_BAND_QUEUE_TYPE queueType);
        void Destroy() const;

      private:
        VkDevice m_device{};
        VkSemaphore m_semaphore{};
        PFN_vkDestroySemaphore m_vkDestroySemaphore{};

        bool m_lowLatencyMode{};
#define PFN_MEMBER(proc) \
    PFN_##proc m_##proc {}
        PFN_MEMBER(vkSetLatencySleepModeNV);
        PFN_MEMBER(vkLatencySleepNV);
        PFN_MEMBER(vkGetLatencyTimingsNV);
        PFN_MEMBER(vkSetLatencyMarkerNV);
        PFN_MEMBER(vkQueueNotifyOutOfBandNV);
#undef PFN_MEMBER
    };

    class NvapiVulkanLowLatencyFakeDevice final : public NvapiVulkanLowLatencyDevice {
      public:
        [[nodiscard]] static std::pair<std::unique_ptr<NvapiVulkanLowLatencyFakeDevice>, VkResult> TryCreate(Vk* vk, VkDevice device);

#define PFN_PARAM(proc) PFN_##proc proc
        [[nodiscard]] explicit NvapiVulkanLowLatencyFakeDevice(
            VkDevice device,
            VkSemaphore semaphore,
            PFN_PARAM(vkDestroySemaphore),
            PFN_PARAM(vkSignalSemaphore));
#undef PFN_PARAM

        [[nodiscard]] VkSemaphore GetSemaphore() const;
        [[nodiscard]] NvBool GetLowLatencyMode() const;
        [[nodiscard]] VkResult SetLatencySleepMode(std::nullptr_t);
        [[nodiscard]] VkResult SetLatencySleepMode(bool lowLatencyMode, bool lowLatencyBoost, uint32_t minimumIntervalUs);
        [[nodiscard]] VkResult LatencySleep(uint64_t value);
        void GetLatencyTimings(std::span<NV_VULKAN_LATENCY_RESULT_PARAMS_V1::vkFrameReport, 64> frameReports);
        [[nodiscard]] bool SetLatencyMarker(uint64_t frameID, NV_VULKAN_LATENCY_MARKER_TYPE marker);
        void QueueNotifyOutOfBand(VkQueue queue, NV_VULKAN_OUT_OF_BAND_QUEUE_TYPE queueType);
        void Destroy() const;

      private:
        VkDevice m_device{};
        VkSemaphore m_semaphore{};
        PFN_vkDestroySemaphore m_vkDestroySemaphore{};

        PFN_vkSignalSemaphore m_vkSignalSemaphore{};
    };
}
