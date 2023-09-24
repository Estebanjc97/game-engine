#include "Noxpch.h"
#include "LayerStack.h"

/*Basicamente 
* Todas las capas (Layers) seran incluidos en un stack std::vector de layer*
* Habran dos funcionalidades principales, inlcuir un layer o incluir un overlay
* los Layer seran incluidos en la primera mitad del stack y los overlays seran incluidos en la segunda mitad
* ex. [Layer1, Layer2, Layer3, 'half', Overlay1, Overlay2, Overlay3]
* Como ejemplo lo nombre 'half' pero sigue siendo un layer. Esto solo se hace para dar a entender la diferencia y el orden entre layer y overlay
* Un nuevo overlay sera incluido al final del arreglo, mientras que un nuevo layer sera incluido en la mitad del arreglo
*/

namespace Nox
{

	LayerStack::LayerStack()
	{
		m_LayersInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) 
	{
		m_LayersInsert = m_Layers.emplace(m_LayersInsert, layer);
	}

	void LayerStack::PushOverlay(Layer* overlay) 
	{
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayersInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}

}