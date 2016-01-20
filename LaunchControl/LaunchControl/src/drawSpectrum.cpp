#include "drawSpectrum.h"

drawSpectrum::drawSpectrum()
{
	//midiOut.listPorts();
	//midiOut.openPort(1);
	for (int i = 0; i < 9; i++) {
		previousFlow[i] = 0;
	}
}

void drawSpectrum::draw(int result[9]){
	for (int i = 0; i < 9; i++) {
		if (result[i] < previousFlow[i]) {

			int debutEffacement = (previousFlow[i]>8) ? 8 : previousFlow[i];
			int x = 9 - debutEffacement;
			drawRectangle(i, debutEffacement, x, 1, 12);
			previousFlow[i] --;
		}
		else {
			drawRectangle(i, 0, result[i], 1, 60);
			previousFlow[i] = result[i];
		}
	}
}

drawSpectrum::~drawSpectrum()
{
}

void drawSpectrum::printColor(int x, int y, int color) {
	bool command = false;
	int position = 0;
	if (x >= 0 && x <= 8 && y >= 0 && y <= 8) {
		if (y == 8)
			command = true; //Top line of launchpad is different. See http://d19ulaff0trnck.cloudfront.net/sites/default/files/novation/downloads/4080/launchpad-programmers-reference.pdf
		else
			command = false;
		if (y == 8)
			position = 104 + x;//Top line again.
		else
			position = (16 * (7 - y)) + x;
	}
	if (command) {
		midiOut.sendControlChange(1, position, color);
	}
	else {
		midiOut.sendNoteOn(1, position, color);
	}
}

void drawSpectrum::drawRectangle(int xBase, int yBase, int height, int width, int color) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printColor(xBase + j, yBase + i, color);
		}
	}
}