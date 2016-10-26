#include "game.h"
#include "testScene.h"

int main(){
    Game game;
    game.initialise(new TestScene);
    while(game.isRunning()){
        game.update();
        game.draw();
    }
    game.cleanup();
    return 0;
}
