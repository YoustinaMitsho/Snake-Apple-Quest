#include "pause.h"
#include <SFML/Graphics.hpp>
using namespace sf;

Pause::Pause(float width, float height) {
	fontP.loadFromFile("RetroGrade.otf");

	pausemenu[0].setFont(fontP);
	pausemenu[0].setFillColor(Color::White);
	pausemenu[0].setString("Continue");
	pausemenu[0].setCharacterSize(72);
	pausemenu[0].setPosition(Vector2f(width / 2 - 18, height / (4) + 55));

	pausemenu[1].setFont(fontP);
	pausemenu[1].setFillColor(Color::White);
	pausemenu[1].setString("Main Menu");
	pausemenu[1].setCharacterSize(72);
	pausemenu[1].setPosition(Vector2f(width / 2 - 22, height / (4) + 200));


	selectedP = 0;
}
Pause::~Pause() {}

void Pause::setselectedP(int m) {
	selectedP = m;
}

void Pause::drawP(RenderWindow& window) {
	for (int i = 0; i < 2; i++) {
		window.draw(pausemenu[i]);
	}
}

void Pause::MoveDownP() {
	if (selectedP + 1 <= 2)
	{
		pausemenu[selectedP].setFillColor(Color::White);
		selectedP++;
		if (selectedP == 2) {
			selectedP = 0;
		}
		pausemenu[selectedP].setFillColor(Color{ 255, 204, 0 });
	}
}

void Pause::MoveUpP() {

	if (selectedP - 1 >= -1) 
	{
		pausemenu[selectedP].setFillColor(Color::White);
		selectedP--;
		if (selectedP == -1) {
			selectedP = 1;
		}
		pausemenu[selectedP].setFillColor(Color{ 255, 204, 0 });
	}
}

