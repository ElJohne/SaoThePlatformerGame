#include "play.h"
using namespace sf;

// Для збереження позиції персонажа
FloatRect playerPosition;
// Для того, щоб в поле зору не попадала пустота за картою
float offsetX = 0, offsetY = 0; 
//Рівень музики, звуків
int soundLevel = 0, musicLevel1 = 0;
//Карта поточного рівня
String TileMapLocal[20];
// Змінна для атаки
int count = 0;
// Висота рівня
const int H = 20;
// Ширина рівня
const int W = 50;
// поточний рівень
int currentLevel; 
bool cutSceneActivated = false;
bool bossIsDead = true;
//Чи рівень піднімається
Texture enemysTextures[13];
Texture shieldTexture;
//Оголошення функції
void lvlPlus(RenderWindow &window, bool isLvlUpping);
void cutScrene(RenderWindow &window, int lvl);

int gameStart(RenderWindow &window, int currentLvl, bool isLoaded)
{
	currentLevel = 0;
	Texture loading;
	loading.loadFromFile(get43()?"img/helloScreen-43.png":"img/helloScreen-169.png");
	//Імітація загрузки
	Sprite loading1(loading);
	loading1.setScale(getCoefX(window), getCoefY(window));
	window.draw(loading1);
	window.display();
	//Забираємо курсор під час ігри
	window.setMouseCursorVisible(false);
	//Робимо карту стандартною
	if (!isLoaded) {
		setTileMapDefault();
		setCurrentLevel(0);
	}
	for (int i = 0; i < H; i++)
	{
		TileMapLocal[i] = getTileMap(getCurrentLevel(), i);
	}
	int frameCount = 100;
	//Обнуляємо оффсети
	offsetX = 0;
	offsetY = 250;
	//Сворення текстур для спрайтів, загрузка з файлів
	Texture tileSet, background[12], player, healthTexture, healthPotionTexture, EnemyHbTexture;
	Texture skillBarTexture, skillHealTexture, skillHealDarkTexture, skillHealHTexture, skillHealHDarkTexture, skillAttackTexture, skillAttackDarkTexture, skillShieldTexture, skillShieldDarkTexture, skillShieldHealTexture, skillShieldHealDarkTexture;
	skillBarTexture.loadFromFile("img/SkillBar.png");
	skillHealTexture.loadFromFile("img/SkillHeal.png"); 
	skillHealDarkTexture.loadFromFile("img/SkillHealDark.png");
	skillHealHTexture.loadFromFile("img/SkillHealH.png");
	skillHealHDarkTexture.loadFromFile("img/SkillHealHDark.png");
	skillAttackTexture.loadFromFile("img/SkillAttack.png");
	skillAttackDarkTexture.loadFromFile("img/SkillAttackDark.png");
	skillShieldTexture.loadFromFile("img/SkillShield.png");
	skillShieldDarkTexture.loadFromFile("img/SkillShieldDark.png");
	skillShieldHealTexture.loadFromFile("img/SkillShieldHeal.png");
	skillShieldHealDarkTexture.loadFromFile("img/SkillShieldHealDark.png");
	EnemyHbTexture.loadFromFile("img/EnemyHealthbar.png");
	background[0].loadFromFile(get43() ? "img/gameBackground3-43.png" : "img/gameBackground3-169.png");
	background[1].loadFromFile(get43() ? "img/gameBackground2-43.png" : "img/gameBackground2-169.png");
	background[2].loadFromFile(get43() ? "img/gameBackground1-43.png" : "img/gameBackground1-169.png");
	background[3].loadFromFile(get43() ? "img/gameBackground4-43.png" : "img/gameBackground4-169.png");
	background[4].loadFromFile(get43() ? "img/gameBackground5-43.png" : "img/gameBackground5-169.png");
	background[5].loadFromFile(get43() ? "img/gameBackground6-43.png" : "img/gameBackground6-169.png");
	background[6].loadFromFile(get43() ? "img/gameBackground3-43.png" : "img/gameBackground3-169.png");
	background[7].loadFromFile(get43() ? "img/gameBackground2-43.png" : "img/gameBackground2-169.png");
	background[8].loadFromFile(get43() ? "img/gameBackground1-43.png" : "img/gameBackground1-169.png");
	background[9].loadFromFile(get43() ? "img/gameBackground4-43.png" : "img/gameBackground4-169.png");
	background[10].loadFromFile(get43() ? "img/gameBackground5-43.png" : "img/gameBackground5-169.png");
	background[11].loadFromFile(get43() ? "img/gameBackground6-43.png" : "img/gameBackground6-169.png");
	tileSet.loadFromFile("img/testTileSet.png"); //tileSet
	player.loadFromFile("img/kiritoHD.png");
	healthTexture.loadFromFile("img/healthBar.png");
	healthPotionTexture.loadFromFile("img/healthPotion.png");
	shieldTexture.loadFromFile("img/shield.png");
	for (int i = 0; i < 13; i++)
	{
		enemysTextures[i].loadFromFile("img/Enemy-"+ std::to_string(i) + ".png");
	}
	//Створення спрайтів, яким передаються текстури
	Sprite tiles(tileSet);
	Sprite backgr(background[currentLvl]);
	Sprite healthBar(healthTexture);
	Sprite healthBar2(healthTexture);
	Sprite healthPotion(healthPotionTexture);
	Sprite skillBar(skillBarTexture);
	Sprite skillAttack(skillAttackDarkTexture), skillHeal(skillHealDarkTexture), skillHealH(skillHealHDarkTexture), skillShield(skillShieldDarkTexture), skillShieldHeal(skillShieldHealDarkTexture);
	skillBar.setScale(0.25*getCoefX(window), 0.25*getCoefY(window));
	skillAttack.setScale(0.25*getCoefX(window), 0.25*getCoefY(window));
	skillHeal.setScale(0.25*getCoefX(window), 0.25*getCoefY(window));
	skillHealH.setScale(0.25*getCoefX(window), 0.25*getCoefY(window));
	skillShield.setScale(0.25*getCoefX(window), 0.25*getCoefY(window));
	skillShieldHeal.setScale(0.25*getCoefX(window), 0.25*getCoefY(window));
	skillBar.setPosition((get43() ? 425 : 685) * getCoefX(window), (get43() ? 930 : 975) * getCoefY(window));
	skillAttack.setPosition((get43() ? 450 : 710) * getCoefX(window), (get43() ? 950 : 995) * getCoefY(window));
	skillHeal.setPosition((get43() ? 550 : 810) * getCoefX(window), (get43() ? 950 : 995) * getCoefY(window));
	skillHealH.setPosition((get43() ? 650 : 910) * getCoefX(window), (get43() ? 950 : 995) * getCoefY(window));
	skillShield.setPosition((get43() ? 750 : 1010) * getCoefX(window), (get43() ? 950 : 995) * getCoefY(window));
	skillShieldHeal.setPosition((get43() ? 850 : 1110) * getCoefX(window), (get43() ? 950 : 995) * getCoefY(window));
	//Створення фонової музики і загрузка її з файла
	SoundBuffer buffer1, buffer2, buffer3, buffer4, buffer5, buffer6;
	buffer1.loadFromFile("sound/jumpSound.ogg");
	buffer2.loadFromFile("sound/eatSound.ogg");
	buffer3.loadFromFile("sound/attackSound.ogg");
	buffer4.loadFromFile("sound/damageSound.ogg");
	buffer5.loadFromFile("sound/enemyDethSound.ogg");
	buffer6.loadFromFile("sound/potion.ogg");
	Font font;
	font.loadFromFile("config/font.ttf");
	String potionsStr;
	String nickNameStr;
	String lvlStr;
	String scoreStr;
	//Створення звуків, музики
	soundLevel = getChoosenGameSound() * 10;
	musicLevel1 = getChoosenGameMusic() * 10;
	Sound sound1(buffer1), damageSound(buffer4);
	sound1.setVolume(soundLevel);
	Music music;
	music.openFromFile("sound/playBackgroundSound.ogg");
	music.setVolume(musicLevel1);
	music.setLoop(true);
	music.play();
	//Створюється гравець, якому передається текстурка і два звуки
	PLAYER p(player, buffer2, buffer3, buffer6);
	//Створюється список, в який закидаються всі вороги рівня
	std::list<BossEnemy> bossEnemys;
	std::list<BossEnemy>::iterator itBossEnemys;
	std::list<HumanEnemy> humanEnemys;
	std::list<HumanEnemy>::iterator itHumanEnemys;
	std::list<AnimalEnemy> animalEnemys;
	std::list<AnimalEnemy>::iterator itAnimalEnemys;
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if (TileMapLocal[i][j] == '0' || TileMapLocal[i][j] == '1' || TileMapLocal[i][j] == '2' || TileMapLocal[i][j] == '3' || TileMapLocal[i][j] == '4' || TileMapLocal[i][j] == '5' || TileMapLocal[i][j] == '6' || TileMapLocal[i][j] == '7' || TileMapLocal[i][j] == '8' || TileMapLocal[i][j] == '9' || TileMapLocal[i][j] == 'W' || TileMapLocal[i][j] == 'Q' || TileMapLocal[i][j] == 'A')
			{
				int temp;
				switch (TileMapLocal[i][j]) {
				case '0': temp = 0; break;
				case '1': temp = 1; break;
				case '2': temp = 2; break;
				case '3': temp = 3; break;
				case '4': temp = 4; break;
				case '5': temp = 5; break;
				case '6': temp = 6; break;
				case '7': temp = 7; break;
				case '8': temp = 8; break;
				case '9': temp = 9; break;
				case 'W': temp = 10; break;
				case 'Q': temp = 11; break;
				case 'A': temp = 12; break;
				}
				HumanEnemy e1;
				AnimalEnemy e2;
				BossEnemy b1;
				if (temp == 0 || temp == 1 || temp == 2 || temp == 3) {
					e1.set(enemysTextures[temp], j, i, buffer5, EnemyHbTexture);
					humanEnemys.push_back(e1);
				}
				else if (temp == 12) {
					b1.set2(enemysTextures[temp], j, i, buffer5, EnemyHbTexture, 3, 10, 800);
					bossEnemys.push_back(b1);
					bossIsDead = false;
				}
				else {
					e2.set(enemysTextures[temp], j, i, buffer5, EnemyHbTexture);
					animalEnemys.push_back(e2);
				}
			}
		}
	}
	p.isWin = false;
	//Ставимо текстуру спрайту атаки
	p.attackSprite.setTexture(player);
	float damageTime = 0; // Час, який пройшов з часу остального получення шкоди
	float attackTime = 0; // Час, який пройшов з часу остальної атаки
	float time = 0;
	float shieldActiveTime = 0;
	float healingTime = 0;
	float jumpingTime = 0;
	float regenTime = 0;
	float regenCDTime = 0;
	float shieldCDTime = 0;
	Vector2f center;
	Vector2f size;
	currentLevel = currentLvl; // Беремо переданий рівень
	setCurrentLevel(currentLevel); // Встановлюємо його як поточний
	int tmpCount = 0; // тимчасова змінна
	if (isLoaded) {
		currentLevel = getCurrentLevel();
		p.rect.left = getPlayerLeft();
		p.rect.top = getPlayerTop();
		offsetX = getOffSetX();
		offsetY = getOffSetY();
		p.health = getPlayerHealth();
		p.score = getCurrentScore();
		for (int i = 0; i < H; i++)
		{
			TileMapLocal[i] = getTileMap(getCurrentLevel(), i);
		}
		tmpCount = 0;
		for (itHumanEnemys = humanEnemys.begin(); itHumanEnemys != humanEnemys.end(); itHumanEnemys++)
		{
			(*itHumanEnemys).life = getEnemyAlive(tmpCount);
			tmpCount++;
		}
		tmpCount = 0;
		for (itAnimalEnemys = animalEnemys.begin(); itAnimalEnemys != animalEnemys.end(); itAnimalEnemys++)
		{
			(*itAnimalEnemys).life = getEnemyAliveAnimal(tmpCount);
			tmpCount++;
		}
		tmpCount = 0;
		isLoaded = false;
	}
	Clock clock; // Годинник для прив`язки зміни кадрів до часу
	Clock attack; // годинник для затримки між атаками
	Clock damage; // годинник для затримки між шкодою нанесеною гравцю
	Clock shieldActive;
	Clock healing;
	Clock jumping;
	Clock regeneration;
	Clock ShieldCD;
	Clock RegenCD;
	float healthCoef;
	//ставимо відповідний до рівня задній фон
	backgr.setTexture(background[getCurrentLevel()]);
	if(!isLoaded)cutScrene(window, -1);
	window.clear();
	window.draw(backgr);
	int shieldHealCount = 1;
	//цикл показу вікна
	while (window.isOpen())
	{
		//Записуємо в змінну час, який пройшов за один цикл в два годинника
		Time attackElapsed = attack.restart();
		Time damageElapsed = damage.restart();
		Time shieldActiveElapsed = shieldActive.restart();
		Time healingElapsed = healing.restart();
		Time jumpingElapsed = jumping.restart();
		Time regenElapsed = regeneration.restart();
		Time shieldCDElapsed = ShieldCD.restart();
		Time regenCDElapsed = RegenCD.restart();
		attackTime += jumpingElapsed.asSeconds();
		damageTime += damageElapsed.asSeconds();
		shieldActiveTime += shieldActiveElapsed.asSeconds();
		healingTime += healingElapsed.asSeconds();
		jumpingTime += jumpingElapsed.asSeconds();
		regenTime += regenElapsed.asSeconds();
		regenCDTime += regenElapsed.asSeconds();
		shieldCDTime += regenElapsed.asSeconds();
		if (shieldActiveTime > p.shieldTime && p.shield) p.shield = false;
		if (shieldActiveTime >= 0.99 && shieldActiveTime < 1.01 && shieldHealCount == 1 && p.shieldRegeneration && p.health < p.maxHealth && p.shield) {
			p.health++;
			shieldHealCount++;
			if (p.st.lvl[2][4] == 0 && p.st.lvl[2][1] == 0) shieldHealCount = 0;
		}
		else if (shieldActiveTime >= 1.99 && shieldActiveTime < 2.01 && shieldHealCount == 2 && p.shieldRegeneration && p.health < p.maxHealth && p.shield) {
			p.health++;
			shieldHealCount++;
		}
		else if (shieldActiveTime > 2.99 && shieldActiveTime < 3.01 && shieldHealCount == 3 && p.shieldRegeneration && p.health < p.maxHealth && p.shield) {
			p.health++;
			shieldHealCount++;
			if (p.st.lvl[2][4] == 0) shieldHealCount = 0;
		}
		else if (shieldActiveTime > 3.99 && shieldActiveTime < 4.01 && shieldHealCount == 4 && p.shieldRegeneration && p.health < p.maxHealth && p.shield) {
			p.health++;
			shieldHealCount++;
		}
		else if (shieldActiveTime > 4.99 && shieldActiveTime < 5.01 && shieldHealCount == 5 && p.shieldRegeneration && p.health < p.maxHealth && p.shield) {
			p.health++;
			shieldHealCount = 1;
		}
		if (p.regeneration && regenTime > 45 && p.health < p.maxHealth) {
			p.health++;
			regenTime = 0;
		}
		//Перезапускаємо годинники
		attack.restart();
		damage.restart();
		shieldActive.restart();
		healing.restart();
		jumping.restart();
		regeneration.restart();
		RegenCD.restart();
		ShieldCD.restart();
		//Провірка, чи event закінчився
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		//якщо йде перехід на новий рівень
		if (p.isLvlUpping) {
			backgr.setTexture(background[getCurrentLevel()]);
			window.clear();
			window.draw(backgr);
			p.isLvlUpping = false;
		}
		//зберігаємо стан ворогів
		tmpCount = 0;
		for (itHumanEnemys = humanEnemys.begin(); itHumanEnemys != humanEnemys.end(); itHumanEnemys++)
		{
			setEnemyAlive(tmpCount, (*itHumanEnemys).life);
			tmpCount++;
		}
		for (itAnimalEnemys = animalEnemys.begin(); itAnimalEnemys != animalEnemys.end(); itAnimalEnemys++)
		{
			setEnemyAliveAnimal(tmpCount, (*itAnimalEnemys).life);
			tmpCount++;
		}
		tmpCount = 0;

		//ставимо текстуру healthbar`a
		healthBar.setTextureRect(IntRect(0, 0, 341, 57));
		healthBar2.setTextureRect(IntRect(0, 57, 303, 13));
		healthCoef = (float)p.health / p.maxHealth;
		healthBar2.setScale(healthCoef, 1);
		healthBar.setPosition(32, 32);
		healthBar2.setPosition(32+21, 32+15);
		healthPotion.setScale(0.1, 0.1);
		healthPotion.setPosition(32, 99);
		//змінюємо рівень музики
		soundLevel = getChoosenGameSound() * 10;
		musicLevel1 = getChoosenGameMusic() * 10;
		music.setVolume(musicLevel1);
		time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		//Настроюємо швидкість ігри зміною змінної, в яку записуємо час
		time /= 350;
		//Не даємо швидкості перевищити 20
		if (time > 20) time = 20;
		//Створення текстів
		setCurrentScore(p.score);
		potionsStr = "x" + std::to_string(p.healthPotion);
		nickNameStr = "" + getAccountName();
		lvlStr = "LVL: " + std::to_string(p.lvl);
		scoreStr = std::to_string(p.score);
		Text lvlText(lvlStr, font, 11), scoreText(scoreStr, font, 11), potionsText(potionsStr, font, 13);
		Text nickName(nickNameStr, font, 13);
		float tmp = p.attackTime - attackTime;
		String tmpCDStr = std::to_string(tmp);
		Text attackCDText(tmpCDStr.substring(0, 4), font, 20);
		attackCDText.setStyle(Text::Italic);
		tmp = 45 - regenTime;
		tmpCDStr = std::to_string(tmp);
		Text regenCDText(tmpCDStr.substring(0, 4), font, 20);
		regenCDText.setStyle(Text::Italic);
		tmp = 60 - regenCDTime;
		tmpCDStr = std::to_string(tmp);
		Text healHCDText(tmpCDStr.substring(0, 4), font, 20);
		healHCDText.setStyle(Text::Italic);
		tmp = 35 - shieldCDTime;
		tmpCDStr = std::to_string(tmp);
		Text shieldCDText(tmpCDStr.substring(0, 4), font, 20);
		shieldCDText.setStyle(Text::Italic);
		nickName.setPosition(32+20, 32+33);
		lvlText.setPosition(332, 70);
		scoreText.setPosition(270, 70);
		potionsText.setPosition(80, 100);
		attackCDText.setPosition((get43() ? 456 : 716) * getCoefX(window), (get43() ? 1015 : 1045) * getCoefY(window));
		regenCDText.setPosition((get43() ? 556 : 816) * getCoefX(window), (get43() ? 1015 : 1045) * getCoefY(window));
		healHCDText.setPosition((get43() ? 656 : 916) * getCoefX(window), (get43() ? 1015 : 1045) * getCoefY(window));
		shieldCDText.setPosition((get43() ? 756 : 1016) * getCoefX(window), (get43() ? 1015 : 1045) * getCoefY(window));
		attackCDText.setFillColor(Color::Black);
		regenCDText.setFillColor(Color::Black);
		healHCDText.setFillColor(Color::Black);
		shieldCDText.setFillColor(Color::Black);
		setPotionCount(p.healthPotion);
		//Обробка кнопки A
		if (Keyboard::isKeyPressed(Keyboard::A) && !p.isAttacking)
		{
			p.dx = -0.1;
			p.setLeft(); //Змінюєм напрям остального руху
		}
		//Обробка кнопки D
		if (Keyboard::isKeyPressed(Keyboard::D) && !p.isAttacking)
		{
			p.dx = 0.1;
			p.setRight();//Змінюємо напрям остального руху
		}
		//Обробка кнопки Space
		if (Keyboard::isKeyPressed(Keyboard::Space) && !p.isAttacking)
		{
			//Якщо гравець на землі
			if (p.onGround)
			{
				p.dy = -0.35;//Змінюємо рух по осі Y
				p.onGround = false;//Позначаємо, що гравець в повітрі
				sound1.play();//Запускаємо звук стрибка
			}
			if (p.shield && jumpingTime > 0.6 && p.shieldJump) {
				p.dy = -0.35;//Змінюємо рух по осі Y
				p.onGround = false;//Позначаємо, що гравець в повітрі
				sound1.play();//Запускаємо звук стрибка
				jumpingTime = 0;
			}
		}
		//Обробка кнопки Esc
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			Sleep(200);//Затримка 0.2 секунди
			music.pause();//Ставимо на павзу музику
			window.setMouseCursorVisible(true);//включаємо курсор мишки
			//Запускаємо павзу, і провіряємо результат її роботи
			int result = pauseStart(window);
			if(result == 1) break;//Якщо функція повернула 1 - закінчуємо ігру
			else if (result == 2) {//Якщо 2 - загружаємо раніше збережені дані
				window.setMouseCursorVisible(false);//виключаємо курсор мишки
				currentLevel = getCurrentLevel();
				backgr.setTexture(background[currentLevel]);
				p.rect.left = getPlayerLeft();
				p.rect.top = getPlayerTop();
				offsetX = getOffSetX();
				offsetY = getOffSetY();
				p.health = getPlayerHealth();
				p.score = getCurrentScore();
				for (int i = 0; i < H; i++)
				{
					TileMapLocal[i] = getTileMap(getCurrentLevel(), i);
				}
				tmpCount = 0;
				for (itHumanEnemys = humanEnemys.begin(); itHumanEnemys != humanEnemys.end(); itHumanEnemys++)
				{
					(*itHumanEnemys).life = getEnemyAlive(tmpCount);
					(*itHumanEnemys).dx = 0.05;
					tmpCount++;
				}
				tmpCount = 0;
				for (itAnimalEnemys = animalEnemys.begin(); itAnimalEnemys != animalEnemys.end(); itAnimalEnemys++)
				{
					(*itAnimalEnemys).life = getEnemyAliveAnimal(tmpCount);
					(*itAnimalEnemys).dx = 0.05;
					tmpCount++;
				}
				tmpCount = 0;
				window.draw(loading1);
				window.display();
				Sleep(3000);
				window.clear();
			}
			else if (result == 10) {
				return 10;
			}
			window.setMouseCursorVisible(false);//виключаємо курсор мишки
			music.play();//Запускаємо музику
		}
		if (attackTime > p.attackTime && !p.isAttacking) {
			p.combo = 0;
			p.DamageTaken = false;
		}
		//Обробка кнопки F
		count = getAttackVar();
		if (Keyboard::isKeyPressed(Keyboard::F) && !p.isBoxPicked)
		{
			//Провіряємо, чи вже можна знову використати удар
			if (attackTime > p.attackTime) {
				//Якщо це перший захід в функцію
				p.fight.setVolume(soundLevel);//Ставимо гучність звука
				p.fight.play();//Запускаємо звук удара
				p.currentFrame = 0;//Ставимо кадр на початковий
				p.isAttacking = true;//Вказуємо, що ведеться атака
				attack.restart();//Перезапускаємо годинник, який рахує час з послідньої атаки
				attackTime = 0; //Обнуляємо змінну часу
				p.combo = 0;
				p.DamageTaken = false;
			}
			else if(attackTime < p.attackTime && p.isAttacking == false){
				if (p.combo < p.maxCombo) {
					p.DamageTaken = false;
					p.combo++;
					p.fight.setVolume(soundLevel);//Ставимо гучність звука
					p.fight.play();//Запускаємо звук удара
					p.currentFrame = 0;//Ставимо кадр на початковий
					count++;//Збільшуємо змінну, щою знову не зайти в попереднє розгалуження
					setAttackVar(count);
					p.isAttacking = true;//Вказуємо, що ведеться атака
					attack.restart();//Перезапускаємо годинник, який рахує час з послідньої атаки
					attackTime = 0; //Обнуляємо змінну часу
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::X) && !p.isAttacking)
		{
			if (p.healthPotion >= 1 && healingTime > 0.5) {
				p.potion.setVolume(soundLevel);
				p.potion.play();
				if (p.health < p.maxHealth) p.health++;
				p.healthPotion--;
				healingTime = 0;
			}
		}
		//Обробка кнопки W
		if (Keyboard::isKeyPressed(Keyboard::H) && !p.isAttacking && p.st.lvl[0][3] == 1 && regenCDTime > 60)
		{
			if (p.health <= (p.maxHealth - 5)) p.health += 5;
			else p.health = p.maxHealth;
			regenCDTime = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::K) && !p.isAttacking)
		{
			window.setMouseCursorVisible(true);
			skillMenu(window, p);
			window.setMouseCursorVisible(false);
			if (p.st.lvl[0][0] == 1) p.maxHealth = 12;
			if (p.st.lvl[0][1] == 1) p.maxHealth = 15;
			if (p.st.lvl[0][2] == 1)  
			{
				p.regeneration = true;
				regenTime = 0;
			}
			if (p.st.lvl[0][3] == 1) p.heal_H_Btn = true;
			if (p.st.lvl[0][4] == 1) p.maxHealth = 20;
			if (p.st.lvl[1][0] == 1) p.attackTime = 1;
			if (p.st.lvl[1][1] == 1) p.attackTime = 0.75;
			if (p.st.lvl[1][2] == 1) p.maxCombo = 1;
			if (p.st.lvl[1][3] == 1) p.maxCombo = 2;
			if (p.st.lvl[1][4] == 1) p.attackTime = 0.5;
			if (p.st.lvl[2][3] == 1) p.shieldRegeneration = true;
			if (p.st.lvl[2][2] == 1) p.shieldJump = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Q) && shieldCDTime > 35 )
		{
			if (p.st.lvl[2][4] == 1 && !p.shield) {
				p.shield = true;
				p.shieldTime = 5;
				shieldActive.restart();
				shieldActiveTime = 0;
				shieldCDTime = 0;
			}
			else if (p.st.lvl[2][1] == 1 && !p.shield) {
				p.shield = true;
				p.shieldTime = 3;
				shieldActive.restart();
				shieldActiveTime = 0;
				shieldCDTime = 0;
			}
			else if (p.st.lvl[2][0] == 1 && !p.shield) {
				p.shield = true;
				p.shieldTime = 1;
				shieldActive.restart();
				shieldActiveTime = 0;
				shieldCDTime = 0;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::E) && !p.isAttacking)
		{
			if (!p.isBoxPicked)
			{
				if (p.isLeft == true) {
					if (TileMapLocal[((int)(p.rect.top / 64 + 1))][((int)(p.rect.left / 64 - 1))] == 'B') {
						TileMapLocal[((int)(p.rect.top / 64 + 1))][((int)(p.rect.left / 64 - 1))] = ' ';
						p.isBoxPicked = true;
						Sleep(200);
					}
				}
				else {
					if (TileMapLocal[((int)(p.rect.top / 64 + 1))][((int)(p.rect.left / 64 + 2))] == 'B') {
						TileMapLocal[((int)(p.rect.top / 64 + 1))][((int)(p.rect.left / 64 + 2))] = ' ';
						p.isBoxPicked = true;
						Sleep(200);
					}
				}
			}
			else {
				if (p.onGround) {
					if (p.isLeft == true) {
						if (TileMapLocal[((int)(p.rect.top / 64 + 1))][((int)(p.rect.left / 64 - 1))] == ' ') {
							bool isBottomClear = true;
							for (int i = 2; isBottomClear; i++) {
								if (TileMapLocal[((int)(p.rect.top / 64 + i))][((int)(p.rect.left / 64-1))] != ' ' && TileMapLocal[((int)(p.rect.top / 64 + i))][((int)(p.rect.left / 64 - 1))] != 'O') {
									TileMapLocal[((int)(p.rect.top / 64 + (i-1)))][((int)(p.rect.left / 64 - 1))] = 'B';
									isBottomClear = false;
								}
							}
							p.isBoxPicked = false;
							p.rect.left = (p.rect.left - ((int)p.rect.left%64));
							Sleep(200);
						}
					}
					else {
						if (TileMapLocal[((int)(p.rect.top / 64 + 1))][((int)(p.rect.left / 64 + 2))] == ' ') {
							bool isBottomClear = true;
							for (int i = 2; isBottomClear; i++) {
								if (TileMapLocal[((int)(p.rect.top / 64 + i))][((int)(p.rect.left / 64 + 2))] != ' ' && TileMapLocal[((int)(p.rect.top / 64 + i))][((int)(p.rect.left / 64 + 2))] != 'O') {
									TileMapLocal[((int)(p.rect.top / 64 + (i-1)))][((int)(p.rect.left / 64 + 2))] = 'B';
									isBottomClear = false;
								}
							}
							p.isBoxPicked = false;
							p.rect.left = (int)(p.rect.left - ((int)p.rect.left % 64));
							Sleep(200);
						}
					}
				}
			}
		}
		//провіряємо чи гравець атакував ворога
		for (itHumanEnemys = humanEnemys.begin(); itHumanEnemys != humanEnemys.end(); itHumanEnemys++) {
			if (!p.DamageTaken) {
				if ((p.attackRectLeft.intersects((*itHumanEnemys).rect) || p.attackRectRight.intersects((*itHumanEnemys).rect)) && p.isAttacking)
				{
					if (p.attackRectLeft.intersects((*itHumanEnemys).rect) && p.isLeft && (*itHumanEnemys).life) {
						(*itHumanEnemys).hit(time);
						p.DamageTaken = true;
						if ((*itHumanEnemys).life == false) (*itHumanEnemys).death(time, p);
					}
					if (p.attackRectRight.intersects((*itHumanEnemys).rect) && !p.isLeft && (*itHumanEnemys).life) {
						(*itHumanEnemys).hit(time);
						p.DamageTaken = true;
						if ((*itHumanEnemys).life == false) (*itHumanEnemys).death(time, p);
					}
				}
				if ((*itHumanEnemys).rect.intersects(p.rect) && (*itHumanEnemys).life) {
					if (damageTime > 0.5) {
						p.dy = -0.15;
						p.onGround = false;
						(*itHumanEnemys).isAttacking = true;
						(*itHumanEnemys).currentFrame = 0;
						if (p.health > 0)p.health -= 1 * (currentLevel + 1);
						setPlayerHealth(p.health);
						damageSound.setVolume(soundLevel);
						damageSound.play();
						damageTime = 0;
						damage.restart();
					}
				}
			}
		}
		for (itAnimalEnemys = animalEnemys.begin(); itAnimalEnemys != animalEnemys.end(); itAnimalEnemys++) {
			if (!p.DamageTaken) {
				if ((p.attackRectLeft.intersects((*itAnimalEnemys).rect) || p.attackRectRight.intersects((*itAnimalEnemys).rect)) && p.isAttacking)
				{
					if (p.attackRectLeft.intersects((*itAnimalEnemys).rect) && p.isLeft && (*itAnimalEnemys).life) {
						(*itAnimalEnemys).hit(time);
						p.DamageTaken = true;
						if ((*itAnimalEnemys).life == false) (*itAnimalEnemys).death(time, p);
					}
					if (p.attackRectRight.intersects((*itAnimalEnemys).rect) && !p.isLeft && (*itAnimalEnemys).life) {
						(*itAnimalEnemys).hit(time);
						p.DamageTaken = true;
						if ((*itAnimalEnemys).life == false) (*itAnimalEnemys).death(time, p);
					}
				}
				if ((*itAnimalEnemys).rect.intersects(p.rect) && (*itAnimalEnemys).life) {
					if (damageTime > 0.5) {
						p.dy = -0.15;
						p.onGround = false;
						(*itAnimalEnemys).isAttacking = true;
						(*itAnimalEnemys).currentFrame = 0;
						if (p.health > 0)p.health -= p.shield ? ((int)(1 * (currentLevel + 1)/2)) : ((int)(1 * (currentLevel + 1)));
						setPlayerHealth(p.health);
						damageSound.setVolume(soundLevel);
						damageSound.play();
						damageTime = 0;
						damage.restart();
					}
				}
			}
		}
		for (itBossEnemys = bossEnemys.begin(); itBossEnemys != bossEnemys.end(); itBossEnemys++) {
			if (!p.DamageTaken) {
				if ((p.attackRectLeft.intersects((*itBossEnemys).rect) || p.attackRectRight.intersects((*itBossEnemys).rect)) && p.isAttacking)
				{
					if (p.attackRectLeft.intersects((*itBossEnemys).rect) && p.isLeft && (*itBossEnemys).life) {
						(*itBossEnemys).hit(time);
						p.DamageTaken = true;
						if ((*itBossEnemys).life == false){
							(*itBossEnemys).death(time, p);
							bossIsDead = true;
						}
					}
					if (p.attackRectRight.intersects((*itBossEnemys).rect) && !p.isLeft && (*itBossEnemys).life) {
						(*itBossEnemys).hit(time);
						p.DamageTaken = true;
						if ((*itBossEnemys).life == false) { 
							(*itBossEnemys).death(time, p);
							bossIsDead = true;
						}
					}
				}
				if ((*itBossEnemys).rect.intersects(p.rect) && (*itBossEnemys).life) {
					if (damageTime > 0.5) {
						p.dy = -0.15;
						p.onGround = false;
						(*itBossEnemys).isAttacking = true;
						(*itBossEnemys).currentFrame = 0;
						if (p.health > 0)p.health -= p.shield ? ((int)(1 * (currentLevel + 1) / 2)) : ((int)(1 * (currentLevel + 1)));
						setPlayerHealth(p.health);
						damageSound.setVolume(soundLevel);
						damageSound.play();
						damageTime = 0;
						damage.restart();
					}
				}
			}
		}
		//Запуск методу update у гравця
		p.update(time, window);
		frameCount++;
		if (frameCount == 30) {
			saveStart(window);
		}
		//якщо йде перехід на новий рівень
		if (p.isLvlUp) {
			frameCount = 25;
			humanEnemys.clear(); //очищуємо список ворогів
			animalEnemys.clear(); //очищуємо список ворогів
			bossEnemys.clear();
			for (int i = 0; i < H; i++)
			{
				for (int j = 0; j < W; j++)
				{
					if (TileMapLocal[i][j] == '0' || TileMapLocal[i][j] == '1' || TileMapLocal[i][j] == '2' || TileMapLocal[i][j] == '3' || TileMapLocal[i][j] == '4' || TileMapLocal[i][j] == '5' || TileMapLocal[i][j] == '6' || TileMapLocal[i][j] == '7' || TileMapLocal[i][j] == '8' || TileMapLocal[i][j] == '9' || TileMapLocal[i][j] == 'W' || TileMapLocal[i][j] == 'Q' || TileMapLocal[i][j] == 'A')
					{
						int temp;
						switch (TileMapLocal[i][j]) {
						case '0': temp = 0; break;
						case '1': temp = 1; break;
						case '2': temp = 2; break;
						case '3': temp = 3; break;
						case '4': temp = 4; break;
						case '5': temp = 5; break;
						case '6': temp = 6; break;
						case '7': temp = 7; break;
						case '8': temp = 8; break;
						case '9': temp = 9; break;
						case 'W': temp = 10; break;
						case 'Q': temp = 11; break;
						case 'A': temp = 12; break;
						}
						HumanEnemy e1;
						AnimalEnemy e2;
						BossEnemy b1;
						if (temp == 0 || temp == 1 || temp == 2 || temp == 3) {
							e1.set(enemysTextures[temp], j, i, buffer5, EnemyHbTexture);
							humanEnemys.push_back(e1);
						}
						else if (temp == 12) {
							b1.set2(enemysTextures[temp], j, i, buffer5, EnemyHbTexture, 3, 10, 800);
							bossEnemys.push_back(b1);
						}
						else {
							e2.set(enemysTextures[temp], j, i, buffer5, EnemyHbTexture);
							animalEnemys.push_back(e2);
						}
					}
				}
			}
			p.isLvlUp = false;
		}
		//Обновляємо кадр всіх ворогів
		for (itHumanEnemys = humanEnemys.begin(); itHumanEnemys != humanEnemys.end(); itHumanEnemys++)
		{
			(*itHumanEnemys).playerDetection(p);
			(*itHumanEnemys).update(time);
		}
		for (itAnimalEnemys = animalEnemys.begin(); itAnimalEnemys != animalEnemys.end(); itAnimalEnemys++)
		{
			(*itAnimalEnemys).playerDetection(p);
			(*itAnimalEnemys).update(time);
		}
		for (itBossEnemys = bossEnemys.begin(); itBossEnemys != bossEnemys.end(); itBossEnemys++)
		{
			(*itBossEnemys).playerDetection(p);
			(*itBossEnemys).update(time);
		}
		//Встановлюємо поточну карту(для збереження)
		for (int i = 0; i < H; i++)
		{
			setTileMap(currentLevel, TileMapLocal);
		}
		//Зберігяємо окремо позицію гравця(для збереження)
		playerPosition = p.rect;
		//Якщо в поле зору попадає територія за межами карти, то зупиняємо скролінг карти
		if (p.rect.left > (Resolutions[getChoosen()][0] / 2) && p.rect.left < ((W-5) * 64 - (Resolutions[getChoosen()][0] * getCoefX(window) / 2))) offsetX = p.rect.left - (getWidth() / 2);
		if (p.rect.top > (64*6 * getCoefY(window)) && p.rect.top < (64*10 * getCoefY(window))) offsetY = p.rect.top - (getHeight() / 2);
		setOffSetX(offsetX);
		setOffSetY(offsetY);
		//Ставимо текстуру заднього фону і розміщення
		backgr.setPosition(0,0);
		window.draw(backgr);
		//Цикли, які малюють карту
		center = { window.getView().getCenter().x + offsetX, window.getView().getCenter().y + offsetY};
		size = window.getView().getSize();
		for (int i = 0; i <= 20; i++) {
			for (int j = 0; j <= 50; j++) {
				if (TileMapLocal[i][j] == 'C') tiles.setTextureRect(IntRect(0, 1024 * getCurrentLevel(), 512, 512));
				if (TileMapLocal[i][j] == 'D') tiles.setTextureRect(IntRect(512, 1024 * getCurrentLevel(), 512, 512));
				if (TileMapLocal[i][j] == 'G') tiles.setTextureRect(IntRect(512 * 2, 1024 * getCurrentLevel(), 512, 512));
				if (TileMapLocal[i][j] == 'T') tiles.setTextureRect(IntRect(512 * 3, 1024 * getCurrentLevel(), 512, 512));
				if (TileMapLocal[i][j] == 'L') tiles.setTextureRect(IntRect(512 * 4, 1024 * getCurrentLevel(), 512, 1024));
				if (TileMapLocal[i][j] == 'P') tiles.setTextureRect(IntRect(512 * 5, 1024 * getCurrentLevel(), -512, 1024));
				if (TileMapLocal[i][j] == 'O') tiles.setTextureRect(IntRect(512 * 5, 1024 * getCurrentLevel(), 512, 512));
				if (TileMapLocal[i][j] == 'H') tiles.setTextureRect(IntRect(512 * 6, 1024 * getCurrentLevel(), 512, 512));
				if (TileMapLocal[i][j] == 'B') tiles.setTextureRect(IntRect(512 * 7, 1024 * getCurrentLevel(), 512, 512));
				if (TileMapLocal[i][j] == ' ' || TileMapLocal[i][j] == '0' || TileMapLocal[i][j] == '1' || TileMapLocal[i][j] == '2' || TileMapLocal[i][j] == '3' || TileMapLocal[i][j] == '4' || TileMapLocal[i][j] == '5' || TileMapLocal[i][j] == '6' || TileMapLocal[i][j] == '7' || TileMapLocal[i][j] == '8' || TileMapLocal[i][j] == '9' || TileMapLocal[i][j] == 'W' || TileMapLocal[i][j] == 'Q' || TileMapLocal[i][j] == 'A') continue;
				tiles.setScale(0.125, 0.125);
				tiles.setPosition(j * 64 - offsetX, i * 64 - offsetY);
				window.draw(tiles);
			}
		}
		//Передаємо всі елементи на вікно
		for (itHumanEnemys = humanEnemys.begin(); itHumanEnemys != humanEnemys.end(); itHumanEnemys++)
		{
			//(*itHumanEnemys).sprite.setScale(0.35, 0.35);
			//window.draw((*itHumanEnemys).sprite);
			if ((*itHumanEnemys).life) {
				(*itHumanEnemys).sprite.setScale(0.35, 0.35);
				window.draw((*itHumanEnemys).sprite);
				window.draw((*itHumanEnemys).hb.back);
				window.draw((*itHumanEnemys).hb.front);
			}
		}
		for (itAnimalEnemys = animalEnemys.begin(); itAnimalEnemys != animalEnemys.end(); itAnimalEnemys++)
		{
			//(*itAnimalEnemys).sprite.setScale(0.35, 0.35);
			//window.draw((*itAnimalEnemys).sprite);
			if ((*itAnimalEnemys).life) {
				(*itAnimalEnemys).sprite.setScale(0.35, 0.35);
				window.draw((*itAnimalEnemys).sprite);
				window.draw((*itAnimalEnemys).hb.back);
				window.draw((*itAnimalEnemys).hb.front);
			}
		}
		for (itBossEnemys = bossEnemys.begin(); itBossEnemys != bossEnemys.end(); itBossEnemys++)
		{
			//(*itBossEnemys).sprite.setScale(0.1245, 0.1245);
			//window.draw((*itBossEnemys).sprite);
			if ((*itBossEnemys).life) {
				(*itBossEnemys).sprite.setScale(0.1245, 0.1245);
				window.draw((*itBossEnemys).sprite);
				window.draw((*itBossEnemys).hb.back);
				window.draw((*itBossEnemys).hb.front);
				if((*itBossEnemys).countHealthBars > 1)window.draw((*itBossEnemys).hb2.back);
				if ((*itBossEnemys).countHealthBars > 1)window.draw((*itBossEnemys).hb2.front);
				if ((*itBossEnemys).countHealthBars > 2)window.draw((*itBossEnemys).hb3.back);
				if ((*itBossEnemys).countHealthBars > 2)window.draw((*itBossEnemys).hb3.front);
				if ((*itBossEnemys).countHealthBars > 3)window.draw((*itBossEnemys).hb4.back);
				if ((*itBossEnemys).countHealthBars > 3)window.draw((*itBossEnemys).hb4.front);
				if ((*itBossEnemys).countHealthBars > 4)window.draw((*itBossEnemys).hb5.back);
				if ((*itBossEnemys).countHealthBars > 4)window.draw((*itBossEnemys).hb5.front);
			}
		}
		window.draw(p.sprite);
		window.draw(p.attackSprite);
		window.draw(p.shieldSpr);
		window.draw(healthBar);
		window.draw(healthBar2);
		window.draw(nickName);
		window.draw(healthPotion);
		window.draw(lvlText);
		window.draw(scoreText);
		window.draw(potionsText);
		window.draw(skillBar);
		if (attackTime < p.attackTime) {
			skillAttack.setTexture(skillAttackDarkTexture);
		}
		else skillAttack.setTexture(skillAttackTexture);
		if (regenTime < 45 && p.st.lvl[0][2] == 1) {
			skillHeal.setTexture(skillHealDarkTexture);
		}
		else if (p.st.lvl[0][2] == 0) skillHeal.setTexture(skillHealDarkTexture);
		else skillHeal.setTexture(skillHealTexture);
		if (regenCDTime < 60 && p.st.lvl[0][3] == 1) {
			skillHealH.setTexture(skillHealHDarkTexture);
		}
		else if (p.st.lvl[0][3] == 0) skillHealH.setTexture(skillHealHDarkTexture);
		else skillHealH.setTexture(skillHealHTexture);
		if (shieldCDTime < 35 && p.st.lvl[2][0] == 1) {
			skillShield.setTexture(skillShieldDarkTexture);
		}
		else if(p.st.lvl[2][0] == 0) skillShield.setTexture(skillShieldDarkTexture);
		else skillShield.setTexture(skillShieldTexture);
		if (p.st.lvl[2][3] == 1) skillShieldHeal.setTexture(skillShieldHealTexture);
		else skillShieldHeal.setTexture(skillShieldHealDarkTexture);
		window.draw(skillAttack);
		window.draw(skillHeal);
		window.draw(skillHealH);
		window.draw(skillShield);
		window.draw(skillShieldHeal);
		if (attackTime < p.attackTime) {
			window.draw(attackCDText);
		}
		if (regenTime < 45 && p.st.lvl[0][2] == 1) {
			window.draw(regenCDText);
		}
		if (regenCDTime < 60 && p.st.lvl[0][3] == 1) {
			window.draw(healHCDText);
		}
		if (shieldCDTime < 35 && p.st.lvl[2][0] == 1) {
			window.draw(shieldCDText);
		}
		if (p.health < 1) {
			try {
				remove("saves/save1.txt");
			}
			catch (std::exception &ex) {
				std::cout << "Can`t delete file: saves/save1.txt is not exist" << std::endl;
			}
			Sleep(1000);
			Texture deathTexture;
			deathTexture.loadFromFile(get43()?"img/deathScreen-43.png":"img/deathScreen-169");
			Sprite death(deathTexture);
			death.setScale(getCoefX(window), getCoefY(window));
			Music deathMusic;
			music.stop();
			deathMusic.openFromFile("sound/deathPlayer.ogg");
			deathMusic.play();
			deathMusic.setVolume(musicLevel1);
			window.draw(death);
			window.display();
			Sleep(3000);
			window.setMouseCursorVisible(true);
			return 1;
		}
		//Виводимо всі елементи
		window.display();
		if (p.isWin) {
			window.setMouseCursorVisible(true);
			return 2;
		}
	}
	return 0;
}

void cutScrene(RenderWindow &window, int lvl) {
	window.clear();
	int slide = 1;
	if (lvl == -1) {
		while (slide < 11) 
		{
			if (Keyboard::isKeyPressed(Keyboard::Space)) 
			{
				slide++;
				Sleep(500);
			}
			String path = "img/CutScenes/Prolog/Slide" + std::to_string(slide) + ".png";
			Texture slideTexture;
			slideTexture.loadFromFile(path);
			Sprite slideSpr(slideTexture);
			slideSpr.setScale(getCoefX(window), getCoefY(window));
			window.draw(slideSpr);
			window.display();
		}
	}
	if (lvl == 1) {
		int maxSlide = 10;
		switch (getCurrentLevel()) {
		case 0:
			maxSlide = 10;
			break;
		case 1:
			maxSlide = 11;
			break;
		case 2:
			maxSlide = 6;
			break;
		case 3:
			maxSlide = -10;
			break;
		case 4:
			maxSlide = -10;
			break;
		case 5:
			maxSlide = -10;
			break;
		}
		while (slide < maxSlide)
		{
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				slide++;
				Sleep(500);
			}
			String path = "img/CutScenes/lvl" + std::to_string(getCurrentLevel()) + "/Slide" + std::to_string(slide) + ".png";
			Texture slideTexture;
			slideTexture.loadFromFile(path);
			Sprite slideSpr(slideTexture);
			slideSpr.setScale(getCoefX(window), getCoefY(window));
			window.draw(slideSpr);
			window.display();
		}
	}
}


//Метод для переходу на наступний рівень
void lvlPlus(RenderWindow & window, bool isLvlUpping) {
	cutScrene(window, 1);
	try {
		remove("saves/save1.txt");
	}
	catch (std::exception &ex) {
		std::cout << "Can`t delete file: saves/save1.txt is not exist" << std::endl;
	}
	saveStart(window);
	for (int i = 0; i < H; i++)
	{
		TileMapLocal[i] = getTileMap(getCurrentLevel(), i);
	}
	isLvlUpping = true;
	Texture loading;
	loading.loadFromFile(get43() ? "img/helloScreen-43.png" : "img/helloScreen-169.png");
	//Імітація загрузки
	Sprite loading1(loading);
	loading1.setScale(getCoefX(window), getCoefY(window));
	window.draw(loading1);
	window.display();
}