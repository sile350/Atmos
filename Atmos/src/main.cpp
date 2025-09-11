#include "pch.h"
#include "Atmos/Core/Application.h"
#include "Atmos.h"

int main(int argc, char** argv)
{
	Log::Init();

	auto* app = new Application("AAA");
	app->Run();
	delete app;
	return 0;
}