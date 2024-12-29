/*
 * SPDX-FileCopyrightText: Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "util/util_env.h"
#include "util/util_log.h"
#include "util/util_string.h"
#include "util/util_statuscode.h"
#include "../version.h"
#include "../config.h"

using namespace dxvk;

static HMODULE m_ofapiCudaModule = nullptr;

extern "C" {
    NV_OF_STATUS __cdecl NvOFAPICreateInstanceCuda(uint32_t apiVer, void* functionList) {
        constexpr auto ofapiCuda = "nvofapi64_cuda.dll";
        constexpr auto cudaFuncName = "NvOFAPICreateInstanceCuda";
        constexpr auto n = __func__;

        uint32_t apiVerMajor = (apiVer & 0xfffffff0) >> 4;
        uint32_t apiVerMinor = (apiVer & 0xf);

        if (log::tracing())
            log::trace(n, apiVer, log::fmt::ptr(functionList));

        log::info(str::format("OFAPI Client Version: ", apiVerMajor, ".", apiVerMinor));

        if(!m_ofapiCudaModule){
            m_ofapiCudaModule = LoadLibraryA(ofapiCuda);
            if (!m_ofapiCudaModule) {
                log::info(str::format("Failed to load ", ofapiCuda, ": ", GetLastError()));
                return ErrorGeneric(n);
            }
        }

        auto pNvOFAPICreateInstanceCuda = reinterpret_cast<NV_OF_STATUS(__cdecl*)(uint32_t, void*)>(
            reinterpret_cast<void*>(GetProcAddress(m_ofapiCudaModule, cudaFuncName))
        );

        if (!pNvOFAPICreateInstanceCuda) {
            log::info(str::format("Failed to locate ", cudaFuncName, " in ", ofapiCuda, ": ", GetLastError()));
            FreeLibrary(m_ofapiCudaModule);
            return ErrorGeneric(n);
        }

        return pNvOFAPICreateInstanceCuda(apiVer, functionList);
    }
}
