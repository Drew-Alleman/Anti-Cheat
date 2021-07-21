#pragma once
#include <windows.h>
#include <string>
#include <regex>

/* Enum Process Checks */
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);
/* Vector of regex patterns to match window titles. */ 
std::vector<std::regex>  regexPatterns = { std::regex(R"(\bCheat Engine \b[0-9]([0-9])?.[0-9]([0-9])?)"), std::regex(R"(\b^Extreme Injector v[0-9]([0-9])?.[0-9]([0-9])?.[0-9]([0-9])?\b by master131\b)") };

/* Enum Opened Windows */
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

/* Debugging Checks */
namespace Debugger {
	/* Calls WINAPI isDebuggerPresent(); */
	bool isDebuggerPresent();
	/* Calls CheckRemoteDebuggerPresent() from WINAPI, can detect ring-3 debuggers. */
	bool isRemoteDebuggerPresent();
	/* Uses ASM INT 0x3 to check for a debugger */
	bool isDebuggerPresentAsm();
	/* Calls isDebuggerPresent(), isRemoteDebuggerPresent() and isDebuggerPresentAsm and returns true a if debugger is found */
	bool Check();
};

namespace Utilities {
	/* Converts a wstring to a standard string */
	std::string toString(const std::wstring& wstr);
}