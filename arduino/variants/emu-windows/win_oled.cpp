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
void PaintWindow(HWND hWnd);

HWND hOled;
WNDPROC oledProc;

#define PYXEL_SIZE 2

LRESULT CALLBACK OledProc(HWND H, UINT M, WPARAM wParam, LPARAM lParam)
{

    RECT rect;
    HPEN pen;
    HBRUSH brush;
    PAINTSTRUCT ps = {0};
    switch (M)
    {
    case WM_PAINT:
        PaintWindow(H);
        return 0;

    case WM_ERASEBKGND:
        return 0;
        //printf("WM_ERASEBKGND %d, %p\n", n, H);
        HDC hDC = BeginPaint(H, &ps);
        brush = CreateSolidBrush(RGB(0, 0, 0));
        SelectObject((HDC)wParam, brush);
        GetClientRect(H, &rect);
        Rectangle((HDC)wParam, rect.left - 2, rect.top - 2, rect.right + 2, rect.bottom + 2);
        //FillRect(hDC, &ps.rcPaint, brush);
        DeleteObject(brush);
        EndPaint(H, &ps);
        return 0;

    } //switch
    return 0;
}

void createDisplay()
{
    hOled = CreateWindow("static", "OLED DISPLAY",
                         WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                         10, 58, 128 * PYXEL_SIZE, 64 * PYXEL_SIZE,
                         hWndMain,
                         NULL,
                         (HINSTANCE)GetWindowLong(hWndMain, GWL_HINSTANCE),
                         NULL);
    oledProc = (WNDPROC)SetWindowLong(hOled, GWL_WNDPROC, (DWORD)OledProc);
}

uint8_t dsp_mem[64 / 8][128];

void PaintWindow(HWND hWnd)
{
    RECT R;
    PAINTSTRUCT ps;
    HDC hDC = BeginPaint(hWnd, &ps);
    HPEN hpenOld = static_cast<HPEN>(SelectObject(hDC, GetStockObject(DC_PEN)));
    HBRUSH hbrushOld = static_cast<HBRUSH>(SelectObject(hDC, GetStockObject(NULL_BRUSH)));
    GetClientRect(hWnd, &R);
    Rectangle(hDC, R.left - 2, R.top - 2, R.right + 2, R.bottom + 2);
    //memset(dsp_mem, 0x1, sizeof(dsp_mem));
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 128; x++)
        {
            int dat = dsp_mem[y][x];
            for (int z = 0; z < 8; z++)
            {
                R.left = x * PYXEL_SIZE;
                R.right = R.left + PYXEL_SIZE;
                R.top = (y * 8 + z) * PYXEL_SIZE;
                R.bottom = R.top + PYXEL_SIZE;
                if (dat & 1)
                    SetDCPenColor(hDC, RGB(255, 255, 255)); // white
                else
                    SetDCPenColor(hDC, RGB(0, 0, 255)); // blue
                Rectangle(hDC, R.left, R.top, R.right, R.bottom);
                dat >>= 1;
            }
        }
    }
#if 0
    // https://stackoverflow.com/questions/16159127/win32-how-to-draw-a-rectangle-around-a-text-string
#endif
    // Clean up after ourselves.
    SelectObject(hDC, hpenOld);
    SelectObject(hDC, hbrushOld);
    EndPaint(hWnd, &ps);
}

#else

#endif /* WIN_EMU */