#pragma once

#include <string>
#include <nfd.hpp>

namespace Hazel {

	class FileDialogs
	{
		FileDialogs() = delete;
		FileDialogs(FileDialogs&&) = delete;
		FileDialogs(const FileDialogs&) = delete;
		FileDialogs& operator=(FileDialogs&&) = delete;
		FileDialogs& operator=(const FileDialogs&) = delete;
		~FileDialogs() = delete;
	public:
		struct FilterItem
		{
			const char* VisibleName;
			const char* FileExtension;
		};
		// These return empty strings if cancelled
		static std::string OpenFile(FilterItem filter = FilterItem(), uint32_t count = 0, const char* defaultPath = nullptr);
		static std::string SaveFile(FilterItem filter = FilterItem(), uint32_t count = 0, const char* defaultPath = nullptr, const char* defaultName = nullptr);
		static std::string PickFolder(const char* defaultPath = nullptr);
		static void Init();
		static void Deinit();
	};

	class Time
	{
	public:
		static float GetTime();
	};

}
