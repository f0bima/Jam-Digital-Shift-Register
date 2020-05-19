#include <DS1307.h>
// Init the DS1307
DS1307  rtc(SDA, SCL);
// Init a Time-data structure
Time  t;
int tgp,tgs,bp,bs,thp,ths,thrb,thrt,jp,js,mp,ms,dp,ds,hr,hari;
int latchPin = 8;//ST_CP
int clockPin = 12;//SH_CP 
int dataPin = 11; //DS 
int ShowDec [15];
// define latch, clock and datapin
 
 
void setup ()
{

  // Initialize the rtc object
  rtc.begin();

  // Set the clock to run-mode
  rtc.halt(false);
  
  // The following lines can be uncommented to set the time
  //rtc.setDOW(MINGGU);        // Set Day-of-Week to SUNDAY
  //rtc.setTime(07, 33, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(16, 7, 2017);   // Set the date to October 3th, 2010
pinMode(latchPin,OUTPUT);
pinMode(clockPin,OUTPUT);
pinMode(dataPin,OUTPUT); 
//set these three pins to output
}
 
//Display function (display word, display position, display if have 
//decimal point) 
void disNum(int Num_Qua, int Num_Pos, int Num_Dec)
{
int Num_Qua_B = 0;
int Num_Pos_B = 0;
int Num_Pos_C = 0;
switch (Num_Qua)
{
case 0:Num_Qua_B = 192;break;
case 1:Num_Qua_B = 249;break;
case 2:Num_Qua_B = 164;break;
case 3:Num_Qua_B = 176;break;
case 4:Num_Qua_B = 153;break;
case 5:Num_Qua_B = 146;break;
case 6:Num_Qua_B = 130;break;
case 7:Num_Qua_B = 248;break;
case 8:Num_Qua_B = 128;break;
case 9:Num_Qua_B = 144;break;
case 11:Num_Qua_B = 254;break;
case 12:Num_Qua_B = 253;break;
case 13:Num_Qua_B = 251;break;
case 14:Num_Qua_B = 247;break;
case 15:Num_Qua_B = 239;break;
case 16:Num_Qua_B = 223;break;
case 17:Num_Qua_B = 191;break;
default: Num_Qua_B = 255;break;
};
//this value convert to binary, which is adcdefg need to light up
switch (Num_Pos)
{
case 1:Num_Pos_B = 1;break;
case 2:Num_Pos_B = 2;break;
case 3:Num_Pos_B = 4;break;
case 4:Num_Pos_B = 8;break;
case 5:Num_Pos_B = 16;break;
case 6:Num_Pos_B = 32;break;
case 7:Num_Pos_B = 64;break;
case 8:Num_Pos_B = 128;break;
case 9:Num_Pos_C = 1;break;
case 10:Num_Pos_C = 2;break;
case 11:Num_Pos_C = 4;break;
case 12:Num_Pos_C = 8;break;
case 13:Num_Pos_C = 16;break;
case 14:Num_Pos_C = 32;break;
case 15:Num_Pos_C = 64;break;
//case 15:Num_Pos_C = 64;break;
//case 16:Num_Pos_C = 128;break;
/*case 9:Num_Pos_C = 256;break;
case 10:Num_Pos_C = 512;break;
case 11:Num_Pos_C = 1024;break;
case 12:Num_Pos_C = 2048;break;
case 13:Num_Pos_C = 4096;break;
case 14:Num_Pos_C = 8192;break;*/
default: Num_Pos_B = 0;break;
};
//this value convert to binary, which is the one light up now.
if (Num_Dec == 1)
{
Num_Qua_B = Num_Qua_B + 128;
};
//========================================
digitalWrite(latchPin,LOW); 
// set latch to low tolet the display ready to receive data
int L = Num_Qua_B; int R = Num_Pos_B; int C =Num_Pos_C;
shiftOut(dataPin,clockPin,MSBFIRST,C);
shiftOut(dataPin,clockPin,MSBFIRST,R);
shiftOut(dataPin,clockPin,MSBFIRST,L);
digitalWrite(latchPin,HIGH); //restore to high TTL back
//========================================
delayMicroseconds(100);
}
 
void loop()
{
// Get data from the DS1307
  t = rtc.getTime();
  tgp = t.date / 10;
  tgs = t.date % 10;
  bp  = (t.mon) / 10;
  bs  = (t.mon) % 10;
  thrb = t.year / 1000;
  thrt = ((t.year % 1000) / 100);
  thp = ((t.year % 100) / 10);
  ths = t.year % 10;
  jp  = t.hour / 10;
  js  = t.hour %10;
  mp  = t.min / 10;
  ms  = t.min % 10;
  dp  = t.sec / 10;
  ds  = t.sec % 10;
  hari  = t.dow;
  switch (hari)
  {
    case 1:hr=17;break;
    case 2:hr=12;break;
    case 3:hr=13;break;
    case 4:hr=14;break;
    case 5:hr=15;break;
    case 6:hr=16;break;
    case 7:hr=11;break;
  }
disNum(jp,1,ShowDec[1]);
disNum(js,2,ShowDec[2]);
disNum(mp,3,ShowDec[3]);
disNum(ms,4,ShowDec[4]);
disNum(dp,5,ShowDec[5]);
disNum(ds,6,ShowDec[6]);
disNum(tgp,7,ShowDec[7]);
disNum(tgs,8,ShowDec[8]);
disNum(bp,9,ShowDec[9]);
disNum(bs,10,ShowDec[10]);
disNum(thrb,11,ShowDec[11]);
disNum(thrt,12,ShowDec[12]);
disNum(thp,13,ShowDec[13]);
disNum(ths,14,ShowDec[14]);
disNum(hr,15,ShowDec[15]);

}
