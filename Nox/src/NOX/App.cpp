#include "Noxpch.h"

#include "App.h"

#include "NOX/EventSystem/ApplicationEvent.h"
#include "NOX/LogSystem/Log.h"

namespace Nox {
	App::App()
	{
	}

	App::~App()
	{
	}

	void App::Run()
	{
		WindowResizeEvent e(1280, 720);
		NOX_TRACE(e);

		while (true); //Este bucle se ejecutará continuamente sin detenerse hasta que se interrumpa manualmente o se termine el programa.
	}
}