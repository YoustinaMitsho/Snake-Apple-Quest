#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

struct Pause {
public:

	Text pausemenu[2];
	Pause(float width, float height);
	void drawP(RenderWindow& window);
	void MoveUpP();
	void MoveDownP();
	void setselectedP(int m);
	int pressedP() {
		return selectedP;
	}
	~Pause();

private:
	int selectedP;
	Font fontP;
};

