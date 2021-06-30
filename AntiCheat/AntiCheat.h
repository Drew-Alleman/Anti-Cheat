#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include <regex>

std::vector<std::wstring> windowTitles;

std::string to_string(const std::wstring& wstr);
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);
bool isWindowRegexFound(std::regex pattern);
