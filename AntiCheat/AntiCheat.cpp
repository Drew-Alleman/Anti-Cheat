#include <iostream>
#include <string>
#include <regex>
#include <windows.h>
#include <codecvt>

const int TITLE_SIZE = 1024;
std::vector<std::wstring> windowTitles;


std::string to_string(const std::wstring& wstr)
{
    /* Converts wstring to string */
    static std::wstring_convert< std::codecvt_utf8<wchar_t>, wchar_t > converter;
    return converter.to_bytes(wstr);
}

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
    /* CALLBACK Function for 'EnumWindows' */
    WCHAR windowTitle[TITLE_SIZE];
    int textLength;
    GetWindowTextW(hWnd, windowTitle, TITLE_SIZE);
    textLength = GetWindowTextLength(hWnd);
    if (textLength != 0) 
        windowTitles.push_back(windowTitle);
    return TRUE;
}

bool isWindowRegexFound(std::regex pattern) {
    /* Applies regex pattern to windows title */
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&windowTitles));
    for (int i = 0; i < windowTitles.size(); ++i) {
        std::string windowTitle = to_string(windowTitles[i]);
        if (std::regex_search(windowTitle, pattern)) 
            return true;
    }
    return false;
}

int main()
{
    std::regex pattern(R"(\bCheat Engine \b[0-9]([0-9])?.[0-9]([0-9])?)");
    if (isWindowRegexFound(pattern)) {
        std::cout << "Cheat Engine was detected!" << std::endl;
    }
}

