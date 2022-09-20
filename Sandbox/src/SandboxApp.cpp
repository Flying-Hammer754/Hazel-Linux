#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Hazel::Application
{
public:
	Sandbox(const Hazel::ApplicationSpecification& specification)
		: Hazel::Application(specification)
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Hazel::Application* Hazel::CreateApplication(Hazel::ApplicationCommandLineArgs args, const std::string& configDir)
{
	ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.WorkingDirectory = "../Hazelnut/";
	spec.SettingsDirectory = configDir;
	spec.CommandLineArgs = args;
	if (args.Count > 3)
	{
		std::string argv3 = args[3];
		if (argv3 == "--apphelp")
		{
			printf(R"apphelpmsg(--- Application help message: ---
	-  Sandbox does not use <Application Specific Arguments>
--- ----------- ---- -------- ---)apphelpmsg");
			return nullptr;
		}
	}

	return new Sandbox(spec);
}
