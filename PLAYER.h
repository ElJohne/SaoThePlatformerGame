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

	float dx, dy; // куди рухається гравець
	FloatRect rect, attackRectLeft, attackRectRight; // тут зберігаються координати гравця, спрайтів атаки
	bool onGround; // Для провірки, чи гравець на землі
	bool isLeft; // Куди в остальнє рухався гравець
	Sprite sprite; // Спрайт гравця
	Sprite attackSprite; // Спрайт атаки
	float currentFrame; // Поточний кадр
	Sound eat, fight, potion; // Звуки їди, удара
	int score, coins; // кількість очків
	int health; // рівень життя
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
	//Конструктор
	PLAYER(Texture &image, SoundBuffer &eat, SoundBuffer &fight, SoundBuffer &potion);
	//Методи для зміни булевої змінної руху
	void setLeft();
	void setRight();
	void setMaxHealth(int maxHealth);
	void lvlUp();
	//Метод для зміни текстури
	void setTexture(Texture &image);
	//Метод, який обновляє кадри гравця
	void update(float time, RenderWindow & window);
	//Метод провірки зіткнення з ігровими елементами
	void Collision(int dir, RenderWindow & window);
};
