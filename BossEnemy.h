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

class BossEnemy :public virtual ENEMY
{
public:
	HealthBar hb2, hb3, hb4, hb5;
	int hbh, hbh2, hbh3, hbh4, hbh5;
	int countHealthBars;
	int scoreGiven;
	void set(Texture &image, int x, int y, SoundBuffer buffer, Texture &texture);
	void set2(Texture &image, int x, int y, SoundBuffer buffer, Texture &texture, int HealthBars, int healthOnEachOne, int scoreGiven);
	int playerDetection(PLAYER &p);
	//�������� ���� ������
	void update(float time);
	//������ ������
	void death(float time, PLAYER &p);
	//
	void hit(float time);
	//����� ������� ������� � ��`������
	void Collision();
};
