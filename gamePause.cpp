#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <fstream>
#include <time.h>
#include "settings.h"
#include "setups.h"
#include "loadMenu.h"
#include "play.h"
#include "saveMenu.h"
using namespace sf;

int pauseStart(RenderWindow &window) {
	//Сворення текстур для спрайтів, загрузка з файлів
	Texture menuBgText, backGround, textBoxTexture,textBoxDarkTexture;
	menuBgText.loadFromFile("img/MenuBackground2.png");
	textBoxTexture.loadFromFile("img/textBox.png");
	textBoxDarkTexture.loadFromFile("img/textBoxDark.png");
	//Створення спрайтів, яким передаються текстури
	Sprite textBox1(textBoxTexture), textBox2(textBoxTexture), textBox3(textBoxTexture), textBox4(textBoxTexture), textBox5(textBoxTexture), textBox6(textBoxTexture);
	Sprite menuBg(menuBgText);
	//
	float CoefX = getCoefX(window), CoefY = getCoefY(window);
	menuBg.setPosition((get43() ? 580 : 860) * CoefX, 75 * CoefY);
	textBox1.setPosition((get43() ? 630 : 910) * CoefX, 109 * CoefY);
	textBox2.setPosition((get43() ? 630 : 910) * CoefX, 193 * CoefY);
	textBox3.setPosition((get43() ? 630 : 910) * CoefX, 277 * CoefY);
	textBox4.setPosition((get43() ? 630 : 910) * CoefX, 361 * CoefY);
	textBox5.setPosition((get43() ? 630 : 910) * CoefX, 445 * CoefY);
	textBox6.setPosition((get43() ? 630 : 910) * CoefX, 529 * CoefY);
	textBox1.setScale(CoefX*0.2222, CoefY*0.25);
	textBox2.setScale(CoefX*0.2222, CoefY*0.25);
	textBox3.setScale(CoefX*0.2222, CoefY*0.25);
	textBox4.setScale(CoefX*0.2222, CoefY*0.25);
	textBox5.setScale(CoefX*0.2222, CoefY*0.25);
	textBox6.setScale(CoefX*0.2222, CoefY*0.25);
	menuBg.setScale(CoefX, CoefY);
	//Cтворення текстів
	String resume = "Resume";
	String options = "Options";
	String mainMenu = "Main menu";
	String exiT = "Exit";
	String save = "Save";
	String load = "Load";
	Font font;
	font.loadFromFile("config/font.ttf");
	Text resumeText(resume, font, 30);
	Text optionsText(options, font, 30);
	Text mainMenuText(mainMenu, font, 27);
	Text exitText(exiT, font, 30);
	Text saveText(save, font, 30);
	Text loadText(load, font, 30);
	//розміщуємо текст
	resumeText.setPosition((get43() ? 700 : 980) * CoefX, 114 * CoefY);
	saveText.setPosition((get43() ? 710 : 990) * CoefX, 198 * CoefY);
	loadText.setPosition((get43() ? 710 : 990) * CoefX, 282 * CoefY);
	optionsText.setPosition((get43() ? 695 : 975) * CoefX, 366 * CoefY);
	mainMenuText.setPosition((get43() ? 685 : 965) * CoefX, 452 * CoefY);
	exitText.setPosition((get43() ? 710 : 990) * CoefX, 534 * CoefY);
	resumeText.setScale(CoefX, CoefY);
	saveText.setScale(CoefX, CoefY);
	loadText.setScale(CoefX, CoefY);
	optionsText.setScale(CoefX, CoefY);
	mainMenuText.setScale(CoefX, CoefY);
	exitText.setScale(CoefX, CoefY);
	//ставимо ширину зовнішньої лінії
	resumeText.setFillColor(Color::Black);
	saveText.setFillColor(Color::Black);
	loadText.setFillColor(Color::Black);
	optionsText.setFillColor(Color::Black);
	mainMenuText.setFillColor(Color::Black);
	exitText.setFillColor(Color::Black);
	//
	int numMenu = 0;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		//Обробка наведення мишкою на кнопку
		//Resume
		if (IntRect((get43() ? 630 : 910) * CoefX, 109 * CoefY, 200 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			textBox1.setTexture(textBoxDarkTexture);
			textBox2.setTexture(textBoxTexture);
			textBox3.setTexture(textBoxTexture);
			textBox4.setTexture(textBoxTexture);
			textBox5.setTexture(textBoxTexture);
			textBox6.setTexture(textBoxTexture);
			resumeText.setFillColor(Color::White);
			optionsText.setFillColor(Color::Black);
			mainMenuText.setFillColor(Color::Black);
			exitText.setFillColor(Color::Black);
			loadText.setFillColor(Color::Black);
			saveText.setFillColor(Color::Black);
			numMenu = 1;
		}//Save
		else if (IntRect((get43() ? 630 : 910) * CoefX, 193 * CoefY, 200 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			textBox1.setTexture(textBoxTexture);
			textBox2.setTexture(textBoxDarkTexture);
			textBox3.setTexture(textBoxTexture);
			textBox4.setTexture(textBoxTexture);
			textBox5.setTexture(textBoxTexture);
			textBox6.setTexture(textBoxTexture);
			resumeText.setFillColor(Color::Black);
			optionsText.setFillColor(Color::Black);
			mainMenuText.setFillColor(Color::Black);
			exitText.setFillColor(Color::Black);
			loadText.setFillColor(Color::Black);
			saveText.setFillColor(Color::White);
			numMenu = 5;
		}//Load
		else if (IntRect((get43() ? 630 : 910) * CoefX, 277 * CoefY, 200 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			textBox1.setTexture(textBoxTexture);
			textBox2.setTexture(textBoxTexture);
			textBox3.setTexture(textBoxDarkTexture);
			textBox4.setTexture(textBoxTexture);
			textBox5.setTexture(textBoxTexture);
			textBox6.setTexture(textBoxTexture);
			resumeText.setFillColor(Color::Black);
			optionsText.setFillColor(Color::Black);
			mainMenuText.setFillColor(Color::Black);
			exitText.setFillColor(Color::Black);
			loadText.setFillColor(Color::White);
			saveText.setFillColor(Color::Black);
			numMenu = 6;
		}//Options
		else if (IntRect((get43() ? 630 : 910) * CoefX, 361 * CoefY, 200 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			textBox1.setTexture(textBoxTexture);
			textBox2.setTexture(textBoxTexture);
			textBox3.setTexture(textBoxTexture);
			textBox4.setTexture(textBoxDarkTexture);
			textBox5.setTexture(textBoxTexture);
			textBox6.setTexture(textBoxTexture);
			resumeText.setFillColor(Color::Black);
			optionsText.setFillColor(Color::White);
			mainMenuText.setFillColor(Color::Black);
			exitText.setFillColor(Color::Black);
			loadText.setFillColor(Color::Black);
			saveText.setFillColor(Color::Black);
			numMenu = 2;
		}//MainMenu
		else if (IntRect((get43() ? 630 : 910) * CoefX, 445 * CoefY, 200 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			textBox1.setTexture(textBoxTexture);
			textBox2.setTexture(textBoxTexture);
			textBox3.setTexture(textBoxTexture);
			textBox4.setTexture(textBoxTexture);
			textBox5.setTexture(textBoxDarkTexture);
			textBox6.setTexture(textBoxTexture);
			resumeText.setFillColor(Color::Black);
			optionsText.setFillColor(Color::Black);
			mainMenuText.setFillColor(Color::White);
			exitText.setFillColor(Color::Black);
			loadText.setFillColor(Color::Black);
			saveText.setFillColor(Color::Black);
			numMenu = 3;
		}//Exit
		else if (IntRect((get43() ? 630 : 910) * CoefX, 529 * CoefY, 200 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			textBox1.setTexture(textBoxTexture);
			textBox2.setTexture(textBoxTexture);
			textBox3.setTexture(textBoxTexture);
			textBox4.setTexture(textBoxTexture);
			textBox5.setTexture(textBoxTexture);
			textBox6.setTexture(textBoxDarkTexture);
			resumeText.setFillColor(Color::Black);
			optionsText.setFillColor(Color::Black);
			mainMenuText.setFillColor(Color::Black);
			exitText.setFillColor(Color::White);
			loadText.setFillColor(Color::Black);
			saveText.setFillColor(Color::Black);
			numMenu = 4;
		}
		else {
			textBox1.setTexture(textBoxTexture);
			textBox2.setTexture(textBoxTexture);
			textBox3.setTexture(textBoxTexture);
			textBox4.setTexture(textBoxTexture);
			textBox5.setTexture(textBoxTexture);
			textBox6.setTexture(textBoxTexture);
			resumeText.setFillColor(Color::Black);
			optionsText.setFillColor(Color::Black);
			mainMenuText.setFillColor(Color::Black);
			exitText.setFillColor(Color::Black);
			loadText.setFillColor(Color::Black);
			saveText.setFillColor(Color::Black);
			numMenu = 0;
		}
		//Якщо нажати Esc меню закривається
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			Sleep(200);
			break;
		}
		//Обробка натиснення лівої кнопки мишки
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (numMenu == 1) {//Resume - виходимо з меню
				return 0;
			}// Options - запускаємо настройки
			if (numMenu == 2) {
				Sleep(200);
				if (settingsStart(window) == 10) {
					window.setMouseCursorVisible(false);
					return 10;
				}
				break;
			}//Main menu - виходимо до головного меню
			if (numMenu == 3) {
				Sleep(200);
				return 1;
			}//Виходимо з програми
			if (numMenu == 4) {
				exit(0);
			}//Запускаємо меню збереження
			if (numMenu == 5) {
				Sleep(200);
				saveStart(window);
				break;
			}//Запускаємо меню загрузки збережень
			if (numMenu == 6) {
				Sleep(200);
				if (loadStart(window) == 2) {
					window.setMouseCursorVisible(false);
					return 2;
				}
				else {
					window.setMouseCursorVisible(false);
					break;
				}
			}
		}



		//Передає всі елементи на вікно
		window.draw(menuBg);
		window.draw(textBox1);
		window.draw(textBox2);
		window.draw(textBox3);
		window.draw(textBox4);
		window.draw(textBox5);
		window.draw(textBox6);
		window.draw(resumeText);
		window.draw(optionsText);
		window.draw(mainMenuText);
		window.draw(exitText);
		window.draw(loadText);
		window.draw(saveText);
		//Виводимо всі елементи
		window.display();
	}
	return 0;
}