#pragma once

#include "RtMidi.h"

#include <iostream>
#include <unistd.h>

using namespace std;

class MidiMarkov {
	public:
		int setup();
		int cleanup();

		void update();
		
	private:
		RtMidiIn *midiin = 0;
		std::vector<unsigned char> message;
		double stamp;
		int nBytes, i;
};
