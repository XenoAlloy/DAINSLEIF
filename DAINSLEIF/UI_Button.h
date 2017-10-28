# include <Siv3D.hpp>
# pragma once

class UI_Button
{
	Color textColor = { 0,0,0 };
	bool brightening = true;
	bool isCursored = false;
	DrawableString buttonText;
	Rect buttonArea;
	int brightnessChange = 15;
	
public:
	void draw();
	void update();

	UI_Button(String,Vec2);
	~UI_Button();
};

