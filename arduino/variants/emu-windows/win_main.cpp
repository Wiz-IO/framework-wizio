/*
    Created on: 01.01.2019
    Author: Georgi Angelov
        http://www.wizio.eu/
        https://github.com/Wiz-IO    

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA   
 */

#ifdef WIN_EMU

extern void setup();
extern void loop();

#define _WIN32_IE 0x0500
#define _WIN32_WINNT 0x0501

#include <interface.h>
#include <variant.h>

#include <commctrl.h>

const char g_szClassName[] = "myArduinoWindowClass";
HINSTANCE hInstance;
HWND hEdit = 0;
HFONT hFont;

void emu_print(LPCTSTR newText)
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

static int startedArduino;

static DWORD WINAPI arduinoThread(void *threadParams)
{
    emu_print("Arduino Visual Emulator 2019 WizIO\r\n");
    setup();
    startedArduino = 1;
    while (startedArduino)
    {
        loop();
        Sleep(1); // thread yield
    }
    return 0;
}

static void run_arduino(void)
{
    DWORD threadDescriptor;
    CreateThread(
        NULL,               /* default security attributes.   */
        0,                  /* use default stack size.        */
        arduinoThread,      /* thread function name.          */
        0,                  /* argument to thread function.   */
        0,                  /* use default creation flags.    */
        &threadDescriptor); /* returns the thread identifier. */
}

LRESULT CALLBACK WndProc(HWND h, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    switch (msg)
    {

    case WM_USER: // print char
        emu_print((LPCTSTR)&lParam);
        break;

    case WM_PAINT:
        hdc = BeginPaint(hWndMain, &ps);
        EndPaint(hWndMain, &ps);
        break;

    case WM_KEYDOWN:
        extern void keyDown(WPARAM wParam);
        keyDown(wParam);
        break;
    case WM_KEYUP:
        extern void keyUp(WPARAM wParam);
        keyUp(wParam);
        break;        

    case WM_CLOSE:
        startedArduino = 0;
        DestroyWindow(h);
        break;
    case WM_DESTROY:
        startedArduino = 0;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(h, msg, wParam, lParam);
    }
    return 0;
}

int main()
{
    MSG Msg;
    WNDCLASSEX wc;
    //hWndMain = FindWindowA("TApplication", "EMU"); // search for external emulator

    // Registering the Window Class
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
    hFont = CreateFont(-16, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "Courier New");

    // Creating the Window
    hWndMain = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName,
        "Arduino Simulator 2019 WizIO",
        WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
        NULL, NULL, hInstance, NULL);
    if (hWndMain == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    SetWindowPos(hWndMain, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE or SWP_NOMOVE or SWP_NOSIZE);

    // Creating the Edit
    hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
                           WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL, // | ES_AUTOHSCROLL,
                           0, 200, 620, 240,
                           hWndMain, (HMENU)0, GetModuleHandle(NULL), NULL);
    SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(true, 0));

    extern void create_leds();
    create_leds();

    extern void createDisplay();
    createDisplay();

    ShowWindow(hWndMain, 1);
    UpdateWindow(hWndMain);

    run_arduino();

    // The Message Loop
    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    startedArduino = 0;
    return Msg.wParam;
}

#endif // WIN_EMU