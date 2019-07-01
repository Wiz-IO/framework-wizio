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

#include <interface.h>
#include <variant.h>

#include <commctrl.h>

extern HWND hWndMain;

LRESULT CALLBACK LedProc(HWND H, UINT M, WPARAM wParam, LPARAM lParam)
{
    extern void emu_print(LPCTSTR newText);
    int n = get_led_by_handle(H);
    if (-1 == n)
        return 0;
    char caption[16];
    HDC hDC;
    RECT rect;
    HPEN pen;
    HBRUSH brush;
    PAINTSTRUCT ps = {0};
    switch (M)
    {
    case WM_PAINT:
        return 0;

    case WM_ERASEBKGND:
        //emu_print("WM_ERASEBKGND\r\n");
        hDC = BeginPaint(H, &ps);
        brush = CreateSolidBrush(leds[n].color);
        SelectObject((HDC)wParam, brush);
        GetClientRect(H, &rect);
        Rectangle((HDC)wParam, rect.left, rect.top, rect.right, rect.bottom);
        //FillRect(hDC, &ps.rcPaint, brush);

        SetBkMode(hDC, TRANSPARENT);
        int n = get_led_by_handle(H);
        snprintf(caption, sizeof(caption), "%u", n);
        DrawText(hDC, caption, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        DeleteObject(brush);
        EndPaint(H, &ps);
        return 0;

    } //switch
    return 0;
}

int createLed(int n)
{
    char txt[16];
    sprintf(txt, "LED%d", n);
    leds[n].h = CreateWindow("static", txt,
                             WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                             10 + n * 36, // x
                             10,          // y
                             34,          // width
                             34,          // height
                             hWndMain,
                             NULL,
                             (HINSTANCE)GetWindowLong(hWndMain, GWL_HINSTANCE),
                             NULL);
    if (!leds[n].h)
        return (0);
    leds[n].proc = (WNDPROC)SetWindowLong(leds[n].h, GWL_WNDPROC, (DWORD)LedProc);
    leds[n].color = RGB(0, 255, 255);
    leds[n].state = 0;
}

void create_leds()
{
    for (int i = 0; i < MAX_LEDS; i++)
        createLed(i);
}

#endif /* WIN_EMU */
