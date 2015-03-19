/*****************************************************************************
*
*   Name:   Lexmark Optra DMC-50461N LCD Demo Program
*
*   Purpose:    Demonstrate the DMC-50461N Optrex custom LCD module for
*               an Lexmark Optra Laser Printer.
*
*   Date:   2008.02.24
*   Ver:    1.00
*   Who:    GJO
*
*   History:
*
*   Ver     Date        Who     Description
*   ---------------------------------------------------------------------------
*   1.00    2008.02.24  GJO     Initial Version
*
*   Tools Used:
*
*   Compiler:   CCS PCH V4.068
*   Programmer: Tech-Tools Quick-Writer
*   PIC HW:     I2C_LCD LCD Mini_Controller Rev6
*   Target:     PIC18F4620
*
*****************************************************************************/

#include <18F4620.h>
#use delay(clock=16000000)
#fuses HS,NOWDT,NOPROTECT,NOLVP, PUT
#use fast_io(d)
#use fast_io(e)

#byte PORTD = 0xF83
#byte PORTE = 0xF84

#include "M50530.c" // M50530 control functions

void main(void)
{
    int i;

    PORTD = 0x00;
    PORTE = 0x00;

    set_tris_d(0);  // Set all PortD pins to outputs
    set_tris_e(0);  // Set all PortE pins to outputs

    init_DMC50461();
    load_bargraph_symbols();    // Load custom character bitmaps

    cursor_XY_DMC50461(0,0);
    delay_ms(100);
    // Display ASCII Table
    for(i=48;i<128;i++){
        printf(put_DMC50461, "%c", i);
    }

    delay_ms(2000);

    clear_home_DMC50461();

    cursor_XY_DMC50461(0,0);
    printf(put_DMC50461, "   DMC-50461 DEMO   ");
    cursor_XY_DMC50461(1,0);
    printf(put_DMC50461, "  OF LEXMARK OPTRA  ");
    cursor_XY_DMC50461(2,0);
    printf(put_DMC50461, "     LCD MODULE     ");

    // Display a custom character in top left position
    cursor_XY_DMC50461(0,0);
    printf(put_DMC50461, "%c", 0xFA);

    i=0;
    for( ; ; )
    {
        draw_bargraph(3, i++);
        if(i>100)
        {
            i=0;
            clear_line_DMC50461(3);
        }
        delay_ms(200);
    }
}