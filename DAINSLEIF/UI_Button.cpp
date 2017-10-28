# include "UI_Button.h"

UI_Button::UI_Button(String text,Vec2 position)
	:buttonText(FontAsset(L"overDrive20")(text))
	,buttonArea(buttonText.region(position))
{
}
UI_Button::~UI_Button()
{
}

void UI_Button::update() {
	auto brightness = textColor.r;
	if (buttonArea.mouseOver)
	{
		if (!isCursored)
		{
			SoundAsset(L"cursor").playMulti();
			textColor.setRGB(255);
			isCursored = true;
		}
		if (brightness <= 0 || 255 <= brightness)
		{
			brightnessChange *= -1;
		}
		if (Input::MouseL.clicked)
		{
			return;
		}
	}
	else
	{
		isCursored = false;
		brightnessChange = abs(brightnessChange);
	}
	textColor.setRGB(brightness + brightnessChange);
}

void UI_Button::draw() {
	buttonText.draw(buttonArea.pos,textColor);
}
