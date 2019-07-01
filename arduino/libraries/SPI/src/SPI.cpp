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

#include "SPI.h"

SPIClass::SPIClass(uint8_t spi_bus) {}

void SPIClass::begin(int8_t sck, int8_t miso, int8_t mosi, int8_t ss) {}

void SPIClass::end() {}

void SPIClass::setHwCs(bool use) {}

void SPIClass::setFrequency(uint32_t freq) {}

void SPIClass::setClockDivider(uint32_t clockDiv) {}

uint32_t SPIClass::getClockDivider() { return 0; }

void SPIClass::setDataMode(uint8_t dataMode) {}

void SPIClass::setBitOrder(uint8_t bitOrder) {}

void SPIClass::beginTransaction(SPISettings settings) {}

void SPIClass::endTransaction() {}

void SPIClass::write(uint8_t data) {}

uint8_t SPIClass::transfer(uint8_t data) { return 0; }

void SPIClass::write16(uint16_t data) {}

uint16_t SPIClass::transfer16(uint16_t data) { return 0; }

void SPIClass::write32(uint32_t data) {}

uint32_t SPIClass::transfer32(uint32_t data) { return 0; }

void SPIClass::transferBits(uint32_t data, uint32_t *out, uint8_t bits) {}

/**
 * @param data uint8_t *
 * @param size uint32_t
 */
void SPIClass::writeBytes(uint8_t *data, uint32_t size) {}

void SPIClass::transfer(uint8_t *data, uint32_t size)
{
    transferBytes(data, data, size);
}

/**
 * @param data void *
 * @param size uint32_t
 */
void SPIClass::writePixels(const void *data, uint32_t size) {}

/**
 * @param data uint8_t * data buffer. can be NULL for Read Only operation
 * @param out  uint8_t * output buffer. can be NULL for Write Only operation
 * @param size uint32_t
 */
void SPIClass::transferBytes(uint8_t *data, uint8_t *out, uint32_t size) {}

/**
 * @param data uint8_t *
 * @param size uint8_t  max for size is 64Byte
 * @param repeat uint32_t
 */
void SPIClass::writePattern(uint8_t *data, uint8_t size, uint32_t repeat) {}

SPIClass SPI(0);