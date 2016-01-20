#pragma once
#include "ofThread.h"
#include "RtMidi.h"
#include "ofApp.h"

class threadDraw : public ofThread
{
public:
	threadDraw(ofBaseApp* const app);
	~threadDraw();
	void threadedFunction();
	void setMatrice(int matrice[9][9]);
	void magnitudeToMatrice(int magnitude[9]);
	void sendMidiMessage(int control, int channel, int data1, int data2);
	void startThread(bool mutexBlocks, int magnitude[9]);

	static const int OFF = 12;
	static const int RED_LOW = 13;
	static const int RED_FULL = 15;
	static const int GREEN_LOW = 28;
	static const int GREEN_FULL = 60;
	static const int AMBER_LOW = 29;
	static const int AMBER_FULL = 63;
	static const int YELLOW = 62;


private:
	void drawMatrice();
	RtMidiOut * midiout;
	vector<unsigned char> infoMidi;
	ofBaseApp* myApp;
	int magnitudePrec[9];
	int matrice[9][9];

};

