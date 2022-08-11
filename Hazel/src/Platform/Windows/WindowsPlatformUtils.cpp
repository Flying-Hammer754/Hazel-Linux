#include "hzpch.h"
#include "Hazel/Utils/PlatformUtils.h"
#include "Hazel/Core/Application.h"
//#include <commdlg.h>
#include <GLFW/glfw3.h>
//#define GLFW_EXPOSE_NATIVE_WIN32
//#include <GLFW/glfw3native.h>

namespace Hazel {

	float Time::GetTime()
	{
		return glfwGetTime();
	}

	void FileDialogs::Init()
	{
		HZ_CORE_ASSERT(NFD::Init(), "nfd initialization failed")
	}

	void FileDialogs::Deinit()
	{
		NFD::Quit();
	}

	std::string FileDialogs::OpenFile(nfdfilteritem_t* filter, uint32_t count, nfdchar_t* defaultPath)
	{
		nfdchar_t* outPath = "";
		HZ_CORE_ASSERT(NFD::OpenDialog(outPath, filter, count, defaultPath) != NFD_ERROR, "nfd file open failed!")
		std::string result = outPath;
		return result;

		/*OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		CHAR currentDir[256] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		if (GetCurrentDirectoryA(256, currentDir))
			ofn.lpstrInitialDir = currentDir;
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;

		return std::string();*/

	}

	std::string FileDialogs::SaveFile(nfdfilteritem_t* filter, uint32_t count, nfdchar_t* defaultPath, nfdchar_t* defaultName)
	{
		nfdchar_t* outPath = "";
		HZ_CORE_ASSERT(NFD::SaveDialog(outPath, filter, count, defaultPath, defaultName) != NFD_ERROR, "nfd file save failed!")
		std::string result = outPath;
		return result;

		/*OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		CHAR currentDir[256] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		if (GetCurrentDirectoryA(256, currentDir))
			ofn.lpstrInitialDir = currentDir;
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

		// Sets the default extension by extracting it from the filter
		ofn.lpstrDefExt = strchr(filter, '\0') + 1;

		if (GetSaveFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;
		
		return std::string();*/
	}

}

/*#include <GLFW/glfw3.h>
#include <nfd.hpp>
namespace Hazel
{
	std::string FileDialogs::OpenFile(const char* filter)
	{

		/*const char zenityP[] = "/usr/bin/zenity";
		char Call[2048];

		sprintf(Call,"%s  --file-selection --modal --title=\"%s\" ", zenityP, "Select file");

		std::string filepath;
		filepath.reserve(512);
		FILE *f = popen(Call,"r");
		fgets(&filepath[0], filepath.capacity(), f); 

		int ret=pclose(f);
		if(ret<0) {perror("file_name_dialog()"); HZ_CORE_ASSERT(false, "ret is less than 0")}
		HZ_CORE_ASSERT(!ret, "Failed to close file")

		return filepath;*/
	/*}

	std::string FileDialogs::SaveFile(const char* filter)
	{

	}

	float Time::GetTime()
	{
		return glfwGetTime();
	}
}*/