#include "skillMenu.h"
using namespace sf;

int skillMenu(RenderWindow &window, PLAYER &p) {
	//Сворення текстур для спрайтів, загрузка з файлів
	Texture menuBgText, backGround, textBoxTexture, textBoxDarkTexture;
	Texture hskill1, hskill2, hskill3, hskill4, hskill5, askill1, askill2, askill3, askill4, askill5, dskill1, dskill2, dskill3, dskill4, dskill5;
	Texture hskill1d, hskill2d, hskill3d, hskill4d, hskill5d, askill1d, askill2d, askill3d, askill4d, askill5d, dskill1d, dskill2d, dskill3d, dskill4d, dskill5d;
	Texture h1mt, h2mt, h3mt, h4mt, h5mt, a1mt, a2mt, a3mt, a4mt, a5mt, d1mt, d2mt, d3mt, d4mt, d5mt;
	backGround.loadFromFile(get43() ? "img/Background-43.png" : "img/Background-169.png");
	menuBgText.loadFromFile("img/MenuBackground4.png");
	textBoxTexture.loadFromFile("img/textBox.png");
	textBoxDarkTexture.loadFromFile("img/textBoxDark.png");
	hskill1.loadFromFile("img/h1.png");
	hskill2.loadFromFile("img/h2.png");
	hskill3.loadFromFile("img/h3.png");
	hskill4.loadFromFile("img/h4.png");
	hskill5.loadFromFile("img/h5.png");
	hskill1d.loadFromFile("img/h1d.png");
	hskill2d.loadFromFile("img/h2d.png");
	hskill3d.loadFromFile("img/h3d.png");
	hskill4d.loadFromFile("img/h4d.png");
	hskill5d.loadFromFile("img/h5d.png");
	askill1.loadFromFile("img/a1.png");
	askill2.loadFromFile("img/a2.png");
	askill3.loadFromFile("img/a3.png");
	askill4.loadFromFile("img/a4.png");
	askill5.loadFromFile("img/a5.png");
	askill1d.loadFromFile("img/a1d.png");
	askill2d.loadFromFile("img/a2d.png");
	askill3d.loadFromFile("img/a3d.png");
	askill4d.loadFromFile("img/a4d.png");
	askill5d.loadFromFile("img/a5d.png");
	dskill1.loadFromFile("img/d1.png");
	dskill2.loadFromFile("img/d2.png");
	dskill3.loadFromFile("img/d3.png");
	dskill4.loadFromFile("img/d4.png");
	dskill5.loadFromFile("img/d5.png");
	dskill1d.loadFromFile("img/d1d.png");
	dskill2d.loadFromFile("img/d2d.png");
	dskill3d.loadFromFile("img/d3d.png");
	dskill4d.loadFromFile("img/d4d.png");
	dskill5d.loadFromFile("img/d5d.png");
	h1mt.loadFromFile("img/h1m.png");
	h2mt.loadFromFile("img/h2m.png");
	h3mt.loadFromFile("img/h3m.png");
	h4mt.loadFromFile("img/h4m.png");
	h5mt.loadFromFile("img/h5m.png");
	a1mt.loadFromFile("img/a1m.png");
	a2mt.loadFromFile("img/a2m.png");
	a3mt.loadFromFile("img/a3m.png");
	a4mt.loadFromFile("img/a4m.png");
	a5mt.loadFromFile("img/a5m.png");
	d1mt.loadFromFile("img/d1m.png");
	d2mt.loadFromFile("img/d2m.png");
	d3mt.loadFromFile("img/d3m.png");
	d4mt.loadFromFile("img/d4m.png");
	d5mt.loadFromFile("img/d5m.png");
	//Створення спрайтів, яким передаються текстури
	Sprite h1, h2, h3, h4, h5, a1, a2, a3, a4, a5, d1, d2, d3, d4, d5;
	Sprite menuBg(menuBgText), tb(textBoxTexture), backgr(backGround);
	Sprite h1m(h1mt), h2m(h2mt), h3m(h3mt), h4m(h4mt), h5m(h5mt), a1m(a1mt), a2m(a2mt), a3m(a3mt), a4m(a4mt), a5m(a5mt), d1m(d1mt), d2m(d2mt), d3m(d3mt), d4m(d4mt), d5m(d5mt);
	//
	reload:
	if (p.st.lvl[0][0] == 1) h1.setTexture(hskill1);
	else h1.setTexture(hskill1d);
	if (p.st.lvl[0][1] == 1) h2.setTexture(hskill2);
	else h2.setTexture(hskill2d);
	if (p.st.lvl[0][2] == 1) h3.setTexture(hskill3);
	else h3.setTexture(hskill3d);
	if (p.st.lvl[0][3] == 1) h4.setTexture(hskill4);
	else h4.setTexture(hskill4d);
	if (p.st.lvl[0][4] == 1) h5.setTexture(hskill5);
	else h5.setTexture(hskill5d);
	if (p.st.lvl[1][0] == 1) a1.setTexture(askill1);
	else a1.setTexture(askill1d);
	if (p.st.lvl[1][1] == 1) a2.setTexture(askill2);
	else a2.setTexture(askill2d);
	if (p.st.lvl[1][2] == 1) a3.setTexture(askill3);
	else a3.setTexture(askill3d);
	if (p.st.lvl[1][3] == 1) a4.setTexture(askill4);
	else a4.setTexture(askill4d);
	if (p.st.lvl[1][4] == 1) a5.setTexture(askill5);
	else a5.setTexture(askill5d);
	if (p.st.lvl[2][0] == 1) d1.setTexture(dskill1);
	else d1.setTexture(dskill1d);
	if (p.st.lvl[2][1] == 1) d2.setTexture(dskill2);
	else d2.setTexture(dskill2d);
	if (p.st.lvl[2][2] == 1) d3.setTexture(dskill3);
	else d3.setTexture(dskill3d);
	if (p.st.lvl[2][3] == 1) d4.setTexture(dskill4);
	else d4.setTexture(dskill4d);
	if (p.st.lvl[2][4] == 1) d5.setTexture(dskill5);
	else d5.setTexture(dskill5d);
	//
	float CoefX = getCoefX(window), CoefY = getCoefY(window);
	menuBg.setPosition((get43() ? 450 : 710) * CoefX, 50 * CoefY);
	h1.setPosition((get43() ? 500 : 760) * CoefX, 100 * CoefY);
	h2.setPosition((get43() ? 500 : 760) * CoefX, 250 * CoefY);
	h3.setPosition((get43() ? 500 : 760) * CoefX, 400 * CoefY);
	h4.setPosition((get43() ? 500 : 760) * CoefX, 550 * CoefY);
	h5.setPosition((get43() ? 500 : 760) * CoefX, 700 * CoefY);
	a1.setPosition((get43() ? 650 : 910) * CoefX, 100 * CoefY);
	a2.setPosition((get43() ? 650 : 910) * CoefX, 250 * CoefY);
	a3.setPosition((get43() ? 650 : 910) * CoefX, 400 * CoefY);
	a4.setPosition((get43() ? 650 : 910) * CoefX, 550 * CoefY);
	a5.setPosition((get43() ? 650 : 910) * CoefX, 700 * CoefY);
	d1.setPosition((get43() ? 800 : 1060) * CoefX, 100 * CoefY);
	d2.setPosition((get43() ? 800 : 1060) * CoefX, 250 * CoefY);
	d3.setPosition((get43() ? 800 : 1060) * CoefX, 400 * CoefY);
	d4.setPosition((get43() ? 800 : 1060) * CoefX, 550 * CoefY);
	d5.setPosition((get43() ? 800 : 1060) * CoefX, 700 * CoefY);
	tb.setPosition((get43() ? 600 : 860) * CoefX, 890 * CoefY);
	h1.setScale(CoefX*0.1, CoefY*0.1);
	h2.setScale(CoefX*0.1, CoefY*0.1);
	h3.setScale(CoefX*0.1, CoefY*0.1);
	h4.setScale(CoefX*0.1, CoefY*0.1);
	h5.setScale(CoefX*0.1, CoefY*0.1);
	a1.setScale(CoefX*0.1, CoefY*0.1);
	a2.setScale(CoefX*0.1, CoefY*0.1);
	a3.setScale(CoefX*0.1, CoefY*0.1);
	a4.setScale(CoefX*0.1, CoefY*0.1);
	a5.setScale(CoefX*0.1, CoefY*0.1);
	d1.setScale(CoefX*0.1, CoefY*0.1);
	d2.setScale(CoefX*0.1, CoefY*0.1);
	d3.setScale(CoefX*0.1, CoefY*0.1);
	d4.setScale(CoefX*0.1, CoefY*0.1);
	d5.setScale(CoefX*0.1, CoefY*0.1); 
	h1m.setPosition((get43() ? 600 : 860) * CoefX, 0 * CoefY);
	h2m.setPosition((get43() ? 600 : 860) * CoefX, 150 * CoefY);
	h3m.setPosition((get43() ? 600 : 860) * CoefX, 300 * CoefY);
	h4m.setPosition((get43() ? 600 : 860) * CoefX, 450 * CoefY);
	h5m.setPosition((get43() ? 600 : 860) * CoefX, 600 * CoefY);
	a1m.setPosition((get43() ? 750 : 1010) * CoefX, 0 * CoefY);
	a2m.setPosition((get43() ? 750 : 1010) * CoefX, 150 * CoefY);
	a3m.setPosition((get43() ? 750 : 1010) * CoefX, 300 * CoefY);
	a4m.setPosition((get43() ? 750 : 1010) * CoefX, 450 * CoefY);
	a5m.setPosition((get43() ? 750 : 1010) * CoefX, 600 * CoefY);
	d1m.setPosition((get43() ? 900 : 1160) * CoefX, 0 * CoefY);
	d2m.setPosition((get43() ? 900 : 1160) * CoefX, 150 * CoefY);
	d3m.setPosition((get43() ? 900 : 1160) * CoefX, 300 * CoefY);
	d4m.setPosition((get43() ? 900 : 1160) * CoefX, 450 * CoefY);
	d5m.setPosition((get43() ? 900 : 1160) * CoefX, 600 * CoefY);
	h1m.setScale(CoefX*0.3, CoefY*0.3);
	h2m.setScale(CoefX*0.3, CoefY*0.3);
	h3m.setScale(CoefX*0.3, CoefY*0.3);
	h4m.setScale(CoefX*0.3, CoefY*0.3);
	h5m.setScale(CoefX*0.3, CoefY*0.3);
	a1m.setScale(CoefX*0.3, CoefY*0.3);
	a2m.setScale(CoefX*0.3, CoefY*0.3);
	a3m.setScale(CoefX*0.3, CoefY*0.3);
	a4m.setScale(CoefX*0.3, CoefY*0.3);
	a5m.setScale(CoefX*0.3, CoefY*0.3);
	d1m.setScale(CoefX*0.3, CoefY*0.3);
	d2m.setScale(CoefX*0.3, CoefY*0.3);
	d3m.setScale(CoefX*0.3, CoefY*0.3);
	d4m.setScale(CoefX*0.3, CoefY*0.3);
	d5m.setScale(CoefX*0.3, CoefY*0.3);
	menuBg.setScale(CoefX, CoefY);
	tb.setScale(CoefX*0.2222, CoefY*0.25);
	//Cтворення текстів
	String exiT = "Exit";
	Font font;
	font.loadFromFile("config/font.ttf");
	Text exitText(exiT, font, 30);
	//розміщуємо текст
	exitText.setPosition((get43() ? 680 : 960) * CoefX, 895 * CoefY);
	exitText.setScale(CoefX, CoefY);
	//ставимо ширину зовнішньої лінії
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
		window.clear();
		if (IntRect((get43() ? 500 : 760) * CoefX, 100 * CoefY, 100 * CoefX, 100 * CoefY).contains(Mouse::getPosition(window)))
		{
			tb.setTexture(textBoxTexture);
			exitText.setFillColor(Color::Black);
			numMenu = 1;
		}
		else if (IntRect((get43() ? 500 : 760) * CoefX, 250 * CoefY, 100 * CoefX, 100 * CoefY).contains(Mouse::getPosition(window)))
		{
			tb.setTexture(textBoxTexture);
			exitText.setFillColor(Color::Black);
			numMenu = 2;
		}
		else if (IntRect((get43() ? 500 : 760) * CoefX, 400 * CoefY, 100 * CoefX, 100 * CoefY).contains(Mouse::getPosition(window)))
		{
			tb.setTexture(textBoxTexture);
			exitText.setFillColor(Color::Black);
			numMenu = 3;
		}
		else if (IntRect((get43() ? 500 : 760) * CoefX, 550 * CoefY, 100 * CoefX, 100 * CoefY).contains(Mouse::getPosition(window)))
		{
			tb.setTexture(textBoxTexture);
			exitText.setFillColor(Color::Black);
			numMenu = 4;
		}
		else if (IntRect((get43() ? 500 : 760) * CoefX, 700 * CoefY, 100 * CoefX, 100 * CoefY).contains(Mouse::getPosition(window)))
		{
			tb.setTexture(textBoxTexture);
			exitText.setFillColor(Color::Black);
			numMenu = 5;
		}
		else if (IntRect((get43() ? 650 : 910) * CoefX, 100 * CoefY, 100 * CoefX, 100 * CoefY).contains(Mouse::getPosition(window)))
		{
			tb.setTexture(textBoxTexture);
			exitText.setFillColor(Color::Black);
			numMenu = 11;
		}
		else if (IntRect((get43() ? 650 : 910) * CoefX, 250 * CoefY, 100 * CoefX, 100 * CoefY).contains(Mouse::getPosition(window)))
		{
			tb.setTexture(textBoxTexture);
			exitText.setFillColor(Color::Black);
			numMenu = 12;
		}
		else if (IntRect((get43() ? 650 : 910) * CoefX, 400 * CoefY, 100 * CoefX, 100 * CoefY).contains(Mouse::getPosition(window)))
		{
			tb.setTexture(textBoxTexture);
			exitText.setFillColor(Color::Black);
			numMenu = 13;
		}
		else if (IntRect((get43() ? 650 : 910) * CoefX, 550 * CoefY, 100 * CoefX, 100 * CoefY).contains(Mouse::getPosition(window)))
		{
			tb.setTexture(textBoxTexture);
			exitText.setFillColor(Color::Black);
			numMenu = 14;
		}
		else if (IntRect((get43() ? 650 : 910) * CoefX, 700 * CoefY, 100 * CoefX, 100 * CoefY).contains(Mouse::getPosition(window)))
		{
			tb.setTexture(textBoxTexture);
			exitText.setFillColor(Color::Black);
			numMenu = 15;
		}
		else if (IntRect((get43() ? 800 : 1060) * CoefX, 100 * CoefY, 100 * CoefX, 100 * CoefY).contains(Mouse::getPosition(window)))
		{
			tb.setTexture(textBoxTexture);
			exitText.setFillColor(Color::Black);
			numMenu = 21;
		}
		else if (IntRect((get43() ? 800 : 1060) * CoefX, 250 * CoefY, 100 * CoefX, 100 * CoefY).contains(Mouse::getPosition(window)))
		{
			tb.setTexture(textBoxTexture);
			exitText.setFillColor(Color::Black);
			numMenu = 22;
		}
		else if (IntRect((get43() ? 800 : 1060) * CoefX, 400 * CoefY, 100 * CoefX, 100 * CoefY).contains(Mouse::getPosition(window)))
		{
			tb.setTexture(textBoxTexture);
			exitText.setFillColor(Color::Black);
			numMenu = 23;
		}
		else if (IntRect((get43() ? 800 : 1060) * CoefX, 550 * CoefY, 100 * CoefX, 100 * CoefY).contains(Mouse::getPosition(window)))
		{
			tb.setTexture(textBoxTexture);
			exitText.setFillColor(Color::Black);
			numMenu = 24;
		}
		else if (IntRect((get43() ? 800 : 1060) * CoefX, 700 * CoefY, 100 * CoefX, 100 * CoefY).contains(Mouse::getPosition(window)))
		{
			tb.setTexture(textBoxTexture);
			exitText.setFillColor(Color::Black);
			numMenu = 25;
		}
		else if (IntRect((get43() ? 600 : 860) * CoefX, 900 * CoefY, 200 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			tb.setTexture(textBoxDarkTexture);
			exitText.setFillColor(Color::White);
			numMenu = -1;
		}
		else {
			tb.setTexture(textBoxTexture);
			exitText.setFillColor(Color::Black);
			numMenu = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			Sleep(200);
			break;
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (numMenu == 1 && p.st.lvl[0][0] == 0) {
				if (p.sp >= 1) {
					p.st.lvl[0][0] = 1;
					p.sp--;
					goto reload;
				}
				Sleep(200);
			}
			if (numMenu == 2 && p.st.lvl[0][1] == 0) {
				if (p.sp >= 2 && p.st.lvl[0][0] == 1) {
					p.st.lvl[0][1] = 1;
					p.sp -= 2;
					goto reload;
				}
				Sleep(200);
			}
			if (numMenu == 3 && p.st.lvl[0][2] == 0) {
				if (p.sp >= 3 && p.st.lvl[0][1] == 1) {
					p.st.lvl[0][2] = 1;
					p.sp -= 3;
					goto reload;
				}
				Sleep(200);
			}
			if (numMenu == 4 && p.st.lvl[0][3] == 0) {
				if (p.sp >= 4 && p.st.lvl[0][2] == 1) {
					p.st.lvl[0][3] = 1;
					p.sp -= 4;
					goto reload;
				}
				Sleep(200);
			}
			if (numMenu == 5 && p.st.lvl[0][4] == 0) {
				if (p.sp >= 5 && p.st.lvl[0][3] == 1) {
					p.st.lvl[0][4] = 1;
					p.sp -= 5;
					goto reload;
				}
				Sleep(200);
			}
			if (numMenu == 11 && p.st.lvl[1][0] == 0) {
				if (p.sp >= 1) {
					p.st.lvl[1][0] = 1;
					p.sp -= 1;
					goto reload;
				}
				Sleep(200);
			}
			if (numMenu == 12 && p.st.lvl[1][1] == 0) {
				if (p.sp >= 2 && p.st.lvl[1][0] == 1) {
					p.st.lvl[1][1] = 1;
					p.sp -= 2;
					goto reload;
				}
				Sleep(200);
			}
			if (numMenu == 13 && p.st.lvl[1][2] == 0) {
				if (p.sp >= 3 && p.st.lvl[1][1] == 1) {
					p.st.lvl[1][2] = 1;
					p.sp -= 3;
					goto reload;
				}
				Sleep(200);
			}
			if (numMenu == 14 && p.st.lvl[1][3] == 0) {
				if (p.sp >= 4 && p.st.lvl[1][2] == 1) {
					p.st.lvl[1][3] = 1;
					p.sp -= 4;
					goto reload;
				}
				Sleep(200);
			}
			if (numMenu == 15 && p.st.lvl[1][4] == 0) {
				if (p.sp >= 5 && p.st.lvl[1][3] == 1) {
					p.st.lvl[1][4] = 1;
					p.sp -= 5;
					goto reload;
				}
				Sleep(200);
			}
			if (numMenu == 21 && p.st.lvl[2][0] == 0) {
				if (p.sp >= 1) {
					p.st.lvl[2][0] = 1;
					p.sp -= 1;
					goto reload;
				}
				Sleep(200);
			}
			if (numMenu == 22 && p.st.lvl[2][1] == 0) {
				if (p.sp >= 2 && p.st.lvl[2][0] == 1) {
					p.st.lvl[2][1] = 1;
					p.sp -= 2;
					goto reload;
				}
				Sleep(200);
			}
			if (numMenu == 23 && p.st.lvl[2][2] == 0) {
				if (p.sp >= 3 && p.st.lvl[2][1] == 1) {
					p.st.lvl[2][2] = 1;
					p.sp -= 3;
					goto reload;
				}
				Sleep(200);
			}
			if (numMenu == 24 && p.st.lvl[2][3] == 0) {
				if (p.sp >= 4 && p.st.lvl[2][2] == 1) {
					p.st.lvl[2][3] = 1;
					p.sp -= 4;
					goto reload;
				}
				Sleep(200);
			}
			if (numMenu == 25 && p.st.lvl[2][4] == 0) {
				if (p.sp >= 5 && p.st.lvl[2][3] == 1) {
					p.st.lvl[2][4] = 1;
					p.sp -= 5;
					goto reload;
				}
				Sleep(200);
			}
			if (numMenu == -1) {
				return 0;
				Sleep(200);
			}
		}

		window.draw(backgr);
		window.draw(menuBg);
		window.draw(tb);
		window.draw(h1);
		window.draw(h2);
		window.draw(h3);
		window.draw(h4);
		window.draw(h5);
		window.draw(a1);
		window.draw(a2);
		window.draw(a3);
		window.draw(a4);
		window.draw(a5);
		window.draw(d1);
		window.draw(d2);
		window.draw(d3);
		window.draw(d4);
		window.draw(d5);
		window.draw(exitText);
		switch (numMenu)
		{
		case 1: window.draw(h1m);
			break;
		case 2: window.draw(h2m);
			break;
		case 3: window.draw(h3m);
			break;
		case 4: window.draw(h4m);
			break;
		case 5: window.draw(h5m);
			break;
		case 11: window.draw(a1m);
			break;
		case 12: window.draw(a2m);
			break;
		case 13: window.draw(a3m);
			break;
		case 14: window.draw(a4m);
			break;
		case 15: window.draw(a5m);
			break;
		case 21: window.draw(d1m);
			break;
		case 22: window.draw(d2m);
			break;
		case 23: window.draw(d3m);
			break;
		case 24: window.draw(d4m);
			break;
		case 25: window.draw(d5m);
			break;
		}
		window.display();
	}
	return 0;
}