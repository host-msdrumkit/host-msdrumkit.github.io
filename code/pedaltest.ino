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
bool hhpedal;

int digitalPin = 2; //CAMBIAR EL NÚMERO DE PIN POR EL QUE TENGA EL PEDAL ENCHUFADO.

void setup() {
  MIDI.begin(MIDI_CHANNEL_OFF);
  Serial.begin(115200);
  for (int x = 0; x < PADS; x++) {
    playing[x] = false;
    highScore[x] = 0;
    timer[x] = 0;
  }
  pinMode(digitalPin, INPUT); 

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
      if (x == 5){ //CAMBIAR 5 POR EL NÚMERO DEL HI-HAT (condición del hi-hat abierto)
        if (digitalRead(2) == LOW){
          MIDI.sendNoteOn(56, highScore[x], CHANNEL); //CAMBIAR EL 56 POR LA NOTA DEL HIHAT ABIERTO!
          MIDI.sendNoteOff(56, 0, CHANNEL); // EL 56, LO MISMO QUE EN LA LÍNEA ANTERIOR
        }
        else{
          MIDI.sendNoteOn(note[x], highScore[x], CHANNEL);
          MIDI.sendNoteOff(note[x], 0, CHANNEL);
        } //condición del hi-hat cerrado, seguimos como siempre
      }
      else{ //no estamos evaluando el hi-hat, seguimos como siempre
        MIDI.sendNoteOn(note[x], highScore[x], CHANNEL);
        MIDI.sendNoteOff(note[x], 0, CHANNEL);
      }
      highScore[x] = 0;
      playing[x] = false;
      timer[x] = millis();
      //delay(20);
    }
  }
}

//Es una solución un poco fea y el código es repetitivo, pero nos ahorramos manipular la lista de notas básica, lo que lo hace todo menos lioso yo creo.



void playNote (int pad, int volume) {
  float velocity = ((volume) / float(sensitivity[pad] - threshold[pad])) * 128;
  if (velocity > 127) velocity = 127;
  if (velocity > highScore[pad]) highScore[pad] = velocity;
}
