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
#include <constants.h>

HWND hWndMain = 0;
LED_T leds[MAX_LEDS] = {0};

int get_led_by_handle(HWND h)
{
    for (int i = 0; i < MAX_LEDS; i++)
        if (leds[i].h == h)
            return i;
    return -1;
}

int led_get(uint8_t pin)
{
    if (pin >= MAX_LEDS)
        return -1;
    return leds[pin].state;
}

void led_set(int pin, int val)
{
    if (pin >= MAX_LEDS)
        return;
    if (leds[pin].mode <= INPUT_PULLDOWN)
        return; // is input
    leds[pin].color = RGB(255, 0, 0);
    if (val)
        leds[pin].color = RGB(0, 255, 0);
    leds[pin].state = val;
    InvalidateRect(leds[pin].h, NULL, TRUE);
}

void led_mode(int pin, int mode)
{
    if (pin >= MAX_LEDS)
        return;
    leds[pin].mode = mode;
    if (leds[pin].mode <= INPUT_PULLDOWN)
        leds[pin].color = RGB(0, 255, 255);
    else
        leds[pin].color = RGB(255, 0, 0);
    InvalidateRect(leds[pin].h, NULL, TRUE);
}

#endif /* WIN_EMU */