#include <interface.h>

extern void setup();
extern void loop();

int main()
{
    printf("\nArduino Windows Simulator 2019 WizIO\n");
    printDateTime();
    printf("\n");
    setup();
    while (true)
    {
        loop();
        Sleep(1);
    }
}

#if 0

#define _WIN32_IE 0x0500
#define _WIN32_WINNT 0x0501
#include <windows.h>
#include <commctrl.h>
// http://www.winprog.org/tutorial/app_one.html
HINSTANCE hInstance;
HWND hwnd = 0;
HWND hEdit = 0;
HFONT font;
int exitCondition;
const char g_szClassName[] = "myArduinoWindowClass";
HWND hwndButton[16];

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        exitCondition = 0;
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        exitCondition = 0;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

static DWORD WINAPI arduinoThread(void *threadParams)
{
    Sleep(10);
    setup();
    while (exitCondition)
    {
        loop();
        Sleep(10);
    }
    return 0;
}

void run_arduino()
{
    DWORD threadDescriptor;
    exitCondition = 1;
    CreateThread(
        NULL,               /* default security attributes.   */
        0,                  /* use default stack size.        */
        arduinoThread,      /* thread function name.          */
        0,                  /* argument to thread function.   */
        0,                  /* use default creation flags.    */
        &threadDescriptor); /* returns the thread identifier. */
}

void createPins()
{
    for (int i = 0; i < 10; i++)
    {
        char buf[16];
        sprintf(buf, "%d", i);
        hwndButton[i] = CreateWindow(
            "BUTTON",                                              // Predefined class; Unicode assumed
            buf,                                                   // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
            10 + i * 30,                                           // x position
            10,                                                    // y position
            20,                                                    // Button width
            20,                                                    // Button height
            hwnd,                                                  // Parent window
            NULL,                                                  // No menu.
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL); // Pointer not needed.
    }
}

int main()
{
    WNDCLASSEX wc;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    font = CreateFont(-17, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "Courier New");

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Arduino Simulator 2019 WizIO",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
        NULL, NULL, hInstance, NULL);

    hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
                           WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                           0, 40, 640, 400, hwnd, (HMENU)0, GetModuleHandle(NULL), NULL);
    SendMessage(hEdit, WM_SETFONT, (WPARAM)font, MAKELPARAM(true, 0));

    if (hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    createPins();

    ShowWindow(hwnd, 1);
    UpdateWindow(hwnd);

    run_arduino();

    // Step 3: The Message Loop
    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    exitCondition = 0;
    return Msg.wParam;
}

void appendLogText(LPCTSTR newText)
{
    if (0 == hEdit)
        return;
    int left, right;
    int len = GetWindowTextLength(hEdit);
    SendMessage(hEdit, EM_GETSEL, (WPARAM)&left, (LPARAM)&right);
    SendMessage(hEdit, EM_SETSEL, len, len);
    SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)newText);
    SendMessage(hEdit, EM_SETSEL, left, right);
}

#endif