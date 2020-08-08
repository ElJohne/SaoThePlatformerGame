#include <SFML\Graphics.hpp>
#include <SFML\Audio\Music.hpp>
#include <Windows.h>
#include "play.h"
#include "settings.h"
#include "setups.h"
#include "preGameMenu.h"
#include "loseScreen.h"

using namespace sf;

//рівень музики
int musicLvl = 0;
//Скільки раз закінчилась анімація
int done = 0;

int menuStart(RenderWindow &window) {
	//Сворення текстур для спрайтів, загрузка з файлів
	Texture startTexture, settingsTexture, quitTexture, backgrTexture, menuBgText, helloScreenTexture;
	Texture startTexture2, settingsTexture2, quitTexture2, infoBarTexture;
	startTexture.loadFromFile("img/StartButton.png");
	infoBarTexture.loadFromFile(get43() ? "img/infoBar-43.png" : "img/infoBar-169.png");
	settingsTexture.loadFromFile("img/SettingsButton.png");
	quitTexture.loadFromFile("img/QuitButton.png");
	startTexture2.loadFromFile("img/StartButtonDark.png");
	settingsTexture2.loadFromFile("img/SettingsButtonDark.png");
	quitTexture2.loadFromFile("img/QuitButtonDark.png");
	backgrTexture.loadFromFile(get43()?"img/Background-43.png":"img/Background-169.png");
	menuBgText.loadFromFile("img/MenuBackground.png");
	helloScreenTexture.loadFromFile(get43()?"img/helloScreen-43.png":"img/helloScreen-169.png");
	//Створення спрайтів, яким передаються текстури
	Sprite start(startTexture);
	Sprite settings(settingsTexture);
	Sprite quit(quitTexture);
	Sprite backgr(backgrTexture);
	Sprite menuBg(menuBgText);
	Sprite helloScreen(helloScreenTexture);
	Sprite infoBar(infoBarTexture);
	//Берем коефіцієнт(відношення стандартного і вибраного розширення)
	float CoefX = getCoefX(window), CoefY = getCoefY(window);
	//Міняється позиція спрайтів
	start.setPosition((get43() ? 625 : 885) * CoefX, 295 * CoefY);
	settings.setPosition((get43() ? 625 : 885) * CoefX, 470 * CoefY);
	quit.setPosition((get43() ? 625 : 885) * CoefX, 645 * CoefY);
	menuBg.setPosition((get43() ? 600 : 860) * CoefX, 270 * CoefY);
	start.setScale(CoefX*0.075, CoefY*0.075);
	settings.setScale(CoefX*0.075, CoefY*0.075);
	quit.setScale(CoefX*0.075, CoefY*0.075);
	menuBg.setScale(CoefX, CoefY);
	helloScreen.setScale(CoefX, CoefY);
	backgr.setScale(CoefX, CoefY);
	infoBar.setScale(CoefX, CoefY);
	Font font;
	font.loadFromFile("config/font.ttf");
	String pNameStr = getAccountName();
	String pStatusStr = getAccountStatus();
	String pCoinsStr = "Coins: " + std::to_string(getAccountCoins());
	String pExpStr = std::to_string(getAccountExp()) + "/" + std::to_string(getMaxScoreAccount());
	String pLvlStr = "Lv." + std::to_string(getAccountLvl());
	Text pName(pNameStr, font, 35);
	Text pStatus(pStatusStr, font, 30);
	Text pCoins(pCoinsStr, font, 20);
	Text pExp(pExpStr, font, 20);
	Text pLvl(pLvlStr, font, 30);
	pName.setOrigin((0.175 * pName.getCharacterSize()) * pName.getString().getSize(), (pName.getCharacterSize() / 2));
	pStatus.setOrigin((0.175 * pStatus.getCharacterSize()) * pStatus.getString().getSize(), (pStatus.getCharacterSize() / 2));
	pCoins.setOrigin((0.175 * pCoins.getCharacterSize()) * pCoins.getString().getSize(), (pCoins.getCharacterSize() / 2));
	pExp.setOrigin((0.175 * pExp.getCharacterSize()) * pExp.getString().getSize(), (pExp.getCharacterSize() / 2));
	pLvl.setOrigin((0.175 * pLvl.getCharacterSize()) * pLvl.getString().getSize(), (pLvl.getCharacterSize() / 2));
	pName.setPosition(258 * CoefX, 53 * CoefY);
	pStatus.setPosition(258 * CoefX, 468 * CoefY);
	pCoins.setPosition(112 * CoefX, 301 * CoefY);
	pExp.setPosition(398 * CoefX, 332 * CoefY);
	pLvl.setPosition(398 * CoefX, 296 * CoefY);
	pName.setScale(CoefX, CoefY);
	pStatus.setScale(CoefX, CoefY);
	pCoins.setScale(CoefX, CoefY);
	pExp.setScale(CoefX, CoefY);
	pLvl.setScale(CoefX, CoefY);
	pName.setFillColor(Color::Black);
	pStatus.setFillColor(Color::Black);
	pCoins.setFillColor(Color::Black);
	pExp.setFillColor(Color::Black);
	pLvl.setFillColor(Color::Black);
	//Заставка
	while(done != 1)
	{
		window.clear();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.draw(helloScreen);
		window.display();
		Sleep(500);
		done++;
	}
	//Створення фонової музики і загрузка її з файла
	musicLvl = getChoosenMenuMusic() * 10;
	Music music;
	music.openFromFile("sound/menuBackgroundSound.ogg");
	music.setVolume(musicLvl);
	music.play();
	// зациклення музики
	music.setLoop(true);
	window.clear();
	// вибраний пункт меню
	int numMenu1 = 0;
	//Цикл показу меню
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		pNameStr = getAccountName();
		pStatusStr = getAccountStatus();
		pCoinsStr = "Coins: " + std::to_string(getAccountCoins());
		pExpStr = std::to_string(getAccountExp()) + "/" + std::to_string(getMaxScoreAccount());
		pLvlStr = "Lv." + std::to_string(getAccountLvl());
		pName.setString(pNameStr);
		pStatus.setString(pStatusStr);
		pCoins.setString(pCoinsStr);
		pExp.setString(pExpStr);
		pLvl.setString(pLvlStr);
		//Провірка, чи курсор попадає на одну з кнопок
		//Якщо так, то елемент підсвічується(міняється текстура)
		//Start
		if (IntRect((get43() ? 625 : 885) * CoefX, 295 * CoefY, 150 * CoefX, 150 * CoefY).contains(Mouse::getPosition(window)))
		{
			start.setTexture(startTexture2);
			settings.setTexture(settingsTexture);
			quit.setTexture(quitTexture);
			numMenu1 = 1;
		}//Settings
		else if (IntRect((get43() ? 625 : 885) * CoefX, 470 * CoefY, 150 * CoefX, 150 * CoefY).contains(Mouse::getPosition(window)))
		{
			start.setTexture(startTexture);
			settings.setTexture(settingsTexture2);
			quit.setTexture(quitTexture);
			numMenu1 = 2;
		}//Quit
		else if (IntRect((get43() ? 625 : 885) * CoefX, 645 * CoefY, 150 * CoefX, 150 * CoefY).contains(Mouse::getPosition(window)))
		{
			start.setTexture(startTexture);
			settings.setTexture(settingsTexture);
			quit.setTexture(quitTexture2);
			numMenu1 = 3;
		}//Якщо не попадає ні на один, то ставимо всім стандартну текстуру
		else {
			start.setTexture(startTexture);
			settings.setTexture(settingsTexture);
			quit.setTexture(quitTexture);
			numMenu1 = 0;
		}
		//Якщо нажали ліву кнопку мишки:
		if (Mouse::isButtonPressed(Mouse::Left)) {
			//Start
			if (numMenu1 == 1)
			{
				Sleep(200); // затримка 0.2 секунди
				window.clear(); //Чистимо вікно
				//Там нижче короче воно працює як має бути, довго пояснитювати
				int tmp = preGameMenuStart(window);
			playAgain:
				int tmp2=0, tmp3=0;
				if (tmp == 3)
				{
					music.stop();
					tmp2 = gameStart(window, getCurrentLevel(), true); // Вкликаємо метод, який запускає ігру
				}
				if (tmp == 4) 
				{
					music.stop();
					tmp2 = gameStart(window, 0, false);
				}
				if (tmp2 == 1) {
					Sleep(200); 
					tmp3 = loseStart(window, false);
				}
				if (tmp2 == 2) {
					Sleep(200);
					tmp3 = loseStart(window, true);
				}
				if (tmp2 == 10) {
					return 10;
				}
				if (tmp3 == 3) {
					tmp = 3; 
					goto playAgain;
				}
				if (tmp3 == 5) {
					music.stop();
					tmp2 = gameStart(window, 0, false);
				}
				tmp = 0;
				tmp2 = 0;
				tmp3 = 0;
			}//Settings
			if (numMenu1 == 2) 
			{
				Sleep(200); // затримка 0.2 секунди
				window.clear(); //Чистимо вікно
				int tmp = settingsStart(window); // Викликаємо метод, який запускає настройки
				musicLvl = getChoosenMenuMusic() * 10;
				music.setVolume(musicLvl);
				if (tmp == 10) return 10;
			}//Quit
			if (numMenu1 == 3) return 0; // завершуємо програму з кодом 0
		}



		//Передає всі елементи на вікно
		window.draw(backgr);
		window.draw(infoBar);
		window.draw(pName);
		window.draw(pStatus);
		window.draw(pLvl);
		window.draw(pExp);
		window.draw(pCoins);
		window.draw(menuBg);
	    window.draw(start);
		window.draw(settings);
		window.draw(quit);
		//Виводимо всі елементи
		window.display();
	}

	return 0;
}