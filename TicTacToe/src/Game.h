#pragma once
#ifndef GAME_H
#define GAME_H

class Game{

public:
    Game();
    ~Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
};

#endif // GAME_H