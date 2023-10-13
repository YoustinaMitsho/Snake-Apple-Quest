//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <bits/stdc++.h>
//
//using namespace sf;
//
//void pt1intro(RenderWindow& window);
//void pt2intro(RenderWindow& window);
//
//int intro = 0;
//
//struct MainCharacter {
//	Sprite herosprite;
//	int current_health = 5, maxhealth = 5;
//	bool restore = false, inc_jump = false, inc_velocity = false;
//	int doublevelocity = 1, doublejump = 1;
//	Vector2f velocity = { 0 * doublevelocity,0 * doublejump };
//};
//
//int main() {
//	RenderWindow window(VideoMode::getDesktopMode(), "intro!");
//	while (true) {
//		if (intro == 0) pt1intro(window);
//		if (intro == 1) pt2intro(window);
//	}
//}
//
//void pt1intro(RenderWindow& window) {
//	Event event;
//
//	window.setFramerateLimit(60);
//
//	//background intro
//	Texture backT;
//	backT.loadFromFile("background_snack.png");
//	Sprite background(backT);
//	background.setScale(1.2, 1.2);
//
//	// intro snake snake
//	Texture snaket;
//	snaket.loadFromFile("snake.png");
//	Sprite snake(snaket);
//	int i = 340 / 3;
//	int c = 1;
//	snake.setTextureRect(IntRect(0 * 138 + 20, 0, i * c, 138));
//
//	//intro apple
//	Texture applet;
//	applet.loadFromFile("apple.png");
//	Sprite apple(applet);
//	apple.setPosition(window.getSize().x / 2, window.getSize().y / 2);
//
//	Vector2f introvelocity = { .4,0 };
//
//	while (window.isOpen()) {
//		while (window.pollEvent(event)) {
//			if (event.type == Event::Closed) {
//				window.close();
//				break;
//			}
//			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
//				window.close();
//				break;
//			}
//			
//		}
//		if (Keyboard::isKeyPressed(Keyboard::Right)) {
//			introvelocity = { 5,0 };
//			snake.setTextureRect(IntRect(0 * 138 + 20, 0, i * c, 138));
//			snake.setScale(1, 1);
//		}
//		if (Keyboard::isKeyPressed(Keyboard::Left)) {
//			snake.setScale(-1, 1);
//			snake.setTextureRect(IntRect(0 * 138 + 20, 0, i * c, 138));
//			introvelocity = { -5,0 };
//		}
//		if (Keyboard::isKeyPressed(Keyboard::Down)) {
//			snake.setScale(1, 1);
//			snake.setTextureRect(IntRect(2 * 138 - 20, 0, i * 3, 138));
//			introvelocity = { 0,5 };
//		}
//		if (Keyboard::isKeyPressed(Keyboard::Up)) {
//			snake.setScale(1, -1);
//			snake.setTextureRect(IntRect(2 * 138 - 20, 0, i * 3, 138));
//			introvelocity = { 0,-5 };
//		}
//
//		snake.move(introvelocity);
//
//		window.clear();
//		window.draw(background);
//		window.draw(apple);
//		window.draw(snake);
//		if (snake.getGlobalBounds().intersects(apple.getGlobalBounds())) {
//			snake.setPosition(apple.getPosition());
//			intro = 1;
//		}
//		if (intro != 0) break;
//		window.display();
//	}
//
//}
//
//void pt2intro(RenderWindow& window) {
//	Event event;
//
//	window.setFramerateLimit(60);
//
//	// # main character
//	Texture maincharct;
//	maincharct.loadFromFile("snaky.png");
//
//	MainCharacter Snake;
//	Snake.herosprite.setTexture(maincharct);
//	Snake.herosprite.setPosition(50.f, 580.f);
//	Snake.herosprite.setOrigin(32.f / 2, 36.f / 2);
//	Snake.herosprite.setTextureRect(IntRect(0, 0, 32, 36));
//	Snake.herosprite.setScale(-5.f, 5.f);
//	//Logics
//	int Animator = 0;
//	int AnimatorDelay = 0;
//	Vector2f Snakevelocity = Snake.velocity;
//
//	// game sounds:
//	Music lop;
//	lop.openFromFile("description.wav");
//	lop.play();
//
//	// desert
//	Texture desertT;
//	desertT.loadFromFile("desert.png");
//	Sprite desert(desertT);
//	desert.setScale(1.75, 1.65);
//
//	//thinking buuble
//	Texture bubbleT[7];
//	bubbleT[0].loadFromFile("./thinking bubble/castle bubble.png");
//	bubbleT[1].loadFromFile("./thinking bubble/garded bubble.png");
//	bubbleT[2].loadFromFile("./thinking bubble/enemy buuble.png");
//	bubbleT[3].loadFromFile("./thinking bubble/help bubble.png");
//	bubbleT[4].loadFromFile("./thinking bubble/chest bubble.png");
//	bubbleT[5].loadFromFile("./thinking bubble/chest opened bubble.png");
//	bubbleT[6].loadFromFile("./thinking bubble/queen bubble.png");
//
//	Sprite bubble[7];
//	for (size_t i = 0; i < 7; i++)
//	{
//		bubble[i].setTexture(bubbleT[i]);
//		bubble[i].setPosition(-555, 10);
//	}
//
//	//castle
//	Texture CastleT;
//	CastleT.loadFromFile("intro background.png");
//	Sprite castle(CastleT);
//	castle.setScale(2, 2.3);
//
//	// blanck
//	Texture blanckT;
//	blanckT.loadFromFile("black layer.png");
//	Sprite blanck(blanckT);
//	// blank texture
//	Font font;
//	font.loadFromFile("RetroGrade.otf");
//
//	Text text;
//	text.setFont(font);
//	text.setString("let the journey begin!");
//	text.setPosition(400, 300);
//	text.setCharacterSize(50);
//
//	Text txt;
//	txt.setFont(font);
//	txt.setString("Snake: Apple Quest");
//	txt.setPosition(430, 400);
//	txt.setCharacterSize(50);
//
//	int bl = 0;
//	int keypause = 0;
//
//	while (window.isOpen()) {
//		keypause++;
//		while (window.pollEvent(event)) {
//			if (event.type == Event::Closed) {
//				window.close();
//				break;
//			}
//			if (Keyboard::isKeyPressed(Keyboard::Return) && keypause >= 60) {
//				keypause = 0;
//				bl = 1;
//			}
//		}
//		//walk animation
//		if (!Keyboard::isKeyPressed(Keyboard::Enter)) // # MOVING RIGHT # 
//		{
//			if (AnimatorDelay < 12)
//			{
//				AnimatorDelay++;
//			}
//			if (AnimatorDelay >= 12) {
//				AnimatorDelay = 0;
//
//				Animator %= 10;
//				Snake.herosprite.setTextureRect(IntRect(32 * Animator, 64, 32, 36));
//				Animator++;
//			}
//			Snake.herosprite.setScale(-8, 8);
//			Snakevelocity.x = 0.2;
//		}
//		Snake.herosprite.move(Snakevelocity);
//
//		window.clear();
//		window.draw(desert);
//		window.draw(Snake.herosprite);
//		if (Snake.herosprite.getPosition().x >= 160) {
//			window.draw(bubble[0]);
//			bubble[0].move(Snakevelocity.x, 0);
//		}
//		if (Snake.herosprite.getPosition().x >= 210) {
//			bubble[1].setPosition(bubble[0].getPosition());
//			window.draw(bubble[1]);
//			bubble[1].move(Snakevelocity.x, 0);
//		}
//		if (Snake.herosprite.getPosition().x >= 320) {
//			bubble[2].setPosition(bubble[1].getPosition());
//			window.draw(bubble[2]);
//			bubble[2].move(Snakevelocity.x, 0);
//		}
//		if (Snake.herosprite.getPosition().x >= 375) {
//			bubble[3].setPosition(bubble[2].getPosition());
//			window.draw(bubble[3]);
//			bubble[3].move(Snakevelocity.x, 0);
//		}
//		if (Snake.herosprite.getPosition().x >= 500) {
//			bubble[4].setPosition(bubble[3].getPosition());
//			window.draw(bubble[4]);
//			bubble[4].move(Snakevelocity.x, 0);
//		}
//		if (Snake.herosprite.getPosition().x >= 565) {
//			bubble[5].setPosition(bubble[4].getPosition());
//			window.draw(bubble[5]);
//			bubble[5].move(Snakevelocity.x, 0);
//		}
//		if (Snake.herosprite.getPosition().x >= 670) {
//			bubble[6].setPosition(bubble[5].getPosition());
//			window.draw(bubble[6]);
//			bubble[6].move(Snakevelocity.x, 0);
//		}
//		if (Snake.herosprite.getPosition().x >= 785) {
//			window.draw(castle);
//		}
//		if (bl == 1) {
//			window.clear();
//			lop.stop();
//			window.draw(blanck);
//			window.draw(text);
//			window.draw(txt);
//
//			if (Keyboard::isKeyPressed(Keyboard::Return) && keypause >= 60) {
//				bl = 2;
//			}
//		}
//		if (intro != 1) break;
//		//if (bl == 2) pagenum = 1; break;
//		window.display();
//	}
//}
