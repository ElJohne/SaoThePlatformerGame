#include "HumanEnemy.h"
using namespace sf;


void HumanEnemy::set(Texture &image, int x, int y, SoundBuffer buffer, Texture &texture)
{
	deathSound.setBuffer(buffer);
	sprite.setTexture(image);
	rect = FloatRect(x * 64, (y * 64)-60, 64, 100);
	leftSide = FloatRect(((x - 5) * 64) + 32, (y * 64) - 36, 64 * 5 + 32, 64 * 3);
	rightSide = FloatRect((x * 64) + 32, (y * 64) - 36, 64 * 5 + 32, 64 * 3);
	health = getCurrentLevel() + 1;
	dx = 0.05;
	currentFrame = 0;
	life = true;
	this->isAttacking = false;
	playerDetected = false;
	hb.set(getCurrentLevel() + 1, texture);
	hb.update(FloatRect(rect.left + 10, rect.top, rect.width, rect.height), health);
}
int HumanEnemy::playerDetection(PLAYER &p) {
	if (leftSide.contains(p.rect.left, p.rect.top)) {
		playerDetected = true;
		pSide = -1;
		return 0;
	}
	else if (rightSide.contains(p.rect.left, p.rect.top)) {
		playerDetected = true;
		pSide = 1;
		return 0;
	}
	else {
		playerDetected = false;
		pSide = 0;
		return 0;
	}
}
//Обновляє кадр ворога
void HumanEnemy::update(float time)
{
	if (health < 1) {
		life = false;
	}
	if (life) hb.update(FloatRect(rect.left + 10, rect.top, rect.width, rect.height), health);
	if (pSide == -1) dx = -0.07;
	else if (pSide == 1) dx = 0.07;
	if (!life) dx = 0;//якщо ворог мертвий - не рухається
	rect.left += dx * time; //рухаємо персонажа 
	leftSide.left = (rect.left - (64 * 5 - 32)) >= 0 ? rect.left - (64 * 5 - 32) : 0;
	leftSide.top = rect.top;
	rightSide.left = rect.left + 32;
	rightSide.top = rect.top;
	this->Collision();
	currentFrame += time * 0.005; //міняємо кадр
	if (currentFrame > 8) {
		currentFrame -= 8;
		if (this->isAttacking == true) this->isAttacking = false;
	}//якщо дойшли до остального кадра - починаємо спочатку
	 //Встановлюємо відповідний спрайт до руху ворогів
	if (this->isAttacking == false) {
		if (dx > 0)sprite.setTextureRect(IntRect(500, 400 * int(currentFrame), -250, 400));
		if (dx < 0)sprite.setTextureRect(IntRect(250, 400 * int(currentFrame), 250, 400));
	}
	else {
		if (dx > 0)sprite.setTextureRect(IntRect(250, 400 * int(currentFrame), -250, 400));
		if (dx < 0)sprite.setTextureRect(IntRect(0, 400 * int(currentFrame), 250, 400));
	}
	//Якщо ворог мертвий - ставимо текстуру смерті
	if (!life) sprite.setTextureRect(IntRect(250, 400 * 7, 250, 400));
	//ставимо спрайт на координати ворога
	if (life)sprite.setPosition(rect.left - getOffSetX(), rect.top - getOffSetY() - 12);
	if (!life)sprite.setPosition(rect.left - getOffSetX(), rect.top - getOffSetY() + 87);
}
//Смерть ворога
void HumanEnemy::death(float time, PLAYER &p) {
	//добавляємо очки гравцю
	p.score += 100;
	//змінюємо стан ворога
	life = false;
	//звук смерті
	deathSound.setVolume(getChoosenGameSound() * 10);
	deathSound.play();
	//обновляємо ворога
	this->update(time);
}
//
void HumanEnemy::hit(float time) {
	deathSound.setVolume(getChoosenGameSound() * 10);
	deathSound.play();
	health--;
	this->update(time);
}
//Метод обробки зіткнень з об`єктами
void HumanEnemy::Collision()
{
	for (int i = rect.top / 64; i < (rect.top + rect.height) / 64; i++)
	{
		for (int j = rect.left / 64; j < (rect.left + rect.width) / 64; j++)
		{
			if ((TileMapLocal[i][j] == 'C') || (TileMapLocal[i][j] == 'D') || (TileMapLocal[i][j] == 'T') || (TileMapLocal[i][j] == 'G') || (TileMapLocal[i][j] == 'B'))
			{
				if (dx > 0)
				{
					rect.left = j * 64 - rect.width; dx *= -1;
				}
				else if (dx < 0)
				{
					rect.left = j * 64 + 64;  dx *= -1;
				}
			}
		}
	}
}