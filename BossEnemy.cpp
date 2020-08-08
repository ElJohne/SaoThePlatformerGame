#include "BossEnemy.h"
using namespace sf;

void BossEnemy::set(Texture &image, int x, int y, SoundBuffer buffer, Texture &texture){}
void BossEnemy::set2(Texture &image, int x, int y, SoundBuffer buffer, Texture &texture, int HealthBars, int healthOnEachOne, int scoreGiven)
{
	deathSound.setBuffer(buffer);
	sprite.setTexture(image);
	rect = FloatRect(x * 64, (y * 64) - 70, 64, 100);
	leftSide = FloatRect(((x - 5) * 64) + 32, (y * 64) - 36, 64 * 5 + 32, 64 * 3);
	rightSide = FloatRect((x * 64) + 32, (y * 64) - 36, 64 * 5 + 32, 64 * 3);
	dx = 0.05;
	currentFrame = 0;
	life = true;
	this->scoreGiven = scoreGiven;
	countHealthBars = HealthBars;
	playerDetected = false;
	hb.set(healthOnEachOne, texture);
	hb.update(rect, hbh);
	hbh = healthOnEachOne;
	if (HealthBars > 1) {
		hb2.set(healthOnEachOne, texture);
		hb2.update(FloatRect(rect.left, rect.top - 180, rect.width, rect.height), hbh2);
		hbh2 = healthOnEachOne;
		if (HealthBars > 2) {
			hb3.set(healthOnEachOne, texture);
			hb3.update(FloatRect(rect.left, rect.top - 157, rect.width, rect.height), hbh3);
			hbh3 = healthOnEachOne;
			if (HealthBars > 3) {
				hb4.set(healthOnEachOne, texture);
				hb4.update(FloatRect(rect.left, rect.top - 135, rect.width, rect.height), hbh4);
				hbh4 = healthOnEachOne;
				if (HealthBars > 4) {
					hb5.set(healthOnEachOne, texture);
					hb5.update(FloatRect(rect.left, rect.top - 102, rect.width, rect.height), hbh5);
					hbh5 = healthOnEachOne;
				}
			}
		}
	}
}
int BossEnemy::playerDetection(PLAYER &p) {
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
void BossEnemy::update(float time)
{
	if (health < 1) {
		life = false;
	}
	if (life) {
		hb.update(rect, hbh);
		if (countHealthBars > 1) {
			hb2.update(FloatRect(rect.left, rect.top - 45, rect.width, rect.height), hbh2);
			if (countHealthBars > 2) {
				hb3.update(FloatRect(rect.left, rect.top - 90, rect.width, rect.height), hbh3);
				if (countHealthBars > 3) {
					hb4.update(FloatRect(rect.left, rect.top - 135, rect.width, rect.height), hbh4);
					if (countHealthBars > 4) {
						hb5.update(FloatRect(rect.left, rect.top - 180, rect.width, rect.height), hbh5);
					}
				}
			}
		}
	}
	if (pSide == -1) dx = -0.07;
	else if (pSide == 1) dx = 0.07;
	if (!life) dx = 0;//якщо ворог мертвий - не рухається
	rect.left += dx * time; //рухаємо персонажа 
	leftSide.left = (rect.left - (64 * 5 - 32)) >= 0 ? rect.left - (64 * 5 - 32) : 0;
	leftSide.top = rect.top;
	rightSide.left = rect.left + 32;
	rightSide.top = rect.top;
	this->Collision();
	currentFrame += time * 0.001; //міняємо кадр
	if (currentFrame > 8) {
		currentFrame -= 8;
		if (this->isAttacking == true) this->isAttacking = false;
	}//якщо дойшли до остального кадра - починаємо спочатку
											//Встановлюємо відповідний спрайт до руху ворогів
	if (this->isAttacking == false) {
		if (dx > 0)sprite.setTextureRect(IntRect(1028, 1028 * int(currentFrame), -514, 1028));
		if (dx < 0)sprite.setTextureRect(IntRect(514, 1028 * int(currentFrame), 514, 1028));
	}
	else {
		if (dx > 0)sprite.setTextureRect(IntRect(514, 1028 * int(currentFrame), -514, 1028));
		if (dx < 0)sprite.setTextureRect(IntRect(0, 1028 * int(currentFrame), 514, 1028));
	}
	//Якщо ворог мертвий - ставимо текстуру смерті
	if (!life) sprite.setTextureRect(IntRect(514, 1028 * 9, 514, 1024));
	//ставимо спрайт на координати ворога
	if (life)sprite.setPosition(rect.left - getOffSetX(), rect.top - getOffSetY());
	if (!life)sprite.setPosition(rect.left - getOffSetX(), rect.top - getOffSetY() + 87);
}
//Смерть ворога
void BossEnemy::death(float time, PLAYER &p) {
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
void BossEnemy::hit(float time) {
	deathSound.setVolume(getChoosenGameSound() * 10);
	deathSound.play();
	if (countHealthBars > 4) {
		if (hbh5 > 0) hbh5--;
		else if (hbh4 > 0) hbh4--;
		else if (hbh3 > 0) hbh3--;
		else if (hbh2 > 0) hbh2--;
		else hbh--;
		if (hbh <= 0) life = false;
	}
	else if (countHealthBars > 3) {
		if (hbh4 > 0) hbh4--;
		else if (hbh3 > 0) hbh3--;
		else if (hbh2 > 0) hbh2--;
		else hbh--;
		if (hbh <= 0) life = false;
	}
	else if (countHealthBars > 2) {
		if (hbh3 > 0) hbh3--;
		else if (hbh2 > 0) hbh2--;
		else hbh--;
		if (hbh <= 0) life = false;
	}
	else if (countHealthBars > 1) {
		if (hbh2 > 0) hbh2--;
		else hbh--;
		if (hbh <= 0) life = false;
	}
	this->update(time);
}
//Метод обробки зіткнень з об`єктами
void BossEnemy::Collision()
{
	for (int i = rect.top / 64; i<(rect.top + rect.height) / 64; i++)
		for (int j = rect.left / 64; j<(rect.left + rect.width) / 64; j++)
			if ((TileMapLocal[i][j] == 'C') || (TileMapLocal[i][j] == 'D') || (TileMapLocal[i][j] == 'T') || (TileMapLocal[i + 1][j] == 'C') || (TileMapLocal[i + 1][j] == 'D') || (TileMapLocal[i + 1][j] == 'T') || (TileMapLocal[i + 1][j] == 'B'))
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