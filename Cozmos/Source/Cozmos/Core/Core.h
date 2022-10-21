#pragma once

#include <memory>

#ifdef COZ_PLATFORM_WINDOWS
#if COZ_DYNAMIC_LINK
	#ifdef COZ_BUILD_DLL
		#define  __declspec(dllexport)
	#else
		#define  __declspec(dllimport)
	#endif
#else
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

namespace Cozmos
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}