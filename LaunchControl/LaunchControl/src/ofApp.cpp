#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	thread = new threadDraw(this);
	//midiOut.listPorts();
	//midiOut.openPort(1);
	midiIn.listPorts();
	midiIn.openPort(0);
	midiIn.addListener(this);
	midiIn.setVerbose(true);

	ofSoundStream* stream = new ofSoundStream();
	vector<ofSoundDevice> mesDevices = stream->getDeviceList();
	for (ofSoundDevice i : mesDevices) {
		cout << i << endl;
	}

	stream->setDeviceID(2);
	stream->setup(0, 2, 44100, BUFFER_SIZE, 4);
	stream->setInput(this);

	left = new float[BUFFER_SIZE];
	right = new float[BUFFER_SIZE];

	for (int i = 0; i < NUM_WINDOWS; i++)
	{
		for (int j = 0; j < BUFFER_SIZE / 2; j++)
		{
			freq[i][j] = 0;
		}
	}

	for (int i = 0; i < 9; i++) {
		resultats[i] = 0;
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(80, 80, 20);
}

//--------------------------------------------------------------
void ofApp::draw(){
	static int index = 0;
	float avg_power = 0.0f;

	if (index < 80)
		index += 1;
	else
		index = 0;

	/* do the FFT	*/
	myfft.powerSpectrum(0, (int)BUFFER_SIZE / 2, left, BUFFER_SIZE, &magnitude[0], &phase[0], &power[0], &avg_power);

	/* start from 1 because mag[0] = DC component */
	/* and discard the upper half of the buffer */
	for (int j = 1; j < BUFFER_SIZE / 2; j++) {
		freq[index][j] = magnitude[j];
	}

	/* draw the FFT */
	float result[9];
	for (int i = 0; i < 9; i++) {
		result[i] = 0;
	}
	modifFFT(magnitude, result);

	for (int i = 0; i < 9; i++) {
		resultats[i] = result[i] * 1000;
		resultats[i] = resultats[i] / 10000;
	}

	if (!thread->isThreadRunning()) {
		((threadDraw*)thread)->startThread(true, resultats);
	}

}

void ofApp::newMidiMessage(ofxMidiMessage& eventArgs){
	cout << eventArgs.status << " " << eventArgs.value << " " << eventArgs.velocity << " " << eventArgs.pitch << " " << eventArgs.control << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::audioReceived(float * input, int bufferSize, int nChannels) {
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++) {
		left[i] = input[i * 2];
		right[i] = input[i * 2 + 1];
	}
	bufferCounter++;
}

void ofApp::modifFFT(float magnitude[], float result[]) {
	result[0] = (magnitude[1] + magnitude[2]) / 2;
	result[1] = (magnitude[3] + magnitude[4]) / 2;
	result[2] = (magnitude[5] + magnitude[6]) / 2;
	result[3] = (magnitude[7] + magnitude[8]) / 2;
	result[4] = (magnitude[7] + magnitude[8] + magnitude[9] + magnitude[10]) / 4;
	for (int i = 0; i < 6; i++) {
		result[5] += magnitude[i + 7];
		result[6] += magnitude[i + 13];
	}
	result[5] /= 6;
	result[6] /= 6;
	for (int i = 0; i < 10; i++) {
		result[7] += magnitude[i + 19];
		result[8] += magnitude[i + 29];
	}
	result[7] /= 10;
	result[8] /= 10;

	result[0] *= 2;
	result[1] *= 2;
	result[2] *= 4;
	result[3] *= 5;
	result[4] *= 6;
	result[5] *= 8;
	result[6] *= 10;
	result[7] *= 15;
	result[8] *= 15;
}

const int* ofApp::getResultat() const{

	return (const int*)resultats;
}