#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <SFML\Audio\Music.hpp>
#include "play.h"
#include "settings.h"
#include "setups.h"
#include "loadMenu.h"
#include "preGameMenu.h"
#include "dbConnect.h"

using namespace sf;

int enterNamePass;
bool registration;

int login(RenderWindow & window)
{
	bool isError = false;
	bool isErrorReg = false;
	Texture wrongRegTexture, wrongTexture, backgrTexture, textBoxTexture, textBoxDarkTexture, yesTexture, noTexture,yesDarkTexture, noDarkTexture;
	wrongRegTexture.loadFromFile("img/wrongReg.png");
	wrongTexture.loadFromFile("img/wrongLog.png");
	yesTexture.loadFromFile("img/Yes.png");
	noTexture.loadFromFile("img/No.png");
	yesDarkTexture.loadFromFile("img/YesDark.png");
	noDarkTexture.loadFromFile("img/NoDark.png");
	backgrTexture.loadFromFile(get43() ? "img/loginWindow-43.png" : "img/loginWindow-169.png");
	textBoxTexture.loadFromFile("img/textBox.png");
	textBoxDarkTexture.loadFromFile("img/textBoxDark.png");
	//Створення спрайтів, яким передаються текстури
	Sprite backgr(backgrTexture);
	Sprite textBox1(textBoxTexture);
	Sprite textBox2(textBoxTexture);
	Sprite yes(yesTexture);
	Sprite no(noTexture);
	Sprite wrong(wrongTexture);
	Sprite wrongReg(wrongRegTexture);
	//Берем коефіцієнт(відношення стандартного і вибраного розширення)
	float CoefX = getCoefX(window), CoefY = getCoefY(window);
	//Створюємо тексти
	String ExitText = "Exit", SinginText = "Sing-In", SingupText = "Sing-Up", EnterText = "Link Start!";
	String usernameStr;
	String passwordStr;
	registration = false;
	Font font;
	if (!font.loadFromFile("config/font.ttf"))
	{
		std::cout << "Can`t find font in: config/font.tff";
	}
	Text usernameTxt(L"Username", font, 55), passwordTxt(L"Password", font, 55);
	Text Singin(SinginText, font, 30), Singup(SingupText, font, 30);
	usernameTxt.setPosition((!get43()? 950 : 703) * CoefX, (!get43() ? 375 : 330) * CoefY);
	passwordTxt.setPosition((!get43() ? 950 : 703) * CoefX, (!get43() ? 555 : 517) * CoefY);
	textBox1.setPosition((!get43() ? 611 : 372) * CoefX, (!get43() ? 985 : 960) * CoefY);
	textBox2.setPosition((!get43() ? 1074 : 835) * CoefX, (!get43() ? 985 : 960) * CoefY);
	Singin.setPosition((!get43() ? 673 : 434) * CoefX, (!get43() ? 990 : 965) * CoefY);
	Singup.setPosition((!get43() ? 1136 : 897) * CoefX, (!get43() ? 990 : 965) * CoefY);
	yes.setPosition((!get43() ? 667 : 435) * CoefX, (!get43() ? 776 : 745) * CoefY);
	no.setPosition((!get43() ? 1127 : 865) * CoefX, (!get43() ? 776 : 745) * CoefY);
	wrong.setPosition((!get43() ? 700 : 455) * CoefX, (!get43() ? 215 : 172) * CoefY);
	wrongReg.setPosition((!get43() ? 700 : 455) * CoefX, (!get43() ? 215 : 172) * CoefY);
	textBox1.setScale(CoefX*0.2222, CoefY*0.25);
	textBox2.setScale(CoefX*0.2222, CoefY*0.25);
	yes.setScale(CoefX*0.05, CoefY*0.05);
	no.setScale(CoefX*0.05, CoefY*0.05);
	backgr.setScale(CoefX, CoefY);
	Singin.setScale(CoefX, CoefY);
	Singup.setScale(CoefX, CoefY);
	passwordTxt.setScale(CoefX, CoefY);
	usernameTxt.setScale(CoefX, CoefY);
	wrong.setScale(CoefX, CoefY);
	wrongReg.setScale(CoefX, CoefY);
	Singin.setFillColor(Color::Black);
	Singup.setFillColor(Color::Black);
	passwordTxt.setFillColor(Color::Black);
	usernameTxt.setFillColor(Color::Black);
	bool isEnterPressed = false;
	//Очищуєм вікно
	window.clear();
	// вибраний пункт меню
	int numMenu1 = 0;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			// Close window : exit
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)
			{
				//Меняем фокус на нужный объект
			}
			if (event.type == sf::Event::TextEntered)
			{
				// отсекаем не ASCII символы
				if (event.text.unicode < 128 || event.text.unicode == 0x8 && event.text.unicode != 0xD)
				{
					if (enterNamePass == 1) {
						switch (event.text.unicode)
						{
						case 0x8://Backspace
							if (!usernameStr.isEmpty())
								usernameStr.erase(usernameStr.getSize() - 1);
							break;
						case 0x09://Tab
							enterNamePass = 2;
							break;
						case 0x1B:
							break;
						default:
							if (usernameStr.getSize() < 15)usernameStr += static_cast<char>(event.text.unicode);
						}
						usernameTxt.setString(usernameStr);
					}
					else if (enterNamePass == 2) {
						switch (event.text.unicode)
						{
						case 0x8://Backspace
							if (!passwordStr.isEmpty())
								passwordStr.erase(passwordStr.getSize() - 1);
							break;
						case 0x09://Tab
							enterNamePass = 1;
							break;
						case 0x1B:
							break;
						default:
							if (passwordStr.getSize() < 15)passwordStr += static_cast<char>(event.text.unicode);
						}
						passwordTxt.setString(passwordStr);
					}
				}
			}
		}
		//Enter
		if (IntRect((!get43() ? 667 : 435) * CoefX, (!get43() ? 776 : 745) * CoefY, 100 * CoefX, 100 * CoefY).contains(Mouse::getPosition(window)))
		{
			yes.setTexture(yesDarkTexture);
			no.setTexture(noTexture);
			textBox1.setTexture(registration ? textBoxTexture : textBoxDarkTexture);
			textBox2.setTexture(registration ? textBoxDarkTexture : textBoxTexture);
			Singin.setFillColor(registration ? Color::Black : Color::White);
			Singup.setFillColor(registration ? Color::White : Color::Black);
			usernameTxt.setFillColor(enterNamePass == 1 ? Color::White : Color::Black);
			passwordTxt.setFillColor(enterNamePass == 2 ? Color::White : Color::Black);
			numMenu1 = 1;
		}//Exit
		else if (IntRect((!get43() ? 1127 : 865) * CoefX, (!get43() ? 776 : 745) * CoefY, 100 * CoefX, 100 * CoefY).contains(Mouse::getPosition(window)))
		{
			yes.setTexture(yesTexture);
			no.setTexture(noDarkTexture);
			textBox1.setTexture(registration ? textBoxTexture : textBoxDarkTexture);
			textBox2.setTexture(registration ? textBoxDarkTexture : textBoxTexture);
			Singin.setFillColor(registration ? Color::Black : Color::White);
			Singup.setFillColor(registration ? Color::White : Color::Black);
			usernameTxt.setFillColor(enterNamePass == 1 ? Color::White : Color::Black);
			passwordTxt.setFillColor(enterNamePass == 2 ? Color::White : Color::Black);
			numMenu1 = 2;
		}//Singin
		else if (IntRect((!get43() ? 611 : 372) * CoefX, (!get43() ? 985 : 960) * CoefY, 200 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			yes.setTexture(yesTexture);
			no.setTexture(noTexture);
			textBox1.setTexture(textBoxDarkTexture);
			textBox2.setTexture(registration ? textBoxDarkTexture : textBoxTexture);
			Singin.setFillColor(Color::White);
			Singup.setFillColor(registration ? Color::White : Color::Black);
			usernameTxt.setFillColor(enterNamePass == 1 ? Color::White : Color::Black);
			passwordTxt.setFillColor(enterNamePass == 2 ? Color::White : Color::Black);
			numMenu1 = 3;
		}//Singup
		else if (IntRect((!get43() ? 1074 : 835) * CoefX, (!get43() ? 985 : 960) * CoefY, 200 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			yes.setTexture(yesTexture);
			no.setTexture(noTexture);
			textBox1.setTexture(registration ? textBoxTexture : textBoxDarkTexture);
			textBox2.setTexture(textBoxDarkTexture);
			Singin.setFillColor(registration ? Color::Black : Color::White);
			Singup.setFillColor(Color::White);
			usernameTxt.setFillColor(enterNamePass == 1 ? Color::White : Color::Black);
			passwordTxt.setFillColor(enterNamePass == 2 ? Color::White : Color::Black);
			numMenu1 = 4;
		}//Username
		else if (IntRect((!get43() ? 940 : 694) * CoefX, (!get43() ? 365 : 323) * CoefY, 380 * CoefX, 80 * CoefY).contains(Mouse::getPosition(window)))
		{
			yes.setTexture(yesTexture);
			no.setTexture(noTexture);
			textBox1.setTexture(registration ? textBoxTexture : textBoxDarkTexture);
			textBox2.setTexture(registration ? textBoxDarkTexture : textBoxTexture);
			Singin.setFillColor(registration ? Color::Black : Color::White);
			Singup.setFillColor(registration ? Color::White : Color::Black);
			usernameTxt.setFillColor(Color::White);
			passwordTxt.setFillColor(enterNamePass == 2 ? Color::White : Color::Black);
			numMenu1 = 5;
		}//Password
		else if (IntRect((!get43() ? 940 : 694) * CoefX, (!get43() ? 546 : 507) * CoefY, 380 * CoefX, 80 * CoefY).contains(Mouse::getPosition(window)))
		{
			yes.setTexture(yesTexture);
			no.setTexture(noTexture);
			textBox1.setTexture(registration ? textBoxTexture : textBoxDarkTexture);
			textBox2.setTexture(registration ? textBoxDarkTexture : textBoxTexture);
			Singin.setFillColor(registration ? Color::Black : Color::White);
			Singup.setFillColor(registration ? Color::White : Color::Black);
			usernameTxt.setFillColor(enterNamePass == 1 ? Color::White : Color::Black);
			passwordTxt.setFillColor(Color::White);
			numMenu1 = 6;
		}
		else {
			yes.setTexture(yesTexture);
			no.setTexture(noTexture);
			textBox1.setTexture(registration ? textBoxTexture : textBoxDarkTexture);
			textBox2.setTexture(registration ? textBoxDarkTexture : textBoxTexture);
			Singin.setFillColor(registration ? Color::Black : Color::White);
			Singup.setFillColor(registration ? Color::White : Color::Black);
			usernameTxt.setFillColor(enterNamePass == 1 ? Color::White : Color::Black);
			passwordTxt.setFillColor(enterNamePass == 2 ? Color::White : Color::Black);
			numMenu1 = 0;
		}
		//Якщо нажали ліву кнопку мишки:
		if (Mouse::isButtonPressed(Mouse::Left) || isEnterPressed) {
			//Enter
			if (numMenu1 == 1 || isEnterPressed)
			{
				Sleep(200);
				enterNamePass = 0;
				int tmp = (registration ? singUp(usernameStr, passwordStr) : singIn(usernameStr, passwordStr));
				if (tmp == -1) {
					(registration ? isErrorReg : isError) = true;
				}
				else {
					setAccountID(tmp);
					getLevel(tmp);
					getExp(tmp);
					getCoins(tmp);
					getStatus(tmp);
					getName(tmp);
					getGold(tmp);
					Sleep(200);
					return 0;
				}
			}//Exit
			if (numMenu1 == 2)
			{
				Sleep(200);
				exit(0);
			}//Singin
			if (numMenu1 == 3) {
				Sleep(200);
				registration = false;
				enterNamePass = 0;
			}//Singup
			if (numMenu1 == 4) {
				Sleep(200); 
				registration = true;
				enterNamePass = 0;
			}//Username
			if (numMenu1 == 5) {
				Sleep(200);
				enterNamePass = 1;
			}//Password
			if (numMenu1 == 6) {
				Sleep(200);
				enterNamePass = 2;
			}
			if (numMenu1 == 0) {
				isError = false;
				isErrorReg = false;
			}
		}
		//Передає всі елементи на вікно
		window.draw(backgr);
		if (isError) window.draw(wrong);
		if (isErrorReg) window.draw(wrongReg);
		window.draw(yes);
		window.draw(no);
		window.draw(textBox1);
		window.draw(textBox2);
		window.draw(usernameTxt);
		window.draw(passwordTxt);
		window.draw(Singin);
		window.draw(Singup);
		//Виводимо всі елементи
		window.display();
	}
	return 0;
}