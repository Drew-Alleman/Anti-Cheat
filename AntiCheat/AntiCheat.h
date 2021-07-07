#pragma once
#include <windows.h>
#include <string>
#include <regex>

// Utils
std::string toString(const std::wstring& wstr);

//Enum Process Checks
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);
bool regexWindowSearch(std::regex pattern);
bool isWindowPatternFound(std::regex pattern);
bool isWindowPatternFound(std::regex pattern);

// Debugging Checks
bool isDebuggerPresent();
bool isRemoteDebuggerPresent();