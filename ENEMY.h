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
using namespace sf;

class ENEMY {
public:
	float dx, dy;// куди рухається ворог
	FloatRect rect; // координати ворога
	FloatRect leftSide, rightSide;
	Sprite sprite; // спрайт ворога
	float currentFrame; // поточний кадр
	int health;
	bool life; // Ворог живий чи ні
	bool playerDetected;
	short pSide;
	Sound deathSound; // Звук смерті
	HealthBar hb;
	bool isAttacking;
	float currentAttackFrame; // поточний кадр
							  //Встановлює текстуру, координати і звук смерті ворогам
	virtual void set(Texture &image, int x, int y, SoundBuffer buffer, Texture &texture) = 0;
	virtual int playerDetection(PLAYER &p) = 0;
	virtual void update(float time) = 0;
	virtual void death(float time, PLAYER &p) = 0;
	virtual void hit(float time) = 0;
	virtual void Collision() = 0;
};