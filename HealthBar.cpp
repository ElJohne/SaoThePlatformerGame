#include "HealthBar.h"
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
using namespace sf;

void HealthBar::set(int maxHP, Texture &texture) {
	this->maxHP = maxHP;
	back.setTexture(texture);
	front.setTexture(texture);
	rect = FloatRect(0, 0, 352, 40);
	back.setTextureRect(IntRect(0, 0, 352, 40));
	front.setTextureRect(IntRect(0, 40, 276, 13));
	back.setScale(0.25, 0.25);
	front.setScale(0.25, 0.25);
}
void HealthBar::update(FloatRect enemy, int enemyhealth) {
	//413
	rect.top = enemy.top + (413 * 0.25);
	rect.left = enemy.left - (35 * 0.25);
	back.setPosition(rect.left - getOffSetX(), rect.top - getOffSetY());
	float tmp = 0.25 * enemyhealth / maxHP;
	front.setScale(tmp, 0.25);
	front.setPosition(rect.left + 36 * 0.25 - getOffSetX(), rect.top + 16 * 0.25 - getOffSetY());
}

