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
	int fadeAlpha = 255;

	// フォントファイルを一時的にインストール
	//失敗した場合プログラムを終了する
	if (!FontManager::Register(L"/1500")) {
		return;
	}
	if (!FontManager::Register(L"/1501")) {
		return;
	}
	if (!FontManager::Register(L"/1502")) {
		return;
	}
	if (!FontManager::Register(L"/1503")) {
		return;
	}

	//ゲーム中で使うフォントの用意
	for (int n = 40; n >= 10; n /= 2) {
		FontAsset::Register(L"overDrive" + ToString(n), n, L"GauFontOverDrive");
		FontAsset::Register(L"whiteBase" + ToString(n), n, L"GauFontWhiteBase");
		FontAsset::Register(L"migMixR" + ToString(n), n, L"MigMix 1M Regular");
		FontAsset::Register(L"migMixB" + ToString(n), n, L"MigMix 1M Bold");
	}
	FontAsset::Register(L"overDrive6", 6, L"GauFontOverDrive");

	//ゲーム中で使うサウンドの用意
	SoundAsset::Register(L"SE_Cursor", L"/3000");
	SoundAsset::Register(L"SE_Warning", L"/3020");
	SoundAsset::Register(L"SE_Death", L"/3021");
	SoundAsset::Register(L"BGM_Keybords Brawl Dance", L"/2000");
	SoundAsset::Register(L"BGM_Bustle of Ghosts", L"/2001");

	const Texture title(L"/1000");

	//メニュー関連
	const Rect rect(0, 0, 800, 600);
	const Rect menubar(0, 0, 800, 30);
	const Rect close(774, 4, 22, 22);
	bool menubarGrabbed = false;
	Point mousePos = Mouse::Pos();

	bool continueGame = true;

	Player player;
	GameManager::get_instance().enemies.push_back(
		Enemy({ 800, 100 }, { 4, 0 },
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

	//auto testCircle = Circle(Vec2(200, 200), 200);

	while (System::Update()) {
		void updateWindow(); {
			if (fadeAlpha > 0) {
				fadeAlpha -= 15;
			}
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
				continueGame = false;
			}
			else if (Input::MouseL.released) {
				// マウスのクリックが離されたら離す
				menubarGrabbed = false;
				continueGame = true;
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

			SoundAsset(L"BGM_Keybords Brawl Dance").setVolume(0.1);
			SoundAsset(L"BGM_Keybords Brawl Dance").play();
			title.draw(40, 100);

			FontAsset(L"whiteBase10")(L"ver.0.0.1").draw(600, 250 - FontAsset(L"whiteBase10").ascent, Color(0, 0, 0));
			FontAsset(L"migMixB20")(L"α").draw(720, 250 - FontAsset(L"migMixB20").ascent, Color(0, 0, 0));

			for (int n = 0; n < buttons.size(); n++) {
				auto newScene = buttons[n].update();
				if (newScene != Scene::None) {
					if (newScene == Scene::Stage) {
						player.reset();
					}
					SoundAsset(L"BGM_Keybords Brawl Dance").stop(1.0s);
					fadeAlpha = 255;
					gamemode = newScene;
				}
				buttons[n].draw();
			}




			break;
		}

		case Scene::Stage: {
			SoundAsset(L"BGM_Bustle of Ghosts").setVolume(0.1);
			SoundAsset(L"BGM_Bustle of Ghosts").play();
			void updateGame(); {
				if (continueGame) {
					//update_player
					player.update_UI();
					player.update();
					player.move();
					player.shot();
					//update_enemies
					for (auto& e : manager.enemies) {
						e.update();
						e.move();
						e.shot();
					}
					//update_bullets
					for (auto& b : manager.bullets) {
						b.update();
					}
					//check_collision
						/*	auto remove_ptr = std::remove_if(manager.bullets.begin(), manager.bullets.end(),
								[&testCircle](const Bullet& b) -> bool { return b.get_shape().intersects(testCircle); });
							manager.bullets.erase(remove_ptr, manager.bullets.end());
						*/
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
					if (player.killed()) {
						SoundAsset(L"BGM_Bustle of Ghosts").stop(2.0s);
						gamemode = Scene::Result;
					}
				}
				if (Input::KeyE.clicked) {
					continueGame = false;
				}
				if (!continueGame) {
					//ポーズ画面
				}
			}
			void drawGame(); {
				player.draw_UI();
				player.draw();
				for (auto& e : manager.enemies) {
					e.draw();
				}
				for (auto& b : manager.bullets) {
					b.draw();
				}
				//				testCircle.draw(Color(255, 0, 0, 80));
			}
			break;
		}

		case Scene::Result: {

		}

		case Scene::Credits: {
			FontAsset(L"migMixR20")(L"DAINSLEIF\n企画 Xenon\n制作 Xenon いるやん\nBGM DIG\nSE Xenon\n\n\n\n\n\n\n\nTHANK YOU FOR PLAYING!!").draw(40, 40, Color(0, 0, 0));
			if (Input::MouseL.clicked) {
				fadeAlpha = 255;
				gamemode = Scene::Title;
			}
			break;
		}

		case Scene::Exit: {
			return;
		}
		}
		void drawWindowFrame(); {
			Rect(0, 0, 800, 600).draw(Color(255, 255, 255, fadeAlpha));
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