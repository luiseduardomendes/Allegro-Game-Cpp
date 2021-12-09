#include "mainHeader.hpp"

void PauseMenu::init(){
    endOfGame = false;
}

bool PauseMenu::isGameEnded(){
    return endOfGame;
}

void PauseMenu::setEndOfGame(bool value_){
    endOfGame = value_;
}
