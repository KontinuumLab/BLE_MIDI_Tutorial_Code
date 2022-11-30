#include <BLEMIDI_Transport.h>
#include <hardware/BLEMIDI_ESP32.h>

BLEMIDI_CREATE_DEFAULT_INSTANCE()
// BLEMIDI_CREATE_INSTANCE("AWESOME_INSTRUMENT", MIDI)


const int btnPin = 13;
const int potPin = 15;
const int potPin2 = 2;

int midiNote;
int btnState;
int lastBtnState;
int velocity;

void setup() {
  pinMode(btnPin, INPUT_PULLUP);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); 
  
  BLEMIDI.setHandleConnected(onConnected);
  BLEMIDI.setHandleDisconnected(onDisconnected);

  MIDI.begin();

}


void loop() {
  
  lastBtnState = btnState;
  btnState = digitalRead(btnPin);
  velocity = map(analogRead(potPin2), 0, 4095, 0, 127);
  
  if(lastBtnState == 1 && btnState == 0){
    midiNote = map(analogRead(potPin), 0, 4095, 60, 80);
    MIDI.sendNoteOn(midiNote, velocity, 1);
  }

  else if(lastBtnState == 0 && btnState == 1){
    MIDI.sendNoteOff(midiNote, 0, 1);
  }

}


void onConnected() {
  digitalWrite(LED_BUILTIN, HIGH);
}
void onDisconnected() {
  digitalWrite(LED_BUILTIN, LOW);
}
