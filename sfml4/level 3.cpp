//#include<SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <time.h>
//#include <cstdlib>
//#include<vector>
//#include<iostream>
//using namespace sf;
//using namespace std;
//
//struct MainCharacter {
//	Sprite herosprite;
//	int current_health = 0,
//		const maxhealth = 0;
//	bool restore = false, inc_jump = false, inc_velocity = false;
//	int doublevelocity = 1, doublejump = 1;
//	Vector2f velocity = { 0 * doublevelocity,0 * doublejump };
//}Snake;
//
//struct Seed {
//	CircleShape S;
//	Vector2f seedSpeed = { 0,0 }; // seed velocity
//
//	void setSeed(float radius, Color color)
//	{
//		this->S.setRadius(radius);
//		this->S.setFillColor(color);
//	}
//};
//
//
//void level3_game(RenderWindow& window) {
//
//	window.setFramerateLimit(60);
//	Event evento;
//
//
//	vector <int> v(11);
//
//	//#Our Cute Lil snake
//	Texture maincharct;
//	maincharct.loadFromFile("snaky.png");
//
//	MainCharacter Snake;
//	Snake.herosprite.setTexture(maincharct);
//	Snake.herosprite.setOrigin(32.f / 2, 36.f / 2);
//	Snake.herosprite.setTextureRect(IntRect(0, 0, 32, 36));
//	Snake.herosprite.setScale(-5.f, 5.f);
//
//	// SNAKE LOGICS
//	int Animator = 0;
//	int AnimatorDelay = 0;
//	Vector2f Snakevelocity = { 0.f,0.f };
//
//	//gravity
//	float  gravity = 1.f;
//
//
//	// boss like circle
//	Texture boss; boss.loadFromFile("final_boss.png");
//	Sprite BadApple; BadApple.setTexture(boss);
//
//	BadApple.setOrigin(320 / 2, 320 / 2);
//	BadApple.setPosition(1245, window.getSize().y - 300);
//	BadApple.setScale(1, 1);
//	// boss logics
//
//	int BigBossHealth = 6;
//	BadApple.setTextureRect(IntRect(320 * BigBossHealth, 0, 320, 320));
//
//	// boss death:
//	Texture deathT;
//	deathT.loadFromFile("AppleDead.png");
//	Sprite death(deathT);
//	death.setScale(3, 3);
//	death.setOrigin(71, 113 / 2);
//
//	// TESTING LAND 
//	RectangleShape land;
//	land.setFillColor(Color::Transparent);
//	land.setSize(Vector2f(200000.f, 50.f));
//	land.setOrigin(0, 25);
//	land.setPosition(-2500.f, window.getSize().y - 100);
//
//	// background:
//	Texture bkgT;
//	bkgT.loadFromFile("l3_map.png");
//	Sprite bkg(bkgT);
//	bkg.setScale(0.95, 1.05);
//
//	// healthbar:
//	Texture healthbarT;
//	healthbarT.loadFromFile("health bar.png");
//	Sprite bar(healthbarT);
//	bar.setScale(0.2, 0.2);
//	bar.setPosition(0, -20);
//
//	//Boss Seeds
//	std::vector<Seed>seeds;
//
//	for (size_t i = 0; i < 10; i++)
//	{
//		Seed seed;
//		seed.S.setPosition(BadApple.getPosition());
//		seed.setSeed(7.f, Color::Black);
//		seed.S.setOrigin(3.5, 3.5);
//		seeds.push_back(Seed(seed));
//	}
//
//	float SeedX = 100;
//	float SeedY = 2.8;
//	float speedx = 20;
//	float speedy = -30;
//
//
//
//	bool alive = true;
//	bool attack = false;
//	bool celebrate = false;
//	bool bossdeath = false;
//
//
//	//gravity
//	double  gravityP = 0.6;
//	float gravityDelay = 0;
//
//	int dir = 0;
//
//	while (window.isOpen()) {
//
//		while (window.pollEvent(evento)) {
//			if (evento.type == Event::Closed)
//				window.close();
//
//			if (Keyboard::isKeyPressed(Keyboard::Space) && !celebrate) // # ATTACKING ANIMATION #
//			{
//
//				Animator = 0;
//				attack = true;
//
//			}
//
//		}
//
//		if (Snake.current_health < 6)
//			bar.setTextureRect(IntRect((Snake.current_health * float(1639 / 6)), 0, float(1639 / 6), 400));
//
//		//update
//		if (alive) {
//			for (int i = 0; i <= 9; i++)
//			{
//
//				bool diff = 1;
//				int x = rand() % 10 + 1;
//				if (seeds[i].S.getPosition() == BadApple.getPosition())
//				{
//					for (int j = 0; j <= i; j++)
//					{
//						if (x == v[j])
//						{
//							diff = 0;
//						}
//
//
//					}
//					if (!diff)
//						i--;
//					else
//					{
//						v[i] = x;
//					}
//				}
//
//			}
//
//			for (size_t i = 0; i < 10; i++)
//			{
//				if (seeds[i].S.getGlobalBounds().intersects(land.getGlobalBounds())) {
//
//					seeds[i].S.setPosition(BadApple.getPosition());
//					seeds[i].seedSpeed = { SeedX, -SeedY * v[i] };
//
//
//				}
//				else {
//					if (gravityDelay < 1)
//						gravityDelay++;
//					if (gravityDelay >= 1)
//					{
//						gravityDelay = 0;
//						seeds[i].seedSpeed.y += gravityP;
//					}
//
//				}
//
//				seeds[i].S.move(seeds[i].seedSpeed);
//			}
//			
//			if (alive && !bossdeath) {
//				// testing idle animation
//				if (Snakevelocity.x == 0 && Snakevelocity.y == 0)
//				{
//					if (AnimatorDelay < 10)
//						AnimatorDelay++;
//					if (AnimatorDelay >= 10) {
//						AnimatorDelay = 0;
//						Animator++;
//						Animator %= 10;
//						if (!attack && !celebrate)
//							Snake.herosprite.setTextureRect(IntRect(32 * Animator, 0, 32, 36));
//					}
//
//				}
//				//testing walk animation
//				if (Keyboard::isKeyPressed(Keyboard::Right) && !celebrate) // # MOVING RIGHT # 
//				{
//					if (AnimatorDelay < 5)
//					{
//						AnimatorDelay++;
//					}
//					if (AnimatorDelay >= 5) {
//						AnimatorDelay = 0;
//
//						Animator %= 10;
//						if (!attack && !celebrate)
//							Snake.herosprite.setTextureRect(IntRect(32 * Animator, 64, 32, 36));
//						Animator++;
//					}
//					Snake.herosprite.setScale(-5, 5);
//					Snakevelocity.x = 5.f;
//
//
//				}
//				else if (Keyboard::isKeyPressed(Keyboard::Left) && !celebrate) // # MOVING LEFT # 
//				{
//
//					if (AnimatorDelay < 5)
//					{
//						AnimatorDelay++;
//					}
//					if (AnimatorDelay >= 5) {
//						AnimatorDelay = 0;
//
//						Animator %= 10;
//						if (!attack && !celebrate)
//							Snake.herosprite.setTextureRect(IntRect(32 * Animator, 64, 32, 36));
//						Animator++;
//					}
//					Snake.herosprite.setScale(5, 5);
//					Snakevelocity.x = -5.f;
//				}
//				else
//					Snakevelocity.x = 0.f;
//
//				// attack animation
//				if (attack && !celebrate)
//				{
//					if (AnimatorDelay < 5)
//					{
//						AnimatorDelay++;
//					}
//					if (AnimatorDelay >= 5) {
//						AnimatorDelay = 0;
//
//						Animator %= 10;
//						Snake.herosprite.setTextureRect(IntRect(32 * Animator, 96, 32, 36));
//						Animator++;
//
//					}
//				}
//
//				// edeha e7tfal 
//				if (!attack && celebrate)
//				{
//					if (AnimatorDelay < 10)
//					{
//						AnimatorDelay++;
//					}
//					if (AnimatorDelay >= 10) {
//						AnimatorDelay = 0;
//
//						Animator %= 10;
//						Snake.herosprite.setTextureRect(IntRect(32 * Animator, 32, 32, 36));
//						Animator++;
//
//					}
//				}
//
//
//				// resuming to idle
//				if (Animator == 10) {
//					attack = false;
//					celebrate = false;
//				}
//
//				//#SNAKE JUMPING , GRAVITY AND GROUNDING
//				if (Snake.herosprite.getGlobalBounds().intersects(land.getGlobalBounds()))
//				{
//					Snakevelocity.y = 0;
//					if (Keyboard::isKeyPressed(Keyboard::Up) && !celebrate)
//					{
//						if (!attack && !celebrate)
//							Snake.herosprite.setTextureRect(IntRect(IntRect(32 * 2, 128, 32, 36)));
//						Snakevelocity.y = -20.f;
//					}
//				}
//				else
//					Snakevelocity.y += gravity;
//
//			}
//			if (alive == false && Animator <= 9) {
//				if (AnimatorDelay < 5)
//				{
//					AnimatorDelay++;
//				}
//				if (AnimatorDelay >= 5) {
//					AnimatorDelay = 0;
//
//
//					Snake.herosprite.setTextureRect(IntRect(32 * Animator, 128, 32, 36));
//					Animator++;
//
//				}
//			}
//
//			// #THE GROW SO FAST...NOW HE IS MOVING#
//			if (alive && !celebrate)
//				Snake.herosprite.move(Snakevelocity);
//
//			if (Snake.herosprite.getPosition().x < BadApple.getPosition().x)
//				SeedX = -15;
//			else if (Snake.herosprite.getPosition().x > BadApple.getPosition().x)
//				SeedX = 15;
//
//			//test damage
//
//			// player damage
//			for (int i = 0; i < 10; i++) {
//				if (seeds[i].S.getGlobalBounds().intersects(Snake.herosprite.getGlobalBounds())) {
//
//					seeds[i].S.setPosition(BadApple.getPosition());
//					Snake.current_health++;
//
//				}
//			}
//
//
//			//boss damage
//
//			if (Snake.herosprite.getGlobalBounds().intersects(BadApple.getGlobalBounds()) && attack && Animator == 5)
//			{
//				attack = false;
//				Animator = 0;
//				celebrate = true;
//				BigBossHealth--;
//				speedx = 16;
//				speedy = -20;
//				if (BigBossHealth % 2 == 0)
//					BadApple.move(speedx, speedy);
//				else
//					BadApple.move(-speedx, speedy);
//
//
//				BadApple.setTextureRect(IntRect(320 * BigBossHealth, 0, 320, 320));
//				
//			}
//			if (BigBossHealth == 0) {
//				bossdeath = true;
//			}
//			
//			if (BigBossHealth % 2 == 0 && BigBossHealth != 6)
//			{
//				BadApple.move(speedx, speedy);
//			}
//			
//			if (BigBossHealth % 2 == 1)
//			{
//				BadApple.move(-speedx, speedy);
//			}
//			
//			if (!BadApple.getGlobalBounds().intersects(land.getGlobalBounds()))
//			{
//				speedy += gravityP;
//			}
//
//			if (BadApple.getGlobalBounds().intersects(land.getGlobalBounds()))
//			{
//				speedx = 0;
//				speedy = 0;
//
//			}
//		}
//		// draw
//		window.clear(Color::White);
//		window.draw(bkg);
//		window.draw(Snake.herosprite);
//		window.draw(land);
//		if (!bossdeath) {
//			for (size_t i = 0; i < 10; i++)
//			{
//				window.draw(seeds[i].S);
//			}
//			window.draw(BadApple);
//		}
//		if (bossdeath) {
//			death.setPosition(BadApple.getPosition());
//			window.draw(death);
//		}
//		window.draw(bar);
//		window.display();
//	}
//}