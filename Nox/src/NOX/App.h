#pragma once
#include "Core.h"

#include "NOX/EventSystem/Event.h"

namespace Nox {
	
	class NOX_API App
	{
	public:
		App();
		virtual ~App();

		void Run();

	private:

	};

	//Se implementa en el cliente, aqui solo se define
	App* CreateApp();
}