#include "game.h"
#include "OtherTestScene.h"

int main(){
    Game game;
    game.initialise(new OtherTestScene);
    while(game.isRunning()){
        game.update();
        game.draw();
    }
    game.cleanup();
    return 0;
}
