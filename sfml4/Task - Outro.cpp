//#include<SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <bits/stdc++.h>
//
//using namespace sf;
//
//void outro(RenderWindow& window);
//
//int main() {
//	RenderWindow window(VideoMode::getDesktopMode(), "game:");
//	window.setFramerateLimit(60);
//	Event evento;
//
//	//background
//	Texture backgroundT;
//	backgroundT.loadFromFile("bkg.png");
//	Sprite back(backgroundT);
//	back.setScale(1.5, 1);
//
//	 snake:
//	Texture snakeT;
//	snakeT.loadFromFile("snaky.png");
//
//	Sprite snaky[4];
//	for (size_t i = 0; i < 4; i++) {
//		snaky[i].setTexture(snakeT);
//		snaky[i].setOrigin(32.f / 2, 36.f / 2);
//		snaky[i].setTextureRect(IntRect(0, 0, 32, 36));
//	}
//	snaky[0].setPosition(1000, 400); // Mama snake
//	snaky[0].setScale(15, 15);
//
//	snaky[1].setPosition(900, 550); // baby snake #1
//	snaky[1].setScale(8, 8);
//	snaky[2].setPosition(1100, 500); // baby snake #2
//	snaky[2].setScale(10, 10);
//
//	snaky[3].setPosition(0, 450);	 // Baba snake
//	snaky[3].setScale(-15, 15);
//
//	int AnimatorDelay = 0;
//	int Animator = 0;
//	int Animatordelay = 0;
//	int animator = 0;
//	int animatordelay = 0;
//	int ANIMATOR = 0;
//	int ANIMATORDELAY = 0;
//	int aNiMaToR = 0;
//	int gravity = 1;
//	Vector2f Snakevelocity = Vector2f(0.f, 0.f);
//
//	 boss:
//	Texture bossT;
//	bossT.loadFromFile("boss_death.png");
//	Sprite boss(bossT);
//	boss.setPosition(-200, 540);
//
//	 texts:
//	Font font;
//	font.loadFromFile("RetroGrade.otf");
//
//	Text out;
//	out.setFont(font);
//	out.setString("Our journey ends here!");
//	out.setPosition(400, 600);
//	out.setCharacterSize(50);
//
//	Text game_name;
//	game_name.setFont(font);
//	game_name.setString("Snake:Apple Quest");
//	game_name.setPosition(450, 650);
//	game_name.setCharacterSize(50);
//
//	Text names;
//	names.setFont(font);
//	names.setString("Developers of the game:");
//	names.setPosition(400, 800);
//	names.setCharacterSize(50);
//
//	Text leader;
//	leader.setFont(font);
//	leader.setString("David Magdy");
//	leader.setPosition(470, 850);
//	leader.setCharacterSize(50);
//
//	Text mem1;
//	mem1.setFont(font);
//	mem1.setString("Youstina Mitsho");
//	mem1.setPosition(470, 900);
//	mem1.setCharacterSize(50);
//
//	Text mem2;
//	mem2.setFont(font);
//	mem2.setString("Mario Maged");
//	mem2.setPosition(470, 950);
//	mem2.setCharacterSize(50);
//
//	Text mem3;
//	mem3.setFont(font);
//	mem3.setString("Christine Medhat");
//	mem3.setPosition(470, 1000);
//	mem3.setCharacterSize(50);
//
//	Text mem4;
//	mem4.setFont(font);
//	mem4.setString("Micheal Nabil");
//	mem4.setPosition(470, 1050);
//	mem4.setCharacterSize(50);
//
//	Text mem5;
//	mem5.setFont(font);
//	mem5.setString("Marvel Medhat");
//	mem5.setPosition(470, 1100);
//	mem5.setCharacterSize(50);
//
//	Text mem6;
//	mem6.setFont(font);
//	mem6.setString("Kerolos Magdy");
//	mem6.setPosition(470, 1150);
//	mem6.setCharacterSize(50);
//
//	Text col;
//	col.setFont(font);
//	col.setString("Faculty of computer and information Sciences");
//	col.setPosition(125, 1300);
//	col.setCharacterSize(50);
//
//	Text finaly;
//	finaly.setFont(font);
//	finaly.setString("SP project May 2022");
//	finaly.setPosition(400, 1350);
//	finaly.setCharacterSize(50);
//
//	int keypause = 0;
//	int bl = 0;
//
//	while (window.isOpen()) {
//		keypause++;
//		while (window.pollEvent(evento)) {
//			if (evento.type == Event::Closed)
//				window.close();
//			if (Keyboard::isKeyPressed(Keyboard::Enter) && keypause >= 20) {
//				keypause = 0;
//				bl = 1;
//			}
//		}
//		 update:
//
//		 //Mama snake animation:
//		if (Animatordelay < 10)
//			Animatordelay++;
//		if (Animatordelay >= 10)
//		{
//			Animatordelay = 0;
//
//			animator++;
//			animator %= 10;
//			snaky[0].setTextureRect(IntRect(32 * animator, 0, 32, 36));
//		}
//		 //Baba snake animation:
//
//		if (snaky[3].getPosition().x <= 700) {
//			if (AnimatorDelay < 5)
//			{
//				AnimatorDelay++;
//			}
//			if (AnimatorDelay >= 5) {
//				AnimatorDelay = 0;
//
//				Animator %= 10;
//				snaky[3].setTextureRect(IntRect(32 * Animator, 64, 32, 36));
//				Animator++;
//			}
//			Snakevelocity.x = 2;
//			snaky[3].move(Snakevelocity);
//			if (boss.getPosition().x <= 500)
//				boss.move(Snakevelocity);
//		}
//		else {
//
//			if (AnimatorDelay < 10)
//				AnimatorDelay++;
//			if (AnimatorDelay >= 10) {
//				AnimatorDelay = 0;
//
//				Animator++;
//				Animator %= 10;
//				snaky[3].setTextureRect(IntRect(32 * Animator, 0, 32, 36));
//			}
//		}
//
//		// baby snake #1:
//
//		if (ANIMATORDELAY < 5)
//		{
//			ANIMATORDELAY++;
//		}
//		if (ANIMATORDELAY >= 5) {
//			ANIMATORDELAY = 0;
//
//			aNiMaToR %= 10;
//			snaky[1].setTextureRect(IntRect(32 * aNiMaToR, 96, 32, 36));
//			aNiMaToR++;
//		}
//		// baby snake #2:
//		if (animatordelay < 10)
//		{
//			animatordelay++;
//		}
//		if (animatordelay >= 10) {
//			animatordelay = 0;
//
//			ANIMATOR %= 10;
//			snaky[2].setTextureRect(IntRect(32 * ANIMATOR, 32, 32, 36));
//			ANIMATOR++;
//
//		}
//
//		 draw:
//		window.clear();
//		window.draw(back);
//		for (size_t i = 0; i < 4; i++)
//		{
//			window.draw(snaky[i]);
//		}
//		window.draw(boss);
//		if (bl == 1) {
//			window.clear(Color::Black);
//			window.draw(out);
//			out.move(0, -0.5);
//			window.draw(game_name);
//			game_name.move(0, -0.5);
//			window.draw(names);
//			names.move(0, -0.5);
//			window.draw(leader);
//			leader.move(0, -0.5);
//			window.draw(mem1);
//			mem1.move(0, -0.5);
//			window.draw(mem2);
//			mem2.move(0, -0.5);
//			window.draw(mem3);
//			mem3.move(0, -0.5);
//			window.draw(mem4);
//			mem4.move(0, -0.5);
//			window.draw(mem5);
//			mem5.move(0, -0.5);
//			window.draw(mem6);
//			mem6.move(0, -0.5);
//			window.draw(col);
//			window.draw(finaly);
//			if (col.getPosition().y <= 300) {
//				col.move(0, 0);
//				finaly.move(0, 0);
//			}
//			else {
//				col.move(0, -0.5);
//				finaly.move(0, -0.5);
//			}
//			if (Keyboard::isKeyPressed(Keyboard::Enter) && keypause >= 10) {
//				window.close();
//			}
//		}
//		window.display();
//	}
//}