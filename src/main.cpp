#include <Arduino.h>
#include <Control_Surface.h>


HardwareSerialMIDI_Interface midi {Serial2, MIDI_BAUD};
const MIDIAddress address {02, CHANNEL_3, CABLE_1};

// Custom MIDI callback that prints incoming messages.
struct MyMIDI_Callbacks : MIDI_Callbacks {

  // Callback for channel messages (notes, control change, pitch bend, etc.).
  void onChannelMessage(MIDI_Interface &, ChannelMessage cm) override {
    // Print the message
    Serial << F("Channel message: ") << hex << cm.header << ' ' << cm.data1 << ' ' << cm.data2 << dec << F(" on cable ") << cm.cable.getOneBased() << endl;
  }
} callback;

uint32_t currentMillis = 0, previousMillis = 0, interval = 1000;
int value = 0;
void setup() {
  Serial.begin(115200);        // For printing the messages
  Serial.println("GO");
  midi.begin();                // Initialize the MIDI interface
  midi.setCallbacks(callback); // Attach the custom callback

}

void loop() {
    midi.update();
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        // save the last time you blinked the LED
        previousMillis = currentMillis;
        if(value == 0){
          midi.sendControlChange(address,value);
          value = 0x7f;
        }
        else{
          midi.sendControlChange(address,value);
          value = 0x00;
        }
    }
}