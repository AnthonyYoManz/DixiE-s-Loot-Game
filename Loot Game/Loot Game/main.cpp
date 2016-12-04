#include "Game.h"
#include "GameplayTestState.h"

int main(){
	Game game;
    game.initialise(new GameplayTestState);
    while(game.isRunning()){
        game.update();
        game.draw();
    }
    game.cleanup();
    return 0;
}
