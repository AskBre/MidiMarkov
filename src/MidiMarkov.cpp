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
	updateMarkovMessages();
}

void MidiMarkov::updateMarkovMessages() {
	curMarkovMessage.stamp = midiin->getMessage(&curMarkovMessage.message);

	if(curMarkovMessage.message.size() > 0) {
		unsigned int curPosition = getPositionInMarkovMessages(curMarkovMessage);

		if(prevPosition != -1) {
			int index = getIndexInSucceedingMessages(markovMessages.at(prevPosition), curPosition);

			if(index == -1) {
				SucceedingMessage_t succeedingMessage;
				succeedingMessage.index = curPosition;
				succeedingMessage.nFrequency = 1;
				markovMessages.at(prevPosition).succeedingMessages.push_back(succeedingMessage);
			} else {
				markovMessages.at(prevPosition).succeedingMessages.at(index).nFrequency++;
			}
		}

		printMarkovMessages();
		prevPosition = curPosition;
	}

}

int MidiMarkov::getPositionInMarkovMessages(MarkovMessage_t &markovMessage) {
	for (int i=0; i<markovMessages.size();i++) {
		if (markovMessages.at(i).message == markovMessage.message){
			return i;
		}
	}

	markovMessage.pos = markovMessages.size();
	markovMessages.push_back(markovMessage);

	return markovMessage.pos;
}

int MidiMarkov::getIndexInSucceedingMessages(MarkovMessage_t &markovMessage, int position) {
	for (int i=0; i<markovMessage.succeedingMessages.size(); i++) {
		if(markovMessage.succeedingMessages.at(i).index == position){
			return i;
		}
	}

	return -1;
}

void MidiMarkov::addMessageToMarkovMessages(MarkovMessage_t &markovMessage) {
}

void MidiMarkov::printMarkovMessage(MarkovMessage_t &markovMessage) {
	int nBytes = markovMessage.message.size();
	cout << markovMessage.pos;

	for(int i=0; i<nBytes; i++) {
		cout << ": Byte " << i << " = " << (int)markovMessage.message[i] << ", ";
	}
	if(nBytes > 0) {
		cout << "stamp = " << markovMessage.stamp << endl; 
	}

	cout << "Succ: ";
	for(auto m : markovMessage.succeedingMessages) {
		cout << m.index << " ," << m.nFrequency << "; ";
	}
	cout << endl;

}

void MidiMarkov::printMarkovMessages() {
	for(int i=0;i<markovMessages.size();i++) {
		if(markovMessages.at(i).succeedingMessages.size()) {
			printMarkovMessage(markovMessages.at(i));
		}
	}
}
