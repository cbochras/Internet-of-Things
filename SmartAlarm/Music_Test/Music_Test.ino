#include <SPI.h>
#include <SD.h>
#include <Adafruit_VS1053.h>
 
  #define VS1053_RESET   -1     // VS1053 reset pin (not used!)
  #define VS1053_CS      16     // VS1053 chip select pin (output)
  #define VS1053_DCS     15     // VS1053 Data/command select pin (output)
  #define CARDCS          2     // Card chip select pin
  #define VS1053_DREQ     0     // VS1053 Data request, ideally an Interrupt pin

  Adafruit_VS1053_FilePlayer musicPlayer = 
  Adafruit_VS1053_FilePlayer(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARDCS);
  
void setup() {
  musicPlayer.begin();
  SD.begin(CARDCS);
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);
  musicPlayer.sineTest(0x44, 500);    // Make a tone to indicate VS1053 is working
  musicPlayer.setVolume(5,5);
  musicPlayer.startPlayingFile("track001.mp3");
}

void loop() {

}
