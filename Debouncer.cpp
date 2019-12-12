/**
This file is part of Debouncer class (https://github.com/CalinRadoni/Debouncer)
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

#ifdef ESP_PLATFORM
    #include "sdkconfig.h"

    const uint32_t default_thrPressed    = CONFIG_DEBOUNCER_thrPressed;    // ticks
    const uint32_t default_thrReleased   = CONFIG_DEBOUNCER_thrReleased;   // ticks
    const uint32_t default_updateTime    = CONFIG_DEBOUNCER_updateTime;    // ms
    const uint32_t default_minKeyPress   = CONFIG_DEBOUNCER_minKeyPress;   // ms
    const uint32_t default_keyRepeatRate = CONFIG_DEBOUNCER_keyRepeatRate; // ms
    const uint32_t default_keyDelay      = CONFIG_DEBOUNCER_keyDelay;      // ms
#else
    const uint32_t default_thrPressed    = 5;   // ticks
    const uint32_t default_thrReleased   = 5;   // ticks
    const uint32_t default_updateTime    = 5;   // ms
    const uint32_t default_minKeyPress   = 50;  // ms
    const uint32_t default_keyRepeatRate = 50;  // ms
    const uint32_t default_keyDelay      = 500; // ms
#endif

Debouncer::Debouncer(void)
{
    pressed    = false;     // assume not pressed initial state
    oldPressed = false;
    counterPressed   = 0;
    counterReleased  = 0;
    lastPressedCount = 0;
    thrPressed  = default_thrPressed;
    thrReleased = default_thrReleased;

    updateTime    = default_updateTime;

    minKeyPress   = default_minKeyPress;
    keyDelay      = default_keyDelay;
    keyRepeatRate = default_keyRepeatRate;
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

void Debouncer::SetUpdateTime(uint32_t updateTimeIn)
{
    updateTime = updateTimeIn;
}

void Debouncer::SetKeyRepeat(uint32_t keyDelayIn, uint32_t keyRepeatRateIn)
{
    keyDelay = keyDelayIn;
    keyRepeatRate = keyRepeatRateIn;
}

uint32_t Debouncer::GetCurrentPressCount(void)
{
    uint32_t res;
    res = updateTime * counterPressed;

    if (res < minKeyPress) {
        return 0;
    }

    if (keyRepeatRate == 0) {
        return 1;
    }

    if (res <= keyDelay) {
        return 1;
    }

    res -= keyDelay;
    return 1 + res / keyRepeatRate;
}
