#include "ofxMidi.h"

class drawSpectrum
{
public:
	drawSpectrum();
	~drawSpectrum();
	void draw(int result[9]);
	void printColor(int x, int y, int color);
	void drawRectangle(int xBase, int yBase, int height, int width, int color);

	static const int OFF = 12;
	static const int RED_LOW = 13;
	static const int RED_FULL = 15;
	static const int GREEN_LOW = 28;
	static const int GREEN_FULL = 60;
	static const int AMBER_LOW = 29;
	static const int AMBER_FULL = 63;
	static const int YELLOW = 62;

private:
	int previousFlow[9];
	ofxMidiOut midiOut;
};
