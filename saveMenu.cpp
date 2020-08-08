#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <iostream>
#include <list>
#include <time.h>
#include "setups.h"
#include "play.h"
#include "settings.h"
#include "loadMenu.h"
#include "levels.h"

using namespace sf;
//Чи вибраний якийсь сейв
bool isSaveChoosed = false;
//Номер вибраного сейва
int choosedSave;
//Рівень музики
int musicLvl1 = 0;
//Позиція гравця
extern FloatRect playerPosition;
//Оффсети по Х-у і У-ку
extern float offsetX;
extern float offsetY;

int saveStart(RenderWindow &window)
{
	Font font;
	font.loadFromFile("config/font.ttf");
	//Берем коефіцієнт(відношення стандартного і вибраного розширення)
	float CoefX = getCoefX(window), CoefY = getCoefY(window);
	//Масиви, в які зберігаються всі загружені данні
	int PlayerPos[2];
	int lvlSaved;
	int offSets[2];
	std::string k1 = "sss12";
	std::string path = "saves/save1.txt";
	String k2 = k1;
	String tempMap;
	Sprite saves;
	Text text[2];
	String str[2];
	int score;
	int potionCount;
	bool isEnemysAlive[10];
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			TileMap[i][j] = getTileMap(i, j);
		}
	}
	//Форматуєм текстові змінні
	str[0] = "LVL: ";
	str[1] = "DATE: ";
	//Загружаємо всі данні з 5-ти збережень
	try {
		std::fstream file;
		char temp[15] = " ";
		std::string temp1 = " ";
		file.open(path, std::fstream::in | std::fstream::out | std::fstream::app);
		file >> temp1;
		k2 = temp1;
		lvlSaved = std::stoi(temp1);
		str[0] += k2;
		file >> temp;
		k2 = temp;
		str[1] += k2;
		file >> temp1;
		PlayerPos[0] = std::stoi(temp1);
		file >> temp1;
		PlayerPos[1] = std::stoi(temp1);
		file >> temp1;
		offSets[0] = std::stoi(temp1);
		file >> temp1;
		offSets[1] = std::stoi(temp1);
		file >> temp1;
		score = std::stoi(temp1);
		file >> temp1;
		potionCount = std::stoi(temp1);
		for (int j = 0; j < 10; j++)
		{
			file >> temp1;
			isEnemysAlive[j] = std::stoi(temp1);
		}
		std::string tmp((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		tempMap = tmp;
		file.close();
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
		std::cout << "File not Found: " << path << std::endl;
		std::cout << "Or file is empty" << std::endl;
	}
	//save
	//Видаляємо файл, щоб перезаписати
	try {
		remove("saves/save1.txt");
	}
	catch (std::exception &ex) {
		std::cout << "Can`t delete file: " << path << " is not exist" << std::endl;
	}
	//Відкриваємо вибраний файл і по черзі зберігаємо всю інформацію в нього
	std::fstream file1;
	try {
		file1.open(path, std::fstream::in | std::fstream::out | std::fstream::app);
		std::string sett;
		SYSTEMTIME st;
		GetSystemTime(&st);
		sett = std::to_string(st.wDay) + "." + std::to_string(st.wMonth) + "." + std::to_string(st.wYear);
		file1 << (getCurrentLevel() + 1);
		file1 << "\n";
		file1 << sett;
		file1 << "\n";
		file1 << playerPosition.left;
		file1 << "\n";
		file1 << playerPosition.top;
		file1 << "\n";
		file1 << offsetX;
		file1 << "\n";
		file1 << offsetY;
		file1 << "\n";
		file1 << getCurrentScore();
		file1 << "\n";
		file1 << getPotionCount();
		file1 << "\n";
		for (int i = 0; i < 10; i++)
		{
			file1 << getEnemyAlive(i);
			file1 << "\n";
		}
		file1 << getPlayerHealth();
		file1 << "\n";
		for (int i = 0; i < 20; i++)
		{
			std::string tempString = TileMap[getCurrentLevel()][i];
			file1 << tempString;
			file1 << "\n";
		}
		file1.close();
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
	}
	Sleep(200);
	return 0;
}