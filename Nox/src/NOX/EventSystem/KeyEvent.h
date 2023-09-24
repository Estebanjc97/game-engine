#pragma once

#include "Event.h"

namespace Nox {

	class NOX_API KeyEvent : public Event //Realmente necesito exportar este tipo al cliente?
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput) //Operracion a nivel de bits -> 0100 | 0010 = 0110  retorna 0110 (0110 contiene ambas categorias, es por esto que hicimos el enmascaramiento)
	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {
		}

		int m_KeyCode;

	};

	class NOX_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), m_RepeatCount(repeatCount) {}
		
		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "keyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};

	class NOX_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "keyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

}