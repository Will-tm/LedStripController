/*
 * led_strip.c - LEDs Strip class dedicated to WS2801
 *
 * Copyright (C) 2013 William Markezana <william.markezana@me.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "led_strip.h"

led_strip::led_strip(const char *pDevice, size_t pLength)
{
	mLength = pLength;
	mBuffer.resize(mLength * 3);
	mSpi = new spi(pDevice);

	set_gamma(0.25);
}

led_strip::~led_strip()
{
	delete mSpi;
}

void led_strip::set_gamma(float pGamma)
{
	float gamma;
	for (int i = 0; i < 256; i++)
	{
		gamma = pow(256.0f,pow((float)i/255.0f,pGamma))-1.0f;
		if (gamma > 255.0f) gamma = 255.0f;
		if (gamma <  0.0f) gamma = 0.0f;
		mGammaTable[i] = (uint8_t)gamma;
	}
}

void led_strip::resize(size_t pSize)
{
	mLength = pSize;
	mBuffer.resize(pSize * 3);
}

void led_strip::paint(bitmap *pBitmap, bool pWaitForCompletion)
{
	int bufferPtr = 0;
	rgb_color CurrentColor;

	for (size_t x = 0; x < mLength; x++)
	{
		CurrentColor = pBitmap->get_pixel(x,0);

		mBuffer[bufferPtr++] = mGammaTable[CurrentColor.B];
		mBuffer[bufferPtr++] = mGammaTable[CurrentColor.G];
		mBuffer[bufferPtr++] = mGammaTable[CurrentColor.R];
	}

	mSpi->write_buffer(&mBuffer.front(), mBuffer.size());

	if (pWaitForCompletion)
		mSpi->waitForTransfertToComplete();
}
