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
    win = false;

	//Setup grid vars
    g.setGH(9);
    g.setGW(9);
	g.autoSize();
	g.setLineColour(ofColor::fromHex(0xCCCCCC));
	g.createGrid();

    //Create the selected tile
    selectedTileX = selectedTileY = 4;

	//Setup completed, log
	debugger::log("Setup complete");
}

void ofApp::update(){
    //Handle keypresses, update selectedTile, check for win
    if(!win){
        handleKeypresses();
    }
    selectedTile = &g.getGameSpace()[selectedTileY][selectedTileX];
}

void ofApp::draw(){
    //Reset previous tile
    g.setTileColour(PrevSelectedTileX, PrevSelectedTileY, ofColor::black);
    if(win){
        ofSetColor(ofColor::black);
        ofDrawBitmapString("You win", 10, 10);
        for(int i = 0; i < g.getGH(); i++){
            for(int j = 0; j < g.getGW(); j++){
                g.setTileColour(i,j,ofColor::green);
            }
        }
    }
    //Set current tile colour
    g.setTileColour(selectedTileX,selectedTileY, ofColor::orange);

    //Draw grid
	g.drawGrid();
}

void ofApp::handleBounds(){
    //Check for out of bounds
    if(selectedTileX < 0){
        selectedTileX = 8;
    } else if(selectedTileX > 8){
        selectedTileX = 0;
    }

    if(selectedTileY < 0){
        selectedTileY = 8;
    } else if(selectedTileY > 8){
        selectedTileY = 0;
    }

    //debugger::log("SelectedTile X/Y: " + std::to_string(selectedTileX) + "/" + std::to_string(selectedTileY));
}

void ofApp::handleKeypresses(){
    if(keys[112]){
        PrevSelectedTileX = selectedTileX;
        PrevSelectedTileY = selectedTileY;
        selectedTileX = 0;
        selectedTileY = 0;

        for(int i = 1; i < 9; i++){
            g.setTileValue(i,0,i+1);
            g.setTileValue(0,i,i+1);
        }

        keys[112] = false;
    }

    // win = sudokuGame::check();
    //This method is called anytime a key is pressed
    //This means that we only need to ask if the player has won
    //whenever they press a key that results in a change

    //Value keys
    if(keys[49]){ //Number 1
        keys[49] = false;
        g.setTileValue(selectedTileX,selectedTileY,1);
        win = sudokuGame::check();
    } else if(keys[50]){ // Number 2
        keys[50] = false;
        g.setTileValue(selectedTileX,selectedTileY,2);
        win = sudokuGame::check();
    } else if(keys[51]){ // Number 3
        keys[51] = false;
        g.setTileValue(selectedTileX,selectedTileY,3);
        win = sudokuGame::check();
    } else if(keys[52]){ // Number 4
        keys[52] = false;
        g.setTileValue(selectedTileX,selectedTileY,4);
        win = sudokuGame::check();
    } else if(keys[53]){ // Number 5
        keys[53] = false;
        g.setTileValue(selectedTileX,selectedTileY,5);
        win = sudokuGame::check();
    } else if(keys[54]){ // Number 6
        keys[54] = false;
        g.setTileValue(selectedTileX,selectedTileY,6);
        win = sudokuGame::check();
    } else if(keys[55]){ // Number 7
        keys[55] = false;
        g.setTileValue(selectedTileX,selectedTileY,7);
        win = sudokuGame::check();
    } else if(keys[56]){ // Number 8
        keys[56] = false;
        g.setTileValue(selectedTileX,selectedTileY,8);
        win = sudokuGame::check();
    } else if(keys[57]){ // Number 9
        keys[57] = false;
        g.setTileValue(selectedTileX,selectedTileY,9);
        win = sudokuGame::check();
    }

    //Moving selected tile
    if(keys[119] or keys[57357]){
        PrevSelectedTileX = selectedTileX;
        PrevSelectedTileY = selectedTileY;
        keys[119] = false;
        keys[57357] = false;
        selectedTileX--;
        handleBounds();
    } else if(keys[97] or keys[57356]){
        PrevSelectedTileX = selectedTileX;
        PrevSelectedTileY = selectedTileY;
        keys[97] = false;
        keys[57356] = false;
        selectedTileY--;
        handleBounds();
    } if(keys[115] or keys[57359]){
        PrevSelectedTileX = selectedTileX;
        PrevSelectedTileY = selectedTileY;
        keys[115] = false;
        keys[57359] = false;
        selectedTileX++;
        handleBounds();
    } else if(keys[100] or keys[57358]){
        PrevSelectedTileX = selectedTileX;
        PrevSelectedTileY = selectedTileY;
        keys[100] = false;
        keys[57358] = false;
        selectedTileY++;
        handleBounds();
    }
}

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
