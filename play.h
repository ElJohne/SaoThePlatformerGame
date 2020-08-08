#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <Windows.h>
#include <iostream>
#include <math.h>
#include <list>
#include <functional>
#include <thread>
#include "setups.h"
#include "levels.h"
#include "gamePause.h"
#include "settings.h"
#include "dbConnect.h"
#include "play.h"
#include "skillMenu.h"
#include "PLAYER.h"
#include "HealthBar.h"
#include "HumanEnemy.h"
#include "AnimalEnemy.h"
#include "BossEnemy.h"
using namespace sf;

int gameStart(RenderWindow &window, int currentLvl, bool isLoaded);
void lvlPlus(RenderWindow & window, bool isLvlUpping);
extern Texture shieldTexture;
extern bool bossIsDead;
extern String TileMapLocal[20];