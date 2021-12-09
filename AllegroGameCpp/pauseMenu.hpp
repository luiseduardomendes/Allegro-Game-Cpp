#pragma once

class PauseMenu{
public:
    bool isGameEnded();
    void init();
    void setEndOfGame(bool value_);

private:
    bool endOfGame;
};
