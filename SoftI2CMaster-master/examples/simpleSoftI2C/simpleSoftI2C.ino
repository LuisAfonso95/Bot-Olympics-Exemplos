// -*- c++ -*-
// Simple sketch to read out one register of an I2C device
#define I2C_TIMEOUT 1000
#define I2C_PULLUP 1
#define SDA_PORT PORTC
#define SDA_PIN 4 // = A4
#define SCL_PORT PORTC
#define SCL_PIN 5 // = A5
#include <SoftI2CMaster.h>

#define I2C_7BITADDR 0x68 // DS1307
#define MEMLOC 0x0A
#define ADDRLEN 1

void setup(void) {
  Serial.begin(57600);
  if (!i2c_init()) Serial.println("I2C init failed");
}

void loop(void){
  if (!i2c_start_wait((I2C_7BITADDR<<1)|I2C_WRITE)) {
    Serial.println("I2C device busy");
    return;
  }
  for (byte i=1; i<ADDRLEN; i++) i2c_write(0x00);
  i2c_write(MEMLOC);
  i2c_rep_start((I2C_7BITADDR<<1)|I2C_READ);
  byte val = i2c_read(true);
  i2c_stop();
  Serial.println(val);
  delay(1000);
}
