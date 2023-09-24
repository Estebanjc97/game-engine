#pragma once

#include "NOX/Core.h"
#include "NOX/EventSystem/Event.h"

namespace Nox 
{
	class NOX_API Layer
	{
	public: 
		Layer(const std::string& name = "Layer");
		virtual ~Layer();
		
		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate() {};
		virtual void OnEvent(Event&) {};

		inline const std::string& GetName() const { return m_DebugName; }

	private:
		std::string m_DebugName;
	};
}
