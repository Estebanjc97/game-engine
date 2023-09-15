//En Core se definiran principalmente los templates y/o macros necesarios en el Engine.

#pragma once

#ifdef NOX_PLATFORM_WINDOWS //Si la plataforma es Windows
	#ifdef NOX_BUILD_DLL //Si la compilacion en un DLL (Aplica solo en el engine)
		#define NOX_API __declspec(dllexport)
	#else
		#define NOX_API __declspec(dllimport)
	#endif // NOX_BUILD_DLL
#else
	#error Nox only support Windows 
#endif // NOX_PLATFORM_WINDOWS