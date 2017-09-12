﻿# include <Siv3D.hpp>
# include "Player.h"
# include "GameManager.h"
void Main()
{
	Window::SetTitle(L"DAINSLEIF");
	Window::Resize(800, 600);
	Window::SetStyle(WindowStyle::NonFrame);
	char Gamemode = 0;

	const Font fontMin(14);


	//メニュー関連
	const Rect rect(0, 0, 800, 600);
	const Rect menubar(0, 0, 800, 30);
	const Rect close(774, 4, 22, 22);
	bool menubarGrabbed = false;
	Point mousePos = Mouse::Pos();

	Player player;

	//GameManagerが一つであることの証明、毎回取らなくていいようにキープ
	GameManager&manager = GameManager::get_instance();


	while (System::Update())
	{
		switch (Gamemode)
		{
		case 0://Title
			void updateGame(); {
			}
			void drawGame(); {
			}




			break;

		case 1://Stage
			void updateGame(); {
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

				if (menubarGrabbed == false) {
					void updateEnemy(); {
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
				}

			}
			void drawGame(); {
				rect.draw(Color(255, 255, 255));
				void drawEnemy(); {
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
				void drawWindow(); {
					rect.drawFrame(30, 0, Color(0, 0, 0));

					if (menubarGrabbed == true) {
						rect.draw(Color(0, 0, 0, 200));
					}
					menubar.draw(Color(0, 0, 0));
					//fontMin(L"DAINSLEIF").draw(8, 4);
					close.draw(Color(0, 0, 0));
					Line(778, 8, 792, 22).draw(2);
					Line(792, 8, 778, 22).draw(2);

					fontMin(L"Position:",player.get_position(), L"  Velocity:",player.get_velocity()).draw();
				}

			}
			break;
		}
	}
}