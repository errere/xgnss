#include "gnssTypes.h"

XGnss x;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 23, 22);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (Serial1.available())
  {
    char c = Serial1.read();
    if (x.OnRecv(c) == 1)
    {
      NMEAType_t t = x.Parse();
      if(t == GGA){
        gga_t gga;
        x.getGGA(&gga);
        x.printGGA(gga);
      }//gga
    }//onrecv
  }//ava
}//loop
