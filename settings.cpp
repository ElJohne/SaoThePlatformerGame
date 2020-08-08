#include <SFML\Graphics.hpp>
#include "setups.h"
#include <Windows.h>

using namespace sf;

//������� ��������� ���������, ���� ����� � ����������� ����
int choosenResolution = 0;
int choosenMenuMusicLvl = 0;
int choosenGameMusicLvl = 0;
int choosenGameSoundLvl = 0;
bool resChanged = false;

int settingsStart(RenderWindow &window){
	bool fullScreen = true;
	resChanged = false;
	fullScreen = getFullscreenMode();
	//�������� ������� ��� �������
	Texture YesTexture, NoTexture, arrowTexture, backgrTexture, fscBtnTexture, fscBtnTexture2;
	Texture YesTexture2, NoTexture2, arrowTexture2, arrow2Texture, arrow2Texture2;
	//�������� �������� � �����
	fscBtnTexture.loadFromFile("img/off.png");
	fscBtnTexture2.loadFromFile("img/offDark.png");
	YesTexture.loadFromFile("img/Yes.png");
	NoTexture.loadFromFile("img/No.png");
	YesTexture2.loadFromFile("img/YesDark.png");
	NoTexture2.loadFromFile("img/NoDark.png");
	backgrTexture.loadFromFile(get43()?"img/BackGroundSettings-43.png":"img/BackGroundSettings-169.png");
	arrowTexture.loadFromFile("img/Plus.png");
	arrowTexture2.loadFromFile("img/PlusDark.png");
	arrow2Texture.loadFromFile("img/Minus.png");
	arrow2Texture2.loadFromFile("img/MinusDark.png");
	//��������� �������, ���� ����������� ��������
	Sprite Yes(YesTexture);
	Sprite No(NoTexture);
	Sprite fscBt(fullScreen ? fscBtnTexture2 : fscBtnTexture);
	Sprite backgr(backgrTexture);
	Sprite arrowLeft(arrow2Texture);
	Sprite arrowRight(arrowTexture);
	Sprite arrowLeft2(arrow2Texture);
	Sprite arrowRight2(arrowTexture);
	Sprite arrowLeft3(arrow2Texture);
	Sprite arrowRight3(arrowTexture);
	Sprite arrowLeft4(arrow2Texture);
	Sprite arrowRight4(arrowTexture);
	//������ �����������, ���� ���������� �� ����������
	float CoefX = getCoefX(window), CoefY = getCoefY(window);
	//������� �� ������� ������� �������
	arrowLeft.setPosition((get43() ? 112 : 150) * CoefX, (get43() ? 232 : 250) * CoefY);
	arrowRight.setPosition((get43() ? 460 : 498) * CoefX, (get43() ? 232 : 250) * CoefY);
	arrowLeft2.setPosition((get43() ? 112 : 150) * CoefX, (get43() ? 344 : 362) * CoefY);
	arrowRight2.setPosition((get43() ? 460 : 498) * CoefX, (get43() ? 344 : 362) * CoefY);
	arrowLeft3.setPosition((get43() ? 112 : 150) * CoefX, (get43() ? 453 : 471) * CoefY);
	arrowRight3.setPosition((get43() ? 460 : 498) * CoefX, (get43() ? 453 : 471) * CoefY);
	arrowLeft4.setPosition((get43() ? 112 : 150) * CoefX, (get43() ? 566 : 584) * CoefY);
	arrowRight4.setPosition((get43() ? 460 : 498) * CoefX, (get43() ? 566 : 584) * CoefY);
	Yes.setPosition((get43() ? 139 : 178) * CoefX, (get43() ? 846 : 859) * CoefY);
	No.setPosition((get43() ? 383 : 421) * CoefX, (get43() ? 846 : 859) * CoefY);
	fscBt.setPosition((get43() ? 287 : 325) * CoefX, (get43() ? 700 : 718) * CoefY);
	Yes.setScale(CoefX*0.05, CoefY*0.05);
	No.setScale(CoefX*0.05, CoefY*0.05);
	arrowLeft.setScale(CoefX*0.025, CoefY*0.025);
	arrowRight.setScale(CoefX*0.025, CoefY*0.025);
	arrowLeft2.setScale(CoefX*0.025, CoefY*0.025);
	arrowRight2.setScale(CoefX*0.025, CoefY*0.025);
	arrowLeft3.setScale(CoefX*0.025, CoefY*0.025);
	arrowRight3.setScale(CoefX*0.025, CoefY*0.025);
	arrowLeft4.setScale(CoefX*0.025, CoefY*0.025);
	arrowRight4.setScale(CoefX*0.025, CoefY*0.025);
	fscBt.setScale(CoefX*0.25, CoefY*0.25);
	backgr.setScale(CoefX, CoefY);
	//��������� �����, ��������� � �����
	Font font;
	font.loadFromFile("config/font.ttf");
	//�������� ����� ����
	int numMenu = 0;
	// ������� � �����: ����� ����������� ����������, ����� �����, ������ 
	choosenResolution = getChoosen();
	choosenMenuMusicLvl = getChoosenMenuMusic();
	choosenGameMusicLvl = getChoosenGameMusic();
	choosenGameSoundLvl = getChoosenGameSound();
	//���� ������ ����
	while (window.isOpen())
	{
		//������� �� �� ������� ����
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		//��������� ����� � ������� �� �������
		String soundLvl[11] = { "0%", "10%","20%","30%","40%","50%","60%","70%","80%","90%","100%" };
		Text menuMusicLvl(soundLvl[choosenMenuMusicLvl], font, 30);
		Text playMusicLvl(soundLvl[choosenGameMusicLvl], font, 30);
		Text playSoundLvl(soundLvl[choosenGameSoundLvl], font, 30);
		Text resolutionText((std::to_string(Resolutions[choosenResolution][0]) + "x" + std::to_string(Resolutions[choosenResolution][1])), font, 30);
		resolutionText.setOrigin((0.175 * resolutionText.getCharacterSize()) * resolutionText.getString().getSize(), (resolutionText.getCharacterSize() / 2));
		resolutionText.setPosition((get43()? 312 : 350) * CoefX, (get43() ? 257 : 275) * CoefY);
		menuMusicLvl.setOrigin((0.175 * menuMusicLvl.getCharacterSize()) * menuMusicLvl.getString().getSize(), (menuMusicLvl.getCharacterSize() / 2));
		menuMusicLvl.setPosition((get43() ? 312 : 350) * CoefX, (get43() ? 369 : 387) * CoefY);
		playMusicLvl.setOrigin((0.175 * playMusicLvl.getCharacterSize()) * playMusicLvl.getString().getSize(), (playMusicLvl.getCharacterSize() / 2));
		playMusicLvl.setPosition((get43() ? 312 : 350) * CoefX, (get43() ? 479 : 496) * CoefY);
		playSoundLvl.setOrigin((0.175 * playSoundLvl.getCharacterSize()) * playSoundLvl.getString().getSize(), (playSoundLvl.getCharacterSize() / 2));
		playSoundLvl.setPosition((get43() ? 312 : 350) * CoefX, (get43() ? 592 : 609) * CoefY);
		menuMusicLvl.setFillColor(Color::Black);
		playMusicLvl.setFillColor(Color::Black);
		playSoundLvl.setFillColor(Color::Black);
		resolutionText.setFillColor(Color::Black);
		resolutionText.setScale(CoefX, CoefY);
		menuMusicLvl.setScale(CoefX, CoefY);
		playMusicLvl.setScale(CoefX, CoefY);
		playSoundLvl.setScale(CoefX, CoefY);
		//������� ��������� ������ �� ������
		//Yes
		if (IntRect((get43() ? 139 : 178) * CoefX, (get43() ? 846 : 859) * CoefY, 100 * CoefX, 100 * CoefY).contains(Mouse::getPosition(window)))
		{
			Yes.setTexture(YesTexture2);
			No.setTexture(NoTexture);
			arrowLeft.setTexture(arrow2Texture);
			arrowRight.setTexture(arrowTexture);
			arrowLeft2.setTexture(arrow2Texture);
			arrowRight2.setTexture(arrowTexture);
			arrowLeft3.setTexture(arrow2Texture);
			arrowRight3.setTexture(arrowTexture);
			arrowLeft4.setTexture(arrow2Texture);
			arrowRight4.setTexture(arrowTexture);
			numMenu = 1;
		}//No
		else if (IntRect((get43() ? 383 : 421) * CoefX, (get43() ? 846 : 859) * CoefY, 100 * CoefX, 100 * CoefY).contains(Mouse::getPosition(window)))
		{
			Yes.setTexture(YesTexture);
			No.setTexture(NoTexture2);
			arrowLeft.setTexture(arrow2Texture);
			arrowRight.setTexture(arrowTexture);
			arrowLeft2.setTexture(arrow2Texture);
			arrowRight2.setTexture(arrowTexture);
			arrowLeft3.setTexture(arrow2Texture);
			arrowRight3.setTexture(arrowTexture);
			arrowLeft4.setTexture(arrow2Texture);
			arrowRight4.setTexture(arrowTexture);
			numMenu = 2;
		}//arrowLeft
		else if (IntRect((get43() ? 112 : 150) * CoefX, (get43() ? 232 : 250) * CoefY, 50 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			Yes.setTexture(YesTexture);
			No.setTexture(NoTexture);
			arrowLeft.setTexture(arrow2Texture2);
			arrowRight.setTexture(arrowTexture);
			arrowLeft2.setTexture(arrow2Texture);
			arrowRight2.setTexture(arrowTexture);
			arrowLeft3.setTexture(arrow2Texture);
			arrowRight3.setTexture(arrowTexture);
			arrowLeft4.setTexture(arrow2Texture);
			arrowRight4.setTexture(arrowTexture);
			numMenu = 3;
		}//arrowRight
		else if (IntRect((get43() ? 460 : 498) * CoefX, (get43() ? 232 : 250) * CoefY, 50 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			Yes.setTexture(YesTexture);
			No.setTexture(NoTexture);
			arrowLeft.setTexture(arrow2Texture);
			arrowRight.setTexture(arrowTexture2);
			arrowLeft2.setTexture(arrow2Texture);
			arrowRight2.setTexture(arrowTexture);
			arrowLeft3.setTexture(arrow2Texture);
			arrowRight3.setTexture(arrowTexture);
			arrowLeft4.setTexture(arrow2Texture);
			arrowRight4.setTexture(arrowTexture);
			numMenu = 4;
		}//arrowLeft2
		else if (IntRect((get43() ? 112 : 150) * CoefX, (get43() ? 344 : 362) * CoefY, 50 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			Yes.setTexture(YesTexture);
			No.setTexture(NoTexture);
			arrowLeft.setTexture(arrow2Texture);
			arrowRight.setTexture(arrowTexture);
			arrowLeft2.setTexture(arrow2Texture2);
			arrowRight2.setTexture(arrowTexture);
			arrowLeft3.setTexture(arrow2Texture);
			arrowRight3.setTexture(arrowTexture);
			arrowLeft4.setTexture(arrow2Texture);
			arrowRight4.setTexture(arrowTexture);
			numMenu = 5;
		}//arrowRight2
		else if (IntRect((get43() ? 460 : 498) * CoefX, (get43() ? 344 : 362) * CoefY, 50 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			Yes.setTexture(YesTexture);
			No.setTexture(NoTexture);
			arrowLeft.setTexture(arrow2Texture);
			arrowRight.setTexture(arrowTexture);
			arrowLeft2.setTexture(arrow2Texture);
			arrowRight2.setTexture(arrowTexture2);
			arrowLeft3.setTexture(arrow2Texture);
			arrowRight3.setTexture(arrowTexture);
			arrowLeft4.setTexture(arrow2Texture);
			arrowRight4.setTexture(arrowTexture);
			numMenu = 6;
		}//arrowLeft3
		else if (IntRect((get43() ? 112 : 150) * CoefX, (get43() ? 453 : 471) * CoefY, 50 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			Yes.setTexture(YesTexture);
			No.setTexture(NoTexture);
			arrowLeft.setTexture(arrow2Texture);
			arrowRight.setTexture(arrowTexture);
			arrowLeft2.setTexture(arrow2Texture);
			arrowRight2.setTexture(arrowTexture);
			arrowLeft3.setTexture(arrow2Texture2);
			arrowRight3.setTexture(arrowTexture);
			arrowLeft4.setTexture(arrow2Texture);
			arrowRight4.setTexture(arrowTexture);
			numMenu = 7;
		}//arrowRight3
		else if (IntRect((get43() ? 460 : 498) * CoefX, (get43() ? 453 : 471) * CoefY, 50 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			Yes.setTexture(YesTexture);
			No.setTexture(NoTexture);
			arrowLeft.setTexture(arrow2Texture);
			arrowRight.setTexture(arrowTexture);
			arrowLeft2.setTexture(arrow2Texture);
			arrowRight2.setTexture(arrowTexture);
			arrowLeft3.setTexture(arrow2Texture);
			arrowRight3.setTexture(arrowTexture2);
			arrowLeft4.setTexture(arrow2Texture);
			arrowRight4.setTexture(arrowTexture);
			numMenu = 8;
		}//arrowLeft4
		else if (IntRect((get43() ? 112 : 150) * CoefX, (get43() ? 566 : 584) * CoefY, 50 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			Yes.setTexture(YesTexture);
			No.setTexture(NoTexture);
			arrowLeft.setTexture(arrow2Texture);
			arrowRight.setTexture(arrowTexture);
			arrowLeft2.setTexture(arrow2Texture);
			arrowRight2.setTexture(arrowTexture);
			arrowLeft3.setTexture(arrow2Texture);
			arrowRight3.setTexture(arrowTexture);
			arrowLeft4.setTexture(arrow2Texture2);
			arrowRight4.setTexture(arrowTexture);
			numMenu = 9;
		}//arrowRight4
		else if (IntRect((get43() ? 460 : 498) * CoefX, (get43() ? 566 : 584) * CoefY, 50 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			Yes.setTexture(YesTexture);
			No.setTexture(NoTexture);
			arrowLeft.setTexture(arrow2Texture);
			arrowRight.setTexture(arrowTexture);
			arrowLeft2.setTexture(arrow2Texture);
			arrowRight2.setTexture(arrowTexture);
			arrowLeft3.setTexture(arrow2Texture);
			arrowRight3.setTexture(arrowTexture);
			arrowLeft4.setTexture(arrow2Texture);
			arrowRight4.setTexture(arrowTexture2);
			numMenu = 10;
		}//FullScreen
		else if (IntRect((get43() ? 287 : 325) * CoefX, (get43() ? 700 : 718) * CoefY, 50 * CoefX, 50 * CoefY).contains(Mouse::getPosition(window)))
		{
			Yes.setTexture(YesTexture);
			No.setTexture(NoTexture);
			arrowLeft.setTexture(arrow2Texture);
			arrowRight.setTexture(arrowTexture);
			arrowLeft2.setTexture(arrow2Texture);
			arrowRight2.setTexture(arrowTexture);
			arrowLeft3.setTexture(arrow2Texture);
			arrowRight3.setTexture(arrowTexture);
			arrowLeft4.setTexture(arrow2Texture);
			arrowRight4.setTexture(arrowTexture);
			fscBt.setTexture(fullScreen ? fscBtnTexture : fscBtnTexture2);
			numMenu = 11;
		}
		else {
			Yes.setTexture(YesTexture);
			No.setTexture(NoTexture);
			arrowLeft.setTexture(arrow2Texture);
			arrowRight.setTexture(arrowTexture);
			arrowLeft2.setTexture(arrow2Texture);
			arrowRight2.setTexture(arrowTexture);
			arrowLeft3.setTexture(arrow2Texture);
			arrowRight3.setTexture(arrowTexture);
			arrowLeft4.setTexture(arrow2Texture);
			arrowRight4.setTexture(arrowTexture);
			fscBt.setTexture(fullScreen ? fscBtnTexture2 : fscBtnTexture);
			numMenu = 0;
		}
		//������� ���������� ��� ������ �����
		if (Mouse::isButtonPressed(Mouse::Left)) {
			// save end exit
			if (numMenu == 1){
				//������� ������� ����������
				setHeight(Resolutions[choosenResolution][1]);
				setWidth(Resolutions[choosenResolution][0]);
				setChoosenRes(choosenResolution);
				setChoosenMenuMusic(choosenMenuMusicLvl);
				setChoosenGameMusic(choosenGameMusicLvl);
				setChoosenGameSound(choosenGameSoundLvl);
				setFullscreenMode(fullScreen);
				//�������� � ����
				saveToFile();
				//�������� ���������� ����
				window.setSize(Vector2u(getWidth(), getHeight()));
				Sleep(200);
				return resChanged ? 10 : 0;
			}// exit
			if (numMenu == 2){
				Sleep(200);
				break;
			}//scroll text left
			if (numMenu == 3) {
				//����������� ����������, ��� ���������� ������
				if (choosenResolution == 0)choosenResolution = 5;
				else choosenResolution--;
				resChanged = true;
				Sleep(200);
			}//scroll text right
			if (numMenu == 4) {
				//����������� ����������, ��� ���������� ������
				if (choosenResolution == 5)choosenResolution = 0;
				else choosenResolution++;
				resChanged = true;
				Sleep(200);
			}//scroll text left2
			if (numMenu == 5) {
				//����������� ����� �������, ���� ���������� ������
				if (choosenMenuMusicLvl == 0)choosenMenuMusicLvl = 10;
				else choosenMenuMusicLvl--;
				Sleep(200);
			}//scroll text right2
			if (numMenu == 6) {
				//����������� ����� �������, ���� ���������� ������
				if (choosenMenuMusicLvl == 10) choosenMenuMusicLvl = 0;
				else choosenMenuMusicLvl++;
				Sleep(200);
			}//scroll text left3
			if (numMenu == 7) {
				//����������� ����� �������, ���� ���������� ������
				if (choosenGameMusicLvl == 0)choosenGameMusicLvl = 10;
				else choosenGameMusicLvl--;
				Sleep(200);
			}//scroll text right3
			if (numMenu == 8) {
				//����������� ����� �������, ���� ���������� ������
				if (choosenGameMusicLvl == 10)choosenGameMusicLvl = 0;
				else choosenGameMusicLvl++;
				Sleep(200);
			}//scroll text left4
			if (numMenu == 9) {
				//����������� ����� �������, ���� ���������� ������
				if (choosenGameSoundLvl == 0)choosenGameSoundLvl = 10;
				else choosenGameSoundLvl--;
				Sleep(200);
			}//scroll text right4
			if (numMenu == 10) {
				//����������� ����� �������, ���� ���������� ������
				if (choosenGameSoundLvl == 10)choosenGameSoundLvl = 0;
				else choosenGameSoundLvl++;
				Sleep(200);
			}
			if (numMenu == 11) {
				fullScreen = !fullScreen;
				resChanged = true;
				Sleep(200);
			}
		}



		//������ �� �������� �� ����
		window.draw(backgr);
		window.draw(Yes);
		window.draw(fscBt);
		window.draw(arrowLeft);
		window.draw(arrowRight);
		window.draw(arrowLeft2);
		window.draw(arrowRight2);
		window.draw(arrowLeft3);
		window.draw(arrowRight3);
		window.draw(arrowLeft4);
		window.draw(arrowRight4);
		window.draw(No);
		window.draw(resolutionText);
		window.draw(menuMusicLvl);
		window.draw(playMusicLvl);
		window.draw(playSoundLvl);
		//�������� �� ��������
		window.display();
	}
	return 0;
}