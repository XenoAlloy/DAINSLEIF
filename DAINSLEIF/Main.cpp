# include <Siv3D.hpp>
# include "Player.h"
void Main()
{
	Window::SetTitle(L"DAINSLEIF");
	Window::Resize(800, 600);
	Window::SetStyle(WindowStyle::NonFrame);
	int Gamemode = 0;

	const Font fontMin(14);



	//メニュー関連
	const Rect rect(0, 0, 800, 600);
	const Rect menuBar(0, 0, 800, 30);
	const Rect close(774, 4, 22, 22);
	bool menuGrabbed = false;
	int menuExtend = 0;
	Point moPos = Mouse::Pos();

	class StraightWeapon{
		void move_pattern() {
		}
	};


	while (System::Update())
	{
		void updateGame(); {
			void updateEnemy(); {
			}
			void updatePlayer(); {
				int dirX(Input::KeyRight.pressed - Input::KeyLeft.pressed);
				int dirY(Input::KeyDown.pressed - Input::KeyUp.pressed);
				player.positionX += dirX * 6;
				player.positionY += dirY * 6;
				if (Input::KeyShift.pressed == 1) {
					player.positionX -= dirX * 4;
					player.positionY -= dirY * 4;
				}


			}
			void updateEneBullet(); {
			}
			void updatePlaBullet(); {
			}
			void updateWindow(); {
				//closeをクリックで閉じる
				if (close.leftClicked)
				{
					System::Exit();
				}
				//ウインドウの移動
				if (menuBar.leftClicked)
				{
					// メニューをクリックしたらつかむ
					if (menuGrabbed == false)
					{
						moPos = Mouse::Pos();
					}
					menuGrabbed = true;

				}
				else if (Input::MouseL.released)
				{
					// マウスのクリックが離されたら離す
					menuGrabbed = false;
				}
				else if (menuGrabbed)
				{
					// つかんでいる間はマウスのポジションに
					Window::SetPos(Mouse::ScreenPos() - moPos);
				}


				if (Input::KeyS.clicked) {
					if (Gamemode == 0)
					{
						Gamemode = 1;
					}
					else {
						Gamemode = 0;
					}
				}
				if (Gamemode >= 1) {
					if (menuExtend <= 370)
					{
						menuExtend += 37;
					}
				}
				else if (menuExtend >= 0)
				{
					menuExtend -= 37;
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
			}
			void drawWindow(); {
				rect.drawFrame(30, 0, Color(0, 0, 0));
				menuBar.draw(Color(0, 0, 0));
				fontMin(L"DAINSLEIF").draw(8, 4);
				close.draw(Color(0, 0, 0));
				Line(778, 8, 792, 22).draw(2);
				Line(792, 8, 778, 22).draw(2);
				Rect(770, 30, -menuExtend, 540).draw(Color(0, 0, 0));

			}
		}
	}
}