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
#include "HealthBar.h"
#include "PLAYER.h"
#include "ENEMY.h"
#include "play.h"
using namespace sf;

class HumanEnemy :public virtual ENEMY {
public:
	void set(Texture &image, int x, int y, SoundBuffer buffer, Texture &texture);
	int playerDetection(PLAYER &p);
	//Обновляє кадр ворога
	void update(float time);
	//Смерть ворога
	void death(float time, PLAYER &p);
	//
	void hit(float time);
	//Метод обробки зіткнень з об`єктами
	void Collision();
};