#include "tile.h"
#include "debugger.h"

//Class-only method
ofRectangle getBitmapStringBoundingBox(string _text);

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
int tile::getValue(){ return value; }

void tile::setX( float _x){ x = _x; }
void tile::setY( float _y){ y = _y; }
void tile::setGridX( float _gridX){ gridX = _gridX; }
void tile::setGridY( float _gridY){ gridY = _gridY; }
void tile::setSize(float _size){ size = _size; }
void tile::setColour( ofColor _colour){ colour = _colour; }
void tile::setValue(int _value){ value = _value; }

void tile::draw(){
	//Set to correct colour and draw square
	ofSetColor(colour);
    ofDrawRectangle(x-(size/2.0),y-(size/2.0),size,size);

    //Display value of the tile, if not 0
    if(1 != 0){

//        if(gridX == 0 and gridY == 0){
//            debugger::log("Tile value is " + std::to_string(value));
//        }

        //Get a string of the value, then calculate the bounding box
        std::string valStr = std::to_string(value);
        ofRectangle rect = getBitmapStringBoundingBox(valStr);

        //Assign the X/Y values of the tile to the bounding box
        rect.x = x;
        rect.y = y;

        //Calculate X/Y midpoint coords of each box
        float tileMidpointX = x + size/2;
        float tileMidpointY = y + size/2;
        float rectMidpointX = x + rect.width/2;
        float rectMidpointY = y + rect.height/2;

        //Increase the value of boundingBox X/Y so that the midpoints overlap
        rect.x = rect.x + std::abs(tileMidpointX - rectMidpointX);
        rect.y = rect.y + std::abs(tileMidpointY - rectMidpointY);

        //Bump it a bit
        rect.x -= 10;
        rect.y -= 0;

        //Draw white text if black background
        if(colour == ofColor::black){
            ofSetColor(ofColor::white);
        } else {
            ofSetColor(ofColor::black);
        }

        //Draw text
        ofDrawBitmapString(valStr, rect.x, rect.y);
    }
}

//Stolen from https://forum.openframeworks.cc/t/how-to-get-size-of-ofdrawbitmapstring/22578/7
ofRectangle getBitmapStringBoundingBox(string _text){
    vector<string> lines = ofSplitString(_text, "\n");
    int maxLineLength = 0;
    for(int i = 0; i < (int)lines.size(); i++) {
        // tabs are not rendered
        const string & line(lines[i]);
        int currentLineLength = 0;
        for(int j = 0; j < (int)line.size(); j++) {
            if (line[j] == '\t') {
                currentLineLength += 8 - (currentLineLength % 8);
            } else {
                currentLineLength++;
            }
        }
        maxLineLength = MAX(maxLineLength, currentLineLength);
    }

    int fontSize = 16;
    float leading = 1.7;
    int height = lines.size() * fontSize * leading - 1;
    int width = maxLineLength * fontSize;

    return ofRectangle(0,0,width, height);
}
