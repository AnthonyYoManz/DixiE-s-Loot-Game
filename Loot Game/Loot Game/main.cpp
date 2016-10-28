#include "Game.h"
#include "OtherTestState.h"

int main(){
	Game game;
    game.initialise(new OtherTestState);
    while(game.isRunning()){
        game.update();
        game.draw();
    }
    game.cleanup();
    return 0;
}
