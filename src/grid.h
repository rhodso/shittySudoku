#ifndef GRID_H
#define GRID_H

#include "ofMain.h"
#include "tile.h"

class grid
{
public:
	//Constructor and Deconstructor
	grid();
	~grid();

	//Getters and Setters
	static bool getDoUpdate();
	static std::vector<std::vector<tile>> getGameSpace();
	static int getGH();
	static int getGW();
	static int getOffsetX();
	static int getOffsetY();
	static ofColor getLineColour();

	static void setDoUpdate( bool _doUpdate );
	static void setGameSpace( std::vector<std::vector<tile>> _gameSpace );
	static void setGH( int _gH );
	static void setGW( int _gW );
	static void setOffsetX( int _offsetX );
	static void setOffsetY( int _offsetY );
	static void setLineColour( ofColor _lineColour );

	//Methods for interfacing with the grid's colours
	static void setTileColour(int _x, int _y, ofColor _colour);
	static ofColor getTileColour(int _x, int _y);

	//Other methods
	void createGrid();
	void drawGrid();
	static void resetGrid();
	static void autoSize();

private:

	//Wheather to update the game or not
	inline static bool doUpdate;

	//2D vector for holding all the tiles
	inline static std::vector<std::vector<tile>> gameSpace;

	inline static int gH = 30; //Game Height
	inline static int gW = 30; //Game Width
	inline static int offsetX; //Offset on the X axis
	inline static int offsetY; //Offset on the Y axis

	//Colour for the lines that seperate tiles for the grid
	inline static ofColor lineColour = ofColor::white;

};

#endif // GRID_H
