#include "AnimalEnemy.h"
using namespace sf;

void AnimalEnemy::set(Texture &image, int x, int y, SoundBuffer buffer, Texture &texture)
{
	deathSound.setBuffer(buffer);
	sprite.setTexture(image);
	rect = FloatRect(x * 64, (y * 64) - 20, 100, 64);
	leftSide = FloatRect(((x - 5) * 64) + 32, (y - 1) * 64, 64 * 5 + 32, 64 * 2);
	rightSide = FloatRect((x * 64) + 32, (y - 1) * 64, 64 * 5 + 32, 64 * 2);
	health = getCurrentLevel() + 1;
	dx = 0.05;
	currentFrame = 0;
	life = true;
	playerDetected = false;
	isAttacking = false;
	hb.set(getCurrentLevel() + 1, texture);
	hb.update(FloatRect(rect.left + 50, rect.top - 40, rect.width, rect.height), health);
}

int AnimalEnemy::playerDetection(PLAYER &p) {
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
void AnimalEnemy::update(float time)
{
	if (health < 1) {
		life = false;
	}
	if (life) {
		hb.update(FloatRect(rect.left + 50, rect.top - 40, rect.width, rect.height), health);
		if (dx > 0) hb.update(FloatRect(rect.left + 35, rect.top - 40, rect.width, rect.height), health);
	}
	if (pSide == -1) dx = -0.07;
	else if (pSide == 1) dx = 0.07;
	if (!life) dx = 0;//якщо ворог мертвий - не рухається
	rect.left += dx * time; //рухаємо персонажа 
	leftSide.left = (rect.left - (64 * 5 - 32)) >= 0 ? rect.left - (64 * 5 - 32) : 0;
	rightSide.left = rect.left + 32;
	this->Collision();
	currentFrame += time * 0.005; //міняємо кадр
	if (currentFrame > 8) {
		currentFrame -= 8;
		if (this->isAttacking == true) this->isAttacking = false;
	}//якщо дойшли до остального кадра - починаємо спочатку
	 //Встановлюємо відповідний спрайт до руху ворогів
	if (this->isAttacking == false) {
		if (dx > 0)sprite.setTextureRect(IntRect(800, 250 * int(currentFrame), -400, 250));
		if (dx < 0)sprite.setTextureRect(IntRect(400, 250 * int(currentFrame), 400, 250));
	}
	else {
		if (dx > 0)sprite.setTextureRect(IntRect(400, 250 * int(currentFrame), -400, 250));
		if (dx < 0)sprite.setTextureRect(IntRect(0, 250 * int(currentFrame), 400, 250));
	}
	//Якщо ворог мертвий - ставимо текстуру смерті
	if (!life) sprite.setTextureRect(IntRect(400, 250 * 8, 400, 250));
	//ставимо спрайт на координати ворога
	if (life)sprite.setPosition(rect.left - getOffSetX(), rect.top - getOffSetY());
	if (!life)sprite.setPosition(rect.left - getOffSetX(), rect.top - getOffSetY() + 30);
}
//Смерть ворога
void AnimalEnemy::death(float time, PLAYER &p) {
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
void AnimalEnemy::hit(float time) {
	deathSound.setVolume(getChoosenGameSound() * 10);
	deathSound.play();
	health--;
	this->update(time);
}
//Метод обробки зіткнень з об`єктами
void AnimalEnemy::Collision()
{
	for (int i = rect.top / 64; i<(rect.top + rect.height) / 64; i++)
		for (int j = rect.left / 64; j<(rect.left + rect.width) / 64; j++)
			if ((TileMapLocal[i][j] == 'G') || (TileMapLocal[i][j] == 'C') || (TileMapLocal[i][j] == 'D') || (TileMapLocal[i][j] == 'T') || (TileMapLocal[i][j] == 'B'))
			{
				if (dx>0)
				{
					rect.left = j * 64 - rect.width; dx *= -1;
				}
				else if (dx<0)
				{
					rect.left = j * 64 + 64;  dx *= -1;
				}
			}
}
