#pragma once

#include "RtMidi.h"

#include <iostream>
#include <unistd.h>
#include <algorithm>

using namespace std;

struct SucceedingMessage_t {
	unsigned int index;
	unsigned int nFrequency;
};

struct MarkovMessage_t {
	vector<unsigned char> message;
	double stamp = 0;
	// Its own position in Markovmessages
	int pos;
	// Vector of messages succeeding this one (position in MarkovMessages and how frequent it is)
	vector<SucceedingMessage_t> succeedingMessages;
};

class MidiMarkov {
	public:
		int setup();
		int cleanup();

		void update();

	private:
		RtMidiIn *midiin = 0;

		vector<MarkovMessage_t> markovMessages;
		MarkovMessage_t curMarkovMessage;
		MarkovMessage_t prevMarkovMessage;
		int prevPosition = -1;

		void updateMarkovMessages();
		int getPositionInMarkovMessages(MarkovMessage_t &markovMessage);
		int getIndexInSucceedingMessages(MarkovMessage_t &markovMessage, int position);

		void addMessageToMarkovMessages(MarkovMessage_t &markovMessage);
		void printMarkovMessage(MarkovMessage_t &markovMessage);
		void printMarkovMessages();


};
