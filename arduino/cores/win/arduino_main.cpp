#ifndef WIN_EMU

#include <interface.h>

extern void setup();
extern void loop();

int main()
{
    printf("\nArduino Windows Simulator 2019 WizIO\n");
    printDateTime();
    printf("\n");
    setup();
    while (true)
    {
        loop();
        Sleep(1);
    }
}

#endif /* WIN_EMU */
