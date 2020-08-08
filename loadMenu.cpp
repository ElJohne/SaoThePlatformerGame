#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <iostream>
#include "setups.h"
#include "play.h"
#include "levels.h"
#include <list>

using namespace sf;
bool isSaveChoosed1 = false; //Чи одне із збережень вибране
int choosedSave1; // Яке збереження вибране

int musicLevel = 0;

int loadStart(RenderWindow &window)
{
	//Берем коефіцієнт(відношення стандартного і вибраного розширення)
	float CoefX = getCoefX(window), CoefY = getCoefY(window);
	//Створюються текстові спрайти
	Font font;
	font.loadFromFile("config/font.ttf");
	int PlayerPos[2];//Для считування позиції персонажа
	int lvlSaved;//Для считування збереженого рівня
	int offSets[2];//Для считування оффсетів
	bool isOpen = false; //Чи збереження получилось відкрити
	//Шлях, по якому знаходяться збереження
	std::string path = "saves/save1.txt";
	String tempMap; //Для считування збереженої карти
	Text text[2]; //Для виведення збереженого рівня і дати збереження
	String str[2]; //Для считування збереженого рівня і дати збереження
	bool isEnemysAlive[10];
	int pHealth;
	int score;
	int potionCount;
	//Форматуємо текстову змінну:
	str[0] = "LVL: ";
	str[1] = "DATE: ";
	//Зчитування файлів збереження:
	try {
		std::fstream file;
		char temp[45] = " ";
		std::string temp1 = " ";
		file.open(path, std::fstream::in | std::fstream::out | std::fstream::app);
		file >> temp1;
		lvlSaved = std::stoi(temp1);
		str[0] += temp1;
		file >> temp;
		str[1] += temp;
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
		file >> temp1;
		pHealth = std::stoi(temp1);
		std::string tmp((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		tempMap = tmp;
		isOpen = true;
		file.close();
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
		std::cout << "File not Found: " << path << std::endl;
		std::cout << "Or file is empty" << std::endl;
	}
	//Цикл показу меню
	if (isOpen) {
		setCurrentLevel((lvlSaved - 1));
		setPlayerLeft(PlayerPos[0]);
		setPlayerTop(PlayerPos[1]);
		setOffSetX(offSets[0]);
		setOffSetY(offSets[1]);
		setPlayerHealth(pHealth);
		setCurrentScore(score);
		setPotionCount(potionCount);
		for (int i = 0; i < 10; i++)
		{
			setEnemyAlive(i, isEnemysAlive[i]);
		}
		std::string tmp[20], replace1 = "\n", replace2 = "";
		tempMap.replace(replace1, replace2);
		for (int i = 0; i < 20; i++)
		{
			tmp[i] = tempMap.substring(50 * i, 50);
		}
		String tmpSFMLString[20];
		for (int i = 0; i < 20; i++)
		{
			tmpSFMLString[i] = tmp[i];
		}
		setTileMap(lvlSaved - 1, tmpSFMLString);
		Sleep(200);
	}
	return 2;
}