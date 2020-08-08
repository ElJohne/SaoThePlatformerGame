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

class SkillTree
{
public:
	short lvl[3][5];
	SkillTree();
};

class PLAYER
{
public:

	float dx, dy; // ���� �������� �������
	FloatRect rect, attackRectLeft, attackRectRight; // ��� ����������� ���������� ������, ������� �����
	bool onGround; // ��� �������, �� ������� �� ����
	bool isLeft; // ���� � ������� ������� �������
	Sprite sprite; // ������ ������
	Sprite attackSprite; // ������ �����
	float currentFrame; // �������� ����
	Sound eat, fight, potion; // ����� ���, �����
	int score, coins; // ������� ����
	int health; // ����� �����
	int maxHealth;
	int healthPotion;
	int combo;
	SkillTree st; // skilltree
	int lvl;
	int sp; // skillpoint
	bool shield;
	float shieldTime;
	Sprite shieldSpr;
	float attackTime;
	int maxCombo;
	bool regeneration;
	bool heal_H_Btn;
	bool shieldRegeneration;
	bool shieldJump;
	bool isBoxPicked;
	bool DamageTaken;
	bool isLvlUp;
	bool isLvlUpping;
	bool isAttacking;
	bool isWin;
	//�����������
	PLAYER(Texture &image, SoundBuffer &eat, SoundBuffer &fight, SoundBuffer &potion);
	//������ ��� ���� ������ ����� ����
	void setLeft();
	void setRight();
	void setMaxHealth(int maxHealth);
	void lvlUp();
	//����� ��� ���� ��������
	void setTexture(Texture &image);
	//�����, ���� �������� ����� ������
	void update(float time, RenderWindow & window);
	//����� ������� �������� � �������� ����������
	void Collision(int dir, RenderWindow & window);
};
