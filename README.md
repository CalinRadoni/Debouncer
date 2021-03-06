# Helper class for button debouncing

[![Build Status](https://travis-ci.com/CalinRadoni/Debouncer.svg?branch=master)](https://travis-ci.com/CalinRadoni/Debouncer)

This class uses a counting algorithm.
I think that it is more "safe" then other algorithms.

In the first implementation I have used a history based algorithm like the one described in [Embed With Elliot: Debounce Your Noisy Buttons, Part II](https://hackaday.com/2015/12/10/embed-with-elliot-debounce-your-noisy-buttons-part-ii/)

## Files

- the implementation is in the `Debouncer.h` and `Debouncer.cpp` fles.
- `CMakeLists.txt` and `Kconfig.projbuild` are only for `esp-idf`
- `build.sh` is used to build and run the `example` executable, manually or by Travis CI

## Dependencies

This should be platform and compiler agnostic but:

- If used with `esp-idf`, [Espressif IoT Development Framework](https://github.com/espressif/esp-idf).

## Development Environment

Main tools used where [Espressif IoT Development Framework](https://github.com/espressif/esp-idf) and *ESP32 toolchain for Linux*
(see [Standard Setup of Toolchain for Linux](https://github.com/espressif/esp-idf/blob/master/docs/get-started/linux-setup.rst)
for the latest version).

Editing was done in [Visual Studio Code](https://code.visualstudio.com).

Version control with [Git](https://git-scm.com).

## License

This software and related documentation is released under the [GNU GPLv3](http://www.gnu.org/licenses/gpl-3.0.html) License. See the `LICENSE-GPLv3.txt` file.
