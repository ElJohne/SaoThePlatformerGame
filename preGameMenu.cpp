#include <SFML\Graphics.hpp>
#include <SFML\Audio\Music.hpp>
#include <Windows.h>
#include "play.h"
#include "settings.h"
#include "setups.h"
#include "loadMenu.h"
#include "preGameMenu.h"

using namespace sf;

int preGameMenuStart(RenderWindow &window) {
	//Сворення текстур для спрайтів, загрузка з файлів
	Texture backgrTexture, menuBgText, textBoxTexture, textBoxDarkTexture;
	backgrTexture.loadFromFile(get43()?"img/Background-43.png":"img/Background-169.png");
	menuBgText.loadFromFile("img/MenuBackground3.png");
	textBoxTexture.loadFromFile("img/textBox.png");
	textBoxDarkTexture.loadFromFile("img/textBoxDark.png");
	//Створення спрайтів, яким передаються текстури
	Sprite backgr(backgrTexture);
	Sprite menuBg(menuBgText);
	Sprite textBox1(textBoxTexture);
	Sprite textBox2(textBoxTexture);
	Sprite textBox3(textBoxTexture);
	//Створюємо тексти
	String newGameText = "New game", loadText = "Load", backText = "Back";
	Font font;
	font.loadFromFile("config/font.ttf");
	Text newGame(newGameText, font, 29), load(loadText, font, 30), back(backText, font, 30);
	//Берем коефіцієнт(відношення стандартного і вибраного розширення)
	float CoefX = getCoefX(window), CoefY = getCoefY(window);
	//Міняється позиція спрайтів
	textBox1.setPosition((get43() ? 580 : 860) * CoefX, 150 * CoefY);
	textBox2.setPosition((get43() ? 580 : 860) * CoefX, 250 * CoefY);
	textBox3.setPosition((get43() ? 580 : 860) * CoefX, 350 * CoefY);
	menuBg.setPosition((get43() ? 530 : 810) * CoefX, 75 * CoefY);
	newGame.setPosition((get43() ? 640 : 920) * CoefX, 156 * CoefY);
	load.setPosition((get43() ? 660 : 940) * CoefX, 256 * CoefY);
	back.setPosition((get43() ? 660 : 940) * CoefX, 356 * CoefY);
	textBox1.setScale(CoefX*0.2222, CoefY*0.25);
	textBox2.setScale(CoefX*0.2222, CoefY*0.25);
	textBox3.setScale(CoefX*0.2222, CoefY*0.25);
	menuBg.setScale(CoefX, CoefY);
	newGame.setScale(CoefX, CoefY);
	load.setScale(CoefX, CoefY);
	back.setScale(CoefX, CoefY);
	newGame.setFillColor(Color::Black);
	load.setFillColor(Color::Black);
	back.setFillColor(Color::Black);
	//Очищуєм вікно
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
		//Провірка, чи курсор попадає на одну з кнопок
		//Якщо так, то елемент підсвічується(міняється текстура)
		//New game
		if (IntRect((get43() ? 580 : 860) * CoefX, 150 * CoefY, 200 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			textBox1.setTexture(textBoxDarkTexture);
			textBox2.setTexture(textBoxTexture);
			textBox3.setTexture(textBoxTexture);
			newGame.setFillColor(Color::White);
			load.setFillColor(Color::Black);
			back.setFillColor(Color::Black);
			numMenu1 = 1;
		}//Load
		else if (IntRect((get43() ? 580 : 860) * CoefX, 250 * CoefY, 200 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			textBox1.setTexture(textBoxTexture);
			textBox2.setTexture(textBoxDarkTexture);
			textBox3.setTexture(textBoxTexture);
			newGame.setFillColor(Color::Black);
			load.setFillColor(Color::White);
			back.setFillColor(Color::Black);
			numMenu1 = 2;
		}//Back
		else if (IntRect((get43() ? 580 : 860) * CoefX, 350 * CoefY, 200 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			textBox1.setTexture(textBoxTexture);
			textBox2.setTexture(textBoxTexture);
			textBox3.setTexture(textBoxDarkTexture);
			newGame.setFillColor(Color::Black);
			load.setFillColor(Color::Black);
			back.setFillColor(Color::White);
			numMenu1 = 3;
		}//Якщо не попадає ні на один, то ставимо всім стандартну текстуру
		else {
			textBox1.setTexture(textBoxTexture);
			textBox2.setTexture(textBoxTexture);
			textBox3.setTexture(textBoxTexture);
			newGame.setFillColor(Color::Black);
			load.setFillColor(Color::Black);
			back.setFillColor(Color::Black);
			numMenu1 = 0;
		}
		//Якщо нажали ліву кнопку мишки:
		if (Mouse::isButtonPressed(Mouse::Left)) {
			//New game
			if (numMenu1 == 1)
			{
				Sleep(200);
				return 4;
			}//Load
			if (numMenu1 == 2)
			{
				Sleep(200);
				int tmp = loadStart(window);
				if (tmp == 2) return 3;
			}//Back
			if (numMenu1 == 3) {
				Sleep(200);
				return 0;
			}
		}

		//Передає всі елементи на вікно
		window.draw(backgr);
		window.draw(menuBg);
		window.draw(textBox1);
		window.draw(textBox2);
		window.draw(textBox3);
		window.draw(newGame);
		window.draw(load);
		window.draw(back);
		//Виводимо всі елементи
		window.display();
	}

	return 0;
}