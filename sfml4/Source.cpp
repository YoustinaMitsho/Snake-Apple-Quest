#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>s
#include "menu.h"
#include "pause.h"

using namespace sf;
/*******************************
*   page num    *     refr     *
* ******************************
*       0       *    intro     *
*       1       *    menu      *
*       2       *   new game   *
*       3       *  load game   *
*       4       * how to play  *
*       5       * main game l1 *
*       6       * main game l2 *
*       7       * main game l3 *
*       8       *    outro     *
*******************************/

// structs:

struct MainCharacter {
	Sprite herosprite;
	int current_health = 0, 
	const maxhealth = 0;
	bool restore = false, inc_jump = false, inc_velocity = false;
	int doublevelocity = 1, doublejump = 1;
	Vector2f velocity = { 0 /* doublevelocity*/, 0 /* doublejump*/ };
}Snake;

struct Bullets {
	CircleShape b;
	Vector2f currvelo = { 0,0 };
	float maxvelo = 15.f;  
	void setinitials(float radius, Color color, Vector2f GunCenter, Vector2f AAN) {
		this->currvelo = maxvelo * AAN;
		this->b.setRadius(radius);
		this->b.setFillColor(color);
		this->b.setPosition(GunCenter.x, GunCenter.y - 12.5);
	}
};

struct shooter
{
	Sprite shooters;
	Sprite gun;
	RectangleShape Range;// range of shooting 
	std::vector<Bullets> projectiles; // independent bullets vector for every shooter
	bool is_gunner_dead = false;

	void settingProps(Texture& shape, Texture& gun, Vector2f position) {
		//setting shooters
		this->shooters.setTexture(shape);
		this->shooters.setOrigin(192 / 2, 199 / 2);
		this->shooters.setScale(0.4, 0.4);
		this->shooters.setPosition(position);
		//setting gun
		this->gun.setTexture(gun);
		this->gun.setOrigin(102 / 2, 77 / 2);
		this->gun.setScale(0.3, 0.3);
		this->gun.setPosition(shooters.getPosition().x - 35, shooters.getPosition().y + 5);

		//setting Range
		Range.setSize((Vector2f(500, 500)));
		Range.setFillColor(Color::Transparent);
		Range.setOrigin(Range.getSize() / 2.f);
		Range.setPosition(shooters.getPosition());
	}
	void pusher(Bullets bullet) {
		this->projectiles.push_back(Bullets(bullet)); // pushing back bullets
	}
};

struct hitbox // hit box minions
{
	RectangleShape rec;
	bool dead = false;

};

struct applend { // collectable apple
	Sprite apple2;
	Texture appleT;
	bool collect = false;

};

struct apple1 // minion number 1 
{
	Vector2f v = { 5,0 };
	Sprite apple;
	hitbox HB;
	int anim = 0;
	Texture appletext;
	RectangleShape shapes;
};

struct Seed {// boss projectiles
	CircleShape S;
	Vector2f seedSpeed = { 0,0 }; // seed velocity

	void setSeed(float radius, Color color)
	{
		this->S.setRadius(radius);
		this->S.setFillColor(color);
	}
};


// functions:
void main_menu(RenderWindow& window);
void PName(RenderWindow& window, std::string& name);
void main_game(RenderWindow& window); 
void savename(std::string name, int score);
void scoreboard(RenderWindow& window);
bool collide_with_enemy(RectangleShape HB, RectangleShape object);// collision for main character 
void platform_collisions(Sprite tile[50], MainCharacter& snake, Vector2f& snakevelociyt);
void powerupfun(int is_coll);// power up and player stat modification
void pt1intro(RenderWindow& window);
void pt2intro(RenderWindow& window);
void levl2_game(RenderWindow& window);
void level3_game(RenderWindow& window);
void outro(RenderWindow& window);

// global variabls:
int pagenum = 0;
int intro = 0;

RectangleShape HitBox; // main character hitbox
float  gravity = 1.f;
int motion = 10.f;
int jumphight = 15.f;
int leveltimer = 0;
int end_of_level_health = 0;
int score = 0;
bool wait = false;// pause menu 
std::string name;

// constants:
const double PI = 3.14159265359;
int const consttimer = 1500; // ( level 2 timer )

int main() {

	// window
	RenderWindow window(VideoMode::getDesktopMode(), "Snake: Apple Quest");
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);

	//sound:
	//start:
	SoundBuffer Buffer5; Buffer5.loadFromFile("l1 start.wav");
	Sound start; start.setBuffer(Buffer5); start.setVolume(100);
	
	while (true) {
		// intro:
		if (pagenum == 0 && intro == 0) { pt1intro(window); }
		if (pagenum == 0 && intro == 1) { pt2intro(window); }
		// main menu:
		if (pagenum == 1) main_menu(window);

		// main game l1:
		if (pagenum == 5) {
			start.play();
			main_game(window);
		}
		// main game l2:
		if (pagenum == 6) {
			levl2_game(window);
		}
		// main game l3:
		if (pagenum == 7) {
			level3_game(window);
		}
		// outro:
		if (pagenum == 8) {
			outro(window);
		}

	}
		
}

void main_menu(RenderWindow& window) {
	Menu menu(1080, 720);
	// main menu:
		// background main menu
	Texture bkgT;
	bkgT.loadFromFile("castle_auto_x3 (1).png");
	Sprite bg(bkgT);
	bg.setScale(1.2, 1.1);

	// how to play:
	// background
	Texture bk;
	bk.loadFromFile("howtoplay.png");
	Sprite howtoplay(bk);
	howtoplay.setScale(1.4, 0.98);

	// sounds
	Music lop;
	lop.openFromFile("intro.wav");
	if (pagenum == 1) lop.play();
	lop.setLoop(true);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				break;
			}
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Up) {
					menu.MoveUp();
				}
				if (event.key.code == Keyboard::Down) {
					menu.MoveDown();
				}
				if (event.key.code == Keyboard::Return) {
					// 0 -> new game  1 -> score board  2-> how to play  3-> exit
					if (menu.pressed() == 0) {
						pagenum = 2;
						lop.stop();
					}
					if (menu.pressed() == 1) pagenum = 3;
					if (menu.pressed() == 2) pagenum = 4;
					if (menu.pressed() == 3) {
						window.close();
						break;
					}
				}
			}
			window.clear();
			window.draw(bg);
			menu.draw(window);
			if (pagenum != 1) {
				break;
			}
			window.display();
		}
		// new game:
		if (pagenum == 2) {
			PName(window, name);
		}
		// score board:
		if (pagenum == 3) {
			scoreboard(window);
		}

		// how to play:
		if (pagenum == 4) {
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				pagenum = 1;
			}
			window.clear();
			window.draw(howtoplay);
			window.display();

		}
		if (pagenum != 1 && pagenum != 2 && pagenum != 3 && pagenum != 4) break;
	}
}

void pt1intro(RenderWindow& window) {
	Event event;

	window.setFramerateLimit(60);

	//background intro
	Texture backT;
	backT.loadFromFile("background_snack.png");
	Sprite background(backT);
	background.setScale(1.2, 1.2);

	// intro snake snake
	Texture snaket;
	snaket.loadFromFile("snake.png");
	Sprite snake(snaket);
	int i = 340 / 3;
	int c = 1;
	snake.setTextureRect(IntRect(0 * 138 + 20, 0, i * c, 138));

	//intro apple
	Texture applet;
	applet.loadFromFile("apple.png");
	Sprite apple(applet);
	apple.setPosition(window.getSize().x / 2, window.getSize().y / 2);

	Vector2f introvelocity = { .4,0 };

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				break;
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
				window.close();
				break;
			}

		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			introvelocity = { 5,0 };
			snake.setTextureRect(IntRect(0 * 138 + 20, 0, i * c, 138));
			snake.setScale(1, 1);
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			snake.setScale(-1, 1);
			snake.setTextureRect(IntRect(0 * 138 + 20, 0, i * c, 138));
			introvelocity = { -5,0 };
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			snake.setScale(1, 1);
			snake.setTextureRect(IntRect(2 * 138 - 20, 0, i * 3, 138));
			introvelocity = { 0,5 };
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			snake.setScale(1, -1);
			snake.setTextureRect(IntRect(2 * 138 - 20, 0, i * 3, 138));
			introvelocity = { 0,-5 };
		}

		snake.move(introvelocity);

		window.clear();
		window.draw(background);
		window.draw(apple);
		window.draw(snake);
		if (snake.getGlobalBounds().intersects(apple.getGlobalBounds())) {
			snake.setPosition(apple.getPosition());
			intro = 1;
		}
		if (intro != 0) break;
		window.display();
	}

}

void pt2intro(RenderWindow& window) {
	Event event;

	window.setFramerateLimit(60);

	// # main character
	Texture maincharct;
	maincharct.loadFromFile("snaky.png");

	MainCharacter Snake;
	Snake.herosprite.setTexture(maincharct);
	Snake.herosprite.setPosition(50.f, 580.f);
	Snake.herosprite.setOrigin(32.f / 2, 36.f / 2);
	Snake.herosprite.setTextureRect(IntRect(0, 0, 32, 36));
	Snake.herosprite.setScale(-5.f, 5.f);
	//Logics
	int Animator = 0;
	int AnimatorDelay = 0;
	Vector2f Snakevelocity = Snake.velocity;

	// game sounds:
	Music lop;
	lop.openFromFile("description.wav");
	lop.play();

	// desert
	Texture desertT;
	desertT.loadFromFile("forest.png");
	Sprite desert(desertT);
	desert.setScale(1.25, 0.95);

	//thinking buuble
	Texture bubbleT[7];
	bubbleT[0].loadFromFile("./thinking bubble/castle bubble.png");
	bubbleT[1].loadFromFile("./thinking bubble/garded bubble.png");
	bubbleT[2].loadFromFile("./thinking bubble/enemy buuble.png");
	bubbleT[3].loadFromFile("./thinking bubble/help bubble.png");
	bubbleT[4].loadFromFile("./thinking bubble/chest bubble.png");
	bubbleT[5].loadFromFile("./thinking bubble/chest opened bubble.png");
	bubbleT[6].loadFromFile("./thinking bubble/queen bubble.png");

	Sprite bubble[7];
	for (size_t i = 0; i < 7; i++)
	{
		bubble[i].setTexture(bubbleT[i]);
		bubble[i].setPosition(-555, 10);
	}

	//castle
	Texture CastleT;
	CastleT.loadFromFile("intro background.png");
	Sprite castle(CastleT);
	castle.setScale(2, 2.3);

	// blanck
	Texture blanckT;
	blanckT.loadFromFile("black layer.png");
	Sprite blanck(blanckT);
	// blank texture
	Font font;
	font.loadFromFile("RetroGrade.otf");

	Text text;
	text.setFont(font);
	text.setString("let the journey begin!");
	text.setPosition(400, 300);
	text.setCharacterSize(50);

	Text txt;
	txt.setFont(font);
	txt.setString("Snake: Apple Quest");
	txt.setPosition(430, 400);
	txt.setCharacterSize(50);

	int bl = 0;
	int keypause = 0;

	while (window.isOpen()) {
		keypause++;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				break;
			}
			if (Keyboard::isKeyPressed(Keyboard::Return) && keypause >= 60) {
				keypause = 0;
				bl = 1;
			}
		}
		//walk animation
		if (!Keyboard::isKeyPressed(Keyboard::Enter)) // # MOVING RIGHT # 
		{
			if (AnimatorDelay < 12)
			{
				AnimatorDelay++;
			}
			if (AnimatorDelay >= 12) {
				AnimatorDelay = 0;

				Animator %= 10;
				Snake.herosprite.setTextureRect(IntRect(32 * Animator, 64, 32, 36));
				Animator++;
			}
			Snake.herosprite.setScale(-8, 8);
			Snakevelocity.x = 0.2;
		}
		Snake.herosprite.move(Snakevelocity);

		window.clear();
		window.draw(desert);
		window.draw(Snake.herosprite);
		if (Snake.herosprite.getPosition().x >= 160) {
			window.draw(bubble[0]);
			bubble[0].move(Snakevelocity.x, 0);
		}
		if (Snake.herosprite.getPosition().x >= 210) {
			bubble[1].setPosition(bubble[0].getPosition());
			window.draw(bubble[1]);
			bubble[1].move(Snakevelocity.x, 0);
		}
		if (Snake.herosprite.getPosition().x >= 320) {
			bubble[2].setPosition(bubble[1].getPosition());
			window.draw(bubble[2]);
			bubble[2].move(Snakevelocity.x, 0);
		}
		if (Snake.herosprite.getPosition().x >= 375) {
			bubble[3].setPosition(bubble[2].getPosition());
			window.draw(bubble[3]);
			bubble[3].move(Snakevelocity.x, 0);
		}
		if (Snake.herosprite.getPosition().x >= 500) {
			bubble[4].setPosition(bubble[3].getPosition());
			window.draw(bubble[4]);
			bubble[4].move(Snakevelocity.x, 0);
		}
		if (Snake.herosprite.getPosition().x >= 565) {
			bubble[5].setPosition(bubble[4].getPosition());
			window.draw(bubble[5]);
			bubble[5].move(Snakevelocity.x, 0);
		}
		if (Snake.herosprite.getPosition().x >= 670) {
			bubble[6].setPosition(bubble[5].getPosition());
			window.draw(bubble[6]);
			bubble[6].move(Snakevelocity.x, 0);
		}
		if (Snake.herosprite.getPosition().x >= 800) {
			window.draw(castle);
		}
		if (bl == 1) {
			window.clear();
			lop.stop();
			window.draw(blanck);
			window.draw(text);
			window.draw(txt);

			if (Keyboard::isKeyPressed(Keyboard::Enter) && keypause >= 8) {
				bl = 2;
			}
		}
		if (intro != 1) break;
		if (bl == 2) { pagenum = 1; }
		if (pagenum != 0) break;
		window.display();
	}
}

void PName(RenderWindow& window, std::string& name) {
	if (!name.empty()) {
		name.clear();
	}
	Texture background;
	background.loadFromFile("pname.png");
	Sprite bg;
	bg.setTexture(background);
	bg.setScale(1.4, 0.98);

	Font font;
	font.loadFromFile("RetroGrade.otf");

	Text t1;
	Text t2;
	t1.setFont(font);
	t2.setFont(font);
	t1.setString("Enter your name");
	t1.setCharacterSize(76);
	t2.setCharacterSize(76);
	t1.setPosition(10, 10);
	t2.setPosition(16, 166);
	t1.setFillColor(Color::White);
	t2.setFillColor(Color::White);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed()) {
				window.close();
			}
			if (event.type == Event::TextEntered) {
				name += static_cast<char>(event.text.unicode);
			}
			if (Keyboard::isKeyPressed(Keyboard::Backspace) && name.size() > 0) {
				name.resize(name.size() - 1);
			}
			if (Keyboard::isKeyPressed(Keyboard::Return) && name.size() > 1) {
				pagenum = 5;
				return;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				pagenum = 1;
				return;
			}
			t2.setString(name);
			window.clear();
			window.draw(bg);
			window.draw(t1);
			window.draw(t2);
			window.display();
		}
	}}

void main_game(RenderWindow& window) {

	window.setFramerateLimit(60);
	Event evento;
	Pause pause(1080, 720);

	// background texture
	Texture backgroundT;
	backgroundT.loadFromFile("level_1_map.png");
	Sprite background(backgroundT);
	background.setPosition(0, 0);

	// minion l1:
	int counter = 0;
	apple1 apple[7];
	//apple[7].HB;
	applend apples[7];
	int dir = 1;

	

	// setting positions lel minions
	apple[1].apple.setPosition(630, 390);
	apple[2].apple.setPosition(1400, 545);
	apple[3].apple.setPosition(3530, 390);
	apple[4].apple.setPosition(7500, 545);
	apple[5].apple.setPosition(10300, 545);
	apple[6].apple.setPosition(12950, 545);

	for (int i = 0; i < 7; i++)
	{//setting initial values
		apple[i].appletext.loadFromFile("apple l1.png");
		apples[i].appleT.loadFromFile("applend.png");
		apple[i].HB.rec.setOutlineColor(Color::Transparent);
		apple[i].HB.rec.setOutlineThickness(5);
		apple[i].HB.rec.setFillColor(Color::Transparent);
		apple[i].HB.rec.setSize(Vector2f(50, 50));
		apple[i].HB.rec.setOrigin(25, 25);
		apples[i].apple2.setOrigin(39 / 2, 45 / 2);
		apple[i].HB.rec.setPosition(apple[i].apple.getPosition());
		apple[i].apple.setTexture(apple[i].appletext);
		apple[i].apple.setTextureRect(IntRect((740 / 6), 0, (740 / 6), 160));
		apples[i].apple2.setTexture(apples[i].appleT);
		apple[i].apple.setScale(0.7, 0.7);
		apple[i].apple.setOrigin(59, 63);
	}

	int an = 0; // minion animator
	//int x = 0;

	bool inter = false;
	int posx = 0.f;

	CircleShape colliders[14];
	
	// enemy random motion #1:
	colliders[0].setRadius(25.f);
	colliders[1].setRadius(25.f);
	colliders[1].setPosition(Vector2f(800, 390));
	colliders[1].setFillColor(Color::Transparent);

	colliders[2].setRadius(25.f);
	colliders[2].setPosition(Vector2f(550, 390));
	colliders[2].setFillColor(Color::Transparent);


	// enemy random motion #2:
	colliders[3].setRadius(25.f);
	colliders[3].setPosition(Vector2f(1600, 545));
	colliders[3].setFillColor(Color::Transparent);

	colliders[4].setRadius(25.f);
	colliders[4].setPosition(Vector2f(1200, 545));
	colliders[4].setFillColor(Color::Transparent);

	// enemy random motion #3:
	colliders[5].setRadius(25.f);
	colliders[5].setPosition(Vector2f(3650, 390));
	colliders[5].setFillColor(Color::Transparent);

	colliders[6].setRadius(25.f);
	colliders[6].setPosition(Vector2f(3430, 390));
	colliders[6].setFillColor(Color::Transparent);

	// enemy random motion #4:
	colliders[7].setRadius(25.f);
	colliders[7].setPosition(Vector2f(7800, 545));
	colliders[7].setFillColor(Color::Transparent);

	colliders[8].setRadius(25.f);
	colliders[8].setPosition(Vector2f(7380, 545));
	colliders[8].setFillColor(Color::Transparent);

	// enemy random motion #5:
	colliders[9].setRadius(25.f);
	colliders[9].setPosition(Vector2f(10640, 545));
	colliders[9].setFillColor(Color::Transparent);

	colliders[10].setRadius(25.f);
	colliders[10].setPosition(Vector2f(10260, 545));
	colliders[10].setFillColor(Color::Transparent);

	// enemy random motion #6:
	colliders[11].setRadius(25.f);
	colliders[11].setPosition(Vector2f(13220, 545));
	colliders[11].setFillColor(Color::Transparent);

	colliders[12].setRadius(25.f);
	colliders[12].setPosition(Vector2f(12845, 545));
	colliders[12].setFillColor(Color::Transparent);

	//static apples level1:
	apple1 staticapple[3];
	staticapple[0].apple.setPosition(2825, 180);
	staticapple[1].apple.setPosition(4995, 180);
	staticapple[2].apple.setPosition(8560, 65);

	applend staticapples[3];

	for (int i = 0; i < 3; i++)
	{
		staticapple[i].appletext.loadFromFile("staticapple.png");
		staticapples[i].appleT.loadFromFile("applend.png");
		staticapple[i].HB.rec.setOutlineColor(Color::Transparent);
		staticapple[i].HB.rec.setOutlineThickness(5);
		staticapple[i].HB.rec.setFillColor(Color::Transparent);
		staticapple[i].HB.rec.setSize(Vector2f(50, 50));
		staticapple[i].HB.rec.setOrigin(25, 25);
		staticapples[i].apple2.setOrigin(39 / 2, 45 / 2);
		staticapple[i].HB.rec.setPosition(staticapple[i].apple.getPosition());
		staticapple[i].apple.setTexture(staticapple[i].appletext);
		staticapples[i].apple2.setTexture(staticapples[i].appleT);
		staticapple[i].apple.setScale(-0.41, 0.41);
		staticapple[i].apple.setOrigin(59, 63);
	}


	// shooter
	//texture
	Texture enemy, gun;
	enemy.loadFromFile("shooter.png"); gun.loadFromFile("gun.png");
	
	shooter Gunner[12];
	Gunner[0].settingProps(enemy, gun, { 4525, 545 });
	Gunner[1].settingProps(enemy, gun, { 6440, 385 });
	Gunner[2].settingProps(enemy, gun, { 7810, 375 });
	Gunner[3].settingProps(enemy, gun, { 8165, 155 });
	Gunner[4].settingProps(enemy, gun, { 9275, 200 });
	Gunner[5].settingProps(enemy, gun, { 9730, 545 });
	Gunner[6].settingProps(enemy, gun, { 10670, 375 });
	Gunner[7].settingProps(enemy, gun, { 12185, 385 });
	Gunner[8].settingProps(enemy, gun, { 13555, 375 });
	Gunner[9].settingProps(enemy, gun, { 15050, 385 });
	Gunner[10].settingProps(enemy, gun, { 11400, 545 });
	Gunner[11].settingProps(enemy, gun, { 14250, 545 });
	

	// gunner colectable:
	Texture applecolect;
	applecolect.loadFromFile("applend.png");
	Sprite colect(applecolect);
	colect.setScale(0, 0);

	bool is_colectable = false;

	//vectors
	Vector2f guncenter;
	Vector2f mouseposition;
	Vector2f aimdir;
	Vector2f aimdirnorm;

	//delayers
	int bulletDelay = 0;

	// tile array
	Texture tileT;
	tileT.loadFromFile("tile.png");
	Sprite tile[100];
	for (size_t t = 0; t < 60; t++) { tile[t].setTexture(tileT); }
	tile[1].setPosition(1895, 480);
	tile[2].setPosition(2055, 420); //tile[2].setColor(Color::Transparent);
	tile[3].setPosition(2038, 362);
	tile[4].setPosition(1990, 320);
	tile[5].setPosition(2020, 270);
	tile[6].setPosition(2050, 225); tile[6].setScale(1.8, 1);
	tile[7].setPosition(2280, 235);
	tile[8].setPosition(2405, 190);
	tile[9].setPosition(2495, 135);
	tile[10].setPosition(2555, 205);
	tile[11].setPosition(2660, 250);
	tile[12].setPosition(2780, 225);
	tile[13].setPosition(2960, 340);
	tile[14].setPosition(4765, 490);
	tile[15].setPosition(4925, 420); //tile[15].setColor(Color::Transparent);
	tile[16].setPosition(4910, 365);
	tile[17].setPosition(4860, 315);
	tile[18].setPosition(4895, 265);
	tile[19].setPosition(4930, 225); tile[19].setScale(1.8, 1);
	tile[20].setPosition(5150, 265);
	tile[21].setPosition(5280, 195);
	tile[22].setPosition(5365, 140);
	tile[23].setPosition(5525, 265);
	tile[24].setPosition(5640, 115);
	tile[25].setPosition(5650, 225);
	tile[26].setPosition(5690, 70); // add collectable
	tile[27].setPosition(5755, 195);
	tile[28].setPosition(5840, 350);
	int n = 2875;
	tile[29].setPosition(4925 + n, 420); //tile[15].setColor(Color::Transparent);
	tile[30].setPosition(4910 + n, 365);
	tile[31].setPosition(4855 + n, 315);
	tile[32].setPosition(4890 + n, 265);
	tile[33].setPosition(4920 + n, 225); tile[33].setScale(1.8, 1);
	tile[34].setPosition(5150 + n, 265);
	tile[35].setPosition(5280 + n, 195);
	tile[36].setPosition(5365 + n, 140);
	tile[37].setPosition(5525 + n, 265);
	tile[38].setPosition(5640 + n, 115);
	tile[39].setPosition(5650 + n, 225);
	tile[40].setPosition(5680 + n, 70); // add health
	tile[41].setPosition(5755 + n, 195);
	tile[42].setPosition(5830 + n, 350);
	tile[43].setPosition(5930 + n, 195);
	tile[44].setPosition(8880, 135);
	tile[45].setPosition(8945, 185);
	tile[46].setPosition(9085, 260);
	tile[47].setPosition(9205, 310);
	tile[48].setPosition(9235, 245); tile[48].setScale(1.8, 1);
	tile[49].setPosition(9235, 435); tile[49].setScale(1.8, 1);

	//level 1  ending 
	RectangleShape end;
	end.setSize(Vector2f(360, 300));
	end.setFillColor(Color::Black);
	end.setPosition(15585, 295);

	// text
	Font font;
	font.loadFromFile("RetroGrade.otf");

	Text text;
	text.setFont(font);
	text.setPosition(10, 10);
	text.setCharacterSize(35);

	// text for level completation
	Text lvl1;
	lvl1.setFont(font);
	lvl1.setCharacterSize(60);
	lvl1.setFillColor(Color::White);
	lvl1.setPosition(15400, 400);
	lvl1.setString("level completed!");

	// # main character
	Texture maincharct;
	maincharct.loadFromFile("snaky.png");

	MainCharacter Snake;
	Snake.herosprite.setTexture(maincharct);
	Snake.herosprite.setPosition(350.f, 50.f);
	Snake.herosprite.setOrigin(32.f / 2, 36.f / 2);
	Snake.herosprite.setTextureRect(IntRect(0, 0, 32, 36));
	Snake.herosprite.setScale(-8.f, 8.f);
	//Logics
	int Animator = 0;
	int AnimatorDelay = 0;
	Vector2f Snakevelocity = Snake.velocity;

	//HitBox
	HitBox.setSize(Vector2f(100.f, 100.f));
	HitBox.setFillColor(Color::Transparent);
	HitBox.setOutlineThickness(2.f);
	HitBox.setOutlineColor(Color::Red);
	HitBox.setOrigin(37, 30);
	float x = 25, y = 37; // hitbox for x & y 



	// healthbar:
	Texture healthbarT;
	healthbarT.loadFromFile("health bar.png");
	Sprite healthbar(healthbarT);
	healthbar.setScale(0.2, 0.2);
	healthbar.setPosition(Vector2f(30.f, -25.f));

	// sounds
	// main loop:
	Music lop;
	lop.openFromFile("l1.wav");
	lop.play();
	lop.setLoop(true);
	int vol = lop.getVolume();
	//jump
	SoundBuffer Buffer1; Buffer1.loadFromFile("jump.wav");
	Sound jump; jump.setBuffer(Buffer1); jump.setVolume(100);
	//damage
	SoundBuffer Buffer2; Buffer2.loadFromFile("damage.wav");
	Sound damage; damage.setBuffer(Buffer2); damage.setVolume(100);
	//attack
	SoundBuffer Buffer3; Buffer3.loadFromFile("attack.wav");
	Sound attack; attack.setBuffer(Buffer3); attack.setVolume(100);
	//colectable:
	SoundBuffer Buffer4; Buffer4.loadFromFile("collector.wav");
	Sound collector; collector.setBuffer(Buffer4); collector.setVolume(100);
	//shot:
	SoundBuffer Buffer6; Buffer6.loadFromFile("singleShot2.wav");
	Sound shot; shot.setBuffer(Buffer6); shot.setVolume(100);
	
	// TESTING LAND 
	RectangleShape land;
	land.setFillColor(Color::Transparent);
	land.setSize(Vector2f(119900.f, 50.f));
	land.setOrigin(1920 / 2, 25);
	land.setPosition(0.f, window.getSize().y - 150);



	Font anotherfont;
	anotherfont.loadFromFile("RetroGrade.otf");

	Text live; // game over:
	live.setFont(anotherfont);
	live.setFillColor(Color::Red);
	live.setPosition(HitBox.getPosition().x + 150, HitBox.getPosition().y + 500);
	live.setCharacterSize(96);
	live.setOrigin(32 / 2, 36 / 2);

	

	bool attacking = false;

	//power ups:
	Texture healthT;
	healthT.loadFromFile("health.png");
	Sprite heal(healthT);
	heal.setScale(0.5, 0.5);
	heal.setPosition(Vector2f(5700 + n, 25));

	Texture speedT;
	speedT.loadFromFile("speed.png");
	Sprite speed(speedT);
	speed.setScale(0.5, 0.5);
	speed.setPosition(Vector2f(12500, 485));

	Texture distanceT;
	distanceT.loadFromFile("distance.png");
	Sprite distance(distanceT);
	distance.setScale(0.5, 0.5);
	distance.setPosition(Vector2f(5660, 65));
	
	int powerup_var = 0;

	//view change
	View camera;
	camera.setSize(Vector2f(1365, 759));
	camera.setCenter(Snake.herosprite.getPosition().x + 485, 759 / 2);

	int whichtile = -1;//save the last tile 
	bool alive = true;//player life

	// collectable counter:
	Texture applecolectT;
	applecolectT.loadFromFile("images (3).png");
	Sprite collecticon(applecolectT);
	collecticon.setPosition(Vector2f(40, -23));

	Text collectnum;
	collectnum.setFont(anotherfont);
	collectnum.setFillColor(Color::White);
	collectnum.setCharacterSize(32);
	collectnum.setPosition(150, 18);

	int collect = 0;

	// pause texture:
	Texture Backgroundpause;
	Backgroundpause.loadFromFile("pause_background.png");
	Sprite bkg(Backgroundpause);
	bkg.setScale(1, 0.75);
	bkg.setPosition(window.getPosition().x +200, window.getPosition().y);

	while (window.isOpen())
	{

		HitBox.setPosition(Snake.herosprite.getPosition().x - x, Snake.herosprite.getPosition().y + y);

		while (window.pollEvent(evento))
		{
			if (evento.type == Event::Closed)
				window.close();

			if (Snake.current_health >= 5)
			{
				Animator = 0;
				alive = false;
			}
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				Animator = 0;
				attacking = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::P))
				wait = true;

			if (wait == true) {
				if (evento.type == Event::KeyPressed) {
					if (evento.key.code == Keyboard::Up) {
						pause.MoveUpP();
					}
					if (evento.key.code == Keyboard::Down) {
						pause.MoveDownP();
					}
					if (evento.key.code == Keyboard::Return) {
						// 0 -> continue 1 -> main menu
						if (pause.pressedP() == 0) wait = false;
						if (pause.pressedP() == 1) pagenum = 1;
					}
					if (evento.key.code == Keyboard::U) {
						vol -= 20;
						lop.setVolume(vol);
					}
					if (evento.key.code == Keyboard::D) {
						vol += 20;
						lop.setVolume(vol);
					}
				}
			}
		}
		//update
		if (alive && wait == false) {
			// health bar animation:
			if (Snake.current_health < 6)
				healthbar.setTextureRect(IntRect((Snake.current_health * float(1639 / 6)), 0, float(1639 / 6), 400));
			// static apples:
			for (int i = 0; i < 3; i++) {
				staticapple[i].HB.rec.setPosition(staticapple[i].apple.getPosition());
				if (attacking == true && HitBox.getGlobalBounds().intersects(staticapple[i].apple.getGlobalBounds()))
				{
					staticapples[i].apple2.setPosition(staticapple[i].apple.getPosition());
					staticapple[i].apple.setScale(0, 0);
					staticapple[i].HB.rec.setScale(0, 0);
					staticapples[i].apple2.setScale(1, 1);
				}
				else {
					if (HitBox.getGlobalBounds().intersects(staticapples[i].apple2.getGlobalBounds())) {
						staticapples[i].apple2.setScale(0, 0);
						collect++;
						staticapple[i].apple.setScale(staticapple[i].apple.getScale().x, staticapple[i].apple.getScale().y);
					}
				}
			}
			// moving minion l1:
			for (int i = 1; i < 7; i++) {
				apple[i].HB.rec.setPosition(apple[i].apple.getPosition());
				if (attacking == true && HitBox.getGlobalBounds().intersects(apple[i].HB.rec.getGlobalBounds())) {
					apples[i].apple2.setScale(1, 1);
					apple[i].HB.rec.setScale(0, 0);
					apple[i].apple.setScale(0, 0);
					apples[i].apple2.setPosition(apple[i].apple.getPosition().x, apple[i].apple.getPosition().y);
					//apple[i].apple.move(0, 0);
					if (apples[i].apple2.getPosition().y == apple[i].apple.getPosition().y)
					{
						if (an <= 300)
						{
							an++;
						}
						if (an > 300)
						{
							apples[i].apple2.move(0, 1);
						}
					}
				}
				else if(HitBox.getGlobalBounds().intersects(apples[i].apple2.getGlobalBounds()))
				{
					apples[i].apple2.setScale(0, 0);
					apples[i].apple2.move(0, 0);
					apple[i].apple.move(0, 0);
					apples[i].collect = true;
					apple[i].apple.setScale(apple[i].apple.getScale().x, apple[i].apple.getScale().y);
					break;
				}
				else if (apples[i].collect == true) {
					collect++;
					apples[i].collect = false;
				}
			}
			// moving apple animation:
			for (int i = 1; i < 7; i++)
			{
				apple[i].HB.rec.setPosition(apple[i].apple.getPosition());

			}

			for (int i = 1; i < 7; i++)
			{
				if (apple[i].HB.dead == false && apples[i].collect == false)
				{

					if (an <= 6)
					{
						an++;
					}
					if (an > 6)
					{
						an = 0;
						apple[i].apple.setTextureRect(IntRect((740 / 6) * apple[i].anim, 0, (740 / 6), 160));
						apple[i].anim++;
						apple[i].anim %= 6;
					}
				}
			}
			// checking collision with transperant colliders to define enemy motion
			for (size_t i = 1; i < 7/*sizeof(apple)*/; i++) {
				if (apple[i].HB.dead == false && apple[i].apple.getGlobalBounds().intersects(colliders[2 * i - 1].getGlobalBounds())) {
					apple[i].v.x = -2;
					apple[i].apple.setScale(-0.7, 0.7);
				}
				else if (apple[i].HB.dead == false && apple[i].apple.getGlobalBounds().intersects(colliders[2 * i].getGlobalBounds())) {
					apple[i].v.x = 2;
					apple[i].apple.setScale(0.7, 0.7);
				}

				apple[i].apple.move(Vector2f(apple[i].v));
			}
			// gunner logics:
			for (size_t i = 0; i < 12; i++)
			{
				if (HitBox.getPosition().x > Gunner[i].shooters.getPosition().x && HitBox.getGlobalBounds().intersects(Gunner[i].Range.getGlobalBounds()) && !Gunner[i].is_gunner_dead ) {
					Gunner[i].shooters.setScale(-0.4, 0.4);
					Gunner[i].gun.setScale(0.3, -0.3);
					Gunner[i].gun.setPosition(Gunner[i].shooters.getPosition().x + 35, Gunner[i].shooters.getPosition().y + 5);
				}
				if (HitBox.getPosition().x < Gunner[i].shooters.getPosition().x && HitBox.getGlobalBounds().intersects(Gunner[i].Range.getGlobalBounds()) && !Gunner[i].is_gunner_dead) {
					Gunner[i].shooters.setScale(0.4, 0.4);
					Gunner[i].gun.setScale(0.3, 0.3);
					Gunner[i].gun.setPosition(Gunner[i].shooters.getPosition().x - 35, Gunner[i].shooters.getPosition().y + 5);
				}
			}

			//final bullet normalization
			for (size_t i = 0; i < 12; i++)
			{
				if (HitBox.getGlobalBounds().intersects(Gunner[i].Range.getGlobalBounds()) ) {
					guncenter = Vector2f(Gunner[i].gun.getPosition());
					mouseposition = Vector2f(HitBox.getPosition());
					aimdir = mouseposition - guncenter;
					aimdirnorm = aimdir / (sqrt((float)pow(aimdir.x, 2) + (float)pow(aimdir.y, 2)));
					//theta of rotation
					float deg = atan2(aimdirnorm.y, aimdirnorm.x) * 180 / PI;
					Gunner[i].gun.setRotation(deg + 180);
				}
			}

			// final shooting 
			for (size_t i = 0; i < 12; i++)
			{
				if (HitBox.getGlobalBounds().intersects(Gunner[i].Range.getGlobalBounds()))
				{
					if (bulletDelay < 40)
						bulletDelay++;

					if (bulletDelay >= 40) {
						bulletDelay = 0;
						// bullets:
						Bullets bul;
						bul.setinitials(3.f, Color::White, guncenter, aimdirnorm);
						if (!Gunner[i].is_gunner_dead) {
							Gunner[i].pusher(bul);
							shot.play();
						}
					}
				}

			}
			// checking bounderies:
			for (size_t i = 0; i < 12; i++)
			{
				for (size_t j = 0; j < Gunner[i].projectiles.size(); j++) {
					Gunner[i].projectiles[j].b.move(Gunner[i].projectiles[j].currvelo);
					
					if (!HitBox.getGlobalBounds().intersects(Gunner[i].Range.getGlobalBounds())) {
						//out of bounds
						if (Gunner[i].projectiles[j].b.getPosition().x < 0 || Gunner[i].projectiles[j].b.getPosition().x > window.getSize().x 
							|| Gunner[i].projectiles[j].b.getPosition().y < 0 
							|| Gunner[i].projectiles[j].b.getPosition().y > window.getSize().y && !Gunner[i].projectiles.empty()) {
							Gunner[i].projectiles.erase(Gunner[i].projectiles.begin() + j);
						}

					}
				}
			}

			// gunner death
			for (size_t i = 0; i < 12; i++)
			{
				if (HitBox.getGlobalBounds().intersects(Gunner[i].shooters.getGlobalBounds()) && attacking == true) {
					Gunner[i].shooters.setScale(0, 0);
					Gunner[i].gun.setScale(0, 0);
					Gunner[i].is_gunner_dead = true;
					colect.setPosition(Gunner[i].shooters.getPosition());
					colect.setScale(1, 1);
					is_colectable = true;
				}
				if (HitBox.getGlobalBounds().intersects(colect.getGlobalBounds()) && is_colectable == true) {
					colect.setScale(0, 0);
					collect++;
					is_colectable = false;
				}
				// player damage:
				for (size_t j = 0; j < Gunner[i].projectiles.size(); j++) {
					if (HitBox.getGlobalBounds().intersects(Gunner[i].projectiles[j].b.getGlobalBounds())) {
						Snake.current_health += 1;
						damage.play();
						Gunner[i].projectiles.erase(Gunner[i].projectiles.begin() + j);
					}

				}
			}
			// snake ideal
			if (Snakevelocity.x == 0 && Snakevelocity.y == 0)
			{
				if (AnimatorDelay < 10)
					AnimatorDelay++;

				if (AnimatorDelay >= 10)
				{
					AnimatorDelay = 0;

					Animator++;
					Animator %= 10;
					Snake.herosprite.setTextureRect(IntRect(32 * Animator, 0, 32, 36));
				}

			}
			//walk animation
			if (Keyboard::isKeyPressed(Keyboard::Right)) // # MOVING RIGHT # 
			{
				if (Snake.herosprite.getPosition().x >= 250 && Snake.herosprite.getPosition().x < 15210) {
					if (AnimatorDelay < 5)
					{
						AnimatorDelay++;
					}
					if (AnimatorDelay >= 5) {
						AnimatorDelay = 0;

						Animator %= 10;
						Snake.herosprite.setTextureRect(IntRect(32 * Animator, 64, 32, 36));
						Animator++;
					}
					Snake.herosprite.setScale(-8, 8);
					Snakevelocity.x = motion;
					camera.setCenter(Snake.herosprite.getPosition().x + 585, 759 / 2);
				}
				else if (Snake.herosprite.getPosition().x < 250)
				{
					camera.move(0, 0);
					if (AnimatorDelay < 5)
					{
						AnimatorDelay++;
					}
					if (AnimatorDelay >= 5) {
						AnimatorDelay = 0;

						Animator %= 10;
						Snake.herosprite.setTextureRect(IntRect(32 * Animator, 64, 32, 36));
						Animator++;
					}
					Snake.herosprite.setScale(-8, 8);
					Snakevelocity.x = motion;
				}
				else if (Snake.herosprite.getPosition().x >= 15210)
				{
					camera.move(0, 0);
					if (AnimatorDelay < 5)
					{
						AnimatorDelay++;
					}
					if (AnimatorDelay >= 5) {
						AnimatorDelay = 0;

						Animator %= 10;
						Snake.herosprite.setTextureRect(IntRect(32 * Animator, 64, 32, 36));
						Animator++;
					}
					Snake.herosprite.setScale(-8, 8);
					Snakevelocity.x = motion;
					camera.setCenter(15210 + 485, 759 / 2);
					if (Snake.herosprite.getPosition().x >= 16300)
						Snake.herosprite.setPosition(16300, Snake.herosprite.getPosition().y);
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left)) // # MOVING LEFT # 
			{
				if (Snake.herosprite.getPosition().x >= 200 && Snake.herosprite.getPosition().x < 15210) {
					if (AnimatorDelay < 5)
					{
						AnimatorDelay++;
					}
					if (AnimatorDelay >= 5) {
						AnimatorDelay = 0;

						Animator %= 10;
						Snake.herosprite.setTextureRect(IntRect(32 * Animator, 64, 32, 36));
						Animator++;
					}
					Snake.herosprite.setScale(8, 8);
					Snakevelocity.x = -motion;
					camera.setCenter(Snake.herosprite.getPosition().x + 600, 759 / 2);
				}
				else if (Snake.herosprite.getPosition().x < 200) {
					camera.move(0, 0);
					if (AnimatorDelay < 5)
					{
						AnimatorDelay++;
					}
					if (AnimatorDelay >= 5) {
						AnimatorDelay = 0;

						Animator %= 10;
						Snake.herosprite.setTextureRect(IntRect(32 * Animator, 64, 32, 36));
						Animator++;
					}
					Snake.herosprite.setScale(8, 8);
					Snakevelocity.x = -motion;
					if (Snake.herosprite.getPosition().x <= 0)
					{
						background.setPosition(0.f, background.getPosition().y);
						Snake.herosprite.setPosition(0, Snake.herosprite.getPosition().y);
						camera.setCenter(690, 759 / 2);
					}
				}
				else if (Snake.herosprite.getPosition().x >= 15210)
				{
					camera.move(0, 0);
					if (AnimatorDelay < 5)
					{
						AnimatorDelay++;
					}
					if (AnimatorDelay >= 5) {
						AnimatorDelay = 0;

						Animator %= 10;
						Snake.herosprite.setTextureRect(IntRect(32 * Animator, 64, 32, 36));
						Animator++;
					}
					Snake.herosprite.setScale(8, 8);
					Snakevelocity.x = -motion;
					camera.setCenter(15210 + 485, 759 / 2);
				}
			}
			else
				Snakevelocity.x = 0.f;

			if (attacking) // # ATTACKING ANIMATION #
			{
				if (AnimatorDelay < 5)
					AnimatorDelay++;
				if (AnimatorDelay >= 5) {
					AnimatorDelay = 0;
					Animator %= 10;
					Snake.herosprite.setTextureRect(IntRect(32 * Animator, 96, 32, 36));
					attack.play();
					Animator++;
				}
				
				
			}
			//return to idle
			if (Animator == 10)
				attacking = false;
			//#SNAKE JUMPING , GRAVITY AND GROUNDING
			for (size_t i = 0; i < 50; i++) {
				if (HitBox.getGlobalBounds().intersects(tile[i].getGlobalBounds())) {
					whichtile = i;
					break;
				}
			}
			// reacting to jumping on tiles:
			if (whichtile != -1) {
				if (HitBox.getGlobalBounds().intersects(tile[whichtile].getGlobalBounds()) || HitBox.getGlobalBounds().intersects(land.getGlobalBounds())) {
					if (tile[whichtile].getGlobalBounds().top < (HitBox.getGlobalBounds().top + HitBox.getGlobalBounds().height)) {
						Snakevelocity.y = 0;
						if (Keyboard::isKeyPressed(Keyboard::Up))
						{
							Snake.herosprite.setTextureRect(IntRect(IntRect(32 * 2, 128, 32, 36)));
							Snakevelocity.y = -jumphight;
							jump.play();

						}
					}
				}
				else
					Snakevelocity.y += gravity;
			}
			// colision with land: (gravity)
			else if (HitBox.getGlobalBounds().intersects(land.getGlobalBounds()))
			{

				Snakevelocity.y = 0;
				if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					Snake.herosprite.setTextureRect(IntRect(IntRect(32 * 2, 128, 32, 36)));
					Snakevelocity.y = -jumphight;
					jump.play();

				}
			}


			else {
				Snakevelocity.y += gravity;
			}

			// checking collision motion:
			for (int i = 0; i < 7; i++) {
				if (collide_with_enemy(HitBox, apple[i].HB.rec) && attacking == true ) {
					apple[i].HB.dead == true;

				}
				else if(collide_with_enemy(HitBox, apple[i].HB.rec) && !apple[i].HB.dead)
				{
					Snake.current_health++;
					if (HitBox.getPosition().x < apple[i].HB.rec.getPosition().x)
						Snakevelocity.x = -120.f;
					else if (HitBox.getPosition().x > apple[i].HB.rec.getPosition().x)
						Snakevelocity.x = 120.f;
					damage.play();
				}
			}
			for (int i = 0; i < 3; i++) {
				if (collide_with_enemy(HitBox, staticapple[i].HB.rec) && attacking == true) {
					apple[i].HB.dead == true;

				}
				else if (collide_with_enemy(HitBox, staticapple[i].HB.rec) && !staticapple[i].HB.dead)
				{
					Snake.current_health++;
					if (HitBox.getPosition().x < staticapple[i].HB.rec.getPosition().x)
						Snakevelocity.x = -120.f;
					else if (HitBox.getPosition().x > staticapple[i].HB.rec.getPosition().x)
						Snakevelocity.x = 120.f;
					damage.play();
				}
			}

			//powerups collision:
			if (HitBox.getGlobalBounds().intersects(heal.getGlobalBounds())) {
				heal.setScale(0, 0);
				Snake.current_health = Snake.maxhealth;
				collector.play();
			}
			else if (HitBox.getGlobalBounds().intersects(speed.getGlobalBounds())) {
				powerup_var = 1;
				speed.setScale(0, 0);
				collector.play();
				powerupfun(powerup_var);
			}
			else if (HitBox.getGlobalBounds().intersects(distance.getGlobalBounds())) {
				powerup_var = 2;
				distance.setScale(0, 0);
				collector.play();
				powerupfun(powerup_var);
			}

			// final movement 
			Snake.herosprite.move(Snakevelocity);
		}
		// snake death animation:
		if (alive == false && Animator <= 9) {
			if (AnimatorDelay < 5)
			{
				AnimatorDelay++;
			}
			if (AnimatorDelay >= 5) {
				AnimatorDelay = 0;

				Snake.herosprite.setTextureRect(IntRect(32 * Animator, 128, 32, 36));
				Animator++;

			}
		}
		
		//Drawing
		window.clear();
		window.setView(camera);
		window.draw(background);
		
		window.draw(Snake.herosprite);
		window.draw(land);
		
		window.draw(HitBox);

		window.draw(heal);
		window.draw(speed);
		window.draw(distance);
		for (size_t i = 1; i < 7; i++)
			window.draw(apple[i].apple);

		for (size_t i = 0; i < 50; i++)
			window.draw(tile[i]);
		for (size_t i = 0; i < 3; i++) 
			window.draw(staticapple[i].apple);

		for (size_t i = 0; i < 12; i++)
		{
			window.draw(Gunner[i].shooters);
			window.draw(Gunner[i].gun);
			for (size_t j = 0; j < Gunner[i].projectiles.size(); j++)
			{
				window.draw(Gunner[i].projectiles[j].b);
			}
		}
		if (is_colectable == true) window.draw(colect);
		for (int i = 1; i < 7; i++)
		{
			window.draw(apple[i].apple);
			window.draw(apple[i].HB.rec);
			window.draw(apples[i].apple2);

		}
		for (int i = 0; i < 3; i++)
		{
			window.draw(staticapple[i].apple);
			window.draw(staticapple[i].HB.rec);
			window.draw(staticapples[i].apple2);

		}
		for (size_t i = 1; i < 14; i++)
			window.draw(colliders[i]);
		window.draw(end);
		if (Snake.herosprite.getGlobalBounds().intersects(end.getGlobalBounds())) {
			Snake.herosprite.setPosition(15550, Snake.herosprite.getPosition().y);
			window.draw(lvl1);
			if(Keyboard::isKeyPressed(Keyboard::Enter))
				pagenum = 6;
		}

		window.setView(window.getDefaultView());
		window.draw(healthbar);
		window.draw(collecticon);
		collectnum.setString("x " + std::to_string(collect));
		window.draw(collectnum);

		if (!alive) {
			// music:
			lop.play();
			lop.setLoop(true);
			live.setString("Game OVER");
			window.draw(live);
			score = (Snake.herosprite.getPosition().x * collect) / 1000;
			savename(name, score);
			if (Keyboard::isKeyPressed(Keyboard::Enter))
				pagenum = 1;
		}

		score = (Snake.herosprite.getPosition().x * collect) / 1000;

		if (pagenum != 5) {
			end_of_level_health = Snake.current_health;
			lop.stop();
			break;
		}
		if (wait == true) {
			window.draw(bkg);
			pause.drawP(window);
		}
		window.display();

	}
}

bool collide_with_enemy(RectangleShape HB, RectangleShape object) {
	if (HB.getGlobalBounds().intersects(object.getGlobalBounds())) {
		return true;
	}
	else
		return false;
}

void platform_collisions(Sprite tile[50], MainCharacter& snake, Vector2f& snakevelocity) {
	for (size_t i = 0; i < 50; i++) {
		if (HitBox.getGlobalBounds().intersects(tile[i].getGlobalBounds())) {
			snakevelocity.y = 0;
			gravity = 0.f;
		}
	}
}

void powerupfun(int is_coll) {
	// speed -> 1   distance ->  2
	switch (is_coll) {
	case 1:
		motion *= 1.2;
		break;
	case 2:
		jumphight *= 1.3;
		break;
	}
}

void savename(std::string name, int score) {
	std::ofstream out("data.txt", std::ios::out);
	out << name << "\t" << score << std::endl;
	
	out.close();
}

void scoreboard(RenderWindow& window) {
	Texture boardT;
	boardT.loadFromFile("score board.png");
	Sprite board(boardT);
	board.setScale(1.4, 0.98);

	Font font;
	font.loadFromFile("RetroGrade.otf");

	Text nm[5];
	Text sc[5];

	std::ifstream out("data.txt");
	int i = 0;

	while (i < 5 && out >> name >> score) {
		nm[i].setFont(font);
		nm[i].setString(name);
		nm[i].setCharacterSize(45);
		nm[i].setPosition(350, 200 + (100 * i));
		nm[0].setPosition(350, 200);
		nm[i].setFillColor(Color::Black);
		sc[i].setFont(font);
		sc[i].setString(std::to_string(score));
		sc[i].setCharacterSize(45);
		sc[i].setPosition(950 * i, 200 + (100 * i));
		sc[0].setPosition(950, 200);
		sc[i].setFillColor(Color::Black);
		i++;
	}

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed()) {
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				pagenum = 1;
			}
		}
		window.clear();
		window.draw(board);
		for (int i = 0; i < 5; i++) {
			window.draw(nm[i]);
			window.draw(sc[i]);
		}
		if (pagenum != 3) {
			out.close();
			break;
		}
		window.display();
	}
}

void levl2_game(RenderWindow& window) {
	window.setFramerateLimit(60);
	Pause pause(1080, 720);

	Font font;
	font.loadFromFile("RetroGrade.otf");

	Text gameover;
	gameover.setFont(font);
	gameover.setString("Game Over ");
	gameover.setPosition(100, 100);
	gameover.setCharacterSize(150);

	//healthbar:
	Texture helBarT;
	helBarT.loadFromFile("health bar.png");
	Sprite bar(helBarT);
	bar.setScale(0.2, 0.2);
	bar.setPosition(0, -20);


	Vector2f center = Vector2f(635, 650);

	Texture backgroundT;
	backgroundT.loadFromFile("l2background (1).png");
	Sprite background(backgroundT);
	background.setScale(2.5, 2);

	std::vector <Sprite> enemies;
	int enemyspawntimer = 0;
	Texture EnemyT;
	EnemyT.loadFromFile("falling enemy.png");
	Sprite enemy(EnemyT);
	enemy.setScale(0.4, 0.4);
	enemy.setRotation(45);
	enemies.push_back(Sprite(enemy));

	// # main character
	Texture maincharct;
	maincharct.loadFromFile("snaky.png");

	MainCharacter Snake;
	Snake.herosprite.setTexture(maincharct);
	Snake.herosprite.setPosition(150.f, 50.f);
	Snake.herosprite.setOrigin(32.f / 2, 36.f / 2);
	Snake.herosprite.setTextureRect(IntRect(0, 0, 32, 36));
	Snake.herosprite.setScale(-5.f, 5.f);
	//Logics
	int Animator = 0;
	int AnimatorDelay = 0;
	Vector2f Snakevelocity = Snake.velocity;
	//HitBox
	RectangleShape HitBox;
	HitBox.setSize(Vector2f(45.f, 45.f));
	HitBox.setFillColor(Color::Transparent);
	HitBox.setOutlineThickness(2.f);
	HitBox.setOutlineColor(Color::Transparent);
	HitBox.setOrigin(36 / 2, 32 / 2);

	// sounds
	// main loop:
	Music lop;
	lop.openFromFile("l2.wav");
	lop.play(); 
	lop.setLoop(true);
	int vol = lop.getVolume();
	//jump
	SoundBuffer Buffer1; Buffer1.loadFromFile("jump.wav");
	Sound jump; jump.setBuffer(Buffer1); jump.setVolume(100);
	//damage
	SoundBuffer Buffer2; Buffer2.loadFromFile("damage.wav");
	Sound damage; damage.setBuffer(Buffer2); damage.setVolume(100);

	//TESTING LAND 
	RectangleShape land;
	land.setFillColor(Color::Transparent);
	land.setSize(Vector2f(2920.f, 50.f));
	land.setOrigin(2920 / 2, 25);
	land.setPosition(0.f, 525);

	//gravity
	float  gravity = 1.f;
	float y = 37;
	bool attacking = false;
	bool alive = true;

	Text timertxt;
	timertxt.setFont(font);
	timertxt.setPosition(70, 15);
	timertxt.setCharacterSize(40);

	Snake.current_health = end_of_level_health;

	// pause texture:
	Texture Backgroundpause;
	Backgroundpause.loadFromFile("pause_background.png");
	Sprite bkg(Backgroundpause);
	bkg.setScale(1, 0.75);
	bkg.setPosition(window.getPosition().x + 200, window.getPosition().y);

	leveltimer = 0;

	while (window.isOpen()) {
		Event closed;
		HitBox.setPosition(Snake.herosprite.getPosition().x, Snake.herosprite.getPosition().y + y);
		while (window.pollEvent(closed)) {
			if (closed.type == Event::Closed) {
				window.close();
			}

			if (Snake.current_health >= 5)
			{
				Animator = 0;
				alive = false;
			}

			if (Keyboard::isKeyPressed(Keyboard::P))
				wait = true;

			if (wait == true) {
				if (closed.type == Event::KeyPressed) {
					if (closed.key.code == Keyboard::Up) {
						pause.MoveUpP();
					}
					if (closed.key.code == Keyboard::Down) {
						pause.MoveDownP();
					}
					if (closed.key.code == Keyboard::Return) {
						// 0 -> continue 1 -> main menu
						if (pause.pressedP() == 0) wait = false;
						if (pause.pressedP() == 1) pagenum = 1;
					}
					if (closed.key.code == Keyboard::U) {
						vol -= 20;
						lop.setVolume(vol);
					}
					if (closed.key.code == Keyboard::D) {
						vol += 20;
						lop.setVolume(vol);
					}
				}
			}
		}
		if (Snake.current_health < 6)
			bar.setTextureRect(IntRect((Snake.current_health * float(1639 / 6)), 0, float(1639 / 6), 400));

		if (alive && leveltimer <= consttimer && wait == false) {
			leveltimer++;

			//Collision with window
			if (Snake.herosprite.getPosition().x <= 0) //Left
				Snake.herosprite.setPosition(0.f, Snake.herosprite.getPosition().y);
			if (Snake.herosprite.getPosition().x >= window.getSize().x - 
				Snake.herosprite.getGlobalBounds().width) //Right
				Snake.herosprite.setPosition(window.getSize().x - Snake.herosprite.getGlobalBounds().width, 
					Snake.herosprite.getPosition().y);
			if (Snake.herosprite.getPosition().y <= 0) //Top
				Snake.herosprite.setPosition(Snake.herosprite.getPosition().x, 0.f);
			if (Snake.herosprite.getPosition().y >= window.getSize().y - 
				Snake.herosprite.getGlobalBounds().height) //Bottom
				Snake.herosprite.setPosition(Snake.herosprite.getPosition().x, 
					Snake.herosprite.getScale().y - Snake.herosprite.getGlobalBounds().height);

			if (Snakevelocity.x == 0 && Snakevelocity.y == 0)
			{
				if (AnimatorDelay < 10)
					AnimatorDelay++;

				if (AnimatorDelay >= 10)
				{
					AnimatorDelay = 0;

					Animator++;
					Animator %= 10;
					Snake.herosprite.setTextureRect(IntRect(32 * Animator, 0, 32, 36));
				}

			}
			//testing walk animation
			if (Keyboard::isKeyPressed(Keyboard::Right)) // # MOVING RIGHT # 
			{
				if (AnimatorDelay < 5)
				{
					AnimatorDelay++;
				}
				if (AnimatorDelay >= 5) {
					AnimatorDelay = 0;

					Animator %= 10;
					Snake.herosprite.setTextureRect(IntRect(32 * Animator, 64, 32, 36));
					Animator++;
				}
				Snake.herosprite.setScale(-5, 5);
				Snakevelocity.x = 5.f;


			}
			else if (Keyboard::isKeyPressed(Keyboard::Left)) // # MOVING LEFT # 
			{

				if (AnimatorDelay < 5)
				{
					AnimatorDelay++;
				}
				if (AnimatorDelay >= 5) {
					AnimatorDelay = 0;

					Animator %= 10;
					Snake.herosprite.setTextureRect(IntRect(32 * Animator, 64, 32, 36));
					Animator++;
				}
				Snake.herosprite.setScale(5, 5);
				Snakevelocity.x = -5.f;


			}
			else
				Snakevelocity.x = 0.f;

			//#SNAKE JUMPING , GRAVITY AND GROUNDING
			if (HitBox.getGlobalBounds().intersects(land.getGlobalBounds()))
			{
				Snakevelocity.y = 0;
				if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					Snake.herosprite.setTextureRect(IntRect(IntRect(32 * 2, 128, 32, 36)));
					Snakevelocity.y = -20.f;
					jump.play();
				}
			}
			else
				Snakevelocity.y += gravity;

			// final movement 
			Snake.herosprite.move(Snakevelocity);


			if (enemyspawntimer < 7) enemyspawntimer++;

			if (enemyspawntimer >= 7)
			{
				enemy.setPosition((rand() % int(window.getSize().x - enemy.getScale().x)), 0.f);
				enemies.push_back(Sprite(enemy));
				enemyspawntimer = 0;
			}
			for (size_t i = 0; i < enemies.size(); i++)
			{
				enemies[i].move(0.f, 5.f);
				if (enemies[i].getPosition().y > window.getSize().y)
					enemies.erase(enemies.begin() + i);
			}

			for (size_t j = 0; j < enemies.size(); j++)
			{
				if (enemies[j].getGlobalBounds().intersects(HitBox.getGlobalBounds())) {
					Snake.current_health++;
					enemies.erase(enemies.begin() + j);
					damage.play();
				}
			}
		}

		// death animation:

		if (alive == false && Animator <= 9) {
			if (AnimatorDelay < 5)
			{
				AnimatorDelay++;
			}
			if (AnimatorDelay >= 5) {
				AnimatorDelay = 0;

				Snake.herosprite.setTextureRect(IntRect(32 * Animator, 128, 32, 36));
				Animator++;

			}
		}

		window.clear();
		window.draw(background);
		for (size_t i = 0; i < enemies.size(); i++) window.draw(enemies[i]);
		window.draw(bar);
		window.draw(Snake.herosprite);
		window.draw(HitBox);
		window.draw(land);
		timertxt.setString("remaining time: " + std::to_string(consttimer - leveltimer));
		window.draw(timertxt);
		if (!alive) {
			window.draw(gameover);
			score += (leveltimer / 100);
			savename(name, score);
			if (Keyboard::isKeyPressed(Keyboard::Enter)) pagenum = 1;
		}
		if (leveltimer > consttimer) {
			gameover.setString("Level completed!");
			window.draw(gameover);
			score += (consttimer / 100);
			savename(name, score);
			if (Keyboard::isKeyPressed(Keyboard::Enter))
				pagenum = 7;
		}
		if (wait == true) {
			window.draw(bkg);
			pause.drawP(window);
		}
		if (pagenum != 6) {
			end_of_level_health = Snake.current_health;
			lop.stop();
			break;
		}
		window.display();
	}
}

void level3_game(RenderWindow& window) {

	window.setFramerateLimit(60);
	Event evento;
	Pause pause(1080, 720);

	//#Our Cute Lil snake
	Texture maincharct;
	maincharct.loadFromFile("snaky.png");

	MainCharacter Snake;
	Snake.herosprite.setTexture(maincharct);
	Snake.herosprite.setOrigin(32.f / 2, 36.f / 2);
	Snake.herosprite.setTextureRect(IntRect(0, 0, 32, 36));
	Snake.herosprite.setScale(-5.f, 5.f);

	//HitBox
	RectangleShape HitBox;
	HitBox.setSize(Vector2f(45.f, 45.f));
	HitBox.setFillColor(Color::Transparent);
	HitBox.setOutlineThickness(2.f);
	HitBox.setOutlineColor(Color::Transparent);
	HitBox.setOrigin(36 / 2, 32 / 2);

	// SNAKE LOGICS
	int Animator = 0;
	int AnimatorDelay = 0;
	Vector2f Snakevelocity = { 0.f,0.f };

	//gravity
	float  gravity = 1.f;


	// boss like circle
	Texture boss; boss.loadFromFile("final_boss.png");
	Sprite BadApple; BadApple.setTexture(boss);

	BadApple.setOrigin(320 / 2, 320 / 2);
	BadApple.setPosition(1245, window.getSize().y - 300);
	BadApple.setScale(1, 1);
	// boss logics

	int BigBossHealth = 6;
	BadApple.setTextureRect(IntRect(320 * BigBossHealth, 0, 320, 320));

	// boss death:
	Texture deathT;
	deathT.loadFromFile("AppleDead.png");
	Sprite death(deathT);
	death.setScale(2, 2);
	death.setOrigin(71, 113 / 2);

	// TESTING LAND 
	RectangleShape land;
	land.setFillColor(Color::Transparent);
	land.setSize(Vector2f(200000.f, 50.f));
	land.setOrigin(0, 25);
	land.setPosition(-2500.f, window.getSize().y - 100);

	// background:
	Texture bkgT;
	bkgT.loadFromFile("l3_map.png");
	Sprite bkg(bkgT);
	bkg.setScale(0.9, 1.05);

	// healthbar:
	Texture healthbarT;
	healthbarT.loadFromFile("health bar.png");
	Sprite bar(healthbarT);
	bar.setScale(0.2, 0.2);
	bar.setPosition(0, -20);

	//Boss Seeds
	Seed seeds[10];

	for (size_t i = 0; i < 10; i++)
	{
		seeds[i].S.setPosition(BadApple.getPosition());
		seeds[i].setSeed(5.f, Color::Black);
		seeds[i].S.setOrigin(3.5, 3.5);
	}

	float SeedX = 0.4;
	float SeedY = 0.7;
	float speedx = 20;
	float speedy = -30;



	bool alive = true;
	bool attack = false;
	bool celebrate = false;
	bool bossdeath = false;


	//gravity
	double boss_gravity = 0.6; // for the boss
	double  gravityP = 1.5; // for projectiles
	float gravityDelay = 0;

	int dir = 0;

	// pause texture:
	Texture Backgroundpause;
	Backgroundpause.loadFromFile("pause_background.png");
	Sprite bkgp(Backgroundpause);
	bkgp.setScale(1, 0.75);
	bkgp.setPosition(window.getPosition().x + 200, window.getPosition().y);

	Snake.current_health = end_of_level_health;

	// text at the end of the level
	Font font;
	font.loadFromFile("RetroGrade.otf");

	Text end;
	end.setFont(font);
	end.setCharacterSize(72);
	end.setPosition(100, 100);

	int seeds_timer = 0;

	// sounds
	// main loop:
	Music lop;
	lop.openFromFile("l3.wav");
	lop.play();
	lop.setLoop(true);
	int vol = lop.getVolume();
	//jump
	SoundBuffer Buffer1; Buffer1.loadFromFile("jump.wav");
	Sound jump; jump.setBuffer(Buffer1); jump.setVolume(100);
	//damage
	SoundBuffer Buffer2; Buffer2.loadFromFile("damage.wav");
	Sound damage; damage.setBuffer(Buffer2); damage.setVolume(100);
	//attack
	SoundBuffer Buffer3; Buffer3.loadFromFile("attack.wav");
	Sound attacking; attacking.setBuffer(Buffer3); attacking.setVolume(100);
	//Hallelujah
	SoundBuffer Buffer4; Buffer4.loadFromFile("Hallelujah Chorus.wav");
	Sound Hallelujah; Hallelujah.setBuffer(Buffer4); Hallelujah.setVolume(100);

	//texture chest:
	Texture chestT;
	chestT.loadFromFile("chest.png");
	Sprite chest(chestT);
	chest.setTextureRect(IntRect(0, 0, 576 / 2, 360));
	chest.setPosition(500, 50);
	chest.setScale(0.5, .5);

	//tile texture:
	Texture tileT;
	tileT.loadFromFile("tile.png");
	Sprite shelf(tileT);
	shelf.setScale(2, 1);
	shelf.setPosition(500, 200);

	bool battle_started = false;

	while (window.isOpen()) {
		HitBox.setPosition(Snake.herosprite.getPosition().x, Snake.herosprite.getPosition().y + 37);
		while (window.pollEvent(evento)) {
			if (evento.type == Event::Closed)
				window.close();

			if (Keyboard::isKeyPressed(Keyboard::Space) && !celebrate) // # ATTACKING ANIMATION #
			{
				Animator = 0;
				attack = true;
			}
			if (Snake.current_health >= 5)
			{
				Animator = 0;
				alive = false;
			}

			if (!battle_started) {
				BadApple.setPosition(1200, 380);
				BadApple.setTextureRect(IntRect(320 * 7, 0, 320, 320));
			}
			else {
				BadApple.setTextureRect(IntRect(320 * BigBossHealth, 0, 320, 320));
			}

			if (Keyboard::isKeyPressed(Keyboard::P))
				wait = true;

			if (wait == true) {
				if (evento.type == Event::KeyPressed) {
					if (evento.key.code == Keyboard::Up) {
						pause.MoveUpP();
					}
					if (evento.key.code == Keyboard::Down) {
						pause.MoveDownP();
					}
					if (evento.key.code == Keyboard::Return) {
						// 0 -> continue 1 -> main menu
						if (pause.pressedP() == 0) wait = false;
						if (pause.pressedP() == 1) pagenum = 1;
					}
					if (evento.key.code == Keyboard::U) {
						vol -= 20;
						lop.setVolume(vol);
					}
					if (evento.key.code == Keyboard::D) {
						vol += 20;
						lop.setVolume(vol);
					}
				}
			}
		}

		if (Snake.current_health < 6)
			bar.setTextureRect(IntRect((Snake.current_health * float(1639 / 6)), 0, float(1639 / 6), 400));
		if (HitBox.getGlobalBounds().left >= 450)
			battle_started = true;
		//update
		if (alive && !wait) {
			if (alive) {
				// testing idle animation
				if (Snakevelocity.x == 0 && Snakevelocity.y == 0)
				{
					if (AnimatorDelay < 10)
						AnimatorDelay++;
					if (AnimatorDelay >= 10) {
						AnimatorDelay = 0;
						Animator++;
						Animator %= 10;
						if (!attack && !celebrate)
							Snake.herosprite.setTextureRect(IntRect(32 * Animator, 0, 32, 36));
					}

				}
				//testing walk animation
				if (Keyboard::isKeyPressed(Keyboard::Right) && !celebrate) // # MOVING RIGHT # 
				{
					if (AnimatorDelay < 5)
					{
						AnimatorDelay++;
					}
					if (AnimatorDelay >= 5) {
						AnimatorDelay = 0;

						Animator %= 10;
						if (!attack && !celebrate)
							Snake.herosprite.setTextureRect(IntRect(32 * Animator, 64, 32, 36));
						Animator++;
					}
					Snake.herosprite.setScale(-5, 5);
					Snakevelocity.x = 5.f;

				}
				else if (Keyboard::isKeyPressed(Keyboard::Left) && !celebrate) // # MOVING LEFT # 
				{

					if (AnimatorDelay < 5)
					{
						AnimatorDelay++;
					}
					if (AnimatorDelay >= 5) {
						AnimatorDelay = 0;

						Animator %= 10;
						if (!attack && !celebrate)
							Snake.herosprite.setTextureRect(IntRect(32 * Animator, 64, 32, 36));
						Animator++;
					}
					Snake.herosprite.setScale(5, 5);
					Snakevelocity.x = -5.f;
				}
				else
					Snakevelocity.x = 0.f;

				// attack animation
				if (attack && !celebrate)
				{
					if (AnimatorDelay < 5)
					{
						AnimatorDelay++;
					}
					if (AnimatorDelay >= 5) {
						AnimatorDelay = 0;

						Animator %= 10;
						Snake.herosprite.setTextureRect(IntRect(32 * Animator, 96, 32, 36));
						Animator++;
						attacking.play();

					}
				}

				// edeha e7tfal 
				if (!attack && celebrate)
				{
					if (AnimatorDelay < 10)
					{
						AnimatorDelay++;
					}
					if (AnimatorDelay >= 10) {
						AnimatorDelay = 0;

						Animator %= 10;
						Snake.herosprite.setTextureRect(IntRect(32 * Animator, 32, 32, 36));
						Animator++;

					}
				}

				// resuming to idle
				if (Animator == 10) {
					attack = false;
					celebrate = false;
				}

				//#SNAKE JUMPING , GRAVITY AND GROUNDING
				if (Snake.herosprite.getGlobalBounds().intersects(land.getGlobalBounds()))
				{
					Snakevelocity.y = 0;
					if (Keyboard::isKeyPressed(Keyboard::Up) && !celebrate)
					{
						if (!attack && !celebrate)
							Snake.herosprite.setTextureRect(IntRect(IntRect(32 * 2, 128, 32, 36)));
						Snakevelocity.y = -20.f;
						jump.play();
					}
				}
				else
					Snakevelocity.y += gravity;
			}
			if (alive == false && Animator <= 9) {
				if (AnimatorDelay < 5)
				{
					AnimatorDelay++;
				}
				if (AnimatorDelay >= 5) {
					AnimatorDelay = 0;

					Snake.herosprite.setTextureRect(IntRect(32 * Animator, 128, 32, 36));
					Animator++;
				}
			}

			// #THE GROW SO FAST...NOW HE IS MOVING#
			if (alive && !celebrate)
				Snake.herosprite.move(Snakevelocity);

		}
		if(alive && !wait && battle_started)
		{
			//for (int i = 0; i <= 9; i++)// random variable vector
			//{
			//	bool diff = 1;
			//	int x = rand() % 10 + 1;
			//	if (seeds[i].S.getPosition() == BadApple.getPosition())
			//	{
			//		for (int j = 0; j <= i; j++)
			//		{
			//			if (x == v[j])
			//			{
			//				diff = 0;
			//			}
			//		}
			//		if (!diff)
			//			i--;
			//		else
			//		{
			//			v[i] = x;
			//		}
			//	}
			//	std::cout << v[i] << "\n";
			//}
			
			for (size_t i = 0; i < 10; i++)
			{
				if (seeds[i].S.getGlobalBounds().intersects(land.getGlobalBounds())) {

					seeds[i].S.setPosition(BadApple.getPosition());
					seeds[i].seedSpeed = { SeedX, -SeedY * ( 1+ rand() % 5)  /*v[i]*/};

				}
				if (seeds_timer < 8) seeds_timer++;
				else {
					seeds_timer = 0;
					if (!seeds[i].S.getGlobalBounds().intersects(land.getGlobalBounds())) {
						if (gravityDelay < 1)
							gravityDelay++;
						if (gravityDelay >= 1)
						{
							gravityDelay = 0;
							seeds[i].seedSpeed.y += gravityP;
						}

					}
				}
				seeds[i].S.move(seeds[i].seedSpeed);
			}

			if (Snake.herosprite.getPosition().x < BadApple.getPosition().x)
				SeedX = -15;
			else if (Snake.herosprite.getPosition().x > BadApple.getPosition().x)
				SeedX = 15;

			//test damage

			// player damage
			for (int i = 0; i < 10; i++) {
				if (seeds[i].S.getGlobalBounds().intersects(HitBox.getGlobalBounds())) {

					seeds[i].S.setPosition(BadApple.getPosition());
					Snake.current_health++;
					damage.play();

				}
			}
			//boss damage
			if (HitBox.getGlobalBounds().intersects(BadApple.getGlobalBounds()) && attack && Animator == 5)
			{
				attack = false;
				Animator = 0;
				celebrate = true;
				BigBossHealth--;
				speedx = 14;
				speedy = -18;
				if (BigBossHealth % 2 == 0)
					BadApple.move(speedx, speedy);
				else
					BadApple.move(-speedx, speedy);


				BadApple.setTextureRect(IntRect(320 * BigBossHealth, 0, 320, 320));

			}

			// resuming to idle
			if (Animator == 10) {
				attack = false;
				celebrate = false;
			}

			if (BigBossHealth == 0) {
				bossdeath = true;
				SeedX = 0;
				SeedY = 0;
			}

			if (BigBossHealth % 2 == 0 && BigBossHealth != 6)
			{
				BadApple.move(speedx, speedy);
			}

			if (BigBossHealth % 2 == 1)
			{
				BadApple.move(-speedx, speedy);
			}

			if (!BadApple.getGlobalBounds().intersects(land.getGlobalBounds()))
			{
				speedy += boss_gravity;
				BadApple.move(0, speedy);
			}

			if (BadApple.getGlobalBounds().intersects(land.getGlobalBounds()))
			{
				speedx = 0;
				speedy = 0;
			}
		}

		// death animation:
		if (alive == false && Animator <= 9) {
			if (AnimatorDelay < 5)
			{
				AnimatorDelay++;
			}
			if (AnimatorDelay >= 5) {
				AnimatorDelay = 0;

				Snake.herosprite.setTextureRect(IntRect(32 * Animator, 128, 32, 36));
				Animator++;

			}
		}
		// draw
		window.clear(Color::White);
		window.draw(bkg);
		window.draw(chest);
		window.draw(shelf);
		window.draw(Snake.herosprite);
		window.draw(HitBox);
		window.draw(land);
		if (!bossdeath) {
			for (size_t i = 0; i < 10; i++)
			{
				window.draw(seeds[i].S);
			}
			window.draw(BadApple);
		}
		if (bossdeath) {
			//sounds:
			lop.stop();

			//boss death
			death.setPosition(BadApple.getPosition());
			window.draw(death);

			// finally:
			shelf.setScale(0, 0);
			chest.setTextureRect(IntRect((576 / 2), 0, 576 / 2, 360));
			if (chest.getPosition().y <= 400) {
				Hallelujah.play();
				chest.setPosition(chest.getPosition().x, chest.getPosition().y + gravity);
			}

			if (HitBox.getGlobalBounds().intersects(chest.getGlobalBounds())) {
				// level completed text
				end.setString("Level Completed");
				end.setFillColor(Color::White);
				end.setScale(1, 1);

				if (Keyboard::isKeyPressed(Keyboard::Enter)) {
					pagenum = 8;
				}
			}
		}
		if (!alive) {
			// game over text:
			end.setString("Game Over");
			end.setFillColor(Color::Red);
			end.setScale(1, 1);
			//window.draw(end);
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				pagenum = 1;
			}
		}
		window.draw(end);
		window.draw(bar);
		if (wait == true) {
			window.draw(bkgp);
			pause.drawP(window);
		}
		score += (6 - BigBossHealth) * 200;
		savename(name, score);
		if (pagenum != 7) {
			break;
			lop.stop();
		}
		window.display();
	}
}

void outro(RenderWindow& window) {
	window.setFramerateLimit(60);
	Event evento;

	//background
	Texture backgroundT;
	backgroundT.loadFromFile("bkg.png");
	Sprite back(backgroundT);
	back.setScale(1.5, 1);

	// snake:
	Texture snakeT;
	snakeT.loadFromFile("snaky.png");

	Sprite snaky[4];
	for (size_t i = 0; i < 4; i++) {
		snaky[i].setTexture(snakeT);
		snaky[i].setOrigin(32.f / 2, 36.f / 2);
		snaky[i].setTextureRect(IntRect(0, 0, 32, 36));
	}
	snaky[0].setPosition(1000, 400); // Mama snake
	snaky[0].setScale(15, 15);

	snaky[1].setPosition(900, 550); // baby snake #1
	snaky[1].setScale(8, 8);
	snaky[2].setPosition(1100, 500); // baby snake #2
	snaky[2].setScale(10, 10);

	snaky[3].setPosition(0, 450);	 // Baba snake
	snaky[3].setScale(-15, 15);

	int AnimatorDelay = 0;
	int Animator = 0;
	int Animatordelay = 0;
	int animator = 0;
	int animatordelay = 0;
	int ANIMATOR = 0;
	int ANIMATORDELAY = 0;
	int aNiMaToR = 0;
	int gravity = 1;
	Vector2f Snakevelocity = Vector2f(0.f, 0.f);

	// boss:
	Texture bossT;
	bossT.loadFromFile("golden apple.png");
	Sprite boss(bossT);
	boss.setPosition(-60, 540);

	// texts:
	Font font;
	font.loadFromFile("RetroGrade.otf");

	Text out;
	out.setFont(font);
	out.setString("Our journey ends here!");
	out.setPosition(400, 600);
	out.setCharacterSize(50);

	Text game_name;
	game_name.setFont(font);
	game_name.setString("Snake:Apple Quest");
	game_name.setPosition(450, 650);
	game_name.setCharacterSize(50);

	Text names;
	names.setFont(font);
	names.setString("Developers of the game:");
	names.setPosition(400, 800);
	names.setCharacterSize(50);

	Text leader;
	leader.setFont(font);
	leader.setString("David Magdy");
	leader.setPosition(470, 850);
	leader.setCharacterSize(50);

	Text mem1;
	mem1.setFont(font);
	mem1.setString("Youstina Mitsho");
	mem1.setPosition(470, 900);
	mem1.setCharacterSize(50);

	Text mem2;
	mem2.setFont(font);
	mem2.setString("Mario Maged");
	mem2.setPosition(470, 950);
	mem2.setCharacterSize(50);

	Text mem3;
	mem3.setFont(font);
	mem3.setString("Christine Medhat");
	mem3.setPosition(470, 1000);
	mem3.setCharacterSize(50);

	Text mem4;
	mem4.setFont(font);
	mem4.setString("Michael Nabil");
	mem4.setPosition(470, 1050);
	mem4.setCharacterSize(50);

	Text mem5;
	mem5.setFont(font);
	mem5.setString("Marvel Medhat");
	mem5.setPosition(470, 1100);
	mem5.setCharacterSize(50);

	Text mem6;
	mem6.setFont(font);
	mem6.setString("Kerolos Magdy");
	mem6.setPosition(470, 1150);
	mem6.setCharacterSize(50);

	Text col;
	col.setFont(font);
	col.setString("Faculty of computer and information Sciences");
	col.setPosition(125, 1300);
	col.setCharacterSize(50);

	Text finaly;
	finaly.setFont(font);
	finaly.setString("SP project May 2023");
	finaly.setPosition(400, 1350);
	finaly.setCharacterSize(50);

	int keypause = 0;
	int bl = 0;

	// sounds
	Music lop;
	lop.openFromFile("outro.wav");
	lop.play();
	lop.setLoop(true);

	while (window.isOpen()) {
		keypause++;
		while (window.pollEvent(evento)) {
			if (evento.type == Event::Closed)
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::Enter) && keypause >= 20) {
				keypause = 0;
				bl = 1;
			}
		}
		// update:

		// Mama snake animation:
		if (Animatordelay < 10)
			Animatordelay++;
		if (Animatordelay >= 10)
		{
			Animatordelay = 0;

			animator++;
			animator %= 10;
			snaky[0].setTextureRect(IntRect(32 * animator, 0, 32, 36));
		}
		// Baba snake animation:

		if (snaky[3].getPosition().x <= 700) {
			if (AnimatorDelay < 5)
			{
				AnimatorDelay++;
			}
			if (AnimatorDelay >= 5) {
				AnimatorDelay = 0;

				Animator %= 10;
				snaky[3].setTextureRect(IntRect(32 * Animator, 64, 32, 36));
				Animator++;
			}
			Snakevelocity.x = 2;
			snaky[3].move(Snakevelocity);
			if (boss.getPosition().x <= 550)
				boss.move(Snakevelocity);
		}
		else {

			if (AnimatorDelay < 10)
				AnimatorDelay++;
			if (AnimatorDelay >= 10) {
				AnimatorDelay = 0;

				Animator++;
				Animator %= 10;
				snaky[3].setTextureRect(IntRect(32 * Animator, 0, 32, 36));
			}
		}

		// baby snake #1:

		if (ANIMATORDELAY < 5)
		{
			ANIMATORDELAY++;
		}
		if (ANIMATORDELAY >= 5) {
			ANIMATORDELAY = 0;

			aNiMaToR %= 10;
			snaky[1].setTextureRect(IntRect(32 * aNiMaToR, 96, 32, 36));
			aNiMaToR++;
		}
		// baby snake #2:
		if (animatordelay < 10)
		{
			animatordelay++;
		}
		if (animatordelay >= 10) {
			animatordelay = 0;

			ANIMATOR %= 10;
			snaky[2].setTextureRect(IntRect(32 * ANIMATOR, 32, 32, 36));
			ANIMATOR++;

		}

		// draw:
		window.clear();
		window.draw(back);
		for (size_t i = 0; i < 4; i++)
		{
			window.draw(snaky[i]);
		}
		window.draw(boss);
		if (bl == 1) {
			window.clear(Color::Black);
			window.draw(out);
			out.move(0, -0.5);
			window.draw(game_name);
			game_name.move(0, -0.5);
			window.draw(names);
			names.move(0, -0.5);
			window.draw(leader);
			leader.move(0, -0.5);
			window.draw(mem1);
			mem1.move(0, -0.5);
			window.draw(mem2);
			mem2.move(0, -0.5);
			window.draw(mem3);
			mem3.move(0, -0.5);
			window.draw(mem4);
			mem4.move(0, -0.5);
			window.draw(mem5);
			mem5.move(0, -0.5);
			window.draw(mem6);
			mem6.move(0, -0.5);
			window.draw(col);
			window.draw(finaly);
			if (col.getPosition().y <= 300) {
				col.move(0, 0);
				finaly.move(0, 0);
			}
			else {
				col.move(0, -0.5);
				finaly.move(0, -0.5);
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter) && keypause >= 5) {
				window.close();
			}
		}
		window.display();
	}
}
