#pragma once

#include "NOX/Core.h"

namespace Nox {

	//En una primera etapa, los eventos seran inmediatamente enviados y tendran que ser manejados en el momento en el que se activan (ocurre inmediatamente).
	//En un futuro, los eventos seran almacenados en forma de buffer en un bus de eventos y seran procesados en la parte de "event" durante la etapa de actualizacion.

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,	//Eventos que ocurren con la ventana
		AppTick, AppUpdate, AppRender,											//Eventos que ocurren en el Cliente (App)
		KeyPressed, KeyReleased,												//Eventos del teclado
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled		//Eventos del mouse
	};

	enum EventCategory //Las categorias la utilizaremos para filtrar los eventos que recibo (EventType), si deseo saber cuales son los eventos asociados a la applicacion, puedo simplemente solicitar EventCategoryApplication
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class NOX_API Event
	{
		friend class EventDispatcher; //La declaración de fried permite que una clase otorgue permisos especiales a otra para acceder a sus miembros que normalmente serían inaccesibles.
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		//La optimización "inlining" es un proceso en el que el cuerpo de una función se copia directamente en el lugar donde se llama en lugar de realizar una llamada a la función. 
		//Esto puede mejorar el rendimiento del programa al reducir la sobrecarga de llamada a la función, pero también puede aumentar el tamaño del código resultante.
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	protected:
		bool m_Handled = false;

	};

	//El despachador de eventos es una clase en base a templates ya que cada despachador sera construido de acuerdo a un tipo de evento
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) 
	{
		return os << e.ToString();
	}
}