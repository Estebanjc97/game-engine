#include <Nox.h>

class ExampleLayer : public Nox::Layer
{
public:
	ExampleLayer() : Layer("Example") {};

	void OnUpdate() override
	{
		NOX_INFO("Example layer :: Update");
	}

	void OnEvent(Nox::Event& event) override 
	{
		NOX_INFO("{0}", event);
	}

};

//La clase Sandbox es la clase cliente que hereda de nuestra clase App que contiene el Engine.
class Sandbox : public Nox::App //La herencia pública significa que la clase Sandbox heredará todos los miembros públicos de la clase base Nox::App.
{
public:
	Sandbox()
	{ 
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	
	}
};

//Esta es la implementacion de la funcion definida en App.h
//Toda app que quiera usar nuestro engine debera implementar esta funcion
Nox::App* Nox::CreateApp()
{
	return new Sandbox(); //Retorno de un nuevo objeto en el heap
}