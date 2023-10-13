#include "menu.h"
#include <SFML/Graphics.hpp>
using namespace sf;

Menu::Menu(float width, float height) {
	font.loadFromFile("RetroGrade.otf");

	mainmenu[0].setFont(font);
	mainmenu[0].setFillColor(Color::White);
	mainmenu[0].setString("New Game");
	mainmenu[0].setCharacterSize(86);
	mainmenu[0].setPosition(Vector2f(width / 2 + 160, height / (4) + 100));

	mainmenu[1].setFont(font);
	mainmenu[1].setFillColor(Color::White);
	mainmenu[1].setString("Score board");
	mainmenu[1].setCharacterSize(86);
	mainmenu[1].setPosition(Vector2f(width / 2 + 160, height / (4) + 175));

	mainmenu[2].setFont(font);
	mainmenu[2].setFillColor(Color::White);
	mainmenu[2].setString("How To Play");
	mainmenu[2].setCharacterSize(75);
	mainmenu[2].setPosition(Vector2f(width / 2 + 160, height / (4) + 250));

	mainmenu[3].setFont(font);
	mainmenu[3].setFillColor(Color::White);
	mainmenu[3].setString("Exit");
	mainmenu[3].setCharacterSize(86);
	mainmenu[3].setPosition(Vector2f(width / 2 + 160, height / (4) + 325));

	selected = 0;
}
Menu::~Menu() {}
void Menu::setselected(int n) {
	selected = n;
}
void Menu::draw(RenderWindow& window) {
	for (int i = 0; i < 4; i++ ) {
		window.draw(mainmenu[i]);
	}
}
void Menu::MoveDown() {
	if (selected + 1 <= 4) // not exit
	{
	mainmenu[selected].setFillColor(Color::White);
	selected++;
	if (selected == 4) {
		selected = 0;
	}
	mainmenu[selected].setFillColor(Color{ 255, 204, 0 });
	}
}
void Menu::MoveUp() {

	if (selected - 1 >= -1) // not play
	{
		mainmenu[selected].setFillColor(Color::White);
		selected--;
		if (selected == -1) {
			selected = 3;
		}
		mainmenu[selected].setFillColor(Color{ 255, 204, 0 });
	}
}