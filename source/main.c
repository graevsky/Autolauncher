#include <windows.h>
#include <stdio.h>

#define COM_PORT "COM3"                   // Com port to disable
#define PROGRAM_PATH "E:\\deej\\deej.exe" // Path to program

void ShowNotification(const char *message)
{
    MessageBox(NULL, message, "COM Port Manager", MB_OK | MB_ICONINFORMATION);
}

int DisableCOMPort(const char *comPort)
{
    HKEY hKey;
    char registryPath[256];
    snprintf(registryPath, sizeof(registryPath), "SYSTEM\\CurrentControlSet\\Services\\Serial\\Parameters");

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, registryPath, 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
    {
        ShowNotification("Registry cannot be opened");
        return -1;
    }

    if (RegSetValueExA(hKey, comPort, 0, REG_SZ, (const BYTE *)"DISABLED", sizeof("DISABLED")) != ERROR_SUCCESS)
    {
        ShowNotification("Com port cannot be disabled");
        RegCloseKey(hKey);
        return -1;
    }

    RegCloseKey(hKey);
    return 0;
}

int EnableCOMPort(const char *comPort)
{
    HKEY hKey;
    char registryPath[256];
    snprintf(registryPath, sizeof(registryPath), "SYSTEM\\CurrentControlSet\\Services\\Serial\\Parameters");

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, registryPath, 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
    {
        ShowNotification("Registry cannot be opened");
        return -1;
    }

    if (RegDeleteValueA(hKey, comPort) != ERROR_SUCCESS)
    {
        ShowNotification("Com port cannot be enabled");
        RegCloseKey(hKey);
        return -1;
    }

    RegCloseKey(hKey);
    return 0;
}

void RunProgram(const char *programPath)
{
    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};

    si.cb = sizeof(si);

    if (CreateProcessA(NULL, (LPSTR)programPath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else
    {
        ShowNotification("Program cannot be run");
    }
}

int main()
{
    FreeConsole();
    if (DisableCOMPort(COM_PORT) != 0)
    {
        return -1;
    }
    ShowNotification("Com port disabled");

    Sleep(5 * 60 * 1000);

    if (EnableCOMPort(COM_PORT) != 0)
    {
        return -1;
    }
    ShowNotification("Com port enabled");

    RunProgram(PROGRAM_PATH);

    return 0;
}
