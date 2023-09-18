#pragma once

//Esta clase sera la abstraccion de la libreria spdlog que usaremos para todos los registros (Logs) de nuestro engine

#include "NOX/Core.h" //Recordatorio > para usar NOX_API debes incluir Core!
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

//El sistema contara con dos niveles de registros (Logs) > Uno para el Engine y otro para la app. Un ejemplo son los logs que ves en el editor del engine vs los log del dispositivo que corre la app desarrollada con el engine.

//Deberia crear esta funcion como un Singleton?

namespace Nox {

	class NOX_API Log
	{
	public:
		static void Init();

		//STATIC Esto permite a otros partes del código acceder al logger centralizado y registrar mensajes de registro sin necesidad de crear una instancia de la clase que lo contiene.
		//La palabra clave inline se utiliza para sugerir al compilador que puede optimizar esta función para una llamada más rápida. En general, se utiliza para funciones pequeñas que se llaman con frecuencia.
		//std::shared_ptr es un puntero inteligente que gestiona automáticamente la vida útil del objeto al que apunta.
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; } //Funciones que retornar una REFERENCIA (&) al objeto spdlog::logger que es un smart pointer compartido (shared)
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		//Miembros no estaticos no pueden ser utilizados con funciones estaticas
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}

//Creacion de Macros para llamar al logger de forma mas sencilla

#define NOX_CORE_ERROR(...)		::Nox::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NOX_CORE_WARN(...)		::Nox::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NOX_CORE_INFO(...)		::Nox::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NOX_CORE_TRACE(...)		::Nox::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NOX_CORE_CRITICAL(...)	::Nox::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client

#define NOX_ERROR(...)			::Nox::Log::GetClientLogger()->error(__VA_ARGS__)
#define NOX_WARN(...)			::Nox::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NOX_INFO(...)			::Nox::Log::GetClientLogger()->info(__VA_ARGS__)
#define NOX_TRACE(...)			::Nox::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NOX_CRITICAL(...)		::Nox::Log::GetClientLogger()->critical(__VA_ARGS__)