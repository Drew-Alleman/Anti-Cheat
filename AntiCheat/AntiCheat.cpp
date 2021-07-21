#include <iostream>
#include <string>
#include <regex>
#include <windows.h>
#include <codecvt>
#include "AntiCheat.h"

const int TITLE_SIZE = 1024;
std::vector<std::wstring> windowTitles;
bool isCheating = false;

std::string Utilities::toString(const std::wstring& wstr) {
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
        std::string windowTitle = Utilities::toString(windowTitles[i]);
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

bool Debugger::isDebuggerPresentAsm()
{
    __try {
        __asm INT 0x03;
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
}

bool Debugger::Check() {
    return Debugger::isRemoteDebuggerPresent() || Debugger::isDebuggerPresent() || Debugger::isDebuggerPresentAsm();
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