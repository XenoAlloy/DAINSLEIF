# include "UI_Button.h"

UI_Button::UI_Button(String text, Vec2 position, Scene scene)
	:buttonText(text)
	, buttonArea(FontAsset(L"overDrive20")(text).region(position))
	, transitTo(scene) {
}
UI_Button::~UI_Button() {
}

Scene UI_Button::update() {
	if (buttonArea.mouseOver) {
		if (!isCursored) {
			SoundAsset(L"SE_Cursor").playMulti();
			textColor.setRGB(255);
			isCursored = true;
		}
		if (textColor.r <= 0 || 255 <= textColor.r) {
			brightnessChange *= -1;
		}
		if (Input::MouseL.clicked) {
			return transitTo;
		}
	}
	else {
		isCursored = false;
		brightnessChange = -abs(brightnessChange);
	}
	textColor.setRGB(Clamp(static_cast<int>(textColor.r) + brightnessChange, 0, 255));
	return Scene::None;
}

void UI_Button::draw() {
	FontAsset(L"overDrive20")(buttonText).draw(buttonArea.pos, textColor);
}
