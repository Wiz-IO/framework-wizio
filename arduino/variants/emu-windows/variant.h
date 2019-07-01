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

#ifndef __VARIANT_H__
#define __VARIANT_H__

#include <interface.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define LED 0                 
#define LED_BUILTIN 0         


#ifdef WIN_EMU

extern HWND hWndMain;

#define MAX_LEDS 16
typedef struct
{
    HWND h;
    WNDPROC proc;
    COLORREF color;
    int mode;
    int state;
} LED_T;
extern LED_T leds[MAX_LEDS];

int get_led_by_handle(HWND h);
int led_get(uint8_t pin);
void led_set(int pin, int val);
void led_mode(int pin, int mode);

#endif /* WIN_EMU */

#ifdef __cplusplus
}

#include <HardwareSerial.h>
extern HardwareSerial Serial;
extern HardwareSerial Serial1;
extern HardwareSerial Serial2;

#endif //__cplusplus

#endif /* __VARIANT_H__ */
