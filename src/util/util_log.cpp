#include "util_log.h"
#include "util_env.h"
#include "util_string.h"

using PFN_wineDbgOutput = int(__cdecl*)(const char*);

namespace dxvk::log {
    static constexpr auto traceName = "trace";
    static constexpr auto infoName = "info";
    static constexpr auto logLevelEnvName = "DXVK_NVAPI_LOG_LEVEL";
    static constexpr auto logPathEnvName = "DXVK_NVAPI_LOG_PATH";
    static constexpr auto logFileName = DXVK_NVAPI_TARGET_NAME ".log";

    static const auto logLevelEnv = env::getEnvVariable(logLevelEnvName);
    static const auto logLevel = logLevelEnv == traceName ? TRACE : (logLevelEnv == infoName ? INFO : NONE);
    static const auto loggingEnabled = logLevel != NONE;
    static const auto traceEnabled = logLevel == TRACE;

    static PFN_wineDbgOutput wineDbgOutput = nullptr;
    static std::mutex fileStreamMutex;

    void print(const std::string_view logMessage) {
        auto line = str::format(logMessage, '\n'); // Do not flush buffers
        if (wineDbgOutput)
            wineDbgOutput(line.c_str());
        else
            std::cerr << line;
    }

    void initialize(std::ofstream& filestream) {
#if defined(_WIN32)
        if (auto ntdllModule = ::GetModuleHandleA("ntdll.dll"))
            wineDbgOutput = reinterpret_cast<PFN_wineDbgOutput>(reinterpret_cast<void*>(GetProcAddress(ntdllModule, "__wine_dbg_output")));
#endif

        if (!loggingEnabled)
            return;

        if (traceEnabled)
            print(str::format(logLevelEnvName, " is set to 'trace', writing all log statements, this has severe impact on performance"));

        auto logPath = env::getEnvVariable(logPathEnvName);
        if (logPath.empty())
            return;

        if (*logPath.rbegin() != '/')
            logPath += '/';

        auto fullPath = logPath + logFileName;
        filestream = std::ofstream(fullPath, std::ios::app);
        filestream << "---------- " << env::getCurrentDateTime() << " ----------" << std::endl;
        print(str::format(logPathEnvName, " is set to '", logPath, "', appending log statements to ", fullPath));
    }

    bool tracing() {
        return traceEnabled;
    }

    void write(const Level level, const std::string_view message) {
        static bool alreadyInitialized = false;
        static std::ofstream filestream;
        if (!std::exchange(alreadyInitialized, true))
            initialize(filestream);

        if (!loggingEnabled)
            return;

        if (level == TRACE && !tracing())
            return;

        LARGE_INTEGER ticks, tickPerSecond;
        QueryPerformanceCounter(&ticks);
        QueryPerformanceFrequency(&tickPerSecond);
        auto seconds = ticks.QuadPart / tickPerSecond.QuadPart;
        auto milliseconds = ((ticks.QuadPart % tickPerSecond.QuadPart) * 1000) / tickPerSecond.QuadPart;

        auto logMessage = str::format(
            seconds, ".",
            std::setfill('0'), std::setw(3), milliseconds, ":",
            std::setfill('0'), std::setw(4), std::hex, ::GetCurrentProcessId(), ":",
            std::setfill('0'), std::setw(4), std::hex, ::GetCurrentThreadId(), ":",
            level == INFO ? infoName : traceName,
            ":" DXVK_NVAPI_TARGET_NAME ":",
            message);

        print(logMessage);
        if (filestream) {
            std::scoped_lock lock(fileStreamMutex);
            filestream << logMessage << std::endl;
        }
    }
}
