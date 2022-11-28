#pragma once

#include "RtMidi.h"

#include <iostream>
#include <unistd.h>
#include <chrono>
#include <algorithm>

using namespace std;

struct MarkovMessage_t {
	vector<unsigned char> message;
	double stamp = 0;
	// Its own position in Markovmessages
	int pos;
	// Vector of messages succeeding this one (position in MarkovMessages)
	vector<unsigned int> succeedingMessages;
};

class MidiMarkov {
	public:
		int setup();
		int cleanup();

		void update();

	private:
		RtMidiIn *midiin = 0;
		RtMidiOut *midiout = 0;

		vector<MarkovMessage_t> markovMessages;
		int prevPosition = -1;
		bool prevIsLongNote = false;
		int playIndex = 0;
		chrono::time_point<chrono::high_resolution_clock> prevTime;

		void updateMarkovMessages();
		void iterateMarkovChain();
		int getPositionInMarkovMessages(MarkovMessage_t &markovMessage);

		void printMarkovMessage(MarkovMessage_t &markovMessage);
		void printMarkovMessages();
};
