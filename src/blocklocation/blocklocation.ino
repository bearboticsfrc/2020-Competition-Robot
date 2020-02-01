#include <SPI.h>
#include <Pixy2.h>
#include <Wire.h>

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
  Wire.beginTransmission(0x80); //TODO: get master hex address
  //Pixy Cam Stuff
  // Grabs the current blocks
  pixy.ccc.getBlocks();
  // Only outputs if a block is detected
  if (pixy.ccc.numBlocks)
  {
    Serial.print("\n");
    Serial.write(pixy.ccc.numBlocks);
    uint8_t serialbuf[] = {
      0, 0, // 2 bytes for x
      
      0, // 1 byte for y,
      
      0, 0, // 2 bytes for width
      
      0  // 1 byte for height
    };
    
    Wire.write(pixy.ccc.numBlocks);
    
    for (int i=0; i<pixy.ccc.numBlocks; i++)
    {
      uint8_t buf[] = { 0, 0 };
      
      //x value 0 to 319, 160 in middle
      serialbuf[0] = buf[0] = pixy.ccc.blocks[i].m_x >> 8;
      serialbuf[1] = buf[1] = pixy.ccc.blocks[i].m_x & 0xFF;
      Serial.write(buf, 2);
      
      //width value 0 to 320, > = closer
      serialbuf[2] = buf[0] = pixy.ccc.blocks[i].m_width >> 8;
      serialbuf[3] = buf[1] = pixy.ccc.blocks[i].m_width & 0xFF;
      Serial.write(buf, 2);

      //y value 0 to 199, 100 in middle
      Serial.write(pixy.ccc.blocks[i].m_y); //Value 0 to 199, 100 in middle
      serialbuf[4] = pixy.ccc.blocks[i].m_y;

      //height value 0 to 200, > = closer
      serialbuf[5] = pixy.ccc.blocks[i].m_height;
      Serial.write(pixy.ccc.blocks[i].m_height);
      Wire.write(serialbuf, 6);
    }
    Wire.endTransmission();
  }
  delay(50);
}