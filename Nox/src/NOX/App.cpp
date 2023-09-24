#include "Noxpch.h"

#include "App.h"

#include "NOX/LogSystem/Log.h"

namespace Nox {

//std::bind(...): La función std::bind se utiliza para crear una función de enlace que vincula una función miembro 
#define BIND_EVENT_FN(x) std::bind(&App::x, this, std::placeholders::_1)

	App::App()
	{
		m_WindowProps = WindowProps("Nox Engine", 1280, 720);

		m_Window = std::unique_ptr<Window>(Window::Create(m_WindowProps)); //Crear una nueva pantalla


		//(en este caso, App::OnEvent) a un objeto (en este caso, this) y permite la posibilidad de proporcionar argumentos adicionales a la función vinculada.
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	App::~App()
	{
	}

	void App::OnEvent(Event& e)
	{
		EventDispatcher dispatcher = EventDispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) //Cliclo para recorrer el stack al revez
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}

	}

	void App::Run()
	{
		while (m_Running) 
		{

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void App::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void App::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

}