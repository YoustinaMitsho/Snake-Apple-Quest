//#include<SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <time.h>
//#include <cstdlib>
//#include<vector>
//
//using namespace sf;
//
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
//int main() {
//
//	srand(time(NULL));
//
//	RenderWindow window(VideoMode::getDesktopMode(), "Big Bad Apple");
//	Event evento;
//	window.setFramerateLimit(60);
//
//	//#Our Cute Lil snake
//	Texture maincharct;
//	maincharct.loadFromFile("snaky.png");
//
//	Sprite Snake;
//	Snake.setTexture(maincharct);
//	Snake.setOrigin(32.f / 2, 36.f / 2);
//	Snake.setTextureRect(IntRect(0, 0, 32, 36));
//	Snake.setScale(5.f, 5.f);
//
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
//	BadApple.setOrigin(128.125 / 2, 65);
//	BadApple.setPosition(350, window.getSize().y - 350);
//	BadApple.setScale(2.5, 2.5);
//	// boss logics
//
//	int BigBossHealth = 6;
//	BadApple.setTextureRect(IntRect(128.125 * BigBossHealth, 0, 128.25, 130));
//
//
//
//	// TESTING LAND 
//	RectangleShape land;
//	land.setFillColor(Color::Red);
//	land.setSize(Vector2f(200000.f, 50.f));
//	land.setOrigin(0, 25);
//	land.setPosition(-2500.f, window.getSize().y - 100);
//
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
//	float SeedX = 6;
//	float SeedY = 4;
//
//
//
//	bool alive = true;
//	bool attack = false;
//	bool celebrate = false;
//
//
//	//gravity
//	double  gravityP = 0.6;
//	int gravityDelay = 0;
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
//
//			}
//
//			if (Keyboard::isKeyPressed(Keyboard::C) && !attack) // # ATTACKING ANIMATION #
//			{
//
//				Animator = 0;
//				celebrate = true;
//
//
//			}
//
//		}
//
//
//
//		//update
//		for (size_t i = 0; i < 10; i++)
//		{
//			if (seeds[i].S.getGlobalBounds().intersects(land.getGlobalBounds())) {
//
//				seeds[i].S.setPosition(BadApple.getPosition());
//				seeds[i].seedSpeed = { SeedX, -SeedY * (1 + rand() % (10)) };
//
//
//			}
//			else {
//				if (gravityDelay < 1)
//					gravityDelay++;
//				if (gravityDelay >= 1)
//				{
//					gravityDelay = 0;
//					seeds[i].seedSpeed.y += gravityP;
//				}
//
//			}
//
//			seeds[i].S.move(seeds[i].seedSpeed);
//		}
//
//		if (alive) {
//			// testing idle animation
//			if (Snakevelocity.x == 0 && Snakevelocity.y == 0)
//			{
//				if (AnimatorDelay < 10)
//					AnimatorDelay++;
//				if (AnimatorDelay >= 10) {
//					AnimatorDelay = 0;
//					Animator++;
//					Animator %= 10;
//					if (!attack && !celebrate)
//						Snake.setTextureRect(IntRect(32 * Animator, 0, 32, 36));
//				}
//
//			}
//			//testing walk animation
//			if (Keyboard::isKeyPressed(Keyboard::Right) && !celebrate) // # MOVING RIGHT # 
//			{
//				if (AnimatorDelay < 5)
//				{
//					AnimatorDelay++;
//				}
//				if (AnimatorDelay >= 5) {
//					AnimatorDelay = 0;
//
//					Animator %= 10;
//					if (!attack && !celebrate)
//						Snake.setTextureRect(IntRect(32 * Animator, 64, 32, 36));
//					Animator++;
//				}
//				Snake.setScale(-5, 5);
//				Snakevelocity.x = 5.f;
//
//
//			}
//			else if (Keyboard::isKeyPressed(Keyboard::Left) && !celebrate) // # MOVING LEFT # 
//			{
//
//				if (AnimatorDelay < 5)
//				{
//					AnimatorDelay++;
//				}
//				if (AnimatorDelay >= 5) {
//					AnimatorDelay = 0;
//
//					Animator %= 10;
//					if (!attack && !celebrate)
//						Snake.setTextureRect(IntRect(32 * Animator, 64, 32, 36));
//					Animator++;
//				}
//				Snake.setScale(5, 5);
//				Snakevelocity.x = -5.f;
//
//
//			}
//			else
//				Snakevelocity.x = 0.f;
//
//			// attack animation
//			if (attack && !celebrate)
//			{
//				if (AnimatorDelay < 5)
//				{
//					AnimatorDelay++;
//				}
//				if (AnimatorDelay >= 5) {
//					AnimatorDelay = 0;
//
//					Animator %= 10;
//					Snake.setTextureRect(IntRect(32 * Animator, 96, 32, 36));
//					Animator++;
//
//				}
//			}
//
//			// edeha e7tfal 
//			if (!attack && celebrate)
//			{
//				if (AnimatorDelay < 10)
//				{
//					AnimatorDelay++;
//				}
//				if (AnimatorDelay >= 10) {
//					AnimatorDelay = 0;
//
//					Animator %= 10;
//					Snake.setTextureRect(IntRect(32 * Animator, 32, 32, 36));
//					Animator++;
//
//				}
//			}
//
//
//			// resuming to idle
//			if (Animator == 10) {
//				attack = false;
//				celebrate = false;
//			}
//
//			//#SNAKE JUMPING , GRAVITY AND GROUNDING
//			if (Snake.getGlobalBounds().intersects(land.getGlobalBounds()))
//			{
//				Snakevelocity.y = 0;
//				if (Keyboard::isKeyPressed(Keyboard::Up) && !celebrate)
//				{
//					if (!attack && !celebrate)
//						Snake.setTextureRect(IntRect(IntRect(32 * 2, 128, 32, 36)));
//					Snakevelocity.y = -20.f;
//				}
//			}
//			else
//				Snakevelocity.y += gravity;
//
//		}
//		if (alive == false && Animator <= 9) {
//			if (AnimatorDelay < 5)
//			{
//				AnimatorDelay++;
//			}
//			if (AnimatorDelay >= 5) {
//				AnimatorDelay = 0;
//
//
//				Snake.setTextureRect(IntRect(32 * Animator, 128, 32, 36));
//				Animator++;
//
//			}
//		}
//
//
//
//		// #THE GROW SO FAST...NOW HE IS MOVING#
//		if (alive && !celebrate)
//			Snake.move(Snakevelocity);
//
//
//
//		//BadApple.move(2, 0);
//
//		if (Snake.getPosition().x < BadApple.getPosition().x)
//			SeedX = -6;
//		else if (Snake.getPosition().x > BadApple.getPosition().x)
//			SeedX = 6;
//
//		// test damage
//		if (Snake.getGlobalBounds().intersects(BadApple.getGlobalBounds()) && attack && Animator == 5)
//		{
//			BigBossHealth--;
//			BadApple.setTextureRect(IntRect(128.125 * BigBossHealth, 0, 128.25, 130));
//			if (Snake.getPosition().x > BadApple.getPosition().x)
//				Snake.move(500, 0);
//			else if (Snake.getPosition().x < BadApple.getPosition().x)
//				Snake.move(-300, 0);
//		}
//		if (BadApple.getPosition().x - 120 <= 0) dir = 1;
//		else if (BadApple.getPosition().x + 120 >= window.getSize().x) dir = 0;
//
//		if (dir == 0) BadApple.move(-2.f, 0.f);
//		else BadApple.move(2.f, 0.f);
//
//
//
//
//		// draw
//		window.clear(Color::White);
//		window.draw(BadApple);
//		window.draw(Snake);
//		window.draw(land);
//		for (size_t i = 0; i < 10; i++)
//		{
//			window.draw(seeds[i].S);
//		}
//
//		window.display();
//	}
//}