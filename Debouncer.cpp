/**
This file is part of Debouncer esp-idf component from
pax-devices (https://github.com/CalinRadoni/pax-devices)
Copyright (C) 2019+ by Calin Radoni

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Debouncer.h"

const uint32_t default_thrPressed = 5;
const uint32_t default_thrReleased = 5;

Debouncer::Debouncer(void)
{
    pressed    = false;     // assume not pressed initial state
    oldPressed = false;
    counterPressed   = 0;
    counterReleased  = 0;
    lastPressedCount = 0;
    thrPressed  = default_thrPressed;
    thrReleased = default_thrReleased;
}

Debouncer::~Debouncer(void)
{
}

void Debouncer::Set(uint32_t samplesPressed, uint32_t samplesReleased)
{
    thrPressed  = samplesPressed;
    thrReleased = samplesReleased;
}

void Debouncer::Update(bool buttonPress)
{
    bool stillPressed = pressed;

    if (pressed) {
        /**
         * In the `pressed` state, waits for thrReleased consecutive states
         * to switch to the `released` state
         */
        if (buttonPress) {
            counterReleased = 0;
            if (counterPressed < UINT32_MAX)
                counterPressed++;
        }
        else {
            counterReleased++;
            if (counterReleased >= thrReleased) {
                stillPressed = false;
                lastPressedCount = counterPressed;
                counterPressed = 0;
            }
        }

    }
    else {
        /**
         * In the `released` state, waits for thrPressed consecutive states
         * to switch to the `pressed` state
         */
        if (buttonPress) {
            counterPressed++;
            if (counterPressed >= thrPressed) {
                stillPressed = true;
                counterReleased = 0;
            }
        }
        else counterPressed = 0;
    }

    if (pressed != stillPressed) {
        // pressed status changed
        oldPressed = pressed;
        pressed = stillPressed;
    }
}

bool Debouncer::IsPressed(void)
{
    return (pressed && !oldPressed);
}

bool Debouncer::IsReleased(void)
{
    return (!pressed && oldPressed);
}

bool Debouncer::IsUp(void)
{
    return !pressed;
}

bool Debouncer::IsDown(void)
{
    return pressed;
}

uint32_t Debouncer::GetCurrentPressLength(void)
{
    return counterPressed;
}

uint32_t Debouncer::GetLastPressLength(void)
{
    return lastPressedCount;
}
