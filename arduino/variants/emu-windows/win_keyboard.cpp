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

/* TODO */

#include <interface.h>
#include <variant.h>

#include <commctrl.h>

extern HWND hWndMain;
void emu_print(LPCTSTR newText);

void keyDown(WPARAM wParam)
{
    //WM_KEYDOWN:
    switch (wParam)
    {
    case VK_LEFT:
        leds[6].state = 1;
        break;
    case VK_RIGHT:
        leds[7].state = 1;
        break;
    case VK_UP:
        leds[8].state = 1;
        break;
    case VK_DOWN:
        leds[9].state = 1;
        break;
    case VK_F1:
        leds[10].state = 1;
        //emu_print("+ ");
        break;
    default:
        break;
    }
}

void keyUp(WPARAM wParam)
{
    //WM_KEYUP:
    switch (wParam)
    {
    case VK_LEFT:
        leds[6].state = 0;
        break;
    case VK_RIGHT:
        leds[7].state = 0;
        break;
    case VK_UP:
        leds[8].state = 0;
        break;
    case VK_DOWN:
        leds[9].state = 1;
        break;
    case VK_F1:
        leds[10].state = 0;
        //emu_print("- ");
        break;
    default:
        break;
    }
}

#endif /* WIN_EMU */