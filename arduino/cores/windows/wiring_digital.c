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

#include <Arduino.h>
#include <variant.h>

#ifndef WIN_EMU

void led_mode(int pin, int mode)
{
  printf("[PIN] %d MODE %d\n", (int)pin, (int)mode);
}

void led_set(int pin, int val)
{
  printf("[PIN] %d WRITE %d\n", (int)pin, (int)val);
}

int led_get(int pin)
{
  printf("[PIN] %d READ\n", (int)pin);
  return -1;
}

#endif /* WIN_EMU */

void pinMode(uint8_t pin, uint8_t mode)
{
  led_mode(pin, mode);
}

void digitalWrite(uint8_t pin, uint8_t val)
{
  led_set(pin, val);
}

int digitalRead(uint8_t pin)
{
  return led_get(pin);
}

void eintMode(uint8_t pin)
{
  printf("[EINT] %d MODE\n", (int)pin);
}