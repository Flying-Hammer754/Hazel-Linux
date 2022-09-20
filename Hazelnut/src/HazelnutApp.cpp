#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Hazel {

	class Hazelnut : public Application
	{
	public:
		Hazelnut(const ApplicationSpecification& spec)
			: Application(spec)
		{
			PushLayer(new EditorLayer());
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args, const std::string& configDir)
	{
		ApplicationSpecification spec;
		spec.Name = "Hazelnut";
		spec.CommandLineArgs = args;
		spec.WorkingDirectory = "../Hazelnut/";
		spec.SettingsDirectory = configDir;
		if (args.Count > 3)
		{
			std::string argv3 = args[3];
			if (argv3 == "--apphelp")
			{
				printf(R"apphelpmsg(--- Application help message: ---
	- <Application Specific Arguments>: -
		1. <StartupScene>: path to a scene file to load at startup
	- ------------ -------- ----------- -)apphelpmsg");
				return nullptr;
			}
		}

		return new Hazelnut(spec);
	}

}
