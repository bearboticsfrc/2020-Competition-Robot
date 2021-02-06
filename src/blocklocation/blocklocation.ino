#include <SPI.h>
#include <Pixy2.h>
#include <Wire.h>

// This is the main Pixy object 
Pixy2 pixy;

void setup()
{
  Serial.begin(115200);
  Wire.begin(80);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  pixy.init();
}

void receiveEvent(int bytes) {
  Serial.println("Receive event");

  char buf[4] = { 0, 0, 0, 0 };
  for (int i = 0; i < 3; ++i) {
    buf[i] = Wire.read();
  }

  //Serial.println(buf);

  
}

void requestEvent() {
    // Grabs the current blocks
  pixy.ccc.getBlocks();
  //Serial.write(pixy.ccc.numBlocks);
  // Only outputs if a block is detected

  //Serial.print("\n");
  /*uint8_t serialbuf[] = {
    0, 0, // 2 bytes for x
    
    0, // 1 byte for y,
    
    0, 0, // 2 bytes for width
    
    0  // 1 byte for height
  };*/

  uint8_t serialbuf[7] = { 0 };

  serialbuf[0] = pixy.ccc.numBlocks;
  
  for (int i=0; i < pixy.ccc.numBlocks && i < 1; i++)
  {
    uint8_t buf[] = { 0, 0 };
    
    //x value 0 to 319, 160 in middle
    serialbuf[1 + i * 6] = buf[0] = pixy.ccc.blocks[i].m_x >> 8;
    serialbuf[2 + i * 6] = buf[1] = pixy.ccc.blocks[i].m_x & 0xFF;
    //Serial.write(buf, 2);
    
    //width value 0 to 320, > = closer
    serialbuf[3 + i * 6] = buf[0] = pixy.ccc.blocks[i].m_width >> 8;
    serialbuf[4 + i * 6] = buf[1] = pixy.ccc.blocks[i].m_width & 0xFF;
    //Serial.write(buf, 2);

    //y value 0 to 199, 100 in middle
    //Serial.write(pixy.ccc.blocks[i].m_y); //Value 0 to 199, 100 in middle
    serialbuf[5 + i * 6] = pixy.ccc.blocks[i].m_y;

    //height value 0 to 200, > = closer
    serialbuf[6 + i * 6] = pixy.ccc.blocks[i].m_height;
    //Serial.write(pixy.ccc.blocks[i].m_height);
  }

  Wire.write(serialbuf, 7);
}

void loop()
{

  delay(10);
}
