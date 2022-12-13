#include <MIDI.h>

#define DRUM1 0
#define PADS 7
#define CHANNEL 1
#define DEBOUNCE 30

MIDI_CREATE_DEFAULT_INSTANCE();

int sensitivity[PADS] = {1000, 1000, 1000, 1000, 1000, 800, 800};
int threshold[PADS] = {40, 40, 40, 40, 40, 150, 90};

unsigned long timer[PADS];
bool playing[PADS];
int highScore[PADS];
byte note[PADS] = {36,37,47,43,48,54,66};

void setup() {
  MIDI.begin(MIDI_CHANNEL_OFF);
  Serial.begin(115200);
  for (int x = 0; x < PADS; x++) {
    playing[x] = false;
    highScore[x] = 0;
    timer[x] = 0;
  }

}

void loop() {
  for (int x = 0; x < PADS; x++) {
    int volume = analogRead(x);
    //Serial.println(volume);
    if (volume >= threshold[x] && playing[x] == false) {
      if (millis() - timer[x] >= DEBOUNCE) {
        playing[x] = true;
        playNote(x, volume);
      }
    }
    else if (volume >= threshold[x] && playing[x] == true) {
      playNote(x, volume);
    }
    else if (volume < threshold[x] && playing[x] == true) {
      //Serial.println(highScore[x], DEC);
      
      MIDI.sendNoteOn(note[x], highScore[x], CHANNEL);
      MIDI.sendNoteOff(note[x], 0, CHANNEL);
      highScore[x] = 0;
      playing[x] = false;
      timer[x] = millis();
      //delay(20);
    }
  }
}

void playNote (int pad, int volume) {
  float velocity = ((volume) / float(sensitivity[pad] - threshold[pad])) * 128;
  if (velocity > 127) velocity = 127;
  if (velocity > highScore[pad]) highScore[pad] = velocity;
}
