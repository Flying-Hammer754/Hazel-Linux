#pragma once
#include "Hazel/Core/Base.h"
#include "Hazel/Core/Application.h"

#include <string>
#include <tuple>
namespace Hazel {
extern Application* CreateApplication(ApplicationCommandLineArgs args, const std::string& settingsDir);
}
int main(int argc, char** argv)
{
	std::string settingsDirectory = "./";
	if (argc > 1)
	{
		std::string argv1 = argv[1];
		if (argv1 == "--help" || argv1 == "-h" || argv1 == "--enginehelp")
		{
			printf(R"helpmsg(Usage: HazelApp <ProjectDirectory> <SettingsDirectory> <Application Specific Arguments>
	<ProjectDirectory> is the directory storing the project's assets folder.
	<SettingsDirectory> is the directory where engine and application configuration files & temporary files are stored.
	<Application Specific Arguments> are handled by the application instead of the engine. Not all applications use it.
			
	--- Commands: ---
		--help, -h, --enginehelp: print this help message.
		--apphelp: print a help message which is application specific,
			you have to input it as the Third argument eg. at <Application Specific Arguments>
	--- --------- ---)helpmsg");
			return 0;
		}
	}
	if (argc > 3)
	{
		std::string argv3 = argv[3];
		if (argv3 == "--apphelp")
		{
			auto app = Hazel::CreateApplication({ argc, argv }, settingsDirectory);
			return 0;
		}
	}
	if (argc > 2)
	{
		settingsDirectory = std::filesystem::absolute(argv[2]);
		chdir(argv[1]);
		if (settingsDirectory.at(settingsDirectory.size() - 1) != '/')
		{
			settingsDirectory += '/';
		}
	}
	Hazel::Log::Init(settingsDirectory);

	HZ_PROFILE_BEGIN_SESSION("Startup", (settingsDirectory + "HazelProfile-Startup.json").c_str());
	auto app = Hazel::CreateApplication({ argc, argv }, settingsDirectory);
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Runtime", (settingsDirectory + "HazelProfile-Runtime.json").c_str());
	app->Run();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Shutdown", (settingsDirectory + "HazelProfile-Shutdown.json").c_str());
	delete app;
	HZ_PROFILE_END_SESSION();
}


