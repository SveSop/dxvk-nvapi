#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
#if __cpp_concepts >= 201907L
#include <concepts>
#endif
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <optional>
#include <regex>
#include <set>
#include <sstream>
#include <string_view>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <dxgi1_6.h>
#include <d3d11_1.h>
#ifdef _MSC_VER
#include <d3d12.h>
#else
#include "../inc/d3d12.h"
#endif
#include <vulkan/vulkan_core.h>
#include "../inc/nvml.h"

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#pragma GCC diagnostic ignored "-Wattributes"
#endif // __GNUC__

// Suppress deprecation warnings.
#define NVAPI_INTERNAL 1
#define __NVAPI_EMPTY_SAL
#include "nvapi.h"
#undef __NVAPI_EMPTY_SAL
#include "nvapi_lite_salend.h"

// TODO: Remove those once they are part of NVAPI headers
#define NV_GPU_ARCHITECTURE_GB200 (NV_GPU_ARCHITECTURE_ID)0x000001B0
#define NV_GPU_ARCH_IMPLEMENTATION_GB202 (NV_GPU_ARCH_IMPLEMENTATION_ID)0x00000002

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif // __GNUC__

#if defined(__GNUC__)
#define _ReturnAddress() __builtin_return_address(0);
#elif defined(_MSC_VER)
#include <intrin.h>
#endif

// clang-format off
#define MAP_ENUM_VALUE(v) {v, #v}
// clang-format on
