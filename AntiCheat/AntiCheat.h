#pragma once
#include <windows.h>
#include <string>
#include <regex>

std::vector<std::wstring> windowTitles;

std::string to_string(const std::wstring& wstr);
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);
bool regexWindowSearch(std::regex pattern);
bool isWindowPatternFound(std::regex pattern);