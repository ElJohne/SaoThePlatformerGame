#include "PLAYER.h"
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



SkillTree::SkillTree()
{
	for (short i = 0; i < 3; i++)
	{
		for (short j = 0; j < 5; j++)
		{
			lvl[i][j] = 0;
		}
	}
};

PLAYER::PLAYER(Texture &image, SoundBuffer &eat, SoundBuffer &fight, SoundBuffer &potion)
{
	lvl = 1;
	isWin = false;
	isAttacking = false;
	isLvlUpping = false;
	isLvlUp = false;
	DamageTaken = false;
	isBoxPicked = false;
	regeneration = false;
	heal_H_Btn = false;
	shieldRegeneration = false;
	shieldSpr.setTexture(shieldTexture);
	shieldSpr.setScale(0.000001, 0.0000001);
	shield = false;
	sp = 45;
	score = 0;
	coins = 0;
	combo = 0;
	healthPotion = 1;
	attackTime = 1.5;
	maxCombo = 0;
	shieldJump = false;
	//������� ������� � ����������� �����
	this->fight.setBuffer(fight);
	this->eat.setBuffer(eat);
	this->potion.setBuffer(potion);
	//������� �� ���������, �� ������� �� �������� � ���
	isLeft = false;
	//������� �������� �������� � ������ ������
	sprite.setTexture(image);
	//������� �������� �������� � ������ �����
	attackSprite.setTexture(image);
	//������ ���������� ����� �� ��������
	attackSprite.setTextureRect(IntRect(3 * 128, 0, 128, 128));
	//������� ���������� ��������� ��������� � ������� �����
	rect = FloatRect(3 * 64, 11 * 64, 90, 118);
	attackRectLeft = FloatRect(2 * 64, 11 * 64, 45, 100);
	attackRectRight = FloatRect(3 * 64, 11 * 64, 45, 100);
	health = 10;
	maxHealth = 10;
	dx = dy = 0.1;
	currentFrame = 0;
}
//������ ��� ���� ������ ����� ����
void PLAYER::setLeft() { isLeft = true; }
void PLAYER::setRight() { isLeft = false; }
void PLAYER::setMaxHealth(int maxHealth) {
	this->maxHealth = maxHealth;
}
//����� ��� ���� ��������
void PLAYER::setTexture(Texture &image)
{
	sprite.setTexture(image);
}
//�����, ���� �������� ����� ������
void PLAYER::update(float time, RenderWindow & window)
{
	// ������� ���������� �� �-� �������� �� �������� ����
	rect.left += dx * time;
	Collision(0, window);
	//���� ������� �� �� ����, �� �� ���� � ������������ 0.0003
	if (!onGround) dy = dy + 0.0003*time;
	//������� ���������� �� Y-�
	rect.top += dy*time;
	//������� ���� ������(����������� � �����)
	onGround = false;
	Collision(1, window);
	lvlUp();
	attackRectLeft.left = rect.left - 45;
	attackRectRight.left = rect.left + 64;
	attackRectLeft.top = rect.top;
	attackRectRight.top = rect.top;
	//������� �������� ���� ����� �������� �� ���� �� �� �����, �� ���� ����
	if (isAttacking) currentFrame += 0.01*time;
	else if (dx == 0) currentFrame += 0.002*time;
	else currentFrame += 0.005*time;
	//���� �������� ���� �������� ��� �����
	if (currentFrame > 8) {
		//������� ���� �� 0-�� ����
		currentFrame -= 8;
		//���� �� ��� �������� ���� �����, �� �������� ����
		if (isAttacking) {
			attackSprite.setTextureRect(IntRect(128 * 3, 128 * int(currentFrame), 128, 128));
		}
		//ϳ��� 8-�� ����� ������ ����� ����� �� false
		isAttacking = false;
		//��������� �����, ��� ������� ������� ���������(������� ���������� Space)
		setAttackVar(0);
	}
	//���� ����� �� ��������, �� ������� ��������� ������, � ��������� �� �������� ����
	if (!isAttacking) {
		if (!isBoxPicked) {
			if (dx > 0) sprite.setTextureRect(IntRect(0, 128 * int(currentFrame), 128, 128));
			if (dx < 0) sprite.setTextureRect(IntRect(0 + 128, 128 * int(currentFrame), -128, 128));
			if (isLeft)
			{
				if (dx == 0) sprite.setTextureRect(IntRect(2 * 128, 128 * int(currentFrame), -128, 128));
			}
			if (!isLeft)
			{
				if (dx == 0) sprite.setTextureRect(IntRect(1 * 128, 128 * int(currentFrame), 128, 128));
			}
		}
		else {
			if (dx > 0) sprite.setTextureRect(IntRect(4 * 128 - 64, 128 * int(currentFrame), 128, 128));
			if (dx < 0) sprite.setTextureRect(IntRect(4 * 128 + 64, 128 * int(currentFrame), -128, 128));
			if (isLeft)
				if (dx == 0) sprite.setTextureRect(IntRect(4 * 128 + 64, 0, -128, 128));
			if (!isLeft)
				if (dx == 0) sprite.setTextureRect(IntRect(4 * 128 - 64, 0, 128, 128));
		}
		attackSprite.setTextureRect(IntRect(7 * 128, 128 * int(currentFrame), -128, 128));
	}
	if (shield) {
		shieldSpr.setScale(0.175, 0.175);
	}
	else shieldSpr.setScale(0.00000000001, 0.000000001);
	//���� �������� �����, �� ������� ��������� ������ �� ���������� �������� ����
	if (isAttacking)
	{
		if (isLeft)
		{
			attackSprite.setTextureRect(IntRect(3 * 128 + 40, 128 * int(currentFrame) * (combo == 0 ? 1 : (combo + 1)), -40, 128));
			attackSprite.setPosition(rect.left - getOffSetX() - 40, rect.top - getOffSetY());
			sprite.setTextureRect(IntRect(3 * 128, 128 * int(currentFrame) * (combo == 0 ? 1 : (combo + 1)), -128, 128));
		}
		if (!isLeft)
		{
			attackSprite.setTextureRect(IntRect(3 * 128, 128 * int(currentFrame) * (combo == 0 ? 1 : (combo + 1)), 40, 128));
			attackSprite.setPosition((rect.left - getOffSetX() + 128 - 36), rect.top - getOffSetY());
			sprite.setTextureRect(IntRect(2 * 128, 128 * int(currentFrame) * (combo == 0 ? 1 : (combo + 1)), 128, 128));
		}
	}
	//������� ������ �� ��� ����
	//if(dx < 0)sprite.setPosition((rect.left - getOffSetX()), rect.top - getOffSetY());
	sprite.setPosition((rect.left - getOffSetX()), rect.top - getOffSetY());
	if (!isLeft)sprite.setPosition((rect.left - getOffSetX() - 36), rect.top - getOffSetY());
	shieldSpr.setPosition(sprite.getPosition().x - 10, sprite.getPosition().y - 10);
	if (!isLeft)shieldSpr.setPosition(sprite.getPosition().x + 5, sprite.getPosition().y - 10);
	//��������� ����� ����
	dx = 0;
}
//����� ������� �������� � �������� ����������
void PLAYER::Collision(int dir, RenderWindow & window)
{
	//��������� ������ �� ����� �� ���� ��������� ���������� ���� �����������
	for (int i = (rect.top / 64); i < (rect.top + rect.height) / 64; i++)
	{
		for (int j = rect.left / 64; j < (rect.left + rect.width) / 64; j++)
		{//���������, �� � ����� ���� ���� �
			if (TileMapLocal[i][j] == 'G' || TileMapLocal[i][j] == 'T' || TileMapLocal[i][j] == 'D' || TileMapLocal[i][j] == 'C' || TileMapLocal[i][j] == 'B')
			{//���� ���, �� �� ������� ���� ������
				if ((dx > 0) && (dir == 0)) rect.left = j * 64 - rect.width;
				if ((dx < 0) && (dir == 0)) rect.left = j * 64 + 64;
				if ((dy > 0) && (dir == 1)) { rect.top = i * 64 - rect.height;  dy = 0;   onGround = true; }
				if ((dy < 0) && (dir == 1)) { rect.top = i * 64 + 64;   dy = 0; }
			}
			//���� �� 0(���������� ��������, �� ����� ������)
			if (TileMapLocal[i][j] == 'O')
			{//������� �� ���� ���� ����� ���� � ��������� ���� �������
				TileMapLocal[i][j] = ' ';
				score += 50;
				coins++;
				eat.setVolume(getChoosenGameSound() * 10);
				eat.play();
			}
			if (TileMapLocal[i][j] == 'H')
			{//������� �� ���� ���� ����� ���� � ��������� ���� �������
				TileMapLocal[i][j] = ' ';
				healthPotion += 1;
			}//���� �� �(Portal)
			if (TileMapLocal[i][j] == 'P')
			{// ����������� ������ �� ������ ���� � ���������, �� ������� �� ���� ������
				if ((getCurrentLevel() < 3 || getCurrentLevel() == 4 || getCurrentLevel() == 6) && bossIsDead) {
					if (getCurrentLevel() >= 6) {
						isWin = true;
						setExp(getAccountID(), getAccountExp() + score);
						getExp(getAccountID());
						getLevel(getAccountID());
						setCoins(getAccountID(), getAccountCoins() + coins);
						getCoins(getAccountID());
					}
					if (getCurrentLevel() < 6) {
						setCurrentLevel(getCurrentLevel() + 1);
					}
					if (!isWin) {
						lvlPlus(window, isLvlUpping);
						setExp(getAccountID(), getAccountExp() + score);
						setCoins(getAccountID(), getAccountCoins() + coins);
						getCoins(getAccountID());
						isLvlUp = true;
						isLvlUpping = true;
					}
				}
			}//���� �� L ��
			if (TileMapLocal[i][j] == 'L')
			{// ����������� ������ �� ������ ���� � ���������, �� ������� �� ���� ������
				if ((getCurrentLevel() == 3 || getCurrentLevel() == 5) && bossIsDead){
					if (getCurrentLevel() >= 6) {
						isWin = true;
						setExp(getAccountID(), getAccountExp() + score);
						setCoins(getAccountID(), getAccountCoins() + coins);
						getCoins(getAccountID());
					}
					if (getCurrentLevel() < 6) setCurrentLevel(getCurrentLevel() + 1);
					if (!isWin)
					{
						lvlPlus(window, isLvlUpping);
						setExp(getAccountID(), getAccountExp() + score);
						getExp(getAccountID());
						setCoins(getAccountID(), getAccountCoins() + coins);
						getCoins(getAccountID());
						isLvlUp = true;
						isLvlUpping = true;
					}
				}
			}
		}
	}
}
void PLAYER::lvlUp() {
	switch (lvl) {
	case 1: if (score > 100) {lvl++; sp++; break; }
	case 2: if (score > 200) {lvl++; sp++; break; }
	case 3: if (score > 300) {lvl++; sp++; break; }
	case 4: if (score > 400) {lvl++; sp++; break; }
	case 5: if (score > 500) {lvl++; sp++; break; }
	case 6: if (score > 700) {lvl++; sp++; break; }
	case 7: if (score > 1000) {lvl++; sp++; break; }
	case 8: if (score > 1200) {lvl++; sp++; break; }
	case 9:if (score > 1400) {lvl++; sp++; break; }
	case 10:if (score > 1600) {lvl++; sp++; break; }
	case 11:if (score > 1800) {lvl++; sp++; break; }
	case 12:if (score > 2000) {lvl++; sp++; break; }
	case 13:if (score > 2200) {lvl++; sp++; break; }
	case 14:if (score > 2400) {lvl++; sp++; break; }
	case 15:if (score > 2600) {lvl++; sp++; break; }
	case 16:if (score > 2800) {lvl++; sp++; break; }
	case 17:if (score > 3000) {lvl++; sp++; break; }
	case 18:if (score > 3200) {lvl++; sp++; break; }
	case 19:if (score > 3400) {lvl++; sp++; break; }
	case 20:if (score > 3600) {lvl++; sp++; break; }
	case 21:if (score > 3800) {lvl++; sp++; break; }
	case 22:if (score > 4000) {lvl++; sp++; break; }
	case 23:if (score > 4200) {lvl++; sp++; break; }
	case 24:if (score > 4400) {lvl++; sp++; break; }
	case 25:if (score > 4600) {lvl++; sp++; break; }
	case 26:if (score > 4800) {lvl++; sp++; break; }
	case 27:if (score > 5000) {lvl++; sp++; break; }
	case 28:if (score > 5200) {lvl++; sp++; break; }
	case 29:if (score > 5500) {lvl++; sp++; break; }
	case 30:if (score > 5800) {lvl++; sp++; break; }
	case 31:if (score > 6000) {lvl++; sp++; break; }
	case 32:if (score > 6200) {lvl++; sp++; break; }
	case 33:if (score > 6500) {lvl++; sp++; break; }
	case 34:if (score > 6800) {lvl++; sp++; break; }
	case 35:if (score > 7000) {lvl++; sp++; break; }
	case 36:if (score > 8300) {lvl++; sp++; break; }
	case 37:if (score > 8800) {lvl++; sp++; break; }
	case 38:if (score > 9000) {lvl++; sp++; break; }
	case 39:if (score > 9300) {lvl++; sp++; break; }
	case 40:if (score > 9800) {lvl++; sp++; break; }
	case 41:if (score > 10000) {lvl++; sp++; break; }
	case 42:if (score > 10300) {lvl++; sp++; break; }
	case 43:if (score > 10800) {lvl++; sp++; break; }
	case 44:if (score > 11000) {lvl++; sp++; break; }
	case 45:break;
	}
}