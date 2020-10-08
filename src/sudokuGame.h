//Header file auto-generated using CPP-Getter-Setter-Generator
#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H

//Includes
#include "tile.h"
#include "grid.h"
#include "debugger.h"
#include "thread"

class sudokuGame {
	public:
		//Constructor and Destructor
		sudokuGame();
		~sudokuGame();

		//Getters and Setters
		int getDifficulty();

		void setDifficulty( int _difficulty );

		//Other methods
        static bool check();
        static void checkCols();
        static void checkSquares();
        static void checkRows();
        static bool checkOne(std::vector<tile> tileList);
        void generateNew();

	private:
		//Variables
		int difficulty;
        static inline bool doneCheck;
        static grid g;
        static inline std::mutex mtx;
};
#endif
