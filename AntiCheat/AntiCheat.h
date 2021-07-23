#pragma once
#include <string>
#include <regex>
#include <vector>
#include <windows.h>
#include <codecvt>

/* Enum Process Checks */
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);
/* Vector of regex patterns to match window titles. */ 

bool isCheating = false;

/* Enumerate Opened Windows */
namespace WindowSearch {
	/* Callback function for EnumWindows(). Gathers all window names and stores them in vec windowTitles*/
	BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);
	/* Gathers all windows titles opened and applies regex pattern to each one
	returns true if the regex pattern matches a window title */
	bool isPatternFound(std::regex pattern);
	/* Returns true if the regex pattern matches the window title
	This function is called in isPatternsFound() */
	bool regexWindowSearch(std::regex pattern);
	/* Takes a vector of regex's as a parameter and returns true if any of them are found */
	bool isPatternsFound(std::vector<std::regex> patterns);
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
/* Miscellaneous functions used by the AntiCheat*/
namespace Utilities {
	/* Converts a wstring to a standard string */
	std::string toString(const std::wstring& wstr);
}

/* AntiCheat */
namespace AntiCheat {
	/* Takes a vector of regexs as an argument and Runs Debugger::Check() 
	and isPatternsFound(). Returns true if either functions returns true */
	bool Check(std::vector<std::regex> patterns);
}