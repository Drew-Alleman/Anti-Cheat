#include "AntiCheat.h"

const int TITLE_SIZE = 1024;
std::vector<std::wstring> windowTitles;

bool isRunning = true;

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
    int windowSize = windowTitles.size();
    for (int i = 0; i < windowSize; ++i) {
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

bool WindowSearch::isPatternsFound(std::vector<std::regex> patterns) {
    for (std::regex pattern : patterns) {
        if (WindowSearch::isPatternFound(pattern)) {
            return true;
        }
    }
    return false;
}

bool Debugger::isDebuggerPresent() {
    return IsDebuggerPresent();
}

bool Debugger::isRemoteDebuggerPresent() {
    BOOL isDebugPresent = FALSE;
    HANDLE hProcess = GetCurrentProcess();
    if (hProcess != nullptr)
        CheckRemoteDebuggerPresent(hProcess, &isDebugPresent);
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
    return Debugger::isRemoteDebuggerPresent() ||  Debugger::isDebuggerPresent() || Debugger::isDebuggerPresentAsm();
}

bool AntiCheat::Check(std::vector<std::regex> patterns) {
    return Debugger::Check() || WindowSearch::isPatternsFound(patterns);
}