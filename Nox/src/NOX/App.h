#pragma once

#include "Core.h"

#include "NOX/EventSystem/Event.h"
#include "NOX/EventSystem/ApplicationEvent.h"
#include "NOX/LayerSystem/LayerStack.h"

#include "Window/Window.h"

namespace Nox {
	
	class NOX_API App
	{
	public:
		App();
		virtual ~App();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		//Utilizaremos un puntero inteligente para no tener que preocuparnos por destruir este puntero ya que Window::Create retorna un objeto en el heap
		std::unique_ptr<Window> m_Window;
		WindowProps m_WindowProps;
		bool m_Running = true;

		LayerStack m_LayerStack;
	};

	//Se implementa en el cliente, aqui solo se define
	App* CreateApp();
}