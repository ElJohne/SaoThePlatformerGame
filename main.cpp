#include <iostream>
#include "menu.h"
#include "setups.h"
#include "settings.h"
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "dbConnect.h"
#include "login.h"

using namespace std;

int main() {
	HWND hWnd = GetConsoleWindow();
	//ShowWindow(hWnd, SW_HIDE);
	int i = 0;
restart:
	//Метод, який загружає збережені в файл настройки
	loadFromFile();
	//Створення вікна, за яким буде працювати програма
	sf::RenderWindow window(sf::VideoMode(getWidth(), getHeight()), "Sword Art Online: The Platformer", (getFullscreenMode()? sf::Style::Fullscreen : sf::Style::Titlebar));
	getCoefX(window);
	getCoefY(window);
	//Метод, який запускає меню
	logOut:
	if (i == 0) login(window);
	i++;
	int tmp = menuStart(window);
	if (tmp == 10) goto restart;
	if (tmp == 0) {
		i = 0;
		goto logOut;
	}
	return 0;
}