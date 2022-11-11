#include "MidiMarkov.h"

int MidiMarkov::setup() {
	try {
		midiin = new RtMidiIn();
	} catch (RtMidiError &error) {
		// Handle the exception here
		error.printMessage();
	}

	midiin->openVirtualPort();
	midiin->ignoreTypes(false, false, false);

	return 0;
}

int MidiMarkov::cleanup() {
	delete midiin;

	return 0;
}

void MidiMarkov::update() {
	stamp = midiin->getMessage(&message);
	nBytes = message.size();

	for(i=0; i<nBytes; i++) {
		cout << "Byte " << i << " = " << (int)message[i] << ", ";
	}
	if(nBytes > 0) {
		cout << "stamp = " << stamp << endl; 
	}

}
