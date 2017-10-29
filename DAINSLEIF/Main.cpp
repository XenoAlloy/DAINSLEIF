# include <Siv3D.hpp>
# include "Scene.hpp"
# include "UI_Button.h"
# include "Player.h"
# include "Enemy.h"
# include "MovePattern.hpp"
# include "GameManager.h"
void Main() {
	Window::SetTitle(L"DAINSLEIF");
	Window::Resize(800, 600);
	Window::SetStyle(WindowStyle::NonFrame);
	Scene gamemode = Scene::Title;
	Cursor::SetStyle(CursorStyle::None);
	Color cursorColor = Color(50, 205, 50, 210);

	// フォントファイルを一時的にインストール
	//失敗した場合プログラムを終了する
	if (!FontManager::Register(L"assets/font/GAU_Over_Drive.TTF")) {
		return;
	}
	if (!FontManager::Register(L"assets/font/GAU_White_Base.TTF")) {
		return;
	}
	if (!FontManager::Register(L"assets/font/migmix-1m-regular.ttf")) {
		return;
	}
	if (!FontManager::Register(L"assets/font/migmix-1m-bold.ttf")) {
		return;
	}

	//ゲーム中で使うフォントの用意
	for (int n = 40; n >= 10; n /= 2) {
		FontAsset::Register(L"migMixB" + ToString(n), n, L"MigMix 1M Bold");
		FontAsset::Register(L"migMixR" + ToString(n), n, L"MigMix 1M Regular");
		FontAsset::Register(L"overDrive" + ToString(n), n, L"GauFontOverDrive");
		FontAsset::Register(L"whiteBase" + ToString(n), n, L"GauFontWhiteBase");
	}

	//ゲーム中で使うサウンドの用意
	SoundAsset::Register(L"cursor", L"assets/se/Cursor.wav");

	const Texture title(L"assets/img/title.png");

	//メニュー関連
	const Rect rect(0, 0, 800, 600);
	const Rect menubar(0, 0, 800, 30);
	const Rect close(774, 4, 22, 22);
	bool menubarGrabbed = false;
	Point mousePos = Mouse::Pos();

	Player player;
	GameManager::get_instance().enemies.push_back(
		Enemy(
			MovePattern::chase<Enemy>(player.get_position())
		)
	);
	Array<UI_Button> buttons{
		{ L"GameStart", Vec2{ 80,320 }, Scene::Stage },

		{ L"Credit", Vec2{ 80,440 }, Scene::Credits },
		{ L"Exit", Vec2{ 80,500 }, Scene::Exit }
	};

	//GameManagerが一つであることの証明、毎回取らなくていいようにキープ
	GameManager&manager = GameManager::get_instance();

	auto testCircle = Circle(Vec2(200, 200), 200);

	while (System::Update()) {
		void updateWindow(); {
			//closeをクリックで閉じる
			if (close.leftClicked) {
				System::Exit();
			}
			//ウインドウの移動
			if (menubar.leftClicked) {
				// メニューをクリックしたらつかむ
				if (menubarGrabbed == false) {
					//メニューつかんでないときマウス座標更新
					mousePos = Mouse::Pos();

				}
				menubarGrabbed = true;

			}
			else if (Input::MouseL.released) {
				// マウスのクリックが離されたら離す
				menubarGrabbed = false;
			}
			else if (menubarGrabbed) {
				// つかんでいる間はマウスのポジションに
				Window::SetPos(Mouse::ScreenPos() - mousePos);
			}

		}
		void drawWindow(); {
			rect.draw(Color(255, 255, 255));
		}
		switch (gamemode) {
		case Scene::Title: {

			title.draw(40, 100);

			FontAsset(L"whiteBase10")(L"ver.0.0.1").draw(600, 250 - FontAsset(L"whiteBase10").ascent, Color(0, 0, 0));
			FontAsset(L"migMixB20")(L"α").draw(720, 250 - FontAsset(L"migMixB20").ascent, Color(0, 0, 0));

			for (int n = 0; n < buttons.size(); n++) {
				auto newScene = buttons[n].update();
				if (newScene != Scene::None) {
					gamemode = newScene;
				}
				buttons[n].draw();
			}




			break;

		}

		case Scene::Stage: {
			void updateGame(); {


				if (menubarGrabbed == false) {
					void updateEnemy(); {
						for (auto& e : manager.enemies) {
							e.update();
							e.move();
							e.shot();
						}
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
						//auto remove_ptr = std::remove_if(manager.bullets.begin(), manager.bullets.end(),
						//	[&testCircle](const Bullet& b) -> bool { return b.get_shape().intersects(testCircle); });
						//manager.bullets.erase(remove_ptr, manager.bullets.end());
						for (auto& e : manager.enemies) {
							if (e.get_shape().intersects(player.get_shape())) {
								player.damaged(e.get_power());
								e.damaged(player.get_power());
							}
							for (auto& b : manager.bullets) {
								if (b.get_shape().intersects(e.get_shape())) {
									e.damaged(b.get_power());
									b.damaged();
								}
							}
						}
						{auto remove_ptr = std::remove_if(manager.bullets.begin(), manager.bullets.end(),
							[](const Bullet& b) -> bool { return b.killed(); });
						manager.bullets.erase(remove_ptr, manager.bullets.end());
						}
						{auto remove_ptr = std::remove_if(manager.enemies.begin(), manager.enemies.end(),
							[](const Enemy& e) -> bool { return e.killed(); });
						manager.enemies.erase(remove_ptr, manager.enemies.end());
						}
					}
				}

			}
			void drawGame(); {
				void drawEnemy(); {
					for (auto& e : manager.enemies) {
						e.draw();
					}
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

		case Scene::Exit: {
			return;
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

			FontAsset(L"migMixR10")(player.get_position()).draw();
		}

		void drawMouseCursor(); {
			Circle(Mouse::Pos(), 16).drawFrame(1, 1, cursorColor);
			Line(Mouse::Pos() + Point(-24, 0), Mouse::Pos() + Point(24, 0)).draw(2, cursorColor);
			Line(Mouse::Pos() + Point(0, -24), Mouse::Pos() + Point(0, 24)).draw(2, cursorColor);
		}
	}
}