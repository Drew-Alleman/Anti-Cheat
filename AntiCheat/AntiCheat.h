#pragma once
#include <windows.h>
#include <string>
#include <regex>

/* Converts a wstring into a std::string */
std::string toString(const std::wstring& wstr);

/* Callback function for EnumWindows() */
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);

/*
returns true if the regex pattern matches the window title
This function is called in isWindowPatternFound()
 */
bool regexWindowSearch(std::regex pattern);

/*
Gathers all windows titles opened and applies regex pattern to each one  
returns true if the regex pattern matches a window title
 */
bool isWindowPatternFound(std::regex pattern);

// Debugging Checks
namespace Debugger {
	/* Calls isDebuggerPresent(); */
	bool isDebuggerPresent();
	/* Can detect ring-3 debugger  */
	bool isRemoteDebuggerPresent();
	/* Calls isDebuggerPresent(), and isRemoteDebuggerPresent() and returns true if debugger is found */
	bool Check();
}