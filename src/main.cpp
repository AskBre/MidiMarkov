#include "MidiMarkov.h"

int main() {
	MidiMarkov midiMarkov;

	midiMarkov.setup();

	while(true) {
		midiMarkov.update();
		usleep(10);
	}

	return 0;
}

