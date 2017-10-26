# include <Siv3D.hpp>
# include "Scene.hpp"
# include "Player.h"
# include "Enemy.h"
# include "MovePattern.hpp"
# include "GameManager.h"
void Main()
{
	Window::SetTitle(L"DAINSLEIF");
	Window::Resize(800, 600);
	Window::SetStyle(WindowStyle::NonFrame);
	Scene gamemode = Scene::Title;


	// フォントファイルを一時的にインストール
	//失敗した場合プログラムを終了する
	if (!FontManager::Register(L"assets/font/GAU_Over_Drive.TTF"))
	{
		return;
	}
	if (!FontManager::Register(L"assets/font/GAU_White_Base.TTF"))
	{
		return;
	}
	if (!FontManager::Register(L"assets/font/migmix-1m-regular.ttf"))
	{
		return;
	}
	if (!FontManager::Register(L"assets/font/migmix-1m-bold.ttf"))
	{
		return;
	}


	//ゲーム中で使うフォントの用意
	const Font fontMin(14);
	const Font migMixB40(40, L"MigMix 1M Bold");
	const Font migMixB20(20, L"MigMix 1M Bold");
	const Font migMixB10(10, L"MigMix 1M Bold");
	const Font migMixR40(40, L"MigMix 1M Regular");
	const Font migMixR20(20, L"MigMix 1M Regular");
	const Font migMixR10(10, L"MigMix 1M Regular");
	const Font overDrive40(40, L"GauFontOverDrive");
	const Font overDrive20(20, L"GauFontOverDrive");
	const Font overDrive10(10, L"GauFontOverDrive");
	const Font whiteBase40(40, L"GauFontWhiteBase");
	const Font whiteBase20(20, L"GauFontWhiteBase");
	const Font whiteBase10(10, L"GauFontWhiteBase");


	const Texture title(L"assets/img/title.png");
	const Rect gameStart = overDrive20(L"Game Start").region(80, 320);
	const Rect credits = overDrive20(L"Credits").region(80, 440);
	const Rect exit = overDrive20(L"Exit").region(80, 500);

	int textAlpha_0 = 255;
	int textAlpha_2 = 255;
	int textAlpha_3 = 255;
	bool isTextAlpha_0 = true;
	bool isTextAlpha_2 = true;
	bool isTextAlpha_3 = true;


	//メニュー関連
	const Rect rect(0, 0, 800, 600);
	const Rect menubar(0, 0, 800, 30);
	const Rect close(774, 4, 22, 22);
	bool menubarGrabbed = false;
	Point mousePos = Mouse::Pos();

	Player player;
	Enemy enemy(MovePattern ::chase<Enemy>(player.get_position()));

	//GameManagerが一つであることの証明、毎回取らなくていいようにキープ
	GameManager&manager = GameManager::get_instance();

	auto testCircle = Circle(Vec2(200, 200), 200);

	while (System::Update())
	{
		void updateWindow(); {
			//closeをクリックで閉じる
			if (close.leftClicked)
			{
				System::Exit();
			}
			//ウインドウの移動
			if (menubar.leftClicked)
			{
				// メニューをクリックしたらつかむ
				if (menubarGrabbed == false)
				{
					//メニューつかんでないときマウス座標更新
					mousePos = Mouse::Pos();

				}
				menubarGrabbed = true;

			}
			else if (Input::MouseL.released)
			{
				// マウスのクリックが離されたら離す
				menubarGrabbed = false;
			}
			else if (menubarGrabbed)
			{
				// つかんでいる間はマウスのポジションに
				Window::SetPos(Mouse::ScreenPos() - mousePos);
			}

		}
		void drawWindow(); {
			rect.draw(Color(255, 255, 255));
		}
		switch (gamemode)
		{
		case Scene::Title: {

				title.draw(40,100);

				whiteBase10(L"ver.0.0.1").draw(600, 250 - whiteBase10.ascent, Color(0, 0, 0));
				migMixB20(L"α").draw(720, 250 - migMixB20.ascent, Color(0, 0, 0));

				gameStart.draw(Color(0, 0, 0, 0));
				overDrive20(L"Game Start").draw(80, 320, Color(0, 0, 0, textAlpha_0));
				credits.draw(Color(0, 0, 0, 0));
				overDrive20(L"Credits").draw(80, 440, Color(0, 0, 0, textAlpha_2));
				exit.draw(Color(0, 0, 0, 0));
				overDrive20(L"Exit").draw(80, 500, Color(0, 0, 0, textAlpha_3));

				const bool isMouse_0 = gameStart.mouseOver;
				const bool isMouse_2 = credits.mouseOver;
				const bool isMouse_3 = exit.mouseOver;

				if(isMouse_0){
					if (textAlpha_0 >= 255) {
						isTextAlpha_0 = true;
					}
					else if (textAlpha_0 <= 100) {
						isTextAlpha_0 = false;
					}
					if (isTextAlpha_0 == true) {
						textAlpha_0 -= 5;
					}
					else if (isTextAlpha_0 == false) {
						textAlpha_0 += 5;
					}
				}
				else if(! isMouse_0){
					if (textAlpha_0 < 255) {
						textAlpha_0 += 5;
					}
					if (textAlpha_0 >= 255) {
						isTextAlpha_0 = true;
					}
				}
				if (isMouse_2) {
					if (textAlpha_2 >= 255) {
						isTextAlpha_2 = true;
					}
					else if (textAlpha_2 <= 100) {
						isTextAlpha_2 = false;
					}
					if (isTextAlpha_2 == true) {
						textAlpha_2 -= 5;
					}
					else if (isTextAlpha_2 == false) {
						textAlpha_2 += 5;
					}
				}
				else if (!isMouse_2) {
					if (textAlpha_2 < 255) {
						textAlpha_2 += 5;
					}
					if (textAlpha_2 >= 255) {
						isTextAlpha_2 = true;
					}
				}
				if (isMouse_3) {
					if (textAlpha_3 >= 255) {
						isTextAlpha_3 = true;
					}
					else if (textAlpha_3 <= 100) {
						isTextAlpha_3 = false;
					}
					if (isTextAlpha_3 == true) {
						textAlpha_3 -= 5;
					}
					else if (isTextAlpha_3 == false) {
						textAlpha_3 += 5;
					}
				}
				else if (!isMouse_3) {
					if (textAlpha_3 < 255) {
						textAlpha_3 += 5;
					}
					if (textAlpha_3 >= 255) {
						isTextAlpha_3 = true;
					}
				}
				

			break;

		}
		case Scene::Stage:{

			void updateGame(); {


				if (menubarGrabbed == false) {
					void updateEnemy(); {
						enemy.update();
						enemy.move();
						enemy.shot();
					}
					void updatePlayer(); {
						player.update();
						player.move();
						player.shot();
					}
					void updateEneBullet(); {
					}
					void updatePlaBullet(); {
						for (auto& b : manager.bullets) {
							b.update();
						}
					}

					void checkcollision(); {
						auto remove_ptr = std::remove_if(manager.bullets.begin(), manager.bullets.end(),
							[&testCircle](const Bullet& b) -> bool
						{ return b.get_shape().intersects(testCircle); });
						manager.bullets.erase(remove_ptr, manager.bullets.end());
					}
				}

			}
			void drawGame(); {
				void drawEnemy(); {
					enemy.draw();
				}
				void drawPlayer(); {
					player.draw();
				}
				void drawEneBullet(); {
				}
				void drawPlaBullet(); {
					for (auto& b : manager.bullets) {
						b.draw();
					}
				}

				testCircle.draw(Color(255, 0, 0, 80));
				break;

			}
			}
		}
		void drawWindowFrame(); {
			rect.drawFrame(30, 0, Color(0, 0, 0));

			if (menubarGrabbed == true) {
				rect.draw(Color(0, 0, 0, 200));
			}
			menubar.draw(Color(0, 0, 0));
			//fontMin(L"DAINSLEIF").draw(8, 4);
			close.draw(Color(0, 0, 0));
			Line(778, 8, 792, 22).draw(2);
			Line(792, 8, 778, 22).draw(2);

			fontMin(player.get_position()).draw();
		}
	}
}