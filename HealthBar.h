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
using namespace sf;

class HealthBar {
public:
	Sprite back, front;
	FloatRect rect;
	Texture texture;
	int maxHP;
	int currentHP;
	void set(int maxHP, Texture &texture);

	void update(FloatRect enemy, int enemyhealth);
};