#pragma once

#include "ofMain.h"
#include "fft.h"
#include "ofxMidi.h"
#include "ofMain.h"
#include "threadDraw.h"


#define BUFFER_SIZE 256
#define NUM_WINDOWS 80

class ofApp : public ofBaseApp, public ofxMidiListener{

	public:

		static const int OFF = 12;
		static const int RED_LOW = 13;
		static const int RED_FULL = 15;
		static const int GREEN_LOW = 28;
		static const int GREEN_FULL = 60;
		static const int AMBER_LOW = 29;
		static const int AMBER_FULL = 63;
		static const int YELLOW = 62;

		void setup();
		void update();
		void draw();

		void newMidiMessage(ofxMidiMessage& eventArgs);
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void audioReceived(float * input, int bufferSize, int nChannels);
		void modifFFT(float magnitude[], float result[]);
		const int* getResultat() const;
		
	private:
		float * left;
		float * right;
		int 	bufferCounter;
		fft		myfft;	
		ofThread* thread;
		float magnitude[BUFFER_SIZE];
		float phase[BUFFER_SIZE];
		float power[BUFFER_SIZE];
		int resultats[9];

		float freq[NUM_WINDOWS][BUFFER_SIZE / 2];
		float freq_phase[NUM_WINDOWS][BUFFER_SIZE / 2];
		ofxMidiIn midiIn;
};
