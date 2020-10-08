#include "tile.h"
#include "debugger.h"

//Constructors and destructors
tile::tile(){}

tile::tile(float _x, float _y){
	x = _x;
	y = _y;
}
tile::tile(float _x, float _y, ofColor _c){
	x = _x;
	y = _y;
	colour = _c;
}
tile::~tile(){}

//Getters and setters
float tile::getX(){ return x; }
float tile::getY(){ return y; }
float tile::getGridX(){ return gridX; }
float tile::getGridY(){ return gridY; }
ofColor tile::getColour(){ return colour; }
float tile::getSize(){ return size; }

void tile::setX( float _x){ x = _x; }
void tile::setY( float _y){ y = _y; }
void tile::setGridX( float _gridX){ gridX = _gridX; }
void tile::setGridY( float _gridY){ gridY = _gridY; }
void tile::setSize(float _size){ size = _size; }
void tile::setColour( ofColor _colour){ colour = _colour; }

void tile::draw(){
	//Set to correct colour and draw square
	ofSetColor(colour);
	ofDrawRectangle(x-(size/2.0),y-(size/2.0),size,size);
}

