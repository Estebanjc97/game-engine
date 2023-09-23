#pragma once

#include "Noxpch.h"

#include "NOX/Core.h"
#include "NOX/EventSystem/Event.h"

namespace Nox 
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		//Constructor con parametros por defecto
		WindowProps(const std::string& title = "Nox Engine",
					unsigned int width = 1280,
					unsigned int height = 1280)
			: Title(title), Width(width), Height(height)
		{}
	};

	//Esta clase es casi una interfaz, en la que se definiran las normas a seguir para que una plataforma implemente una ventana (Window)
	class NOX_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0; //Fuerza a las clases que implementar Window a implementar la funcion

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Window Attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		//Esta interfaz sera implementada de forma diferente en cada plataforma, por lo que esta funcion devolvera una ventana de acuerdo a la plataforma (ex WindowsWindow)
		static Window* Create(const WindowProps& props = WindowProps());
	};

}