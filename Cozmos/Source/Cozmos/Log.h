#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Cozmos
{
	class COZMOS_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define COZ_CORE_TRACE(...)    ::Cozmos::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define COZ_CORE_INFO(...)     ::Cozmos::Log::GetCoreLogger()->info(__VA_ARGS__)
#define COZ_CORE_WARN(...)     ::Cozmos::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define COZ_CORE_ERROR(...)    ::Cozmos::Log::GetCoreLogger()->error(__VA_ARGS__)
#define COZ_CORE_FATAL(...)    ::Cozmos::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define COZ_TRACE(...)         ::Cozmos::Log::GetClientLogger()->trace(__VA_ARGS__)
#define COZ_INFO(...)          ::Cozmos::Log::GetClientLogger()->info(__VA_ARGS__)
#define COZ_WARN(...)          ::Cozmos::Log::GetClientLogger()->warn(__VA_ARGS__)
#define COZ_ERROR(...)         ::Cozmos::Log::GetClientLogger()->error(__VA_ARGS__)
#define COZ_FATAL(...)         ::Cozmos::Log::GetClientLogger()->fatal(__VA_ARGS__)

