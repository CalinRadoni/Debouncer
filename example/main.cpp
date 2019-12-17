#include <iostream>
#include "../Debouncer.h"

Debouncer debouncer;
bool state, oldState;
uint32_t oldPressCnt = 0;
uint32_t pressCnt = 0;
uint32_t cnt = 0;

void VirtualPress(uint32_t val)
{
    uint32_t mask = 0x80000000;
    while (mask != 0) {
        debouncer.Update(val & mask);
        mask = mask >> 1;

        cnt++;
        state = debouncer.IsPressed();
        if (state != oldState) {
            oldState = state;
            std::cout << cnt << " " << (state ? "pressed" : "released") << std::endl;
        }

        if (debouncer.IsDown()){
            pressCnt = debouncer.GetCurrentPressCount();
        }
        if (pressCnt != oldPressCnt) {
            oldPressCnt = pressCnt;
            std::cout << cnt << " presses " << pressCnt << std::endl;
        }
    }
}

int main()
{
    debouncer.SetUpdateTime(5);
    debouncer.SetKeyRepeat(500, 50);

    state = oldState = debouncer.IsPressed();

    VirtualPress(0x0AAFFFFF);
    VirtualPress(0xFFFFFFFF);
    VirtualPress(0xFFFFFFFF);
    VirtualPress(0xFFFFFFFF);
    VirtualPress(0xFFFFFFFF);
    VirtualPress(0xFFF00000);

    std::cout << "Presses " << pressCnt << std::endl;
    return 0;
}
