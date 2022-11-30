#include <BLEMIDI_Transport.h>
#include <hardware/BLEMIDI_ESP32.h>

//BLEMIDI_CREATE_DEFAULT_INSTANCE()
 BLEMIDI_CREATE_INSTANCE("AWESOME_INSTRUMENT", MIDI)


const int btnPin = 13;
const int potPin = 15;

int midiNote;
int btnState;
int lastBtnState;


void setup() {
  pinMode(btnPin, INPUT_PULLUP);

  MIDI.begin();

}


void loop() {
  midiNote = map(analogRead(potPin), 0, 4095, 60, 80);

  lastBtnState = btnState;
  btnState = digitalRead(btnPin);

  if(lastBtnState == 1 && btnState == 0){
    MIDI.sendNoteOn(midiNote, 127, 1);
  }
  

}
