#include <SFML\Graphics.hpp>
#include <fstream>
#include <string>
#include "settings.h"

//Висота, ширина екрана
int hg, wd;
//Вибране розширення екрану
int choosen;
//Збережений рівень
int savedLevel;
//Масив з розширеннями
int Resolutions[6][2] = { {640 , 480}, { 800,600 }, { 1024,768 }, {1280 , 720}, {1400, 1050} , {1920 , 1080} };
//Змінні для збереження координат персонажа
int pLeft, pTop;
//Змінні для збереження оффсетів(для того, щоб в поле зору не попадали предмети за рівнем)
int offSetX, offSetY;
//Змінні для збереження рівня гучності звуків, музики
int menuMusicLevel, playMusicLevel, playSoundLevel;
//Масив для збереження стану ворогів(живі\мертві)
int isEnemAlive[10] = { true,true,true,true,true,true,true,true,true,true };
int isEnemAliveAnimal[10] = { true,true,true,true,true,true,true,true,true,true };
//Збережений рівень життя гравця
int savedPlayerHealth = 10;
//Поточна кількість очків
int currentScore;
int countPotion;
bool is43 = false;
int accountID;
int accountLvl;
int accountExp;
int accountCoins;
int accountGold;
sf::String accountName;
sf::String accountStatus;
bool isFullScreen;
int attackVar;


int getAttackVar() {
	return attackVar;
}
void setAttackVar(int i) {
	attackVar = i;
}
bool getFullscreenMode() {
	return isFullScreen;
}
void setFullscreenMode(bool screen) {
	isFullScreen = screen;
}
int getMaxScoreAccount() {
	switch (accountLvl) {
	case 0:return 500;
	case 1:return 1000;
	case 2:return 3000;
	case 3:return 7000;
	case 4:return 10000;
	case 5:return 12500;
	case 6:return 15000;
	case 7:return 20000;
	case 8:return 25000;
	case 9:return 30000;
	case 10:return 35000;
	case 11:return 40000;
	case 12:return 45000;
	case 13:return 50000;
	case 14:return 55000;
	case 15:return 60000;
	case 16:return 70000;
	case 17:return 80000;
	case 18:return 90000;
	case 19:return 95000;
	case 20:return 100000;
	case 21:return 110000;
	case 22:return 120000;
	case 23:return 130000;
	case 24:return 140000;
	case 25:return 150000;
	default: return 999999;
	}
}
void setAccountName(sf::String Name) {
	accountName = Name; 
}
sf::String getAccountName() { 
	return accountName; 
}
void setAccountStatus(sf::String Status) {
	accountStatus = Status; 
}
sf::String getAccountStatus() {
	return accountStatus; 
}
void setAccountCoins(int Coins) {
	accountCoins = Coins; 
}
int getAccountCoins() {
	return accountCoins; 
}
void setAccountGold(int Gold) {
	accountGold = Gold; 
}
int getAccountGold() {
	return accountGold; 
}
void setAccountLvl(int lvl) { 
	accountLvl = lvl; 
}
int getAccountLvl() {
	return accountLvl; 
}
void setAccountExp(int Exp) {
	accountExp = Exp; 
}
int getAccountExp() { 
	return accountExp; 
}
void setAccountID(int id) {
	accountID = id; 
}
int getAccountID() {
	return accountID; 
}
bool get43() {
	return is43;
}
void setPotionCount(int count) {
	countPotion = count;
}
int getPotionCount() {
	return countPotion;
}
//Встановлює кількість набраних очків
void setCurrentScore(int score) {
	currentScore = score;
}
//Повертає кількість набраних очків
int getCurrentScore() {
	return currentScore;
}
//Повертає максимальну кількість очків на рівні 
int getMaxScore(int lvl) {
	switch (lvl) {
	case 0: return 850;
	case 1: return 1050;
	case 2: return 850;
	case 3: return 1050;
	case 4: return 750;
	case 5: return 800;
	}
}
//Встановити рівень життя гравця
void setPlayerHealth(int health) {
	savedPlayerHealth = health;
}
//Взяти рівень життя гравця
int getPlayerHealth() {
	return savedPlayerHealth;
}
//Встановити чи живий ворог на рівні
void setEnemyAlive(int i, bool is) {
	isEnemAlive[i] = is;
}
//Загрузити чи живий ворог на рівні
int getEnemyAlive(int i) {
	return isEnemAlive[i];
}
void setEnemyAliveAnimal(int i, bool is) {
	isEnemAliveAnimal[i] = is;
}
//Загрузити чи живий ворог на рівні
int getEnemyAliveAnimal(int i) {
	return isEnemAliveAnimal[i];
}
//Взяти гучність музики в меню
int getChoosenMenuMusic() {
	return menuMusicLevel;
}
//Взяти гучність музики в ігрі
int getChoosenGameMusic() {
	return playMusicLevel;
}
//Взяти гучність звуків в ігрі
int getChoosenGameSound() {
	return playSoundLevel;
}
//Встановити гучність музики в меню
void setChoosenMenuMusic(int a) {
	menuMusicLevel = a;
}
//Встановити гучність музики в ігрі
void setChoosenGameMusic(int a) {
	playMusicLevel = a;
}
//Встановити гучність звуків в ігрі
void setChoosenGameSound(int a) {
	playSoundLevel = a;
}
//Встановлює оффсет по Х-у
void setOffSetX(int x) {
	offSetX = x;
}
//Встановлює оффсет по У-ку
void setOffSetY(int y) {
	offSetY = y;
}
//Передає оффсет по У-ку
int getOffSetY() {
	return offSetY;
}
//Передає оффсет по Х-у
int getOffSetX() {
	return offSetX;
}
//Встановлює координати персонажа по Х-у
void setPlayerLeft(int left) {
	pLeft = left;
}
//Встановлює координати персонажа по У-ку
void setPlayerTop(int top) {
	pTop = top;
}
//Передає координати персонажа по Х-у
int getPlayerLeft() {
	return pLeft;
}
//Передає координати персонажа по У-ку
int getPlayerTop() {
	return pTop;
}
//Встановлює поточний рівень
void setCurrentLevel(int lvl) {
	savedLevel = lvl;
}
//Передає поточний рівень
int getCurrentLevel() {
	return savedLevel;
}
//Берем відношення стандартного розширення до вибраного
float getCoefX(sf::RenderWindow &window) {
	switch(window.getSize().x) {
	case 1920:
		is43 = false;
		return 1;
		break;
	case 1400:
		is43 = true;
		return 1;
		break;
	case 1024:
		is43 = true;
		return 0.7314;
		break;
	case 1280:
		is43 = false;
		return 0.6666;
		break;
	case 800:
		is43 = true;
		return 0.5714;
		break;
	case 640:
		is43 = true;
		return 0.4571;
		break;
	}
}
//Берем відношення стандартного розширення до вибраного
float getCoefY(sf::RenderWindow &window) {
	switch (window.getSize().y) 
	{
	case 1080: 
		is43 = false;
		return 1; 
		break;
	case 1050:
		is43 = true;
		return 1; 
		break;
	case 768:
		is43 = true;
		return 0.7314;
		break;
	case 720:
		is43 = false;
		return 0.6666;
		break;
	case 600:
		is43 = true;
		return 0.5714;
		break;
	case 480:
		is43 = true;
		return 0.4571;
		break;
	}
}
//Загружає всі настройки з файла
void loadFromFile() {
	try {
		std::string sett;
		std::fstream file;
		file.open("config/settings.txt", std::fstream::in | std::fstream::out | std::fstream::app);
		file >> sett;
		wd = std::stoi(sett);
		file >> sett;
		hg = std::stoi(sett);
		file >> sett;
		choosen = stoi(sett);
		file >> sett;
		menuMusicLevel = stoi(sett);
		file >> sett;
		playMusicLevel = stoi(sett);
		file >> sett;
		playSoundLevel = stoi(sett);
		file >> sett;
		isFullScreen = stoi(sett);
		file.close();
	}
	catch (std::exception &ex)
	{
		wd = 1024;
		hg = 768;
		isFullScreen = true;
	}
}
//Зберігаємо в файл всі настройки
void saveToFile(){
	try {
		remove("config/settings.txt");
		std::fstream file;
		file.open("config/settings.txt", std::fstream::in | std::fstream::out | std::fstream::app);
		file << wd << "\n";
		file << hg << "\n";
		file << choosen << "\n";
		file << menuMusicLevel << "\n";
		file << playMusicLevel << "\n";
		file << playSoundLevel << "\n";
		file << isFullScreen << "\n";
		file.close();
		loadFromFile();
	}
	catch (std::exception &ex) 
	{
		
	}
}
//Повертає номер вибраного розширення
int getChoosen() {
	return choosen;
}
//Ставить значення вибраного розширення
void setChoosenRes(int Choosen) {
	choosen = Choosen;
}
//Повертає ширину екрану
int getWidth() {
	return wd;
}
//Повертає висоту екрану
int getHeight() {
	return hg;
}
//Ставить ширину екрану
void setWidth(short width) {
	wd = width;
}
//Ставить висоту екрану
void setHeight(short height) {
	hg = height;
}