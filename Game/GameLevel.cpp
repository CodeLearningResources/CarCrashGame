/*
 * GameLevel.cpp
 *
 *  Created on: 31-mrt.-2015
 *      Author: Thomas
 */

#include "GameLevel.h"

using namespace CCG;

GameLevel::GameLevel() : GameState()
{
	levelStatus = LEVEL_INTRO;
	levelIntroStatus = LEVEL_INTRO_STARTUP;
	nextAnimationTime = -1;
	gameSpeedAcceleration = 1.0f;
	enemySpawnAcceleration = 0.0f;
	highscoreAchieved = false;
}

GameLevel::GameLevel(GameFactory* factory, GameStateManager* stateManager, GameManager* gameManager, Level* level) : GameState(factory, stateManager, gameManager)
{
	this->levelStatus = LEVEL_INTRO;
	this->levelIntroStatus = LEVEL_INTRO_STARTUP;
	this->nextAnimationTime = -1;
	this->gameSpeedAcceleration = 1.0f;
	this->enemySpawnAcceleration = 0.0f;
	this->highscoreAchieved = false;
	this->level = new Level(*level);
}

GameLevel::~GameLevel()
{
	delete(level);
}

void GameLevel::initialize()
{
	int i;
	float backgroundSizeX, backgroundSizeY = 0.0f;

	factory->getCursor()->visible(false);

	musicPlayer = factory->getMusicPlayer();
	musicPlayer->setMusic(factory->getMusic(MUSIC_RADIO01));
	musicPlayer->startMusic(true);

	frameTimer = factory->getTimer();
	playTimer = factory->getTimer();
	animationTimer = factory->getTimer();
	animationTimer->start();

	//Initialize level background
	level->getBackgroundSize(&backgroundSizeX, &backgroundSizeY);
	background = factory->getBackground(level->getMap());
	background->setPos(0, 0);
	background->setSize(backgroundSizeX, backgroundSizeY);

	if(level->getLevelDirection() == DIRECTION_UP || level->getLevelDirection() == DIRECTION_LEFT)
	{
		background->setSpeed(level->getStartGameSpeed());
	}
	else
	{
		background->setSpeed(-level->getStartGameSpeed());
	}

	background->visible(true);

	//Initialize player
	gameManager->getThisPlayer()->setScore(0.0f);
	gameManager->getThisPlayer()->setRockets(level->getStartRockets());
	playerCar = gameManager->getThisPlayer()->getPlayerCar();
	playerCar->setVelocity(level->getPlayerSpawnPoint()->getMoveSpeed(), level->getPlayerSpawnPoint()->getMoveSpeed());
	playerCar->setRotVelocity(level->getPlayerSpawnPoint()->getMoveSpeed());
	playerCar->setPos(-playerCar->getSizeX(), -playerCar->getSizeY());
	playerCar->setSize(50, 80);
	playerCar->setAlive(true);
	playerCar->setHealth(100);
	playerCar->setNitro(100);
	playerCar->setDriveDirection(level->getLevelDirection());

	if(level->getLevelDirection() == DIRECTION_UP || level->getLevelDirection() == DIRECTION_DOWN)
	{
		playerCar->setCollider(2.5, 2.5, 45, 75);
	}
	else
	{
		playerCar->setCollider(-12, 17, 75, 45);
	}

	//Initialize HUD
	hud = factory->getHUD(HUD_01);
	hud->visible(true);
	hud->setPlayer(gameManager->getThisPlayer(), 0);

	//Initialize enemy spawn
	enemySpawners = level->getEnemySpawnPoints();

	for(i = 0; i < level->getEnemySpawnPointsSize(); i++)
	{
		enemySpawners[i]->initialize(factory->getTimer());
	}

	enemyCars = new std::list<Car*>();

	//Initialize power-ups spawn
	powerUpSpawners = level->getPowerUpSpawnPoints();

	for(i = 0; i < level->getPowerUpSpawnPointsSize(); i++)
	{
		powerUpSpawners[i]->initialize(factory->getTimer());
	}

	powerUps = new std::list<PowerUp*>();

	//Initialize explosions list
	explosions = new std::list<Animation*>();

	//Initialize rockets list
	rockets = new std::list<Rocket*>();

	//Initialize buttons
	exitButton = factory->getButton(BUTTON_01);
	exitButton->setSize(250, 80);
	exitButton->setPos(350 - exitButton->getSizeX()/2, 600 - exitButton->getSizeY()/2);

	exitText = factory->getText("Exit", FONT_TEXT_LARGE);
	exitText->setPos(350 - exitText->getSizeX()/2, 600 - exitText->getSizeY()/2);
	exitText->setColor(255, 255, 255, 0);

	retryButton = factory->getButton(BUTTON_01);
	retryButton->setSize(250, 80);
	retryButton->setPos(674 - retryButton->getSizeX()/2, 600 - retryButton->getSizeY()/2);

	retryText = factory->getText("Retry", FONT_TEXT_LARGE);
	retryText->setPos(674 - retryText->getSizeX()/2, 600 - retryText->getSizeY()/2);
	retryText->setColor(255, 255, 255, 0);

	//Initialize text
	stageText = factory->getText("Stage: " + level->getName(), FONT_TITLE_LARGE);
	stageText->setPos(512 - stageText->getSizeX()/2, 200 - stageText->getSizeY()/2);
	stageText->setColor(255, 255, 255, 0);

	countdownText = factory->getText("Ready", FONT_DISPLAY_LARGE);
	countdownText->setPos(512 - countdownText->getSizeX()/2, 250 - countdownText->getSizeY()/2);
	countdownText->setColor(255, 255, 255, 0);

	gameOverText = factory->getText("GAME OVER", FONT_TITLE_LARGE);
	gameOverText->setPos(512 - gameOverText->getSizeX()/2, 200 - gameOverText->getSizeY()/2);
	gameOverText->setColor(255, 255, 255, 0);

	highscoreAchievedText = factory->getText("HIGHSCORE", FONT_TITLE_LARGE);
	highscoreAchievedText->setPos(512 - highscoreAchievedText->getSizeX()/2, 425);
	highscoreAchievedText->setColor(255, 0, 0, 0);

	playerGameOverText = factory->getText("Final score:", FONT_TEXT_LARGE);
	playerGameOverText->setPos(512 - playerGameOverText->getSizeX()/2, 300 - playerGameOverText->getSizeY()/2);
	playerGameOverText->setColor(255, 255, 255, 0);

	playerFinalScoreText = factory->getText("", FONT_DISPLAY_LARGE);
	playerFinalScoreText->setPos(512 - playerFinalScoreText->getSizeX()/2, 325 - playerFinalScoreText->getSizeY()/2);
	playerFinalScoreText->setColor(255, 255, 255, 0);

	//Initialize game state
	this->levelStatus = LEVEL_INTRO;
	this->levelIntroStatus = LEVEL_INTRO_STARTUP;
	this->nextAnimationTime = -1;
	this->gameSpeedAcceleration = 1.0f;
	this->enemySpawnAcceleration = 0.0f;
	this->highscoreAchieved = false;
}

void GameLevel::release()
{
	int i;
	std::list<Car*>::iterator itCar = enemyCars->begin();
	std::list<PowerUp*>::iterator itPowerUp = powerUps->begin();
	std::list<Animation*>::iterator itExplosion = explosions->begin();
	std::list<Rocket*>::iterator itRocket = rockets->begin();

	delete(frameTimer);
	frameTimer = NULL;

	delete(playTimer);
	playTimer = NULL;

	delete(animationTimer);
	animationTimer = NULL;

	delete(hud);
	hud = NULL;

	for(i = 0; i < level->getEnemySpawnPointsSize(); i++)
	{
		level->getEnemySpawnPoints()[i]->clearQueue();
	}

	while(itCar != enemyCars->end())
	{
		itCar = enemyCars->erase(itCar);
	}

	for(i = 0; i < level->getPowerUpSpawnPointsSize(); i++)
	{
		level->getPowerUpSpawnPoints()[i]->clearQueue();
	}

	while(itPowerUp != powerUps->end())
	{
		itPowerUp = powerUps->erase(itPowerUp);
	}

	while(itExplosion != explosions->end())
	{
		itExplosion = explosions->erase(itExplosion);
	}

	while(itRocket != rockets->end())
	{
		itRocket = rockets->erase(itRocket);
	}

	delete(enemyCars);
	enemyCars = NULL;

	delete(powerUps);
	powerUps = NULL;

	delete(explosions);
	explosions = NULL;

	delete(rockets);
	rockets = NULL;

	delete(exitButton);
	exitButton = NULL;

	delete(retryButton);
	retryButton = NULL;

	delete(stageText);
	stageText = NULL;

	delete(gameOverText);
	gameOverText = NULL;

	delete(highscoreAchievedText);
	highscoreAchievedText = NULL;

	delete(playerGameOverText);
	playerGameOverText = NULL;

	delete(playerFinalScoreText);
	playerFinalScoreText = NULL;

	delete(exitText);
	exitText = NULL;

	delete(retryText);
	retryText = NULL;
}

void GameLevel::pause()
{
	if(levelStatus == LEVEL_RUNNING)
	{
		pauseLevel();
	}

	this->musicPlayer->pauseMusic();
	this->musicPlayer->pauseSFXSounds();
	this->frameTimer->pause();
	this->animationTimer->pause();
}

void GameLevel::resume()
{
	if(levelStatus == LEVEL_RUNNING)
	{
		resumeLevel();
		this->musicPlayer->resumeMusic();
	}
	else if(levelStatus == LEVEL_INTRO)
	{
		this->musicPlayer->resumeMusic();
	}

	this->musicPlayer->resumeSFXSounds();
	this->frameTimer->unpause();
	this->animationTimer->unpause();
}

void GameLevel::handleEvents(Event* event)
{
	int mouseX, mouseY = 0;
	bool mousePressed = false;

	if(event != NULL)
	{
		switch(event->getType())
		{
			case GAME_QUIT:
				stateManager->exitGame();
				break;
			case KEYBOARD_EVENT:
				if(event->getKeyEvent()->getKeyValue() == KEY_ESCAPE && event->getButtonState() == BUTTON_PRESSED)
				{
					if(levelStatus == LEVEL_INTRO || levelStatus == LEVEL_RUNNING)
					{
						stateManager->pushState(new GamePauseMenu(factory, stateManager, gameManager));
					}
				}
				else
				{
					if(levelStatus == LEVEL_RUNNING)
					{
						gameManager->getThisPlayer()->handleEvent(event);
					}
				}
				break;
			case MOUSE_EVENT:
				event->getMousePosition(&mouseX, &mouseY);

				if(event->getLMouseButtonState() == BUTTON_PRESSED)
				{
					mousePressed = true;
				}

				handleButtonsEvents(mouseX, mouseY, mousePressed);
			default:
				break;
		}
		delete(event);
		event = NULL;
	}
}

void GameLevel::update()
{
	float timeStep = 0.0f;

	//Calculate time step
	if(!frameTimer->isPaused())
	{
		timeStep = frameTimer->getTicks() / 1000.f;
	}

	switch(levelStatus)
	{
		case LEVEL_INTRO:
			factory->getCursor()->visible(false);
			updateLevelIntro(timeStep);
			break;
		case LEVEL_RUNNING:
			factory->getCursor()->visible(false);
			updateLevelRunning(timeStep);
			break;
		case LEVEL_GAMEOVER:
			factory->getCursor()->visible(true);
			updateLevelGameOver(timeStep);
			break;
		case LEVEL_HIGHSCORE:
			updateLevelHighscore(timeStep);
			break;
	}

	if(!frameTimer->isPaused())
	{
		frameTimer->start();
	}
}

void GameLevel::handleButtonsEvents(int mouseX, int mouseY, bool mousePressed)
{
	if(levelStatus == LEVEL_GAMEOVER)
	{
		if(exitButton->checkButtonState(mouseX, mouseY, mousePressed))
		{
			stateManager->setState(new GameStartMenu(factory, stateManager, gameManager));
		}
		else if(retryButton->checkButtonState(mouseX, mouseY, mousePressed))
		{
			this->release();
			this->initialize();
		}
	}
}

void GameLevel::updateLevelIntro(float timeStep)
{
	float moveToX, moveToY;
	float animationTime = this->animationTimer->getTicks() / 1000.f;

	switch(levelIntroStatus)
	{
		case LEVEL_INTRO_STARTUP:
			if(nextAnimationTime == -1)
			{
				this->animationTimer->reset();
				nextAnimationTime = (this->animationTimer->getTicks() / 1000.f) + 2.5;

				//Initialize player spawn
				level->getPlayerSpawnPoint()->initialize(factory->getTimer());
				level->getPlayerSpawnPoint()->queueObject(this->playerCar);
				level->getPlayerSpawnPoint()->start();

				//Initialize player animation
				level->getPlayerStartPoint(&moveToX, &moveToY);
				playerCar->moveToLocation(moveToX, moveToY, true);

				//Display stage text
				stageText->visible(true);
			}
			else if(animationTime > nextAnimationTime)
			{
				nextAnimationTime = -1;
				playerCar->moveToLocation(0, 0, false);
				levelIntroStatus = LEVEL_INTRO_READY;
			}
			break;
		case LEVEL_INTRO_READY:
			if(nextAnimationTime == -1)
			{
				nextAnimationTime = animationTime + 2;

				//Display ready text
				countdownText->setText("Ready");
				countdownText->setPosX(512 - countdownText->getSizeX()/2);
				countdownText->visible(true);
			}
			else if(animationTime > nextAnimationTime)
			{
				nextAnimationTime = -1;
				levelIntroStatus = LEVEL_INTRO_COUNTDOWN_3;
			}
			break;
		case LEVEL_INTRO_COUNTDOWN_3:
			if(nextAnimationTime == -1)
			{
				nextAnimationTime = animationTime + 1;

				//Display countdown: 3 text
				countdownText->setText("3");
				countdownText->setPosX(512 - countdownText->getSizeX()/2);
			}
			else if(animationTime > nextAnimationTime)
			{
				nextAnimationTime = -1;
				levelIntroStatus = LEVEL_INTRO_COUNTDOWN_2;
			}
			break;
		case LEVEL_INTRO_COUNTDOWN_2:
			if(nextAnimationTime == -1)
			{
				nextAnimationTime = animationTime + 1;

				//Display countdown: 2 text
				countdownText->setText("2");
				countdownText->setPosX(512 - countdownText->getSizeX()/2);
			}
			else if(animationTime > nextAnimationTime)
			{
				nextAnimationTime = -1;
				levelIntroStatus = LEVEL_INTRO_COUNTDOWN_1;
			}
			break;
		case LEVEL_INTRO_COUNTDOWN_1:
			if(nextAnimationTime == -1)
			{
				nextAnimationTime = animationTime + 1;

				//Display countdown: 1 text
				countdownText->setText("1");
				countdownText->setPosX(512 - countdownText->getSizeX()/2);
			}
			else if(animationTime > nextAnimationTime)
			{
				nextAnimationTime = -1;
				levelIntroStatus = LEVEL_INTRO_COUNTDOWN_START;
			}
			break;
		case LEVEL_INTRO_COUNTDOWN_START:
			if(nextAnimationTime == -1)
			{
				nextAnimationTime = animationTime + 1;

				//Display start text
				countdownText->setText("START");
				countdownText->setPosX(512 - countdownText->getSizeX()/2);
			}
			else if(animationTime > nextAnimationTime)
			{
				nextAnimationTime = -1;
				levelIntroStatus = LEVEL_INTRO_STARTUP;
				levelStatus = LEVEL_RUNNING;

				stageText->visible(false);
				countdownText->visible(false);
				playTimer->start();

				resumeLevel();
			}
			break;
	}

	background->move(timeStep);
	background->update();

	level->getPlayerSpawnPoint()->update();

	playerCar->move(timeStep);
	playerCar->update();

	stageText->update();
	countdownText->update();
}

void GameLevel::updateLevelRunning(float timeStep)
{
	//Level boundaries
	int boundaryX, boundaryY, boundaryWidth, boundaryHeight = 0;
	level->getLevelBoundaries(&boundaryX, &boundaryY, &boundaryWidth, &boundaryHeight);

	//Update score
	if(gameManager->getThisPlayer()->isAlive())
	{
		gameManager->getThisPlayer()->addScore(level->getSurvivalPointsPerSecond() * timeStep);
	}

	//Update game speed
	if(gameSpeedAcceleration < level->getMaxAccelerationGameSpeed())
	{
		float acceleration = 0.0f;

		acceleration = level->getAccelerationGameSpeed() * timeStep;
		gameSpeedAcceleration += acceleration;
	}

	//Update enemy spawner speed
	if(enemySpawnAcceleration < level->getEnemySpawnMaxAccelerationTime())
	{
		float acceleration = 0.0f;

		acceleration = level->getEnemySpawnAccelerationTime() * timeStep;
		enemySpawnAcceleration += acceleration;
	}

	background->move(timeStep);
	background->update();

	playerCar->keepInLevelBoundaries(boundaryX, boundaryY, boundaryWidth, boundaryHeight);
	playerCar->move(timeStep);
	playerCar->updateStatus(timeStep);

	updatePowerUpSpawners();
	movePowerUps(timeStep);
	removePowerUps();

	updateEnemySpawners();
	moveEnemies(timeStep);
	removeEnemies();

	moveRockets(timeStep);
	removeRockets();

	checkNewRockets();
	removeExplosions();
	moveExplosions(timeStep);

	updatePowerUps();
	updateEnemies();
	updateRockets();
	playerCar->update();
	updateExplosions(timeStep);

	checkCollisions();
	checkPlayerState();

	hud->update();
}

void GameLevel::updateLevelGameOver(float timeStep)
{
	background->move(timeStep);
	background->update();

	updatePowerUpSpawners();
	movePowerUps(timeStep);
	removePowerUps();
	updatePowerUps();

	updateEnemySpawners();
	moveEnemies(timeStep);
	removeEnemies();
	updateEnemies();

	removeExplosions();
	moveExplosions(timeStep);
	updateExplosions(timeStep);

	gameOverText->update();

	playerGameOverText->update();
	playerFinalScoreText->update();

	highscoreAchievedText->update();

	exitButton->update();
	exitText->update();

	retryButton->update();
	retryText->update();
}

void GameLevel::updateLevelHighscore(float timeStep)
{
	background->move(timeStep);
	background->update();

	updatePowerUpSpawners();
	movePowerUps(timeStep);
	removePowerUps();
	updatePowerUps();

	updateEnemySpawners();
	moveEnemies(timeStep);
	removeEnemies();
	updateEnemies();

	removeExplosions();
	moveExplosions(timeStep);
	updateExplosions(timeStep);

	gameOverText->update();

	playerGameOverText->update();
	playerFinalScoreText->update();

	exitButton->update();
	exitText->update();

	retryButton->update();
	retryText->update();
}

void GameLevel::displayGameOver(bool flag)
{
	gameOverText->visible(flag);

	if(!flag)
	{
		highscoreAchievedText->visible(false);
	}
	else if(highscoreAchieved)
	{
		highscoreAchievedText->visible(true);
	}

	playerGameOverText->visible(flag);
	playerFinalScoreText->visible(flag);

	exitButton->visible(flag);
	exitText->visible(flag);

	retryButton->visible(flag);
	retryText->visible(flag);

	playTimer->stop();
}

void GameLevel::checkCollisions()
{
	std::list<PowerUp*>::iterator itPowerUps;
	std::list<Car*>::iterator itCars;
	std::list<Rocket*>::iterator itRockets;

	itPowerUps = powerUps->begin();
	while(itPowerUps != powerUps->end())
	{
		if(playerCar->checkCollision((GameElement*)(*itPowerUps)) && (*itPowerUps)->isAvailable())
		{
			switch((*itPowerUps)->getBonusType())
			{
				case POWERUP_BONUS_HEALTH:
					playerCar->heal((*itPowerUps)->getBonusValue());
					break;
				case POWERUP_BONUS_POINTS:
					gameManager->getThisPlayer()->addScore((float)(*itPowerUps)->getBonusValue());
					break;
				case POWERUP_BONUS_INVINCIBILITY:
					playerCar->setInvincibleTime((*itPowerUps)->getBonusValue());
					break;
				case POWERUP_BONUS_ROCKETS:
					gameManager->getThisPlayer()->addRockets((*itPowerUps)->getBonusValue());
					break;
				default:
					break;
			}

			(*itPowerUps)->setAvailability(false);
		}

		itPowerUps++;
	}

	itCars = enemyCars->begin();
	while(itCars != enemyCars->end())
	{
		itRockets = rockets->begin();
		while(itRockets != rockets->end())
		{
			if((*itCars)->checkCollision((GameElement*)(*itRockets)))
			{
				(*itCars)->playCrashSound();
				(*itCars)->setAlive(false);
				(*itRockets)->setAlive(false);

				(*itRockets)->getOwner()->addScore(level->getRocketHitPoints());

				this->createExplosion((*itCars)->getPosX() + ((*itCars)->getSizeX() / 2), (*itCars)->getPosY() + ((*itCars)->getSizeY() / 2));
			}

			itRockets++;
		}

		if((*itCars)->isAlive())
		{
			if(playerCar->checkCollision((GameElement*)(*itCars)))
			{
				if(!playerCar->isInvincible())
				{
					playerCar->hit(25);
				}

				(*itCars)->playCrashSound();
				(*itCars)->setAlive(false);

				this->createExplosion((*itCars)->getPosX() + ((*itCars)->getSizeX() / 2), (*itCars)->getPosY() + ((*itCars)->getSizeY() / 2));
			}
		}

		itCars++;
	}
}

void GameLevel::checkPlayerState()
{
	char score[25];

	if(!playerCar->isAlive())
	{
		this->levelStatus = LEVEL_GAMEOVER;
		this->musicPlayer->stopMusic(true);

		this->createExplosion(playerCar->getPosX(), playerCar->getPosY());

		sprintf(score, "%d", (int)gameManager->getThisPlayer()->getScore());
		this->playerFinalScoreText->setText(score);
		this->playerFinalScoreText->setPosX(512 - this->playerFinalScoreText->getSizeX()/2);

		this->highscoreAchieved = this->gameManager->addHighscore(this->level->getLevelIndex(), gameManager->getThisPlayer()->getName(), gameManager->getThisPlayer()->getScore());

		displayGameOver(true);
	}
}

void GameLevel::gameSpeedUp(float speedUpFactor)
{
	std::list<PowerUp*>::iterator itPowerUps;
	std::list<Car*>::iterator itCars;
	std::list<Animation*>::iterator itExplosions;

	if(level->getLevelDirection() == DIRECTION_UP || level->getLevelDirection() == DIRECTION_LEFT)
	{
		background->setSpeed(level->getStartGameSpeed() * gameSpeedAcceleration * speedUpFactor);
	}
	else
	{
		background->setSpeed(-level->getStartGameSpeed() * gameSpeedAcceleration * speedUpFactor);
	}

	itPowerUps = powerUps->begin();
	while(itPowerUps != powerUps->end())
	{
		(*itPowerUps)->setVelocity(background->getVelX(), background->getVelY());

		itPowerUps++;
	}

	itCars = enemyCars->begin();
	while(itCars != enemyCars->end())
	{
		(*itCars)->setVelocity((*itCars)->getVelX() * speedUpFactor, (*itCars)->getVelY() * speedUpFactor);

		itCars++;
	}

	itExplosions = explosions->begin();
	while(itExplosions != explosions->end())
	{
		(*itExplosions)->setVelocity((*itExplosions)->getVelX() * speedUpFactor, (*itCars)->getVelY() * speedUpFactor);

		itExplosions++;
	}

	playerCar->setVelocity(level->getPlayerSpawnPoint()->getMoveSpeed() * gameSpeedAcceleration, level->getPlayerSpawnPoint()->getMoveSpeed() * gameSpeedAcceleration);
}

void GameLevel::updatePowerUpSpawners()
{
	PowerUp* newPowerUp;
	PowerUpType powerUpType;
	int i;

	for(i = 0; i < level->getPowerUpSpawnPointsSize(); i++)
	{
		powerUpSpawners[i]->update();

		if(powerUpSpawners[i]->isEmpty())
		{
			powerUpType = level->getPowerUpSpawnPointsTypes()[i];

			newPowerUp = factory->getPowerUp(powerUpType);
			newPowerUp->setBonusValue(level->getPowerUpBonusValue(newPowerUp->getBonusType()));
			newPowerUp->setVelocity(background->getVelX(), background->getVelY());
			newPowerUp->setSize(50, 50);
			newPowerUp->setCollider(0, 0, 50, 50);

			powerUpSpawners[i]->queueObject(newPowerUp);
			powerUps->push_back(newPowerUp);
		}
	}
}

void GameLevel::removePowerUps()
{
	int screenWidth = factory->getScreenWidth();
	int screenHeight = factory->getScreenHeight();

	std::list<PowerUp*>::iterator it = powerUps->begin();

	while(it != powerUps->end())
	{
		if(!(*it)->checkInBoundaries(-(*it)->getSizeX(), -(*it)->getSizeY(), screenWidth + ((*it)->getSizeX() * 2), screenHeight + ((*it)->getSizeY() * 2)))
		{
			(*it)->setAvailability(false);
		}

		if(!(*it)->isAvailable())
		{
			it = this->powerUps->erase(it);
		}
		else
		{
			it++;
		}
	}
}

void GameLevel::movePowerUps(float timeStep)
{
	std::list<PowerUp*>::iterator it;

	for(it = powerUps->begin(); it != powerUps->end(); it++)
	{
		if((*it)->isVisible() && (*it)->isAvailable())
		{
			(*it)->move(timeStep);
		}
	}
}

void GameLevel::updatePowerUps()
{
	std::list<PowerUp*>::iterator it;

	for(it = powerUps->begin(); it != powerUps->end(); it++)
	{
		(*it)->update();
	}
}

void GameLevel::updateEnemySpawners()
{
	Car* newEnemyCar;
	CarType carType;
	Direction spawnDirection;
	float moveSpeed;
	int i;

	for(i = 0; i < level->getEnemySpawnPointsSize(); i++)
	{
		enemySpawners[i]->update();
		enemySpawners[i]->setSpawnDelayAcceleration(enemySpawnAcceleration);

		if(enemySpawners[i]->isEmpty() && enemyCars->size() < (unsigned)level->getEnemyMaxEntities())
		{
			carType = (CarType)((rand() + 1) % ENEMYCARS_MAX);
			spawnDirection = enemySpawners[i]->getSpawnDirection();
			moveSpeed = enemySpawners[i]->getMoveSpeed();

			newEnemyCar = factory->getCar(carType);
			newEnemyCar->setVelocity(moveSpeed * gameSpeedAcceleration, moveSpeed * gameSpeedAcceleration);
			newEnemyCar->setRotVelocity(150);
			newEnemyCar->setSize(50, 80);
			newEnemyCar->setDriveDirection(spawnDirection);
			if(spawnDirection == DIRECTION_UP || spawnDirection == DIRECTION_DOWN)
			{
				newEnemyCar->setCollider(5, 2.5, 40, 75);
			}
			else
			{
				newEnemyCar->setCollider(-12, 21, 75, 40);
			}

			enemySpawners[i]->queueObject(newEnemyCar);
			enemyCars->push_back(newEnemyCar);
		}
	}
}

void GameLevel::removeEnemies()
{
	int screenWidth = factory->getScreenWidth();
	int screenHeight = factory->getScreenHeight();
	float sizeX, sizeY = 0;

	std::list<Car*>::iterator it = enemyCars->begin();

	while(it != enemyCars->end())
	{
		if((*it)->getDriveDirection() == DIRECTION_UP || (*it)->getDriveDirection() == DIRECTION_DOWN)
		{
			sizeX = (*it)->getSizeX();
			sizeY = (*it)->getSizeY();
		}
		else
		{
			//Car is rotated
			sizeX = (*it)->getSizeY();
			sizeY = (*it)->getSizeX();
		}

		if(!(*it)->checkInBoundaries(-sizeX, -sizeY, screenWidth + (sizeX * 2), screenHeight + (sizeY * 2)))
		{
			(*it)->setAlive(false);
		}

		if(!(*it)->isAlive())
		{
			it = this->enemyCars->erase(it);
		}
		else
		{
			it++;
		}
	}
}

void GameLevel::moveEnemies(float timeStep)
{
	std::list<Car*>::iterator it;

	for(it = enemyCars->begin(); it != enemyCars->end(); it++)
	{
		if((*it)->isVisible() && (*it)->isAlive())
		{
			switch((*it)->getDriveDirection())
			{
				case DIRECTION_UP:
					(*it)->goUp(true);
					break;
				case DIRECTION_RIGHT:
					(*it)->goRight(true);
					break;
				case DIRECTION_DOWN:
					(*it)->goDown(true);
					break;
				case DIRECTION_LEFT:
					(*it)->goLeft(true);
					break;
			}

			(*it)->move(timeStep);
		}
	}
}

void GameLevel::updateEnemies()
{
	std::list<Car*>::iterator it;

	for(it = enemyCars->begin(); it != enemyCars->end(); it++)
	{
		(*it)->update();
	}
}

void GameLevel::createExplosion(float posX, float posY)
{
	Animation* newExplosion = factory->getAnimation(ANIMATION_EXPLOSION);

	newExplosion->setSize(75, 75);
	newExplosion->setPos(posX - (newExplosion->getSizeX() / 2), posY - (newExplosion->getSizeY() / 2));
	newExplosion->setVelocity(this->background->getVelX(), this->background->getVelY());
	newExplosion->run();

	this->explosions->push_back(newExplosion);
}

void GameLevel::removeExplosions()
{
	int screenWidth = factory->getScreenWidth();
	int screenHeight = factory->getScreenHeight();

	std::list<Animation*>::iterator it = explosions->begin();

	while(it != explosions->end())
	{
		if(!(*it)->checkInBoundaries(-(*it)->getSizeX(), -(*it)->getSizeY(), screenWidth + ((*it)->getSizeX() * 2), screenHeight + ((*it)->getSizeY() * 2)))
		{
			it = this->explosions->erase(it);
		}
		else if(!((*it)->isRunning()))
		{
			it = this->explosions->erase(it);
		}
		else
		{
			it++;
		}
	}
}

void GameLevel::moveExplosions(float timeStep)
{
	std::list<Animation*>::iterator it;

	for(it = explosions->begin(); it != explosions->end(); it++)
	{
		(*it)->move(timeStep);
	}
}

void GameLevel::updateExplosions(float timeStep)
{
	std::list<Animation*>::iterator it;

	for(it = explosions->begin(); it != explosions->end(); it++)
	{
		(*it)->updateAnimation(timeStep);
		(*it)->update();
	}
}

void GameLevel::checkNewRockets()
{
	Car* playerCar;
	Player* playerIt = this->gameManager->getThisPlayer();

	if(playerIt->isFiring())
	{
		playerCar = playerIt->getPlayerCar();

		createRocket(playerCar->getPosX() + (playerCar->getSizeX() / 2), playerCar->getPosY() + (playerCar->getSizeY() / 2), playerCar->getDriveDirection(), level->getRocketSpeed(), level->getRocketDamage(), playerIt);

		playerIt->setFiring(false);
	}
}

void GameLevel::createRocket(float posX, float posY, Direction direction, float speed, int hitPoints, Player* owner)
{
	Rocket* newRocket = factory->getRocket(ROCKET_01);

	newRocket->setSize(10, 35);
	newRocket->setCollider(0, 0, 10, 35);
	newRocket->setPos(posX - (newRocket->getSizeX() / 2), posY - (newRocket->getSizeY() / 2));
	newRocket->setDirection(direction);
	newRocket->setSpeed(speed);
	newRocket->setHitPoints(hitPoints);
	newRocket->setOwner(owner);
	newRocket->visible(true);

	newRocket->playLaunchSound();

	rockets->push_back(newRocket);
}

void GameLevel::removeRockets()
{
	int screenWidth = factory->getScreenWidth();
	int screenHeight = factory->getScreenHeight();
	float sizeX, sizeY = 0;

	std::list<Rocket*>::iterator it = rockets->begin();

	while(it != rockets->end())
	{
		if((*it)->getDirection() == DIRECTION_UP || (*it)->getDirection() == DIRECTION_DOWN)
		{
			sizeX = (*it)->getSizeX();
			sizeY = (*it)->getSizeY();
		}
		else
		{
			//Rocket is rotated
			sizeX = (*it)->getSizeY();
			sizeY = (*it)->getSizeX();
		}

		if(!(*it)->checkInBoundaries(-sizeX, -sizeY, screenWidth + (sizeX * 2), screenHeight + (sizeY * 2)))
		{
			(*it)->setAlive(false);
		}

		if(!(*it)->isAlive())
		{
			it = this->rockets->erase(it);
		}
		else
		{
			it++;
		}
	}
}

void GameLevel::moveRockets(float timeStep)
{
	std::list<Rocket*>::iterator it;

	for(it = rockets->begin(); it != rockets->end(); it++)
	{
		(*it)->move(timeStep);
	}
}

void GameLevel::updateRockets()
{
	std::list<Rocket*>::iterator it;

	for(it = rockets->begin(); it != rockets->end(); it++)
	{
		(*it)->update();
	}
}

void GameLevel::pauseLevel()
{
	int i;

	for(i = 0; i < level->getEnemySpawnPointsSize(); i++)
	{
		enemySpawners[i]->pause();
	}

	for(i = 0; i < level->getPowerUpSpawnPointsSize(); i++)
	{
		powerUpSpawners[i]->pause();
	}

	this->playTimer->pause();
}

void GameLevel::resumeLevel()
{
	int i;

	for(i = 0; i < level->getEnemySpawnPointsSize(); i++)
	{
		enemySpawners[i]->start();
	}

	for(i = 0; i < level->getPowerUpSpawnPointsSize(); i++)
	{
		powerUpSpawners[i]->start();
	}

	this->playTimer->unpause();
}
