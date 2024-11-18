#include <windows.h>
#include <stdio.h>

#define DEVCON_PATH "C:\\Path\\To\\devcon.exe"
#define DEVICE_ID "FTDIBUS\\VID_0403+PID_6001+FTB6SPL3A\\0000"
#define PROGRAM_PATH "E:\\deej\\deej.exe"

void ShowNotification(const char* message) {
    MessageBox(NULL, message, "Device Manager", MB_OK | MB_ICONINFORMATION);
}

void RunCommand(const char* command) {
    if (system(command) != 0) {
        ShowNotification("Failed to execute command");
    }
}

void RunProgram(const char* programPath) {
    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};

    si.cb = sizeof(si);

    if (CreateProcessA(NULL, (LPSTR)programPath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        ShowNotification("Program cannot be run");
    }
}

int main() {
    FreeConsole(); 

    char disableCommand[512];
    char enableCommand[512];

    snprintf(disableCommand, sizeof(disableCommand), "\"%s\" disable \"%s\"", DEVCON_PATH, DEVICE_ID);
    snprintf(enableCommand, sizeof(enableCommand), "\"%s\" enable \"%s\"", DEVCON_PATH, DEVICE_ID);

    RunCommand(disableCommand);
    ShowNotification("Device disabled");

    Sleep(5 * 60 * 1000);

    RunCommand(enableCommand);
    ShowNotification("Device enabled");

    // Запуск программы
    RunProgram(PROGRAM_PATH);

    return 0;
}
