#pragma once
#include <windows.h>
#include <string>
#include <regex>

std::vector<std::regex>  regexPatterns = { std::regex(R"(\bCheat Engine \b[0-9]([0-9])?.[0-9]([0-9])?)"), std::regex(R"(\b^Extreme Injector v[0-9]([0-9])?.[0-9]([0-9])?.[0-9]([0-9])?\b by master131\b)") };
const int TITLE_SIZE = 1024;
bool isCheating = false;
std::vector<std::wstring> windowTitles;

/* Converts a wstring into a std::string */
std::string toString(const std::wstring& wstr);

// Regex pattern search for window titles
namespace WindowSearch {
	/* Callback function for EnumWindows(). Gathers all window names and stores them in vec windowTitles*/
	BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);
	/* Gathers all windows titles opened and applies regex pattern to each one
	returns true if the regex pattern matches a window title */
	bool isPatternFound(std::regex pattern);
	/* returns true if the regex pattern matches the window title
	This function is called in isWindowPatternFound() */
	bool regexWindowSearch(std::regex pattern);

};


// Debugging Checks
namespace Debugger {
	/* Calls isDebuggerPresent(); */
	bool isDebuggerPresent();
	/* Can detect ring-3 debugger  */
	bool isRemoteDebuggerPresent();
	/* Calls isDebuggerPresent(), and isRemoteDebuggerPresent() and returns true if debugger is found */
	bool Check();
};