#pragma once
#include <SFML\Graphics.hpp>


int getAttackVar();
void setAttackVar(int i);
void setWidth(short width);
void setHeight(short height);
int getWidth();
int getHeight();
float getCoefY(sf::RenderWindow &window);
float getCoefX(sf::RenderWindow &window);
void saveToFile();
void loadFromFile();
int getChoosen();
void setChoosenRes(int Choosen);
int Resolutions[][2];
void setCurrentLevel(int lvl);
int getCurrentLevel();
void setPlayerLeft(int left);
void setPlayerTop(int top);
int getPlayerLeft();
int getPlayerTop();
void setOffSetX(int x);
void setOffSetY(int y);
int getOffSetY();
int getOffSetX();
int getChoosenMenuMusic();
int getChoosenGameMusic();
int getChoosenGameSound();
void setChoosenMenuMusic(int a);
void setChoosenGameMusic(int a);
void setChoosenGameSound(int a);
void setEnemyAlive(int i, bool is);
int getEnemyAlive(int i);
void setPlayerHealth(int health);
int getPlayerHealth();
int getMaxScore(int lvl);
void setCurrentScore(int score);
int getCurrentScore();
void setPotionCount(int count);
int getPotionCount();
bool get43();
void setAccountID(int id);
int getAccountID();
void setAccountName(sf::String Name);
sf::String getAccountName();
void setAccountStatus(sf::String Status);
sf::String getAccountStatus();
void setAccountCoins(int Coins);
int getAccountCoins();
void setAccountGold(int Gold);
int getAccountGold();
void setAccountLvl(int lvl);
int getAccountLvl();
void setAccountExp(int Exp);
int getAccountExp();
int getMaxScoreAccount();
bool getFullscreenMode();
void setFullscreenMode(bool screen);
void setEnemyAliveAnimal(int i, bool is);
int getEnemyAliveAnimal(int i);