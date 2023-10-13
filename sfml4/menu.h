#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
struct Menu {
public:

	Text mainmenu[4]; // intro, main menu, credit, how to play, top score, saved
	Menu(float width, float height);
	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void setselected(int n);
	int pressed() {
		return selected;
	}
	~Menu();

private:
	int selected;
	Font font;
};