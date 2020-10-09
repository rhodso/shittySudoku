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
    doneCheck = true;

/*
    std::vector<std::thread> checkem;

    checkem.push_back(std::thread(checkCols));
    checkem.push_back(std::thread(checkRows));
    checkem.push_back(std::thread(checkSquares));

    for(std::thread &t : checkem){
        t.join();
    }
*/

    checkCols();
    //checkRows();
    //checkSquares();

    debugger::log("Finished checking");

    return doneCheck;

}
void sudokuGame::checkCols(){
    //Get a copy of the game space
    mtx.lock();
    std::vector<std::vector<tile>> gs = g.getGameSpace();
    mtx.unlock();

    //For each column in the space
    for(int i = 0; i < g.getGW(); i++){
        std::vector<std::vector<int>> v; //Create a vector
        for(int j = 0; j < g.getGH(); j++){
            //Create temp vector to store gridX/Y of set, and add to
            std::vector<int> crd;
            crd.push_back(i);
            crd.push_back(j);

            //Add to set
            v.push_back(crd);
        }
        mtx.lock();
        //if(i==0){ debugger::setDebug(true); }
        bool checkem = checkOne(v);
        if(i == 0){
            //debugger::log("Cols: Cycle " + std::to_string(i) + ", result: " + std::to_string(checkem));
            //debugger::log("Printing tile X/Y list...");
            //debugger::setDebug(false);
        }
        if(!checkem){ //Check 'em
           doneCheck = false; //return false if there's a problem
        }
        mtx.unlock();
    }
}
void sudokuGame::checkSquares(){
    //Get a copy of the game space
    mtx.lock();
    std::vector<std::vector<tile>> gs = g.getGameSpace();
    mtx.unlock();

    for(int i = 0; i < g.getGH(); i+=3){
        std::vector<std::vector<int>> v;
        for(int j = 0; j < g.getGW(); j+= 3){

            /*
                1-1 1-2 1-3
                2-1 2-2 2-3
                3-1 3-2 3-3
            */


            //Create temp vector to store gridX/Y of set, and add to
            std::vector<int> crd;

            //For each tile we need to look at:
            // Clear crd if needed
            // crd.push_bakc(X); crd.push_back(Y);
            // v.push_back(Tile we just make in crd


            //Part 1
            crd.push_back(i); crd.push_back(j);
            v.push_back(crd);

            crd.clear();
            crd.push_back(i); crd.push_back(j+1);
            v.push_back(crd);

            crd.clear();
            crd.push_back(i); crd.push_back(j+2);
            v.push_back(crd);

            //Part 2
            crd.clear();
            crd.push_back(i+1);crd.push_back(j);
            v.push_back(crd);

            crd.clear();
            crd.push_back(i+1);crd.push_back(j+1);
            v.push_back(crd);

            crd.clear();
            crd.push_back(i+1);crd.push_back(j+2);
            v.push_back(crd);


            //Part 3
            crd.clear();
            crd.push_back(i+2);crd.push_back(j);
            v.push_back(crd);

            crd.clear();
            crd.push_back(i+2);crd.push_back(j+1);
            v.push_back(crd);

            crd.clear();
            crd.push_back(i+2);crd.push_back(j+2);
            v.push_back(crd);

        }
        mtx.lock();
        if(!checkOne(v)){ //Check 'em
           doneCheck = false; //return false if there's a problem
        }
        mtx.unlock();
    }
}
void sudokuGame::checkRows(){
    //Get a copy of the game space
    mtx.lock();
    std::vector<std::vector<tile>> gs = g.getGameSpace();
    mtx.unlock();

    //For each column in the space
    for(int i = 0; i < g.getGH(); i++){
        std::vector<std::vector<int>> v; //Create a vector
        for(int j = 0; j < g.getGW(); j++){
            //Create temp vector to store gridX/Y of set, and add to
            std::vector<int> crd;
            crd.push_back(i);
            crd.push_back(j);

            //Add to set
            v.push_back(crd);
        }
        mtx.lock();
        if(!checkOne(v)){ //Check 'em
           doneCheck = false; //return false if there's a problem
        }
        mtx.unlock();
    }
}
bool sudokuGame::checkOne(std::vector<std::vector<int>> tileList){
    //debugger::log("Started checkOne");
    if(tileList.size() != 9){
        return false;
    }

    //debugger::log("Init precense check");
    std::vector<bool> presenceCheck = {false,false,false,false,false,false,false,false,false,false};

    //debugger::log("Checking through");
    for(std::vector<int> t : tileList){
        int tileX = t[0];
        int tileY = t[1];
        int valueOfTile = g.getTileValue(tileX, tileY);
        //debugger::log("Tile X/Y/value is " + std::to_string(tileX) + "/" + std::to_string(tileY) + "/" + std::to_string(valueOfTile));
        if(presenceCheck[valueOfTile] == false){
            presenceCheck[valueOfTile] = true;
        } else {
            debugger::log("Dupe detected, printing output");
            if(debugger::getDebug()){
                int tmp = 0;
                for(bool b : presenceCheck){
                    debugger::log("tmp: " + std::to_string(tmp) + ": " + std::to_string(b));
                    tmp++;
                }
                return false;
            }
        }
    }

    //debugger::log("Counting trues");
    //Count the number of trues
    int tot = 0;
    for(bool b : presenceCheck){
        if(b){
            tot++;
        }
    }

    //debugger::log(std::to_string(tot) + " trues");
    //debugger::log("Finishing up...");

    //If we've 9 trues, return true
    if(tot == 9){
        return true;
    } else{ //Not all numbers are present
        return false;
    }

}
void sudokuGame::generateNew(){

}
