/******************************************************************************

Name:		M50530 LCD DRIVER LIBRARY tested with LEXMARK OPTRA DISPLAY MODULE

Who:		GJO

Ver:		1.00

Date:		2008.02.20

Credits:	Based on BASIC STAMP example code published by Mario Kienspergher,
			OE9MKV, which is based on work by Hans Luyten and Peter Pitzeier

Hardware:	I2CLCD Board Rev6 (Existing HD44780 Interface was re-mapped)

*******************************************************************************
*
*	LCD WIRING:
*	===========
*
*   I2CLCD	HD44780		M50530		I2C LCD
*	PIN     FUNCTION	FUNCTION	PIC IO      COMMENT
*--------------------------------------------------------------------------
*   1       VSS     	VSS
*   2       VCC     	+5V
*   3       VO      	n/c
*   4       RS          n/c       	RE1
*   5       WR          R/W			GND
*   6       E           EX        	RE0
*	 7		DB0			OC1			DB0
* 	 8		DB1   		OC2			DB1
*	 9		DB2			R/W			DB2 		Currently not used, grounded
*	10		DB3			n/c			DB3
*	11      DB4         DB4       	DB4
*  12      DB5         DB5       	DB5
*  13      DB6         DB6       	DB6
*  14      DB7         DB7       	DB7
*
*******************************************************************************

Character Graphics RAM bitmaps start at address 0xA0

CG for 5x7 matrix are accessed using character code 0xF4 to 0xFF (0-11)

******************************************************************************/
// Makro to strobe the EX Signal
#define DMC50461_EX_STROBE lcd.enable = 1; delay_cycles(5); lcd.enable = 0;

#define	FUNCTION_LCD 0				// IOC1=IOC2=0
#define DISPLAY_START_ADDRESS 1		//
#define RAM_ADDDRESS 2
#define CURSOR_ADDRESS 3

#define CGRAM_OFFSET 0xa0

// Port D overlay
struct lcd_pin_map {
           BOOLEAN IOC : 2;         // DB0/1 IOC1 and 2
           BOOLEAN rw;				// DB2
           BOOLEAN free4;           // DB3
           int     data : 4;        // LCD DB4-7 (transposed to bits 0-3)
        } bus;

// Port E overlay
struct lcd_control {
            BOOLEAN enable;         // RE0
            BOOLEAN rs;             // RE1
            BOOLEAN free;           // RE2
        } lcd;

#byte lcd = 0xF84
#byte bus = 0xF83                   // Port D

unsigned char _lcd_addr, _lcd_line;
char const addLUT[4] = {0,40,80,120};  // for 4x20 LCD

void init_DMC50461(void);
void cursor_home_DMC50461(void);
void cursor_XY_DMC50461(int, int);
void clear_home_DMC50461(void);
void put_DMC50461(char );
void line_DMC50461(char);
void write_char_DMC50461 (char);
void set_function_DMC50461(int);
void set_start_address_DMC50461(int );

void Turn_off_block_cursor_DMC50461();
void Turn_off_underline_cursor_DMC50461();
void Turn_on_underline_cursor_DMC50461();
void move_cursor_right_DMC50461();
void move_cursor_left_DMC50461();
void move_home_DMC50461();
void line_set(char which_line);
void load_custom_characters_DMC50561(char * data);
void clear_line_DMC50461(int);

void load_bargraph_symbols();
void draw_bargraph(int, int);
