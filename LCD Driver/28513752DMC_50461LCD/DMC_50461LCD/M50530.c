/******************************************************************************

Name:		M50530 LCD DRIVER LIBRARY tested with LEXMARK OPTRA DISPLAY MODULE

Who:		GJO

Ver:		1.00

Date:		2008.02.20

Credits:	Based on BASIC STAMP example code published by Mario Kienspergher,
			OE9MKV, which is based on work by Hans Luyten and Peter Pitzeier

Hardware:	I2CLCD Board Rev6 (Existing HD44780 Interface was re-mapped)

Note: The old Microcomputer must be removed from the DMC-50461N.

============================= READ BEFORE APPLYING POWER =============================

The module as is intended to operate from 3.3V DC. If you want to operate the LCD at 5VDC
follow the instructions below:

Remove R16 and install a 100K potentiometer in the pads of (RV1) provided to allow
proper operation at 5VDC. The LCD (Vee) Voltage is approximately 6.25V at 5VDC Supply
voltage. The adjustment is quite critical.

    ========================= WARNING WARNING WARNING =========================

Do not run the LCD without proper initialization to prevent permanent damage to the
LCD liquid crystals. It is possible to leave the controller in a state with no
internal LCD drive activity. If left in this condition, the LCD will be permanently
damaged due to absent square wave operating waveforms. DC kills LCD!!!

This can be observed when the LCD pixels start to bleed and look unusually dark.
Sometimes adjacent structures show faintly. If this occurs, shut off power to the
LCD quickly.

******************************************************************************/

#include "M50530.h"

/*****************************************************************************
* load custom character graphics (CG)
*
* data contains character address and eight bitmap pixel data from top to bottom
*
* CG data format = [CGa,d0,d1,d2,d3,d4,d5,d6,d7]
*
* CGa = CG start location in CG RAM
*
*	bit  43210
*	d0 = XXXXX
*	d1 = XXXXX
*	d2 = XXXXX
*	d3 = XXXXX
*	d4 = XXXXX
*	d5 = XXXXX
*	d6 = XXXXX
*	d7 = XXXXX
*
* Access CG from 0xF4 < n < 0xFF
*
*	Note: 	This function cannot be used with data stored in FLASH ROM due to
*			CCS does not allow pointer use here.
*
******************************************************************************/
void load_custom_characters_DMC50561(char * data)
{
	int i;
	int address;

	if(*data > 11) return;

	address = *data * 8;
	address += CGRAM_OFFSET;
	data++;

	for(i=0;i<8;i++)
	{
		bus.IOC = CURSOR_ADDRESS;
		write_char_DMC50461(address + i);
		bus.IOC = RAM_ADDDRESS;
		write_char_DMC50461(*data);
		data++;
	}

}



void init_DMC50461(void)
{
   	// SF: Nibble mode, 5x7 font, 4x20 chars, 160 bytes DD RAM, 96 bytes CG RAM
    set_function_DMC50461(0xdb);
	// SD: Set Display: LCD=ON, CUR=OFF, U.L=OFF, CUR BLNK=OFF, CHR=BLNK
    set_function_DMC50461(0x30);
	// SE: Set Entry Mode
    set_function_DMC50461(0x58);
    clear_home_DMC50461();
}



void write_char_DMC50461(char data)
{
    bus.data = data >> 4;         // Write to display upper nibble
    DMC50461_EX_STROBE
    delay_cycles(5);
    bus.data = data & 0x0f;       // Write to display lower nibble
    DMC50461_EX_STROBE
    delay_us(100);                 // allow display time to accept the new data
}



// SF Instruction
void set_function_DMC50461(int cmd)
{
    bus.IOC = FUNCTION_LCD ;
    write_char_DMC50461(cmd);
}



// WS Instruction
void set_start_address_DMC50461(int cmd)
{
    bus.IOC = DISPLAY_START_ADDRESS;
    write_char_DMC50461(cmd);
}



// MH Instruction
void cursor_home_DMC50461(void)
{
    bus.IOC = FUNCTION_LCD ;
    write_char_DMC50461(0x03);
}



// WC Instruction
void cursor_XY_DMC50461(int row, int col)
{
//    int temp;
    bus.IOC = CURSOR_ADDRESS;
    _lcd_addr = addLUT[row] + col;
    write_char_DMC50461(_lcd_addr);
    _lcd_line = row;
}



// CH Instruction
void clear_home_DMC50461(void)
{
    bus.IOC = FUNCTION_LCD ;
    write_char_DMC50461 (0x01);
    delay_ms(10);
    line_set(1);
}



// WD Instruction
void put_DMC50461(char c)
{

    bus.IOC = RAM_ADDDRESS;
    write_char_DMC50461(c);
    _lcd_addr++;

    if(_lcd_addr == 20)
        line_set(2);
    if(_lcd_addr == 40)
        line_set(3);
    if(_lcd_addr == 60)
        line_set(4);
    if(_lcd_addr == 80)
        line_set(1);
}



void line_set(char which_line)
{
    int temp;
    temp = addLUT[which_line - 1];
    bus.IOC = CURSOR_ADDRESS;
    write_char_DMC50461(temp);
    _lcd_line = which_line;
}



// MH Instruction
void move_home_DMC50461()
{
    bus.IOC = FUNCTION_LCD ;
    write_char_DMC50461(0x03);
}



// MA - Move cursor left
void move_cursor_left_DMC50461()
{
    bus.IOC = FUNCTION_LCD ;
    write_char_DMC50461(0x1C);
}



// MA Move cursor right
void move_cursor_right_DMC50461()
{
    bus.IOC = FUNCTION_LCD ;
    write_char_DMC50461(0x18);
}



// SD: Turn On Underline Cursor
void Turn_on_underline_cursor_DMC50461()
{
    bus.IOC = FUNCTION_LCD ;
    write_char_DMC50461(0x3a);
}



// SD: Turn Off Underline Cursor
void Turn_off_underline_cursor_DMC50461()
{
    bus.IOC = FUNCTION_LCD ;
    write_char_DMC50461(0x30);
}



// SD: Turn On Block Cursor
void Turn_on_block_cursor_DMC50461()
{
    bus.IOC = FUNCTION_LCD ;
    write_char_DMC50461(0x33);
}



// SD: Turn Off Block Cursor
void Turn_off_block_cursor_DMC50461()
{
    bus.IOC = FUNCTION_LCD ;
    write_char_DMC50461(0x30);
}




void clear_line_DMC50461(int line)
{

	int i;
	cursor_XY_DMC50461(line, 0);
	for(i=0;i<20;i++)
	{
		put_DMC50461(32);
	}
}



void load_bargraph_symbols()
{

    char data0[8]={0,0,0,0,0,0,0,0};
    char data1[8]={1,16,16,16,16,16,16,16};
    char data2[8]={2,24,24,24,24,24,24,24};
    char data3[8]={3,28,28,28,28,28,28,28};
    char data4[8]={4,30,30,30,30,30,30,30};
    char data5[8]={5,31,31,31,31,31,31,31};
    char data6[8]={6,14,17,17,14,4,4,31};

    load_custom_characters_DMC50561(data0);
    load_custom_characters_DMC50561(data1);
    load_custom_characters_DMC50561(data2);
    load_custom_characters_DMC50561(data3);
    load_custom_characters_DMC50561(data4);
    load_custom_characters_DMC50561(data5);
    load_custom_characters_DMC50561(data6);
}



void draw_bargraph(int row, int data)
{
    int i,temp, remainder;

    if(data>100)data=100;

    temp = data / 5;
    remainder = data % 5;

    cursor_XY_DMC50461(row,0);

    for(i=1;i<=temp;i++)
        printf(put_DMC50461, "%c", 0xF4 + 5);

    if(remainder > 0)
        printf(put_DMC50461, "%c", 0xF4 + remainder);

}





