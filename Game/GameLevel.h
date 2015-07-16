/*
 * GameLevel.h
 *
 *  Created on: 31-mrt.-2015
 *      Author: Thomas
 */

#ifndef GAME_GAMELEVEL_H_
#define GAME_GAMELEVEL_H_

#include <stdlib.h>
#include <time.h>
#include <list>

#include "MusicPlayer.h"
#include "GamePauseMenu.h"
#include "GameState.h"
#include "Event.h"
#include "GameManager.h"
#include "Level.h"

namespace CCG
{
	//State in the running game
	enum LevelStatus
	{
		LEVEL_INTRO,
		LEVEL_RUNNING,
		LEVEL_GAMEOVER,
		LEVEL_HIGHSCORE
	};

	//Intro animation state
	enum LevelIntroStatus
	{
		LEVEL_INTRO_STARTUP,
		LEVEL_INTRO_READY,
		LEVEL_INTRO_COUNTDOWN_3,
		LEVEL_INTRO_COUNTDOWN_2,
		LEVEL_INTRO_COUNTDOWN_1,
		LEVEL_INTRO_COUNTDOWN_START
	};

	/*
	 * Main game state
	 */
	class GameLevel : public GameState
	{
		public:
			/*
			 * Constructor
			 * @param Level The level configurations to be loaded
			 * @see GameState
			 */
			GameLevel(GameFactory* factory, GameStateManager* stateManager, GameManager* gameManager, Level* level);
			~GameLevel(void);

			/*
			 * Initialize the state
			 * @see GameState
			 */
			void initialize(void);

			/*
			 * Release the state
			 * @see GameState
			 */
			void release(void);

			/*
			 * Pause the state
			 * @see GameState
			 */
			void pause(void);

			/*
			 * Resume the state
			 * @see GameState
			 */
			void resume(void);

			/*
			 * Handle the given event
			 * @see GameState
			 */
			void handleEvents(Event* event);

			/*
			 * Update the values of all elements (cars,...)
			 * @see GameState
			 */
			void update(void);

			/*
			 * Handle the events of all displayed buttons
			 * @param mouseX The X-position of the cursor
			 * @param mouseY The Y-position of the cursor
			 * @param mousePressed The state of the mouse button
			 */
			void handleButtonsEvents(int mouseX, int mouseY, bool mousePressed);

			/*
			 * Update all objects according the the current game state
			 * @param timeStep Elapsed time according to the previous frame
			 */
			void updateLevelIntro(float timeStep);
			void updateLevelRunning(float timeStep);
			void updateLevelGameOver(float timeStep);
			void updateLevelHighscore(float timeStep);

			/*
			 * Change state from RUNNING to GAMEOVER
			 * @param flag Toggle game over state
			 */
			void displayGameOver(bool flag);

			/*
			 * Check collisions between all game objects
			 */
			void checkCollisions(void);

			/*
			 * Check the state of the player if he's still alive
			 */
			void checkPlayerState(void);

			/*
			 * Speed up the entire game with a factor
			 * @param speedUpFactor Factor to increase/decrease the game speed with
			 */
			void gameSpeedUp(float speedUpFactor);

			//Power-Ups
			/*
			 * Check for new spawns of power-ups
			 */
			void updatePowerUpSpawners(void);

			/*
			 * Remove taken or out-of-range power-ups
			 */
			void removePowerUps(void);

			/*
			 * Move power-ups on screen
			 * @param timeStep Elapsed time according to the previous frame
			 */
			void movePowerUps(float timeStep);

			/*
			 * Update function to draw power-ups on screen
			 */
			void updatePowerUps(void);

			//Enemies
			/*
			 * Check for new spawns of enemies
			 */
			void updateEnemySpawners(void);

			/*
			 * Remove destroyed or out-of-range enemies
			 */
			void removeEnemies(void);

			/*
			 * Move enemies on screen
			 * @param timeStep Elapsed time according to the previous frame
			 */
			void moveEnemies(float timeStep);

			/*
			 * Update function to draw enemies on screen
			 */
			void updateEnemies(void);

			//Explosion animations
			/*
			 * Create a new explosion on screen with velocity according to the game speed
			 * @param posX The X-position to create the explosion
			 * @param posY The Y-position to create the explosion
			 */
			void createExplosion(float posX, float posY);

			/*
			 * Remove stopped or out-of-range animations
			 */
			void removeExplosions(void);

			/*
			 * Move animations on screen
			 * @param timeStep Elapsed time according to the previous frame
			 */
			void moveExplosions(float timeStep);

			/*
			 * Update function to change the animationframe and draw the animation on screen
			 * @param timeStep Elapsed time according to the previous frame
			 */
			void updateExplosions(float timeStep);

			//Rockets
			/*
			 * Check players for firing new rockets
			 */
			void checkNewRockets(void);

			/*
			 * Create new rockets
			 * @param posX The X-position to create the new rocket
			 * @param posY The Y-position to create the new rocket
			 * @param direction The direction where the rocket is headed
			 * @param speed The velocity that the rocket will travel with
			 * @param hitPoints The damage the rocket will deal when collide
			 * @param owner The player who fired the rocket
			 */
			void createRocket(float posX, float posY, Direction direction, float speed, int hitPoints, Player* owner);

			/*
			 * Remove destroyed or out-of-range rockets
			 */
			void removeRockets(void);

			/*
			 * Move rockets on screen
			 * @param timeStep Elapsed time according to the previous frame
			 */
			void moveRockets(float timeStep);

			/*
			 * Update function to draw rockets on screen
			 */
			void updateRockets(void);

			/*
			 * Pause the running level, score counters and spawners
			 */
			void pauseLevel(void);

			/*
			 * Resume the running level, score counters and spanwers
			 */
			void resumeLevel(void);

		private:
			LevelStatus levelStatus;
			LevelIntroStatus levelIntroStatus;
			MusicPlayer* musicPlayer = NULL;
			Level* level = NULL;
			SpawnPoint** enemySpawners = NULL;
			SpawnPoint** powerUpSpawners = NULL;
			Timer* frameTimer = NULL;
			Timer* animationTimer = NULL;
			Timer* playTimer = NULL;
			Background* background = NULL;
			HUD* hud = NULL;
			Car* playerCar = NULL;
			std::list<Car*>* enemyCars = NULL;
			std::list<PowerUp*>* powerUps = NULL;
			std::list<Animation*>* explosions = NULL;
			std::list<Rocket*>* rockets = NULL;
			Button* exitButton = NULL;
			Button* retryButton = NULL;
			Text* stageText = NULL;
			Text* countdownText = NULL;
			Text* gameOverText = NULL;
			Text* highscoreAchievedText = NULL;
			Text* playerGameOverText = NULL;
			Text* playerFinalScoreText = NULL;
			Text* exitText = NULL;
			Text* retryText = NULL;

			float nextAnimationTime;					//Intro level animation time
			float gameSpeedAcceleration;				//Current speed acceleration
			float enemySpawnAcceleration;				//Current enemey spawn acceleration
			bool highscoreAchieved;						//A new highscore achieved

		protected:
			GameLevel(void);
	};
}

#endif /* GAME_GAMELEVEL_H_ */
