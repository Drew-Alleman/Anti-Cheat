#include <iostream>
#include <string>
#include <regex>
#include <windows.h>
#include <codecvt>

std::vector<std::regex>  regexPatterns = { std::regex(R"(\bCheat Engine \b[0-9]([0-9])?.[0-9]([0-9])?)"), std::regex(R"(\b^Extreme Injector v[0-9]([0-9])?.[0-9]([0-9])?.[0-9]([0-9])?\b by master131\b)")};
const int TITLE_SIZE = 1024;
std::vector<std::wstring> windowTitles;
bool isCheating = false;

std::string toString(const std::wstring& wstr) {
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

bool regexWindowSearch(std::regex pattern) {
    /* Applies regex pattern to windows title */
    for (int i = 0; i < windowTitles.size(); ++i) {
        std::string windowTitle = toString(windowTitles[i]);
        if (std::regex_search(windowTitle, pattern)) 
            return true;
    }
    return false;
}

bool isDebuggerPresent() {
    return IsDebuggerPresent();
}

bool isRemoteDebuggerPresent() {
    PBOOL isDebugPresent = FALSE;
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
    if (hProcess != nullptr)
        CheckRemoteDebuggerPresent(hProcess, isDebugPresent);
    return isDebugPresent;
}

bool isWindowPatternFound(std::regex pattern) {
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&windowTitles));
    bool isWindowFound = regexWindowSearch(pattern);
    windowTitles.empty();
    return isWindowFound;
}

int main() {
    std::regex pattern(R"(\bCheat Engine \b[0-9]([0-9])?.[0-9]([0-9])?)");
    while (!isCheating) {
        if (isWindowPatternFound(pattern)) {
            printf("Please close any hacking/cheating software!");
            for (std::regex pattern : regexPatterns) {
                if (isWindowPatternFound(pattern)) {
                    printf("Please close any hacking/cheating software!\n");
                    isCheating = true;
                }
            }
            if (isRemoteDebuggerPresent() || isDebuggerPresent()) {
                printf("Please detach the debugger!\n");
                isCheating = true;
            }
        }
    }
}