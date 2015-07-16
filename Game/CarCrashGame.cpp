/*
 * CarCrashGame.cpp
 *
 *  Created on: 9-mrt.-2015
 *      Author: Thomas
 */

#include "CarCrashGame.h"

using namespace CCG;

int main(int argc, char* args[])
{
	GameFactory* factory = new CCG_SDL::SDLFactory();

	//Create game and start
	Game* game = new Game(factory);
	game->launch();

	//Destroy game and factory
	delete(game);
	delete(factory);

	return 0;
}
