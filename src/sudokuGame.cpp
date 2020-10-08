//Source file auto-generated using CPP-Getter-Setter-Generator

//Includes
#include "sudokuGame.h"

//Constructor and Destructor
sudokuGame::sudokuGame(){}
sudokuGame::~sudokuGame(){}

//Getters and Setters
int sudokuGame::getDifficulty(){ return difficulty; }

void sudokuGame::setDifficulty( int _difficulty){ difficulty = _difficulty; }

//Other methods
bool sudokuGame::check(){
    debugger::log("Started check");
    std::vector<std::thread> checkem;
    doneCheck = true;

    checkem.push_back(std::thread(checkCols));
    checkem.push_back(std::thread(checkRows));
    checkem.push_back(std::thread(checkSquares));

    for(std::thread &t : checkem){
        t.join();
    }

    return doneCheck;

}
void sudokuGame::checkCols(){
    debugger::log("Started checkCols");
    //Get a copy of the game space
    mtx.lock();
    std::vector<std::vector<tile>> gs = g.getGameSpace();
    mtx.unlock();

    debugger::log("Cols: Got gs");

    //For each column in the space
    for(int i = 0; i < g.getGW(); i++){
        debugger::log("Cols: " + std::to_string(i));
        vector<tile> v; //Create a vector
        for(int j = 0; j < g.getGH(); j++){
            v.push_back(gs[i][j]); //Add all the tiles in the column
        }
        mtx.lock();
        debugger::log("Cols: Started checking 'em");
        if(!checkOne(v)){ //Check 'em
            debugger::log("Cols: Checked 'em");
           doneCheck = false; //return false if there's a problem
        }
        mtx.unlock();
    }
    debugger::log("Finished checkCols");
}
void sudokuGame::checkSquares(){
    debugger::log("Started checkSquares");
    //Get a copy of the game space
    mtx.lock();
    std::vector<std::vector<tile>> gs = g.getGameSpace();
    mtx.unlock();

    debugger::log("Squares: Got gs");

    for(int i = 0; i < g.getGH(); i+=3){
        debugger::log("Squares: " + std::to_string(i));
        vector<tile> v;
        for(int j = 0; j < g.getGW(); j+= 3){
            v.push_back(gs[i][j]);
            v.push_back(gs[i+1][j]);
            v.push_back(gs[i+2][j]);

            v.push_back(gs[i][j+1]);
            v.push_back(gs[i+1][j+1]);
            v.push_back(gs[i+2][j+1]);

            v.push_back(gs[i][j+2]);
            v.push_back(gs[i+1][j+2]);
            v.push_back(gs[i+2][j+2]);
        }
        mtx.lock();
        debugger::log("Squares: Started checking 'em");
        if(!checkOne(v)){ //Check 'em
            debugger::log("Squares: Checked 'em");
           doneCheck = false; //return false if there's a problem
        }
        mtx.unlock();
    }
    debugger::log("Finished checkSquares");
}
void sudokuGame::checkRows(){
    debugger::log("Started checkRows");
    //Get a copy of the game space
    mtx.lock();
    std::vector<std::vector<tile>> gs = g.getGameSpace();
    mtx.unlock();

    debugger::log("Rows: Got gs");

    //For each column in the space
    for(int i = 0; i < g.getGH(); i++){
        debugger::log("Rows: " + std::to_string(i));
        vector<tile> v; //Create a vector
        for(int j = 0; j < g.getGW(); j++){
            v.push_back(gs[i][j]); //Add all the tiles in the column
        }
        mtx.lock();
        debugger::log("Rows: Started checking 'em");
        if(!checkOne(v)){ //Check 'em
            debugger::log("Rows: Checked 'em");
           doneCheck = false; //return false if there's a problem
        }
        mtx.unlock();
    }
    debugger::log("Finished checkRows");
}
bool sudokuGame::checkOne(std::vector<tile> tileList){
    debugger::log("Started checkOne");
    if(tileList.size() != 9){
        return false;
    }

    debugger::log("Started checking for dupes");
    std::vector<bool> presenceCheck = {false*9};
    for(tile t : tileList){
        if(!presenceCheck[t.getValue()-1]){ //Ensure that there's no duplicate numbers
            presenceCheck[t.getValue()-1] = true;
        } else {
            return false;
        }
    }
    debugger::log("Started counting number of trues");
    //Count the number of trues
    int tot = 0;
    for(bool b : presenceCheck){
        if(b){
            tot++;
        }
    }
    debugger::log("Finishing up");
    //If we've 9 trues, return true
    if(tot == 9){
        return true;
    } else{ //Not all numbers are present
        return false;
    }

}
void sudokuGame::generateNew(){

}
