#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
int commandIsPerformed_fl = 0;
int quit_fl = 0;
int light_fl = 0;
void interrupt NewInterrupt(...);
void interrupt(*oldInterrupt)(...);
void setMask(unsigned char mask);
void main()
{
    oldInterrupt = getvect(0x09);
    setvect(0x09, NewInterrupt);
    while (!quit_fl)
    {
        if (light_fl)
        {
            setMask(0x02); // turn on Num lock
            delay(500);
            setMask(0x00); // turn off all lights
            delay(500);
            setMask(0x02);
            delay(500);
            setMask(0x00);
            delay(500);
            setMask(0x04); // turn on Caps Lock
            delay(500);
            setMask(0x00);
            delay(500);
            setMask(0x04);
            delay(500);
            setMask(0x00);
            delay(500);
            setMask(0x06); // turn on all lights (intsead of SCroll lock)
            delay(500);
            setMask(0x00);
            delay(500);
            setMask(0x06);
            delay(500);
            setMask(0x00);
            delay(500);
            setMask(0x01); // turn on Scroll Lock
            delay(500);
            setMask(0x00);
            light_fl = 0;
        }
    }
    setvect(0x09, oldInterrupt);
    return;
}
void interrupt NewInterrupt(...)
{
    unsigned char value = 0;
    value = inp(0x60);
    if (value == 0x01)                      // exit has been pressed
        quit_fl = 1;
    else if (value == 0x9c)                 // enter is pressed
        light_fl = !light_fl;
    commandIsPerformed_fl = value == 0xFA;  // the command was executed successfully
    printf("\t%X", value);
    oldInterrupt();
}
void setMask(unsigned char mask)
{
    int i = 0;
    commandIsPerformed_fl = 0;
    while (!commandIsPerformed_fl && i != 3)
    {
        i++;
        while ((inp(0x64) & 0x02) != 0x00); // buffer isn't empty
        outp(0x60, 0xED);                   // enter command
        while ((inp(0x64) & 0x02) != 0x00); // buffer isn't empty
        outp(0x60, mask);
        delay(50);
    }
    if (i == 3)
    {
        printf("\n3 times error\n");
        setvect(0x09, oldInterrupt);
        exit(-1);
    }
}
