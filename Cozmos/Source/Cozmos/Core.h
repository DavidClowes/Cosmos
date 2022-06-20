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