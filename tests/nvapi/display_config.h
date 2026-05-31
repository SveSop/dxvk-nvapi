#pragma once

#include "nvapi_tests_private.h"

template <typename T_NV_DISPLAYCONFIG_PATH_INFO, typename T_NV_DISPLAYCONFIG_PATH_TARGET_INFO, typename T_NV_DISPLAYCONFIG_PATH_ADVANCED_TARGET_INFO>
struct DisplayConfig {
    NvU32 pathInfoCount{};
    std::vector<T_NV_DISPLAYCONFIG_PATH_INFO> pathInfo{};

    void InitializePathInfo(NvU32 version) {
        pathInfo.resize(pathInfoCount, {});
        pathInfoData.resize(pathInfoCount, {});
        for (auto i = 0U; i < pathInfoCount; i++) {
            pathInfo[i].version = version;
            pathInfo[i].sourceModeInfo = &pathInfoData[i].sourceModeInfo; // Only works because we don't modify the vector anymore
        }
    }

    void InitializeTargetInfo(NvU32 version) {
        for (auto i = 0U; i < pathInfoData.size(); i++) {
            pathInfoData[i].targetInfos.resize(pathInfo[i].targetInfoCount, {});
            pathInfoData[i].targetInfoDetails.resize(pathInfo[i].targetInfoCount, {});
            for (auto j = 0U; j < pathInfo[i].targetInfoCount; j++) {
                pathInfoData[i].targetInfoDetails[j].version = version;
                pathInfoData[i].targetInfos[j].details = &pathInfoData[i].targetInfoDetails[j]; // See above
            }
            pathInfo[i].targetInfo = pathInfoData[i].targetInfos.data();
        }
    }

  private:
    struct PathInfoData {
        NV_DISPLAYCONFIG_SOURCE_MODE_INFO sourceModeInfo{};
        std::vector<T_NV_DISPLAYCONFIG_PATH_TARGET_INFO> targetInfos{};
        std::vector<T_NV_DISPLAYCONFIG_PATH_ADVANCED_TARGET_INFO> targetInfoDetails{};
    };

    std::vector<PathInfoData> pathInfoData{};
};
