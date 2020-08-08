#pragma once
#include <Windows.h>
#include <iostream>
#include <mysql.h>

//using namespace std;

int singIn(std::string name, std::string password);
int singUp(std::string name, std::string password);

void getLevel(int id);
void setLevel(int id, int lvl);
void getExp(int id);
void setExp(int id, int exp);
void getCoins(int id);
void setCoins(int id, int coins);
void getStatus(int id);
void setStatus(int id);
void getName(int id);
void getGold(int id);
void setGold(int id, int gold);