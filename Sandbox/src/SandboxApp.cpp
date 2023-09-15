#include <Nox.h>

namespace Nox {
	NOX_API void CheckDllLinking();
}

//La clase Sandbox es la clase cliente que hereda de nuestra clase App que contiene el Engine.
class Sandbox : public Nox::App
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{
	
	}
};

//Esta es la implementacion de la funcion definida en App.h
//Toda app que quiera usar nuestro engine debera implementar esta funcion
Nox::App* Nox::CreateApp()
{
	return new Sandbox();
}