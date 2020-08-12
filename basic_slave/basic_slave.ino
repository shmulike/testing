//=====[ INCULDE ]==============================================================
#include "RLS_Encoder.h"        // <- This is a library that i made that read data from RLS-magnetic rotatary encoder
// https://www.rls.si/en/products/rotary-magnetic-encoders/absolute-encoders/aksim-2-off-axis-rotary-absolute-encoder
#include <i2c_t3.h>

//=====[ VARIABLES ]============================================================
RLS_Encoder enc;            // The RLS_Encoder is a class that reads data from an encoder 
uint8_t slave_addr = 0x64;
union u_tag {
     byte b[4];
     float fval;
} u;

//=====[ Function declaraion ]========================================
void requestEvent();

//=====[ SETUP ]================================================================
void setup() {
  //Serial.begin(115200); while(!Serial);
  enc.begin(); delay(5);
  Wire.begin(I2C_SLAVE, slave_addr, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);
  Wire.onRequest(requestEvent);
}

//=====[ LOOP ]=================================================================
void loop() {
  Serial2.flush();              // flush serial buffer
  if (Serial2.available() > 0){
    u.fval = enc.get_pos();     // read the last data from encoder - this works well !!!
    Serial.println(u.fval, 3);  // This works well !!!
  }
  delay(2);
}

//=====[ FUNCTIONS ]=================================================================

void requestEvent(){      
   Wire.Write(u.b, 4);
}
