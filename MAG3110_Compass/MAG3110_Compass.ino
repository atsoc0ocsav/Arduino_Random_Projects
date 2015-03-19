// http://www.bajdi.com
// MAG3110 Compass sketch
// Used code found here: http://users.soe.ucsc.edu/~karplus/Arduino/accel_magnet/
// This sketch will print the heading calculated from the readings of a MAG3110 sensor
 
#include "i2c.h" // Use I2C library found here: http://users.soe.ucsc.edu/~karplus/Arduino/libraries/i2c/
 
#define degrees_per_radian  (180./3.14159265358979)
 
// minimum and maximum values seen during calibration time
int16_t mag_low_x = -1404; 
int16_t mag_high_x = -613;
int16_t mag_low_y = 385;
int16_t mag_high_y = 1307;
int16_t mag_low_z = 5;
int16_t mag_high_z = 926;
 
// I2C 7-bit address of the magnetometer
#define MAG_3110_I2C  0x0E
 
// registers on the magnetometer
#define MAG_3110_DR_STATUS 0x00
 
// add 1 for LSB
#define MAG_3110_OUT_X_MSB 0x01
#define MAG_3110_OUT_Y_MSB 0x03
#define MAG_3110_OUT_Z_MSB 0x05
 
// add 1 for LSB  // user offset
#define MAG_3110_OFF_X_MSB 0x09
#define MAG_3110_OFF_Y_MSB 0x0B
#define MAG_3110_OFF_Z_MSB 0x0D
 
#define MAG_3110_CTRL_REG1 0x10
#define MAG_3110_CTRL_REG2 0x11
 
// Fields in registers
// CTRL_REG1: dr2,dr1,dr0  os1,os0  fr tm ac
 
// Sampling rate 80Hz 
#define MAG_3110_SAMPLE80 0
 
// How many samples to average (lowers data rate)
#define MAG_3110_OVERSAMPLE1 0
#define MAG_3110_OVERSAMPLE2 0x08
#define MAG_3110_OVERSAMPLE3 0x10
#define MAG_3110_OVERSAMPLE4 0x18
 
// put in active mode
#define MAG_3110_ACTIVE 0x01  
 
// CTRL_REG2: AUTO_MRST_EN  _ RAW MAG_RST _ _ _ _ _
// reset sensor after each reading
#define MAG_3110_AUTO_MRST_EN 0x80
 
// DR_STATUS Register ZYXOW ZOW YOW XOW ZYXDR ZDR YDR XDR
#define MAG_3110_ZYXDR  0x08
 
#define mag_write_reg(r,v)   (i2cWriteRegister(MAG_3110_I2C,r,v))
#define mag_read_reg(r)      (i2cReadRegister(MAG_3110_I2C,r))
 
inline uint8_t mag_data_ready(void)
{   return mag_read_reg(MAG_3110_DR_STATUS) & MAG_3110_ZYXDR;
}
 
void mag_read_xyz(int16_t&x, int16_t&y, int16_t&z)
{
    while (!mag_data_ready()) {} // wait for new set of data
     
    static uint8_t data[6];
    i2cReadRegisters(MAG_3110_I2C, MAG_3110_OUT_X_MSB, 6, data);
    x = (data[0]<<8) + data[1];
    y = (data[2]<<8) + data[3];
    z = (data[4]<<8) + data[5];
}
 
void mag_set_offsets(void)
{  
    int16_t mag_x_offset = (mag_low_x+mag_high_x)/2;
    int16_t mag_y_offset = (mag_low_y+mag_high_y)/2;
    int16_t mag_z_offset = (mag_low_z+mag_high_z)/2;
    static uint8_t data[6];
      
    data[0]=mag_x_offset>>7;    data[1]=(mag_x_offset<<1)& 0xFF;
    data[2]=mag_y_offset>>7;    data[3]=(mag_y_offset<<1)& 0xFF;
    data[4]=mag_z_offset>>7;    data[5]=(mag_z_offset<<1)& 0xFF;
      
    i2cWriteRegisters(MAG_3110_I2C, MAG_3110_OFF_X_MSB, 6, data);
}
 
void print_heading(int16_t x, int16_t y, int16_t z)
{     
  float mag_x_scale = 1.0/(mag_high_x-mag_low_x);
  float mag_y_scale = 1.0/(mag_high_y-mag_low_y);
   
   
  float heading = atan2(-y*mag_y_scale,x*mag_x_scale);  
  if(heading < 0)
  {
  heading += 2*PI;  // correct for when the heading is negative
  }
  float headingDegrees = heading * degrees_per_radian;  // convert to degrees
  
        Serial.print("headingDegrees = " );
        Serial.print(headingDegrees);
        Serial.println();
}
 
void mag_setup(void)  
{      
    mag_write_reg(MAG_3110_CTRL_REG2, MAG_3110_AUTO_MRST_EN);
    mag_write_reg(MAG_3110_CTRL_REG1, MAG_3110_SAMPLE80+MAG_3110_OVERSAMPLE1+MAG_3110_ACTIVE);
    mag_set_offsets();
}
 
void setup(void)
{
    Serial.begin(115200);
 
    i2cInit();
    i2cSetBitrate(100);  // try 100kHz
    delay(20);
    mag_setup();   
    delay(50);
}
 
void loop(void)
{
    int mag_x,mag_y,mag_z;   
    mag_read_xyz(mag_x,mag_y,mag_z);  // read from sensor
    print_heading(mag_x,mag_y,mag_z);  // print the heading
}
