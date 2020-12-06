#include "gnssTypes.h"
#include <dht11.h>

dht11 DHT11;

#define DHT11PIN PA7

XGnss x;
xxvtg_t vtg;
xxgga_t gga;

uint8_t Snum = 0;
uint8_t fix = 0;
float Shumidity;
float Stemperature ;
uint8_t i;
uint8_t ii;
uint8_t iii;
uint8_t f;
uint8_t ff;
uint8_t fff;
void printHT() {
  int chk = DHT11.read(DHT11PIN);
  if (chk != DHTLIB_OK && chk != DHTLIB_ERROR_CHECKSUM) {

    Serial3.write(iii);
    Serial3.write(fff);
    
    Serial3.write(ii);
    Serial3.write(ff);

  } else {
    Shumidity = (float)DHT11.humidity;
    Stemperature = (float)DHT11.temperature;

    iii = (int)Stemperature;
    Stemperature = Stemperature - iii;
    Stemperature = Stemperature * 100;
    fff = (int)Stemperature;
    Serial3.write(iii);
    Serial3.write(fff);

    ii = (int)Shumidity;
    Shumidity = Shumidity - ii;
    Shumidity = Shumidity * 100;
    ff = (int)Shumidity;
    Serial3.write(ii);
    Serial3.write(ff);
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial1.begin(19200);
  Serial3.begin(19200);
  Serial2.begin(19200);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (Serial3.available())
  {
    char c = Serial3.read();
    if (x.OnRecv(c) == 1)
    {
      uint8_t type = x.Parse();
      if (type == GPVTG)
      {
        x.getVTG(&vtg);
        x.printVTG(vtg);
        //0xa0 s s t t h h 0x0a

        if (fix == 0)
        {
          Serial3.write(0xa0);
          Serial3.write(0xfc);//252
          Serial3.write(Snum);

          printHT();

          Serial3.write(0x0a);
        }
        else
        {
          double speed = vtg.K_Horizontal_Velocity;
          i = (int)speed;
          speed = speed - i;
          speed = speed * 100;
          f = (int)speed;

          Serial3.write(0xa0);
          Serial3.write(i);
          Serial3.write(f);

          printHT();

          Serial3.write(0x0a);
        }
      }
      else if (type == GPGGA)
      {
        x.getGGA(&gga);
        x.printGGA(gga);
        Snum = gga.S_Num;
        fix = gga.Fix;
      }
    }
  }
}
