/*
this code is WTFPL, please reuse it, improve it and share it as much as you like and pay me a beer !
(c)2011 guyzmo at leloop dot org
(c)2015 Kushulain
                            _
pixel is changing at each _/
if NDATA == true and NCP == true
    if DATA == true
        at each CP = !CP next pixel is set to on
    if DATA == false
        at each CP = !CP next pixel is set to off
CD74HC4094E
*/

// 1h = 0.0416666
//#define D_DAYS 35.5


#define NB_DISP 9
#define NB_LINES 8
#define NB_COLS 96

#define NCP   2 // 5. 2Z  / Clock
#define CP    10 // 6. 2Y / 
#define NDATA 3 // 3. 1Z  / Data
#define DATA  12 // 2. 1Y /
#define STROBE 6  // Unknown, must be HIGH

#define RISING_AND_FALLING_EDGE false  //(Tells when the clock pushes the LED) Depends on the wiring (false == RISING EDGE)

//#define NCP   11 // 5. 2Z  / Clock
//#define CP    10 // 6. 2Y / 
//#define NDATA 13 // 3. 1Z  / Data
//#define DATA  12 // 2. 1Y /

//#define NCP   10 // 5. 2Z  / Clock
//#define CP    11 // 6. 2Y / 
//#define NDATA 12 // 3. 1Z  / Data
//#define DATA  13 // 2. 1Y /

//#define NCP   13 // 5. 2Z  / Clock
//#define CP    12 // 6. 2Y / 
//#define NDATA 11 // 3. 1Z  / Data
//#define DATA  10 // 2. 1Y /

//#define NCP   13 // 5. 2Z  / Clock
//#define CP    12 // 6. 2Y / 
//#define NDATA 10 // 3. 1Z  / Data
//#define DATA  11 // 2. 1Y /

//#define NCP   12 // 5. 2Z  / Clock
//#define CP    13 // 6. 2Y / 
//#define NDATA 11 // 3. 1Z  / Data
//#define DATA  10 // 2. 1Y /

//#define NCP   12 // 5. 2Z  / Clock
//#define CP    13 // 6. 2Y / 
//#define NDATA 10 // 3. 1Z  / Data
//#define DATA  11 // 2. 1Y /

#define DATA_DEFAULT HIGH
#define CP_DEFAULT   HIGH
#define NDATA_DEFAULT HIGH
#define NCP_DEFAULT   HIGH

const uint8_t Fond5x7_nbchar = 96;
const uint8_t Font5x7_nbcols = 5;
const uint8_t Font5x7_nblines = 7;
const uint8_t Font5x7[96][5] = {                                            
    0x00, 0x00, 0x00, 0x00, 0x00,// (space) 32
    0x00, 0x00, 0x5F, 0x00, 0x00,// !       33
    0x00, 0x07, 0x00, 0x07, 0x00,// "       34
    0x14, 0x7F, 0x14, 0x7F, 0x14,// #       35
    0x24, 0x2A, 0x7F, 0x2A, 0x12,// $       36
    0x23, 0x13, 0x08, 0x64, 0x62,// %       37
    0x36, 0x49, 0x55, 0x22, 0x50,// &       38
    0x00, 0x05, 0x03, 0x00, 0x00,// '       39
    0x00, 0x1C, 0x22, 0x41, 0x00,// (       40
    0x00, 0x41, 0x22, 0x1C, 0x00,// )       41
    0x08, 0x2A, 0x1C, 0x2A, 0x08,// *       42
    0x08, 0x08, 0x3E, 0x08, 0x08,// +       43
    0x00, 0x50, 0x30, 0x00, 0x00,// ,       44
    0x08, 0x08, 0x08, 0x08, 0x08,// -       45
    0x00, 0x60, 0x60, 0x00, 0x00,// .       46
    0x20, 0x10, 0x08, 0x04, 0x02,// /       47
    0x3E, 0x51, 0x49, 0x45, 0x3E,// 0       48
    0x00, 0x42, 0x7F, 0x40, 0x00,// 1       49
    0x42, 0x61, 0x51, 0x49, 0x46,// 2       50
    0x21, 0x41, 0x45, 0x4B, 0x31,// 3       51
    0x18, 0x14, 0x12, 0x7F, 0x10,// 4       52
    0x27, 0x45, 0x45, 0x45, 0x39,// 5       53
    0x3C, 0x4A, 0x49, 0x49, 0x30,// 6       54
    0x01, 0x71, 0x09, 0x05, 0x03,// 7       55
    0x36, 0x49, 0x49, 0x49, 0x36,// 8       56
    0x06, 0x49, 0x49, 0x29, 0x1E,// 9       57
    0x00, 0x36, 0x36, 0x00, 0x00,// :       58
    0x00, 0x56, 0x36, 0x00, 0x00,// ;       59
    0x00, 0x08, 0x14, 0x22, 0x41,// <       60
    0x14, 0x14, 0x14, 0x14, 0x14,// =       61
    0x41, 0x22, 0x14, 0x08, 0x00,// >       62
    0x02, 0x01, 0x51, 0x09, 0x06,// ?       63
    0x32, 0x49, 0x79, 0x41, 0x3E,// @       64
    0x7E, 0x11, 0x11, 0x11, 0x7E,// A       65
    0x7F, 0x49, 0x49, 0x49, 0x36,// B       66
    0x3E, 0x41, 0x41, 0x41, 0x22,// C       67
    0x7F, 0x41, 0x41, 0x22, 0x1C,// D       68
    0x7F, 0x49, 0x49, 0x49, 0x41,// E       69
    0x7F, 0x09, 0x09, 0x01, 0x01,// F       70
    0x3E, 0x41, 0x41, 0x51, 0x32,// G       71
    0x7F, 0x08, 0x08, 0x08, 0x7F,// H       72
    0x00, 0x41, 0x7F, 0x41, 0x00,// I       73
    0x20, 0x40, 0x41, 0x3F, 0x01,// J       74
    0x7F, 0x08, 0x14, 0x22, 0x41,// K       75
    0x7F, 0x40, 0x40, 0x40, 0x40,// L       76
    0x7F, 0x02, 0x04, 0x02, 0x7F,// M       77
    0x7F, 0x04, 0x08, 0x10, 0x7F,// N       78
    0x3E, 0x41, 0x41, 0x41, 0x3E,// O       79
    0x7F, 0x09, 0x09, 0x09, 0x06,// P       80
    0x3E, 0x41, 0x51, 0x21, 0x5E,// Q       81
    0x7F, 0x09, 0x19, 0x29, 0x46,// R       82
    0x46, 0x49, 0x49, 0x49, 0x31,// S       83
    0x01, 0x01, 0x7F, 0x01, 0x01,// T       84
    0x3F, 0x40, 0x40, 0x40, 0x3F,// U       85
    0x1F, 0x20, 0x40, 0x20, 0x1F,// V       86
    0x7F, 0x20, 0x18, 0x20, 0x7F,// W       87
    0x63, 0x14, 0x08, 0x14, 0x63,// X       88
    0x03, 0x04, 0x78, 0x04, 0x03,// Y       89
    0x61, 0x51, 0x49, 0x45, 0x43,// Z       90
    0x00, 0x00, 0x7F, 0x41, 0x41,// [       91
    0x02, 0x04, 0x08, 0x10, 0x20,// "\"     92
    0x41, 0x41, 0x7F, 0x00, 0x00,// ]       93
    0x04, 0x02, 0x01, 0x02, 0x04,// ^       94
    0x40, 0x40, 0x40, 0x40, 0x40,// _       95
    0x00, 0x01, 0x02, 0x04, 0x00,// `       96
    0x20, 0x54, 0x54, 0x54, 0x78,// a       97
    0x7F, 0x48, 0x44, 0x44, 0x38,// b       98
    0x38, 0x44, 0x44, 0x44, 0x20,// c       99
    0x38, 0x44, 0x44, 0x48, 0x7F,// d       100
    0x38, 0x54, 0x54, 0x54, 0x18,// e       101
    0x08, 0x7E, 0x09, 0x01, 0x02,// f       102
    0x08, 0x14, 0x54, 0x54, 0x3C,// g       103
    0x7F, 0x08, 0x04, 0x04, 0x78,// h       104
    0x00, 0x44, 0x7D, 0x40, 0x00,// i       105
    0x20, 0x40, 0x44, 0x3D, 0x00,// j       106
    0x00, 0x7F, 0x10, 0x28, 0x44,// k       107
    0x00, 0x41, 0x7F, 0x40, 0x00,// l       108
    0x7C, 0x04, 0x18, 0x04, 0x78,// m       109
    0x7C, 0x08, 0x04, 0x04, 0x78,// n       110
    0x38, 0x44, 0x44, 0x44, 0x38,// o       111
    0x7C, 0x14, 0x14, 0x14, 0x08,// p       112
    0x08, 0x14, 0x14, 0x18, 0x7C,// q       113
    0x7C, 0x08, 0x04, 0x04, 0x08,// r       114
    0x48, 0x54, 0x54, 0x54, 0x20,// s       115
    0x04, 0x3F, 0x44, 0x40, 0x20,// t       116
    0x3C, 0x40, 0x40, 0x20, 0x7C,// u       117
    0x1C, 0x20, 0x40, 0x20, 0x1C,// v       118
    0x3C, 0x40, 0x30, 0x40, 0x3C,// w       119
    0x44, 0x28, 0x10, 0x28, 0x44,// x       120
    0x0C, 0x50, 0x50, 0x50, 0x3C,// y       121
    0x44, 0x64, 0x54, 0x4C, 0x44,// z       122
    0x00, 0x08, 0x36, 0x41, 0x00,// {       123
    0x00, 0x00, 0x7F, 0x00, 0x00,// |       124
    0x00, 0x41, 0x36, 0x08, 0x00,// }       125
    // EXTRA CHARS
    0x08, 0x08, 0x2A, 0x1C, 0x08,// ->      
    0x08, 0x1C, 0x2A, 0x08, 0x08 // <-      
};

class DotMatrixDisplay {
    uint8_t cp, ncp, data, ndata;

    public:
        void setup() {
            //Serial.println("dotmatrixdisplay.setup");
            cp = CP_DEFAULT;
            data = DATA_DEFAULT;
            ncp = NCP_DEFAULT;
            ndata = NDATA_DEFAULT;

            
            pinMode(STROBE, OUTPUT);
            digitalWrite(STROBE, HIGH);
            
            // set negated outputs to always high
            pinMode(NCP, OUTPUT);
            pinMode(NDATA, OUTPUT);
            digitalWrite(NCP, ncp);
            digitalWrite(NDATA, ndata);

            // set outputs to default
            pinMode(CP, OUTPUT);
            pinMode(DATA, OUTPUT);
            digitalWrite(CP, cp);
            digitalWrite(DATA, data);
        }

        void step() {

          if (RISING_AND_FALLING_EDGE)
          {
            if (cp == HIGH) cp = LOW; else cp = HIGH;
            digitalWrite(NCP,  cp);
          }
          else
          {
            digitalWrite(NCP,  HIGH);
            digitalWrite(NCP,  LOW);
          }
        }

        void setOn() {
            //Serial.println("dotmatrix.set_on");
            //Serial.print(1);
            digitalWrite(NDATA, HIGH);
        }

        void setOff() {
            //Serial.println("dotmatrix.set_off");
            //Serial.print(0);
            digitalWrite(NDATA, LOW);
        }

        void clear() {
            //Serial.println("dotmatrix.clear");
            digitalWrite(NDATA, LOW);
            for (int i=0;i<NB_COLS*NB_LINES*NB_DISP;++i) {
                step();
            }
        }

        void allOn() {
            //Serial.println("dotmatrix.all_on");
            digitalWrite(NDATA, HIGH);
            for (int i=0;i<NB_COLS*NB_LINES*NB_DISP;++i) {
                step();
            }
        }

} dotmatrix;



void setup() {
    Serial.begin(9600);
    Serial.println("STARTED");
    dotmatrix.setup();
    //digitalWrite(STROBE, LOW);
    
}

#define FREQ 0
int blinking = 0;

void loop() {
  
    char* text = "danger98768D5-S.O.S.-129caserne6675expulsion7J8459-H.E.L.P.-5437879675-S.O.S.-3456JARDIN D'ALICE";

    for (int8_t i=0;i<strlen(text);i++)  //browse string
    {
    
      for (int x=0; x<5; x++) //browse char x coord
      {
        for (int y=7; y>=0; y--) //brows char y coords
        {
          if (y == 0)
          {
            dotmatrix.setOff();dotmatrix.step();
          }
          else
          {
            //uint8_t byt = (uint8_t)((Font5x7[65-32][x]));
            uint8_t byt = (uint8_t)((Font5x7[text[i]-32][x]));
            if ((1&(byt >> (y-1))) == 1) dotmatrix.setOn(); else dotmatrix.setOff(); dotmatrix.step();
            delayMicroseconds(FREQ);
          
          }
        }
            //delay(FREQ);
      }
    
        //CHAR SPACING
        for (int y=0; y<8; y++)
        {
            dotmatrix.setOff();dotmatrix.step(); // invisible bit
            delayMicroseconds(FREQ);
        }
    }




  //SOS Blinking
  switch (blinking%9)
  {
    case 0 :
      delay(100);
      break;
    case 1 :
      delay(100);
      break;
    case 2 :
      delay(400);
      break;
    case 3 :
      delay(400);
      break;
    case 4 :
      delay(400);
      break;
    case 5 :
      delay(400);
      break;
    case 6 :
      delay(100);
      break;
    case 7 :
      delay(100);
      break;
    case 8 :
      delay(1500);
      break;

      
      default : 
      //delay();
      break;
  }

  //Human like randomness
  switch (blinking%4)
  {
    case 1 :
      delay(40);
      break;
    case 2 :
      delay(150);
      break;
      
      default : 
      //delay();
      break;
  }
    
    blinking++;
}
