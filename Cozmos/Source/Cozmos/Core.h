#pragma once

#ifdef COZ_PLATFORM_WINDOWS

	#ifdef COZ_BUILD_DLL
		#define COZMOS_API __declspec(dllexport)
	#else
		#define COZMOS_API __declspec(dllimport)
	#endif
#else
	#error Cozmos only runs on windows at the moment!
#endif

#ifdef COZ_DEBUG
	#define COZ_ENABLE_ASSERTS
#endif

#ifdef COZ_ENABLE_ASSERTS
	#define COZ_ASSERT(x, ...) { if(!(x)) { COZ_ERROR("Assertation Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define COZ_CORE_ASSERT(x, ...) { if (!(x)) {COZ_CORE_ERROR("Assertation Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define COZ_ASSERT(x, ...)
	#define COZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define COZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)