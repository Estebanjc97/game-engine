//El Punto de entrada de nuestro Engine, sera necesario para toda aplicacion que quiera usar nuestra API. Se dividira dependiendo la plataforma.
#pragma once
#include "LogSystem/Log.h"

#ifdef NOX_PLATFORM_WINDOWS

extern Nox::App* Nox::CreateApp(); //Esto es basicamente una funcion que estara definida en otro lugar y se encargara de retornar la aplicacion por nosotros / CreateApp se implementara en el cliente!

int main(int argc, char** argv)
{
	Nox::Log::Init();
	NOX_CORE_INFO("Nox Engine esta vivo!");

	auto app = Nox::CreateApp(); //Alojaremos los datos de la nueva app de Nox en el heap, esto es porque Sandbox sera bastante grande y queremos controlar explicitamente la vida de este objeto que es basicamente nuestro engine.

	app->Run();

	delete app; //Liberando memoria del heap
}

#endif // NOX_PLATFORM_WINDOWS