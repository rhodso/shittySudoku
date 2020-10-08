#pragma once

#include "ofMain.h"
#include "grid.h"
#include "tile.h"
#include "debugger.h"

class ofApp : public ofBaseApp{

public:
	//oF functions we're using
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	//Other methods
	void handleKeypresses();

	//Unused, but if we take them out then oF throws a hissy fit
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

private:
	bool keys[65535];       //Key array
	bool debug = true;      //Show/Hide debug info
	unsigned long long frameCount;  //Frame counter
		//Can store up to 9.749 billion years at 60FPS so no worries about it running out

	//Vars needed for the game
	grid g;

};
