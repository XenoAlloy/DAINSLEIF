# include <Siv3D.hpp>
# include "Scene.hpp"
# pragma once

class UI_Button
{
	Color textColor = { 0,0,0 };
	bool brightening = true;
	bool isCursored = false;
	String buttonText;
	Rect buttonArea;
	int brightnessChange = 5;
	Scene transitTo;

public:
	void draw();
	Scene update();

	UI_Button(String, Vec2, Scene);
	~UI_Button();
};

