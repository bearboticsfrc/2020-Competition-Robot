#include <SPI.h>
#include <Pixy2.h>
#include <Wire.h>

//TODO: Find the pixy cam i2c slave address and the address of the master if Carson hasn't already.

// This is the main Pixy object 
Pixy2 pixy;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  pixy.init();
}
void loop()
{ 
//i2c start transmission
Wire.beginTransmission(); //TODO: get master hex address
Wire.write(byte(0x00)); //Send instruction byte
//Pixy Cam Stuff
  // Grabs the current blocks
  pixy.ccc.getBlocks();
  // Only outputs if a block is detected
  if (pixy.ccc.numBlocks)
  {
    Serial.print("\n");
    Serial.write(pixy.ccc.numBlocks);
    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
      uint8_t buf[] = { 0, 0 };
      buf[0] = pixy.ccc.blocks[i].m_x >> 8;
      buf[1] = pixy.ccc.blocks[i].m_x & 0xFF;
      Serial.write(buf, 2); //Value 0 to 319, 160 in middle
      Serial.write(pixy.ccc.blocks[i].m_y); //Value 0 to 199, 100 in middle
      buf[0] = pixy.ccc.blocks[i].m_width >> 8;
      buf[1] = pixy.ccc.blocks[i].m_width & 0xFF;
      Serial.write(buf, 2); //Value 0 to 320, > = closer
      Serial.write(pixy.ccc.blocks[i].m_height); //Value 0 to 200, > = closer
      //TODO: Assign the binary to a variable for output on i2c
      //TODO: Get rid of serial ouput once determined functional
    }
  }
  Wire.write(/*placeholder*/);
  Wire.endTransmission();
  delay(50);
}