#pragma once
#include <string>
#include <regex>
#include <vector>
#include <windows.h>
#include <thread>
#include <codecvt>

/* Enum Process Checks */
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);

/* Sample Vector of regex patterns to match window titles. */
std::vector<std::regex> regexPatterns = {
	/* Pattern for Cheat Engine https://regex101.com/r/olJ8Ns/1 */
	std::regex(R"(\b^Cheat Engine \b[0-9]([0-9])?.([0-9]?).([0-9])?\b)"),
	/* Pattern for Extreme Injector https://regex101.com/r/bCabrN/1 */
	std::regex(R"(\b^Extreme Injector v[0-9]([0-9])?.[0-9]([0-9])?.[0-9]([0-9])?\b by master131\b)"),
	/* Pattern for HxD https://regex101.com/r/1dlzan/1 */
	std::regex(R"(\b^HxD\b)"),
	/* Pattern for  dllinjector.com DLL injector https://regex101.com/r/HrIu9S/1 */
	std::regex(R"(\b^DLL Injector v[0-9].[0-9] www.dllinjector.com\b)"),
	/* Pattern for Process Explorer https://regex101.com/r/3x1aqa/1 NOT WORKING! ? */
	//std::regex(R"(\b^Process Explorer - Sysinternals:www.sysinternals.com \[[A-Za-z0-9_-].*.]\b)"),
};

/* Set true if user is cheating */
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
	/*  Runs Debugger::Check() and isPatternsFound(). Called in AntiCheat::Run() */
	bool Check(std::vector<std::regex>);
};