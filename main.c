// Made BY Hani Marji
// Date: 25/03/2025
// Description: This script scans the connected monitors to your device and displays their information Using Python.

#include <windows.h>
#include <stdio.h>
#include <string.h>

int monitorCount = 0;

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
    MONITORINFOEX mi;
    mi.cbSize = sizeof(MONITORINFOEX);
    
    if (GetMonitorInfo(hMonitor, &mi)) {
        monitorCount++;

        // Get monitor device name
        DISPLAY_DEVICE dd;
        dd.cb = sizeof(dd);
        EnumDisplayDevices(mi.szDevice, 0, &dd, 0);

        // Get display settings for refresh rate (Hz)
        DEVMODE devMode;
        devMode.dmSize = sizeof(DEVMODE);
        EnumDisplaySettings(mi.szDevice, ENUM_CURRENT_SETTINGS, &devMode);

        int width = mi.rcMonitor.right - mi.rcMonitor.left;
        int height = mi.rcMonitor.bottom - mi.rcMonitor.top;

        const char* orientation = (height > width) ? "Portrait" : "Landscape";

        char buffer[512];
        sprintf(buffer,
                "Monitor %d: %s\n"
                "  Position: (%ld, %ld)\n"
                "  Resolution: %dx%d\n"
                "  Orientation: %s\n"
                "  Refresh Rate: %d Hz\n\n",  // Displaying the refresh rate
                monitorCount,
                dd.DeviceString,  // Monitor name
                mi.rcMonitor.left,
                mi.rcMonitor.top,
                width,
                height,
                orientation,
                devMode.dmDisplayFrequency);  // Refresh rate

        strcat((char*)dwData, buffer);
    }
    return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    char info[2048] = "Connected Monitors Info:\n\n";
    EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)info);

    MessageBox(NULL, info, "Monitor Info", MB_OK | MB_ICONINFORMATION);
    return 0;
}
