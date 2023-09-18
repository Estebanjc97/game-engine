#include "Noxpch.h"

#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Nox {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		//Configurando el formato de los mensajes con la ayuda de la libreria, puedes obtener mas informacion aqui > https://github.com/gabime/spdlog/wiki/3.-Custom-formatting

		//Explicacion del patter > [%T] : Tiempo (Timestamp) > %n : nombre del log > %v%$ : el mensaje.
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("NOX_ENGINE");
		s_CoreLogger->set_level(spdlog::level::trace); //Level 0

		s_ClientLogger = spdlog::stdout_color_mt("NOX_APP");
		s_ClientLogger->set_level(spdlog::level::trace); //Level 0

	}

}