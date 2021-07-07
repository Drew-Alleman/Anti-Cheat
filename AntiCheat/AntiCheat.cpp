#include <iostream>
#include <string>
#include <regex>
#include <windows.h>
#include <codecvt>
#include "AntiCheat.h"

std::vector<std::regex>  regexPatterns = { std::regex(R"(\bCheat Engine \b[0-9]([0-9])?.[0-9]([0-9])?)"), std::regex(R"(\b^Extreme Injector v[0-9]([0-9])?.[0-9]([0-9])?.[0-9]([0-9])?\b by master131\b)") };
const int TITLE_SIZE = 1024;
bool isCheating = false;
std::vector<std::wstring> windowTitles;

std::string toString(const std::wstring& wstr) {
    static std::wstring_convert< std::codecvt_utf8<wchar_t>, wchar_t > converter;
    return converter.to_bytes(wstr);
}

BOOL CALLBACK WindowSearch::EnumWindowsProc(HWND hWnd, LPARAM lParam) {
    WCHAR windowTitle[TITLE_SIZE];
    int textLength;
    GetWindowTextW(hWnd, windowTitle, TITLE_SIZE);
    textLength = GetWindowTextLength(hWnd);
    if (textLength != 0) 
        windowTitles.push_back(windowTitle);
    return TRUE;
}

bool WindowSearch::regexWindowSearch(std::regex pattern) {
    for (int i = 0; i < windowTitles.size(); ++i) {
        std::string windowTitle = toString(windowTitles[i]);
        if (std::regex_search(windowTitle, pattern)) 
            return true;
    }
    return false;
}

bool WindowSearch::isPatternFound(std::regex pattern) {
    EnumWindows(WindowSearch::EnumWindowsProc, reinterpret_cast<LPARAM>(&windowTitles));
    bool isWindowFound = WindowSearch::regexWindowSearch(pattern);
    windowTitles.empty();
    return isWindowFound;
}


bool Debugger::isDebuggerPresent() {
    return IsDebuggerPresent();
}

bool Debugger::isRemoteDebuggerPresent() {
    PBOOL isDebugPresent = FALSE;
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
    if (hProcess != nullptr)
        CheckRemoteDebuggerPresent(hProcess, isDebugPresent);
    return isDebugPresent;
}

bool Debugger::Check() {
    return Debugger::isRemoteDebuggerPresent() || Debugger::isDebuggerPresent();
}

int main() {
    while (!isCheating) {
        for (std::regex pattern : regexPatterns) {
            if (WindowSearch::isPatternFound(pattern)) {
                printf("Please close any hacking/cheating software!\n");
                isCheating = true;
            }
            if (Debugger::Check()) {
                printf("Please detach the debugger!\n");
                isCheating = true;
            }
        }
    }
}