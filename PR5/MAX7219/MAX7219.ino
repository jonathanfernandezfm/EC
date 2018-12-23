//www.elegoo.com
//2016.12.9

//We always have to include the libraries
#include <LedControl.h>
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to LOAD(CS)
 pin 10 is connected to the CLK 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,10,11,1);

/* we always wait a bit between updates of the display */
unsigned long delaytime1=1000;
unsigned long delaytime2=50;

/*
 This method will display the characters that are pressed
 on the keypad on the matrix . 
 */

void writeMatrix(byte C[8]){
  lc.setRow(0,0,C[0]);
  lc.setRow(0,1,C[1]);
  lc.setRow(0,2,C[2]);
  lc.setRow(0,3,C[3]);
  lc.setRow(0,4,C[4]);
  lc.setRow(0,5,C[5]);
  lc.setRow(0,6,C[6]);
  lc.setRow(0,7,C[7]);
}

void printKey(char key){
  byte A[8]={B00000000,B00000000,B01111111,B10011000,B10011000,B01111111,B00000000,B00000000};
  byte B[8]={B00111000,B00100100,B00100100,B00111000,B00111000,B00100100,B00100100,B00111000};
  byte C[8]={B00011000,B00100100,B00100000,B00100000,B00100000,B00100000,B00100100,B00011000};
  byte D[8]={B00111000,B00100100,B00100100,B00100100,B00100100,B00100100,B00100100,B00111000};
  byte n0[8]={B00111100,B00100100,B00100100,B00100100,B00100100,B00100100,B00100100,B00111100};
  byte n1[8]={B00001000,B00011000,B00101000,B00001000,B00001000,B00001000,B00001000,B00001000};
  byte n2[8]={B00011000,B00100100,B00000100,B00001000,B00010000,B00100000,B00100000,B00111100};
  byte n3[8]={B00011000,B00100100,B00000100,B00011000,B00011000,B00000100,B00100100,B00011000};
  byte n4[8]={B00000100,B00001100,B00010100,B00100100,B00111100,B00000100,B00000100,B00000100};
  byte n5[8]={B00111100,B00100000,B00100000,B00111000,B00000100,B00000100,B00000100,B00111000};
  byte n6[8]={B00011000,B00100100,B00100000,B00100000,B00111000,B00100100,B00100100,B00011000};
  byte n7[8]={B00111100,B00000100,B00000100,B00001000,B00001000,B00010000,B00010000,B00010000};
  byte n8[8]={B00011000,B00100100,B00100100,B00011000,B00011000,B00100100,B00100100,B00011000};
  byte n9[8]={B00011000,B00100100,B00100100,B00011100,B00000100,B00000100,B00100100,B00011000};
  byte cross[8]={B00000000,B00010100,B01001000,B00111010,B01011100,B00010010,B00101000,B00000000};
  byte hashtag[8]={B00010100,B00010100,B01111110,B00100100,B00100100,B01111110,B00101000,B00101000};
  
  switch(key){
    case 'A':
      Serial.println(key);
      writeMatrix(A);
      break;
    case 'B':
      Serial.println(key);
      writeMatrix(B);
      break;
    case 'C':
      Serial.println(key);
      writeMatrix(C);
      break;
    case 'D':
      Serial.println(key);
      writeMatrix(D);
      break;
    case '0':
      Serial.println(key);
      writeMatrix(0);
      break;
    case '1':
      Serial.println(key);
      writeMatrix(1);
      break;
    case '2':
      Serial.println(key);
      writeMatrix(2);
      break;
    case '3':
      Serial.println(key);
      writeMatrix(3);
      break;
    case '4':
      Serial.println(key);
      writeMatrix(4);
      break;
    case '5':
      Serial.println(key);
      writeMatrix(5);
      break;
    case '6':
      Serial.println(key);
      writeMatrix(6);
      break;
    case '7':
      Serial.println(key);
      writeMatrix(7);
      break;
    case '8':
      Serial.println(key);
      writeMatrix(8);
      break;
    case '9':
      Serial.println(key);
      writeMatrix(9);
      break;
    case '*':
      Serial.println(key);
      writeMatrix(cross);
      break;
    case '#':
      Serial.println(key);
      writeMatrix(hashtag);
      break;
    default:
      break;
  }
}

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
  /* open a port to print */
  Serial.begin(9600);
}

void loop() {
  char customKey = customKeypad.getKey();
  if (customKey){
    lc.clearDisplay(0);
    printKey(customKey);
  }
}
