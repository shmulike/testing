//=====[ INCULDE ]==============================================================
#include <i2c_t3.h>

//=====[ VARIABLES ]============================================================
uint8_t slave_1 = 0x64;
union u_tag {
  byte b[4];
  float fval;
} u;
byte data[4] = {0};
int count;

//=====[ SETUP ]================================================================
void setup()
{
    // Setup for Master mode, pins 18/19, external pullups, 400kHz, 200ms default timeout
    Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);
    Wire.setDefaultTimeout(200000); // 200ms
    Serial.begin(115200);
    while(!Serial);
}

//=====[ LOOP ]=================================================================
void loop(){
  Serial.print("Reading from Slave; ");
  Wire.requestFrom(slave_1, sizeof(data)); // Read from Slave (string len unknown, request full buffer)
  if(Wire.getError()){
    Serial.print("FAIL code: ");
    Serial.println(Wire.getError());
    }
  else{
    Serial.print("Encoder value: ");
    Wire.read(data, Wire.available());
    for (int i = 0; i < 4; i++)
      u.b[i] = data[i];
    Serial.println(u.fval,3);
    }
  delay(100);                       // Delay to space out tests 
  }
