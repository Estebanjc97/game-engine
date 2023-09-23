#pragma once
#include "Core.h"

#include "NOX/EventSystem/Event.h"
#include "Window/Window.h"

namespace Nox {
	
	class NOX_API App
	{
	public:
		App();
		virtual ~App();

		void Run();

	private:
		//Utilizaremos un puntero inteligente para no tener que preocuparnos por destruir este puntero ya que Window::Create retorna un objeto en el heap
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//Se implementa en el cliente, aqui solo se define
	App* CreateApp();
}