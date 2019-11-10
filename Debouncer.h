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

#ifndef Debouncer_H
#define Debouncer_H

#include <stdint.h>
#include <stdlib.h>

/**
 * This class is meant to be used to debounce buttons
 */
class Debouncer
{
public:
    Debouncer(void);
    ~Debouncer(void);

    /**
     * @brief Set the parameters of the debouncer
     *
     * Sets the number of consecutive samples that will change between
     * pressed and released states.
     *
     * By default these are set to 5.
     */
    void Set(uint32_t samplesPressed, uint32_t samplesReleased);

    /**
     * @brief Bouncer update function
     *
     * This function should be called on a regular interval.
     * Suggested interval is between 5 ms and 10 ms.
     *
     * In the default configuration the state will be changed after 5 identical updates.
     *
     * Using 5 ms as a call interval and 5 as the number of identical updates required to
     * change from a state to another will lead to a latency of 25 ms to 30 ms since
     * the input has been stabilized.
     *
     * A latency betwwen 20 ms to 50 ms should be
     *
     * @param  buttonPress  true if the button is pressed, false otherway.
     */
    void Update(bool buttonPress);

    /**
     * @brief Returns true if the button was released and now is pressed
     */
    bool IsPressed(void);

    /**
     * @brief Returns true if the button was pressed and now is released
     */
    bool IsReleased(void);

    /**
     * @brief Returns true if the button is currently pressed
     */
    bool IsDown(void);

    /**
     * @brief Returns true if the button is currently released
     */
    bool IsUp(void);

    /**
     * For a pressed button, returns the update steps since was pressed.
     */
    uint32_t GetCurrentPressLength(void);

    /**
     * For a released button, returns the update steps that it was pressed.
     */
    uint32_t GetLastPressLength(void);

    /**
     * Sets the time betwwen updates, in milliseconds
     */
    void SetUpdateTime(uint32_t updateTime);

    /**
     * Set key repeat parameters
     *
     * @param keyDelay      the delay, in milliseconds, before first repeat;
     * @param keyRepeatRate the rate, in milliseconds, for repeating keys. If keyRepeatRate is 0
     *                      key repeat is disabled.
     */
    void SetKeyRepeat(uint32_t keyDelay, uint32_t keyRepeatRate);

    /**
     * For a pressed button, returns the number of presses considering repeat parameters
     */
    uint32_t GetCurrentPressCount(void);

protected:
    bool pressed, oldPressed;
    uint32_t counterPressed;
    uint32_t counterReleased;
    uint32_t lastPressedCount;
    uint32_t thrPressed;
    uint32_t thrReleased;

    uint32_t updateTime;
    uint32_t keyDelay;
    uint32_t keyRepeatRate;
};

#endif
