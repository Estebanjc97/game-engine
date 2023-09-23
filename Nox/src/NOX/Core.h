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


//Logs con verificacion de condiciones
#ifdef NOX_ENABLE_ASSERTS
	#define NOX_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define NOX_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define NOX_ASSERT(x, ...)
	#define NOX_CORE_ASSERT(x, ...)
#endif

#include "Noxpch.h"

//La macro #define BIT(x) (1 << x) es una construcción común en C++ que se utiliza para crear máscaras de bits. 
//Lo que hace esta macro es desplazar el número 1 a la izquierda en la cantidad de posiciones especificadas por x. 
//En otras palabras, crea un valor en el que solo el bit en la posición x está establecido en 1, mientras que todos los demás bits están en 0.
#define BIT(x) (1 << x)
