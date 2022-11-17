#include "MidiMarkov.h"

int main() {
	MidiMarkov midiMarkov;

	midiMarkov.setup();

	while(true) {
		midiMarkov.update();
		usleep(1);
	}

	return 0;
}

