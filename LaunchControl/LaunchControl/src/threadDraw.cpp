#include "threadDraw.h"



threadDraw::threadDraw(ofBaseApp* const app)
{
	myApp = app;
	midiout = new RtMidiOut();
	midiout->openPort(1);
	infoMidi.push_back(0);
	infoMidi.push_back(0);
	infoMidi.push_back(0);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			matrice[i][j] = OFF;
		}
	}

	for (int i = 0; i < 9; i++) {
		magnitudePrec[i] = 0;
	}
}


threadDraw::~threadDraw()
{
}

void threadDraw::threadedFunction() {
	drawMatrice();
}

void threadDraw::setMatrice(int newMatrice[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			matrice[i][j] = newMatrice[i][j];
		}
	}
}

void threadDraw::drawMatrice() {
	sendMidiMessage(144, 1, 0, 0);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j = j+2) {
			sendMidiMessage(144, 3, matrice[j][7-i], matrice[j + 1][7-i]);
		}
	}
	for (int i = 0; i < 8; i = i + 2) {
		sendMidiMessage(144, 3, matrice[8][7 - i], matrice[8][7 - i - 1]);
	}
	for (int i = 0; i < 8; i=i+2) {
		sendMidiMessage(144, 3, matrice[i][8], matrice[i+1][8]);
	}
}

void threadDraw::magnitudeToMatrice(int magnitude[9]) {
	for (int i = 0; i < 9; i++) {
		if (magnitude[i] < magnitudePrec[i]) magnitude[i] = magnitudePrec[i] - 1;
		magnitudePrec[i] = magnitude[i];
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			matrice[i][j] = OFF;
		}
	}

	for (int j = 0; j < magnitude[0]; j++) {
		matrice[0][j] = 15;
	}
	for (int j = 0; j < magnitude[1]; j++) {
		matrice[1][j] = 31;
	}
	for (int j = 0; j < magnitude[2]; j++) {
		matrice[2][j] = 47;
	}
	for (int j = 0; j < magnitude[3]; j++) {
		matrice[3][j] = 63;
	}
	for (int j = 0; j < magnitude[4]; j++) {
		matrice[4][j] = 63;
	}
	for (int j = 0; j < magnitude[5]; j++) {
		matrice[5][j] = 62;
	}
	for (int j = 0; j < magnitude[6]; j++) {
		matrice[6][j] = 61;
	}
	for (int j = 0; j < magnitude[7]; j++) {
		matrice[7][j] = 60;
	}
	for (int j = 0; j < magnitude[8]; j++) {
		matrice[8][j] = 60;
	}
}

void threadDraw::sendMidiMessage(int control, int channel, int data1, int data2) {
	lock();
	infoMidi[0] = channel - 1 + control;
	infoMidi[1] = data1;
	infoMidi[2] = data2;
	midiout->sendMessage(new vector<unsigned char>(infoMidi));
	unlock();
}

void threadDraw::startThread(bool mutexBlocks, int magnitude[9]) {
	magnitudeToMatrice(magnitude);
	ofThread::startThread(mutexBlocks);
}