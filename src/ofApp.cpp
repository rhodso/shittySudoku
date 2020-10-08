#include "ofApp.h"

void ofApp::setup(){
	//Setup variables
	srand (time(NULL));
	grid::setDoUpdate(true);
	debugger::setDebug(debug);

	//Log that app has started
	debugger::log("App started");

	//Setup game vars
	frameCount = 0;

	//Setup grid vars
	g.setGH(10);
	g.setGW(10);
	g.autoSize();
	g.setLineColour(ofColor::fromHex(0xCCCCCC));
	g.createGrid();

	//Setup completed, log
	debugger::log("Setup complete");
}

void ofApp::update(){}

void ofApp::draw(){
	g.drawGrid();
}

void ofApp::handleKeypresses(){}

void ofApp::keyPressed(int key){
	//Log key press
	std::string msg = "Key "; msg += key; msg += "("; msg += std::to_string(key); msg += ")"; msg += " pressed on frame "; msg += std::to_string(frameCount);
	debugger::log(msg);

	//Show specified key as being pressed
	keys[key] = true;
}

//Not used
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}
