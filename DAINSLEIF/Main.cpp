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
	Cursor::SetStyle(CursorStyle::None);
	Color cursorColor = Color(50,205,50,210);

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


	const Sound cursor(L"assets/se/Cursor.wav");


	const Texture title(L"assets/img/title.png");
	const Rect gameStart = overDrive20(L"Game Start").region(80, 320);
	const Rect credits = overDrive20(L"Credits").region(80, 440);
	const Rect exit = overDrive20(L"Exit").region(80, 500);


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

				void Cursor_0(); {
					static int textAlpha = 255;
					static bool isTextAlpha = true;
					static bool isCursored = false;
					gameStart.draw(Color(0, 0, 0, 0));
					overDrive20(L"Game Start").draw(80, 320, Color(0, 0, 0, textAlpha));
					const bool isMouse = gameStart.mouseOver;
					if (isMouse)
					{
						if (! isCursored)
						{
							cursor.playMulti();
							textAlpha = 100;
							isCursored = true;
						}
						if (textAlpha >= 255)
						{
							isTextAlpha = true;
						}
						else if (textAlpha <= 100)
						{
							isTextAlpha = false;
						}
						if (isTextAlpha == true)
						{
							textAlpha -= 5;
						}
						else
						{
							textAlpha += 5;
						}
						if (Input::MouseL.clicked)
						{
							gamemode = Scene::Stage;
						}
					}
					else
					{
						isCursored = false;
						if (textAlpha < 255)
						{
							textAlpha += 5;
						}
						else
						{
							isTextAlpha = true;
						}
					}
				}
				void Cursor_1();{}
				void Cursor_2(); {
					static int textAlpha = 255;
					static bool isTextAlpha = true;
					static bool isCursored = false;
					credits.draw(Color(0, 0, 0, 0));
					overDrive20(L"Credits").draw(80, 440, Color(0, 0, 0, textAlpha));
					const bool isMouse = credits.mouseOver;
					if (isMouse)
					{
						if (!isCursored)
						{
							cursor.playMulti();
							textAlpha = 100;
							isCursored = true;
						}
						if (textAlpha >= 255)
						{
							isTextAlpha = true;
						}
						else if (textAlpha <= 100)
						{
							isTextAlpha = false;
						}
						if (isTextAlpha == true)
						{
							textAlpha -= 5;
						}
						else
						{
							textAlpha += 5;
						}
						if (Input::MouseL.clicked)
						{
							gamemode = Scene::Credits;
						}
					}
					else
					{
						isCursored = false;
						if (textAlpha < 255)
						{
							textAlpha += 5;
						}
						else
						{
							isTextAlpha = true;
						}
					}
				}
				void Cursor_3(); {
					static int textAlpha = 255;
					static bool isTextAlpha = true;
					static bool isCursored = false;
					exit.draw(Color(0, 0, 0, 0));
					overDrive20(L"Exit").draw(80, 500, Color(0, 0, 0, textAlpha));
					const bool isMouse = exit.mouseOver;
					if (isMouse)
					{
						if (!isCursored)
						{
							cursor.playMulti();
							textAlpha = 100;
							isCursored = true;
						}
						if (textAlpha >= 255)
						{
							isTextAlpha = true;
						}
						else if (textAlpha <= 100)
						{
							isTextAlpha = false;
						}
						if (isTextAlpha == true)
						{
							textAlpha -= 5;
						}
						else
						{
							textAlpha += 5;
						}
						if (Input::MouseL.clicked)
						{
							return;
						}
					}
					else
					{
						isCursored = false;
						if (textAlpha < 255)
						{
							textAlpha += 5;
						}
						else
						{
							isTextAlpha = true;
						}
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

		case Scene::Credits: {


			break;
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

		void drawMouseCursor(); {
			Circle(Mouse::Pos(), 16).drawFrame(1, 1, cursorColor);
			Line(Mouse::Pos() + Point(-24, 0), Mouse::Pos() + Point(24, 0)).draw(2, cursorColor);
			Line(Mouse::Pos() + Point(0, -24), Mouse::Pos() + Point(0, 24)).draw(2, cursorColor);
		}
	}
}