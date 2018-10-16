/***************************************************
  This is an example for the Adafruit VS1053 Codec Breakout

  Designed specifically to work with the Adafruit VS1053 Codec Breakout
  ----> https://www.adafruit.com/products/1381

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/
//--------------------------------------------------
// sound device related
//--------------------------------------------------
// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// These are the pins used for the breakout example
#define BREAKOUT_RESET  9      // VS1053 reset pin (output)
#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)
// These are the pins used for the music maker shield
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer =
  // create breakout-example object!
  Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
// create shield-example object!
// Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);



//------------------------------------------------

//------------------------------------------------

#include <Adafruit_NeoPixel.h>
#define PIXELNUMBER 8
#define CHANNELNUMBER 4

int A_Pin[] = {24, 26, 28, 30};
int B_Pin[] = {25, 27, 29, 31};
int mode_Pin = 32;
int sensorPin[] = {A0, A1, A2, A3};
int NeoPixelPin[] = {33, 34, 35, 36};

int sensorValue[CHANNELNUMBER];
bool A_buttonStatus[CHANNELNUMBER];
bool last_A_buttonStatus[CHANNELNUMBER];
bool B_buttonStatus[CHANNELNUMBER];
bool last_B_buttonStatus[CHANNELNUMBER];

int sensorMin[CHANNELNUMBER] = {0, 0, 0, 0};
int sensorMax[CHANNELNUMBER] = {1023, 1023, 1023, 1023};
int trackNum[CHANNELNUMBER] = {0, 1, 2, 3};
String trackName[8] = {"track001.mp3", "track002.mp3", "track003.mp3", "track004.mp3", "track005.mp3", "track006.mp3", "track007.mp3", "track008.mp3"};


long doubleClickMarker[CHANNELNUMBER];
long doubleClickMarkerB[CHANNELNUMBER];

long calibrationMarker[CHANNELNUMBER];

int longPressCntr[CHANNELNUMBER];

int mode[CHANNELNUMBER] = {0, 0, 0, 0};
//-----------
// mode0: play
// mode1: reset
// mode2: calibration
// mode3: track select
//-----------

int playMode = 0;
int lastPlayMode;
//-----------
// mode1: play trigger
// mode0: play volume
//-----------

bool playSound = true;
long playCntr;
int playNum;

int on_LED = 2;

Adafruit_NeoPixel strip[] = {Adafruit_NeoPixel(PIXELNUMBER, 33, NEO_GRB + NEO_KHZ800), Adafruit_NeoPixel(PIXELNUMBER, 34, NEO_GRB + NEO_KHZ800), Adafruit_NeoPixel(PIXELNUMBER, 35, NEO_GRB + NEO_KHZ800), Adafruit_NeoPixel(PIXELNUMBER, 36, NEO_GRB + NEO_KHZ800)};



// the setup routine runs once when you press reset:
void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  //-----------------------------------------------------
  // music player initialization
  //-----------------------------------------------------
  // initialise the music player
  if (! musicPlayer.begin()) { // initialise the music player
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1);
  }
  Serial.println(F("VS1053 found"));

  //musicPlayer.sineTest(0x44, 500);    // Make a tone to indicate VS1053 is working

  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }
  Serial.println("SD OK!");

  // list files
  printDirectory(SD.open("/"), 0);

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(150, 150);

  if (! musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT))
    Serial.println(F("DREQ pin is not an interrupt pin"));



  //-----------------------------------------------------
  // initialize pins
  //-----------------------------------------------------

  pinMode (mode_Pin, INPUT_PULLUP);
  pinMode (on_LED, OUTPUT);
  digitalWrite(on_LED, HIGH);

  for (int i = 0; i < CHANNELNUMBER; i++) {
    pinMode(A_Pin[i], INPUT_PULLUP);
    pinMode(B_Pin[i], INPUT_PULLUP);

    //-----------------------------------------------------
    // initialize neoPixel display
    //-----------------------------------------------------
    strip[i].begin();
    strip[i].setBrightness(20);
    strip[i].show(); // Initialize all pixels to 'off'
  }


  Serial.println("init");
}

// the loop routine runs over and over again forever:
void loop() {

  playMode = digitalRead(mode_Pin);

  for (int i = 0; i < CHANNELNUMBER; i++) {
    A_buttonStatus[i] = digitalRead(A_Pin[i]);
    B_buttonStatus[i] = digitalRead(B_Pin[i]);

    //----------------------------
    // check the button A behavior
    //----------------------------
    if (!A_buttonStatus[i]) {
      if (A_buttonStatus[i] != last_A_buttonStatus[i]) {

        if ( millis() - doubleClickMarker[i] < 500) {
          //double click
          Serial.println("reset");
          mode[i] = 1;
        }
        else {
          // mark the pressed time
          doubleClickMarker[i] = millis();

        }
      }
      else {
        longPressCntr[i]++;
        if ( longPressCntr[i] > 100 && mode[i] != 2) {
          Serial.println("calibrate");
          mode[i] = 2;
          sensorMin[i] = 1023;
          sensorMax[i] = 0;
          calibrationMarker[i] = millis();
          longPressCntr[i] = 0;
        }
      }
    }
    else longPressCntr[i] = 0;

    last_A_buttonStatus[i] = A_buttonStatus[i];

    //----------------------------
    // check the button B behavior
    //----------------------------
    if (B_buttonStatus[i] != last_B_buttonStatus[i]) {
      if (!B_buttonStatus[i]) {
        if ( millis() - doubleClickMarkerB[i] < 500) {
          //double click
          mode[i] = 3;
          delay(100);
        }
        else {
          // mark the pressed time
          doubleClickMarkerB[i] = millis();
        }
      }
    }
    last_B_buttonStatus[i] = B_buttonStatus[i];


    switch (mode[i]) {
      case 0: // play sound
        // reading textile sensor and maping to display range of 8
        sensorValue[i] = analogRead(sensorPin[i]);
        sensorValue[i] = constrain(sensorValue[i], sensorMin[i], sensorMax[i]);
        sensorValue[i] = map(sensorValue[i], sensorMin[i], sensorMax[i], 0, 255);

        displayPixel(i, 0, sensorValue[i]);
        musicPlayMode(i, sensorValue[i]);
        break;

      case 1: // reset

        sensorMin[i] = 0;
        sensorMax[i] = 1023;
        for (int t = 0; t < 5; t++) {
          strip[i].setPixelColor(0, strip[i].Color(0, 0, 255));
          strip[i].show();
          delay(100);
          strip[i].setPixelColor(0, strip[i].Color(0, 0, 0));
          strip[i].show();
          delay(100);
        }
        longPressCntr[i] = 0;
        mode[i] = 0;
        break;

      case 2:// calibrate

        sensorValue[i] = analogRead(sensorPin[i]);
        if (sensorValue[i] > sensorMax[i]) {
          sensorMax[i] = sensorValue[i];
        }
        if (sensorValue[i] < sensorMin[i]) {
          sensorMin[i] = sensorValue[i];
        }
        sensorValue[i] = constrain(sensorValue[i], sensorMin[i], sensorMax[i]);
        sensorValue[i] = map(sensorValue[i], sensorMin[i], sensorMax[i], 0, 255);
        displayPixel(i, 2, sensorValue[i]);
        // if the time passes more than 5 sec, then return to play mode
        if (millis() - calibrationMarker[i] > 5000) {
          sensorMin[i] = sensorMin[i] + 100;
          sensorMax[i] = sensorMax[i] - 50;
          mode[i] = 0;
        }
        break;

      case 3: // select track
        // show the current track number
        displayPixel(i, 3, trackNum[i]);


        for (int t = 0; t < 500; t++) {
          B_buttonStatus[i] = digitalRead(B_Pin[i]);
          A_buttonStatus[i] = digitalRead(A_Pin[i]);
          if (B_buttonStatus[i] != last_B_buttonStatus[i] && !B_buttonStatus[i]) {
            trackNum[i]++;
            trackNum[i] = trackNum[i] % 8;
            displayPixel(i, 3, trackNum[i]);
          }
          last_B_buttonStatus[i] = B_buttonStatus[i];
          if (A_buttonStatus[i] != last_A_buttonStatus[i] && !A_buttonStatus[i]) {
            trackNum[i]--;
            trackNum[i] = trackNum[i] % 8;
            displayPixel(i, 3, trackNum[i]);
          }
          last_A_buttonStatus[i] = A_buttonStatus[i];
          delay(10);
        }
        mode[i] = 0;
        break;
    }


  }

  //comment out the below to print the sensor values
  debugPrint();
  delay(10);        // delay in between reads for stability
}


void displayPixel(int stripNum, int modeNum, int val) {
  int R;
  int G;
  int B;
  int LED;
  int intensity;

  // decide on the color
  switch (modeNum) {
    case 0:
      R = 255;
      G = 255;
      B = 255;
      // calculate which LED to light up
      LED = val / 28 ; // deviding into 0-8 LED

      // trigger mode
      if (playMode == 1) {
        for (int m = 0; m < 8; m++) {
          if (m < LED) {
            if (m > 3) {
              // after the sound is triggered, change the color
              G = 0;
            }
            strip[stripNum].setPixelColor(m, strip[stripNum].Color(R, G, B));
          }
          else {
            strip[stripNum].setPixelColor(m, strip[stripNum].Color(0, 0, 0));
          }
        }
      }

      // volume mode
      if (playMode == 0) {
        R = 255;
        G = 255;
        B = 255;
        for (int m = 0; m < 8; m++) {
          if (m < LED) {
            if (m > 1) {
              // after the sound is triggered, change the color
              R = 0;
              G = 128;
              B = 22;
            }
            strip[stripNum].setPixelColor(m, strip[stripNum].Color(R, G, B));
          }
          else {
            strip[stripNum].setPixelColor(m, strip[stripNum].Color(0, 0, 0));
          }
        }
      }
      strip[stripNum].show();
      break;

    case 2:
      R = 0;
      G = 255;
      B = 255;
      // calculate which LED to light up
      LED = val / 28;

      for (int m = 0; m < 8; m++) {
        if (m < LED) {
          strip[stripNum].setPixelColor(m, strip[stripNum].Color(R, G, B));
        }
        else {
          strip[stripNum].setPixelColor(m, strip[stripNum].Color(0, 0, 0));
        }
      }
      strip[stripNum].show();
      break;

    case 3:
      R = 0;
      G = 255;
      B = 0;

      for (int m = 0; m < 8; m++) {
        if (m == val) {
          strip[stripNum].setPixelColor(m, strip[stripNum].Color(R, G, B));
        }
        else {
          strip[stripNum].setPixelColor(m, strip[stripNum].Color(0, 0, 0));
        }
      }
      strip[stripNum].show();
      break;
  }
}


/// File listing helper
void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      //Serial.println("**nomorefiles**");
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}


void musicPlayMode( int channelNum, int val) {
  // if the mode has been changed, stop playing the sample
if (playMode!=lastPlayMode){
  musicPlayer.stopPlaying();
}
lastPlayMode=playMode;
  
  switch (playMode) {
    case 1: // trigger
      if (val > 128) {
        if (playNum != channelNum) {
          if (musicPlayer.playingMusic) {
            musicPlayer.stopPlaying();
          }

          if (!musicPlayer.playingMusic) {
            musicPlayer.setVolume(30, 30);
            // choose the file name of the sound
            char filename[15];
            trackName[trackNum[channelNum]].toCharArray(filename, 15);
            // play the soundfile
            musicPlayer.startPlayingFile(filename);
            // mark which channgel is playing
            playNum = channelNum;
          }
        }
      }
      if (val < 50) {
        if (playNum == channelNum) {
          //  musicPlayer.stopPlaying();
          playNum = 10; // out of range num as placeholder
        }
      }
      break;

    case 0: // volume
      if (val > 64) {
        if (playNum != channelNum) {
          //          if (musicPlayer.playingMusic) {
          //            musicPlayer.stopPlaying();
          //          }

          if (!musicPlayer.playingMusic) {
            // choose the file name of the sound
            char filename[15];
            trackName[trackNum[channelNum]].toCharArray(filename, 15);
            // play the soundfile
            musicPlayer.startPlayingFile(filename);

            // mark which channgel is playing
            playNum = channelNum;
          }
        }

        if (musicPlayer.playingMusic) {
          if (playNum == channelNum) {

            int vol = map(val, 64,  255, 120, 30);
            vol = constrain(vol, 30, 120);
            musicPlayer.setVolume(vol, vol);
          }
        }
      }

      // if the sensor value is lower than threshold
      if (val < 50) {
        if (playNum == channelNum) {
          musicPlayer.stopPlaying();
          playNum = 10; // out of range num as placeholder
        }
      }
      break;
  }
}

void debugPrint() {

  Serial.print("sensor0: ");
  Serial.print(sensorValue[0]);
  Serial.print("\t");
  Serial.print("sensor1: ");
  Serial.print(sensorValue[1]);
  Serial.print("\t");
  Serial.print("sensor2: ");
  Serial.print(sensorValue[2]);
  Serial.print("\t");
  Serial.print("sensor3: ");
  Serial.print(sensorValue[3]);

  Serial.println();


}

