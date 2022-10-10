#include <Arduino.h>
#include <Control_Surface.h>


HardwareSerialMIDI_Interface midi{Serial2, MIDI_BAUD};
const MIDIAddress address{02, CHANNEL_3, CABLE_1};

// Custom MIDI callback that prints incoming messages.
/*struct MyMIDI_Callbacks : MIDI_Callbacks {

  // Callback for channel messages (notes, control change, pitch bend, etc.).
  void onChannelMessage(MIDI_Interface &, ChannelMessage cm) override {
    // Print the message
    Serial << F("Channel message: ") << hex << cm.header << ' ' << cm.data1
           << ' ' << cm.data2 << dec << F(" on cable ")
           << cm.cable.getOneBased() << endl;
  }
} callback;*/

uint32_t currentMillis = 0, previousMillis = 0, interval = 1000;
int value = 0;
int button_input[4] = {0, 0, 0, 0};
void setup() {
	Serial.begin(115200); // For printing the messages
	Serial.println("GO");
	midi.begin();                // Initialize the MIDI interface
	//midi.setCallbacks(callback); // Attach the custom callback
	pinMode(12, INPUT_PULLDOWN);
	pinMode(13, INPUT_PULLDOWN);
	pinMode(14, INPUT_PULLDOWN);
	pinMode(15, INPUT_PULLDOWN);
}

void loop() {
	midi.update();
	button_input[0] = digitalRead(12);
	button_input[1] = digitalRead(13);
	button_input[2] = digitalRead(14);
	button_input[3] = digitalRead(15);
	if ( (button_input[0] + button_input[1] + button_input[2] + button_input[3]) == 1){
		if(button_input[0] == 1){
			midi.sendControlChange(address, 0x00); //left panorama
			Serial.println("Taster 1 gedrückt");
		}
		if(button_input[1] == 1){
			midi.sendControlChange(address, 0x7F); //right panorama
			Serial.println("Taster 2 gedrückt");
		}
		if(button_input[2] == 1){
			//midi.sendControlChange(address, value); //nothig
			Serial.println("Taster 3 gedrückt");
		}
		if(button_input[3] == 1){
			midi.sendControlChange(address, 0x3F); //center panorama
			Serial.println("Taster 4 gedrückt");
		}
		delay(200); //Contact bounce wait
	}
}