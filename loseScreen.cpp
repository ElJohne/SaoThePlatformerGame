#include <SFML\Graphics.hpp>
#include <SFML\Audio\Music.hpp>
#include <Windows.h>
#include "play.h"
#include "settings.h"
#include "setups.h"
#include "loadMenu.h"
#include "preGameMenu.h"

using namespace sf;

int loseStart(RenderWindow &window, bool win) {
	//Сворення текстур для спрайтів, загрузка з файлів
	Texture backgrTexture, backgrTexture2, menuBgText, textBoxTexture,textBoxDarkTexture;
	//Загружаємо фон відповідно до результату гри
	if (win)backgrTexture.loadFromFile(get43()?"img/winText-43.png":"img/winText-169.png");
	if (!win)backgrTexture.loadFromFile(get43()?"img/deathScreen-43.png":"img/deathScreen-169.png");
	if (!win)backgrTexture2.loadFromFile(get43() ? "img/Background-43.png" : "img/Background-169.png");
	menuBgText.loadFromFile("img/MenuBackground2.png");
	textBoxTexture.loadFromFile("img/textBox.png");
	textBoxDarkTexture.loadFromFile("img/textBoxDark.png");
	//Створення спрайтів, яким передаються текстури
	Sprite backgr(backgrTexture);
	Sprite backgr2(backgrTexture2);
	Sprite menuBg(menuBgText);
	Sprite textBox1(textBoxTexture);
	Sprite textBox2(textBoxTexture);
	Sprite textBox3(textBoxTexture);
	Sprite textBox4(textBoxTexture);
	//Створення текстів
	String newGameText = "New game", loadText = "Load", backText = "Main menu", exitText = "Exit";
	Font font;
	font.loadFromFile("config/font.ttf");
	Text newGame(newGameText, font, 29), load(loadText, font, 30), back(backText, font, 28), Exit(exitText, font, 30);
	//Берем коефіцієнт(відношення стандартного і вибраного розширення)
	float CoefX = getCoefX(window), CoefY = getCoefY(window);
	//Міняється позиція спрайтів
	textBox1.setPosition((get43() ? 630 : 910) * CoefX, 150 * CoefY);
	textBox2.setPosition((get43() ? 630 : 910) * CoefX, 250 * CoefY);
	textBox3.setPosition((get43() ? 630 : 910) * CoefX, 350 * CoefY);
	textBox4.setPosition((get43() ? 630 : 910) * CoefX, 450 * CoefY);
	menuBg.setPosition((get43() ? 580 : 860) * CoefX, 75 * CoefY);
	newGame.setPosition((get43() ? 695 : 965) * CoefX, 156 * CoefY);
	load.setPosition((get43() ? 710 : 990) * CoefX, 256 * CoefY);
	back.setPosition((get43() ? 685 : 965) * CoefX, 356 * CoefY);
	Exit.setPosition((get43() ? 710 : 990) * CoefX, 456 * CoefY);
	textBox1.setScale(CoefX*0.2222, CoefY*0.25);
	textBox2.setScale(CoefX*0.2222, CoefY*0.25);
	textBox3.setScale(CoefX*0.2222, CoefY*0.25);
	textBox4.setScale(CoefX*0.2222, CoefY*0.25);
	menuBg.setScale(CoefX, CoefY);
	backgr.setScale(CoefX, CoefY);
	backgr2.setScale(CoefX, CoefY);
	newGame.setScale(CoefX, CoefY);
	load.setScale(CoefX, CoefY);
	back.setScale(CoefX, CoefY);
	Exit.setScale(CoefX, CoefY);
	newGame.setFillColor(Color::Black);
	load.setFillColor(Color::Black);
	back.setFillColor(Color::Black);
	Exit.setFillColor(Color::Black);
	///////////////////////
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
		if (IntRect((get43() ? 630 : 910) * CoefX, 150 * CoefY, 200 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			textBox1.setTexture(textBoxDarkTexture);
			textBox2.setTexture(textBoxTexture);
			textBox3.setTexture(textBoxTexture);
			textBox4.setTexture(textBoxTexture);
			newGame.setFillColor(Color::White);
			load.setFillColor(Color::Black);
			back.setFillColor(Color::Black);
			Exit.setFillColor(Color::Black);
			numMenu1 = 1;
		}//load
		else if (IntRect((get43() ? 630 : 910) * CoefX, 250 * CoefY, 200 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			textBox1.setTexture(textBoxTexture);
			textBox2.setTexture(textBoxDarkTexture);
			textBox3.setTexture(textBoxTexture);
			textBox4.setTexture(textBoxTexture);
			newGame.setFillColor(Color::Black);
			load.setFillColor(Color::White);
			back.setFillColor(Color::Black);
			Exit.setFillColor(Color::Black);
			numMenu1 = 2;
		}//Main Menu
		else if (IntRect((get43() ? 630 : 910) * CoefX, 350 * CoefY, 200 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			textBox1.setTexture(textBoxTexture);
			textBox2.setTexture(textBoxTexture);
			textBox3.setTexture(textBoxDarkTexture);
			textBox4.setTexture(textBoxTexture);
			newGame.setFillColor(Color::Black);
			load.setFillColor(Color::Black);
			back.setFillColor(Color::White);
			Exit.setFillColor(Color::Black);
			numMenu1 = 3;
		}//Exit
		else if (IntRect((get43() ? 630 : 910) * CoefX, 450 * CoefY, 200 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			textBox1.setTexture(textBoxTexture);
			textBox2.setTexture(textBoxTexture);
			textBox3.setTexture(textBoxTexture);
			textBox4.setTexture(textBoxDarkTexture);
			newGame.setFillColor(Color::Black);
			load.setFillColor(Color::Black);
			back.setFillColor(Color::Black);
			Exit.setFillColor(Color::White);
			numMenu1 = 4;
		}//Якщо не попадає ні на один, то ставимо всім стандартну текстуру
		else {
			textBox1.setTexture(textBoxTexture);
			textBox2.setTexture(textBoxTexture);
			textBox3.setTexture(textBoxTexture);
			textBox4.setTexture(textBoxTexture);
			newGame.setFillColor(Color::Black);
			load.setFillColor(Color::Black);
			back.setFillColor(Color::Black);
			Exit.setFillColor(Color::Black);
			numMenu1 = 0;
		}
		//Якщо нажали ліву кнопку мишки:
		if (Mouse::isButtonPressed(Mouse::Left)) {
			//New game
			if (numMenu1 == 1)
			{
				Sleep(200);
				return 5;
			}//Load
			if (numMenu1 == 2)
			{
				Sleep(200);
				int tmp = loadStart(window);
				if (tmp == 2) return 3;
			}//MainMenu
			if (numMenu1 == 3) Sleep(200); return 0;
			//Exit
			if (numMenu1 == 4) Sleep(200); exit(0); // завершуємо програму з кодом 0
		}

		//Передає всі елементи на вікно
		if (!win)window.draw(backgr2);
		window.draw(backgr);
		window.draw(menuBg);
		window.draw(textBox1);
		window.draw(textBox2);
		window.draw(textBox3);
		window.draw(textBox4);
		window.draw(newGame);
		window.draw(load);
		window.draw(back);
		window.draw(Exit);
		//Виводимо всі елементи
		window.display();
	}

	return 0;
}