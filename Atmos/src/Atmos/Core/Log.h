#pragma once
#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

class Log
{
public:
	static void Init();

	static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }

    template<typename... Args>
    static inline void CoreTrace(const char* fmt, Args&&... args) 
    {
        s_Logger->trace(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static inline void CoreInfo(const char* fmt, Args&&... args)
    {
        s_Logger->info(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static inline void CoreWarn(const char* fmt, Args&&... args)
    {
        s_Logger->warn(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static inline void CoreError(const char* fmt, Args&&... args)
    {
        s_Logger->error(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static inline void CoreCritical(const char* fmt, Args&&... args)
    {
        s_Logger->critical(fmt, std::forward<Args>(args)...);
    }

private:
	static std::shared_ptr<spdlog::logger> s_Logger;
};

