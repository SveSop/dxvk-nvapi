#pragma once

#include "../nvapi_private.h"

namespace dxvk {
    inline std::string fromPsoExtension(const uint32_t code) {
        static const std::map<uint32_t, std::string> codes{
            MAP_ENUM_VALUE(NV_PSO_RASTER_EXTENSION),
            MAP_ENUM_VALUE(NV_PSO_REQUEST_FASTGS_EXTENSION),
            MAP_ENUM_VALUE(NV_PSO_GEOMETRY_SHADER_EXTENSION),
            MAP_ENUM_VALUE(NV_PSO_ENABLE_DEPTH_BOUND_TEST_EXTENSION),
            MAP_ENUM_VALUE(NV_PSO_EXPLICIT_FASTGS_EXTENSION),
            MAP_ENUM_VALUE(NV_PSO_SET_SHADER_EXTENSION_SLOT_AND_SPACE),
            MAP_ENUM_VALUE(NV_PSO_VERTEX_SHADER_EXTENSION),
            MAP_ENUM_VALUE(NV_PSO_DOMAIN_SHADER_EXTENSION),
            MAP_ENUM_VALUE(NV_PSO_HULL_SHADER_EXTENSION),
        };

        auto it = codes.find(code);
        return it != codes.end() ? it->second : "UNKNOWN_SHADER_EXTENSION";
    }
}
