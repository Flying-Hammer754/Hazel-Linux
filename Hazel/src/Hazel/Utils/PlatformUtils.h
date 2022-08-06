#pragma once

#include <string>
#include <nfd.hpp>

namespace Hazel {

	class FileDialogs
	{
	public:
		// These return empty strings if cancelled
		static std::string OpenFile(nfdfilteritem_t* filter = nullptr, uint32_t count = 0, nfdchar_t* defaultPath = nullptr);
		static std::string SaveFile(nfdfilteritem_t* filter = nullptr, uint32_t count = 0, nfdchar_t* defaultPath = nullptr, nfdchar_t* defaultName = nullptr);
		static void Init();
		static void Deinit();
	};

	class Time
	{
	public:
		static float GetTime();
	};

}
