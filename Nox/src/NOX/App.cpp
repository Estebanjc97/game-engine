#include "Noxpch.h"

#include "App.h"

#include "NOX/EventSystem/ApplicationEvent.h"
#include "NOX/LogSystem/Log.h"

namespace Nox {
	App::App()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	App::~App()
	{
	}

	void App::Run()
	{
		while (m_Running) 
		{
			m_Window->OnUpdate();
		}
	}
}