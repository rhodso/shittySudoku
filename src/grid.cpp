#include "grid.h"
#include "debugger.h"
#include <thread>
#include <vector>

//Constructor
grid::grid(){}
grid::~grid(){
	//Clear the gameSpace to avoid memory leaks
	gameSpace.clear();
}


//Getters and setters
bool grid::getDoUpdate(){ return doUpdate; }
std::vector<std::vector<tile>> grid::getGameSpace(){ return gameSpace; }
int grid::getGH(){ return gH; }
int grid::getGW(){ return gW; }
int grid::getOffsetX(){ return offsetX; }
int grid::getOffsetY(){ return offsetY; }
ofColor grid::getLineColour(){ return lineColour; }

void grid::setDoUpdate( bool _doUpdate){ doUpdate = _doUpdate; }
void grid::setGameSpace( std::vector<std::vector<tile>> _gameSpace){ gameSpace = _gameSpace; }
void grid::setGH( int _gH){ gH = _gH; }
void grid::setGW( int _gW){ gW = _gW; }
void grid::setOffsetX( int _offsetX){ offsetX = _offsetX; }
void grid::setOffsetY( int _offsetY){ offsetY = _offsetY; }
void grid::setLineColour( ofColor _lineColour){ lineColour = _lineColour; }

//Methods to allow other classes to interface with the grid easily
void grid::setTileColour(int _x, int _y, ofColor _colour){ gameSpace[_x][_y].setColour(_colour); }
ofColor grid::getTileColour(int _x, int _y){ return gameSpace[_x][_y].getColour(); }

//Other methods
void grid::createGrid(){
	//Log starting
	debugger::log("Creating new grid...");

	//Setting up the offset for the grid
	debugger::log("Setting vars");
	offsetX = (ofGetWidth()/2) - ((gW/2) * tile::getSize());
	offsetY = (ofGetHeight()/2) - ((gH/2) * tile::getSize());

	//Display vars
	std::string msg = "Height = "; msg += std::to_string(gH);
	debugger::log(msg);
	msg = "Width = "; msg += std::to_string(gW);
	debugger::log(msg);
	msg = "X offset = "; msg += std::to_string(offsetX);
	debugger::log(msg);
	msg = "Y offset = "; msg += std::to_string(offsetY);
	debugger::log(msg);
	msg = "Tile Size = "; msg += std::to_string(tile::getSize());
	debugger::log(msg);


	//Clear gameSpace
	gameSpace.clear();

	//Setup the tiles and add to gameSpace
	for(int i = 0; i < gH; i++){
		std::vector<tile> tmp;
		for(int j = 0; j < gW; j++){
			//Create tile and assign X/Y/black
			tile a = tile(((tile::getSize()*j) + offsetX), ((tile::getSize()*i) + offsetY), ofColor::black);
			a.setGridX(i);
			a.setGridY(j);

			//Push to back of tile queue
			tmp.push_back(a);
		}
		//Push completed "row" to back of tile vector
		gameSpace.push_back(tmp);
	}

	//Grid created, log
	debugger::log("Game created");
}

void grid::drawGrid(){
	//Tiles drawing setup
	ofFill();
	ofSetLineWidth(5);

	//Draw the tiles
	for(int i = 0; i < gW; i++){
		for(int j = 0; j < gH; j++){
			gameSpace[j][i].draw();
		}
	}

	//Lines drawing setup
	ofNoFill();
	ofSetLineWidth(5);
	ofSetColor(grid::getLineColour());
	float s = tile::getSize();

	//Draw the lines
	for(int i = 0; i < gH; i++){
		for(int j = 0; j < gW; j++){
			ofDrawRectangle(
						((s*j) + offsetX)-(s/2), //X
						((s*i) + offsetY)-(s/2), //Y
						s,    //Width
						s );  //Height
		}
	}
	ofFill();
}

void grid::resetGrid(){
	//This could be multithreaded if optimisations are needed
	for(int i = 0; i < gH; i++){
		for(int j = 0; j < gW; j++){
			setTileColour(i,j,ofColor::black);
		}
	}
}

void grid::autoSize(){
	//Find the maxWidth and maxHeight
	float border = 200.0;
	float maxWidth = (ofGetWindowWidth()-border) / gW;
	float maxHeight = (ofGetWindowHeight()-border) / gH;

	//Log the maxWidth and maxHeight
	debugger::log("maxWidth: " + std::to_string( (int) maxWidth));
	debugger::log("maxHeight: " + std::to_string( (int) maxHeight));

	//Set the size
	if(maxWidth < maxHeight){
		tile::setSize(maxWidth);
	} else {
		tile::setSize(maxHeight);
	}

	//Log what the size was set to
	debugger::log("tileSize set to " + std::to_string( (int) tile::getSize()));
}
