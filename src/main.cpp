#include "pch.h"
#include "Atmos.h"

int main(int argc, char** argv)
{
	Log::Init();
	auto app = std::make_unique<Application>("AAA");
	app->Run();

	return 0;
}