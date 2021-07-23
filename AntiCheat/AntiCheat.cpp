#include "AntiCheat.h"

const int TITLE_SIZE = 1024;
std::vector<std::wstring> windowTitles;

bool isRunning = true;
std::vector<std::regex>  regexPatterns = { 
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
    PBOOL isDebugPresent = FALSE;
    HANDLE hProcess = GetCurrentProcess();
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
    return Debugger::isRemoteDebuggerPresent() ||  Debugger::isDebuggerPresent() || Debugger::isDebuggerPresentAsm();
}

bool AntiCheat::Check(std::vector<std::regex> patterns) {
    return WindowSearch::isPatternsFound(patterns) || Debugger::Check();
}