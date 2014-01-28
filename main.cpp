/*
 * main.c - Example
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

#include <cstdio>
#include <unistd.h>

#include "led_strip.h"


#define STRIP_LENGTH		(72) 		// pixels
#define SPI_DEVICE			"/dev/spidev0.0"

int main()
{
	bitmap mBitmap(STRIP_LENGTH, 1);	// one dimension led_strip
	led_strip mLedStrip(SPI_DEVICE, mBitmap.width * mBitmap.height);	// LED Strip initialized on spi.0

	mBitmap.fill(ColorRed);				// full red color	
	mLedStrip.paint(&mBitmap, true);
	sleep(1);

	mBitmap.fill(ColorGreen);			// full green color
	mLedStrip.paint(&mBitmap, true);
	sleep(1);

	mBitmap.fill(ColorBlue);			// full blue color
	mLedStrip.paint(&mBitmap, true);
	sleep(1);

	mBitmap.fill(ColorWhite);			// full white color
	mLedStrip.paint(&mBitmap, true);
	sleep(1);

	hsv_color color;					// HSV pixel
	color.S = 255;						// maximum saturation
	color.V = 255;						// maximum value
	for(int i = 0; i < STRIP_LENGTH; i++)
	{									// rainbow colors
		color.H = i * 360 / STRIP_LENGTH;
		mBitmap.set_hsv_pixel(i, 0, color);
	}
	mLedStrip.paint(&mBitmap, true);

	return 0;
}
