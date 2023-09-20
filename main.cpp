#include "iostream"
#include "raylib.h"

using namespace std;

struct Ball {
	float x, y;
	float speedX, speedY;
	float radius;

	void Draw() {
		DrawCircle((int)x, (int)y, (int)radius, WHITE);
	}
};
	struct Paddle {
		float x, y;
		float speed;
		float width, height;

		Rectangle GetRect() {
			return Rectangle{ x - width / 2, y - height / 2, 10, 100 };
		}

		void Draw() {
			DrawRectangleRec(GetRect(), WHITE);
		}
};

int main() {
	InitWindow(800, 600, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);

	Ball ball;
	ball.x = GetScreenWidth() / 2.0;
	ball.y = GetScreenHeight() / 2.0;
	ball.radius = 5;
	ball.speedX = 200;
	ball.speedY = 200;

	Paddle leftPad;
	leftPad.x = 50;
	leftPad.y = GetScreenHeight() / 2;
	leftPad.width = 10;
	leftPad.height = 100;
	leftPad.speed = 300;

	Paddle rightPad;
	rightPad.x = GetScreenWidth() - 50;
	rightPad.y = GetScreenHeight() / 2;
	rightPad.width = 10;
	rightPad.height = 100;
	rightPad.speed = 300;

	const char* winnerText = nullptr;

		while (!WindowShouldClose()) {

			ball.x += ball.speedX * GetFrameTime();
			ball.y += ball.speedY * GetFrameTime();

			
			//So ball doesn't go off top or bottom of screen
			if (ball.y < 0)
			{
				ball.y = 0;
				ball.speedY *= -1;
			}

			if (ball.y > GetScreenHeight())
			{
				ball.y = GetScreenHeight();
				ball.speedY *= -1;
			}

			//So paddle doesnt go off screen
			if (leftPad.y - leftPad.height / 2 < 0) {
				leftPad.y = 0 + leftPad.height / 2;
			}
			if (leftPad.y + leftPad.height / 2 > GetScreenHeight()) {
				leftPad.y = GetScreenHeight() - leftPad.height / 2 ;
			}

			if (rightPad.y - rightPad.height / 2 < 0) {
				rightPad.y = 0 + rightPad.height / 2;
			}
			if (rightPad.y + rightPad.height / 2 > GetScreenHeight()) {
				rightPad.y = GetScreenHeight() - rightPad.height / 2;
			}
			
			//Paddle movement with Key input W,S,UP arrow,Down arrow
				//Key input for left Paddle
			if (IsKeyDown(KEY_W)) {
				leftPad.y -= leftPad.speed * GetFrameTime();
			}
			if (IsKeyDown(KEY_S)) {
				leftPad.y += leftPad.speed * GetFrameTime();
			}
				//Key input for right Paddle
			if (IsKeyDown(KEY_UP)) {
				rightPad.y -= rightPad.speed * GetFrameTime();
			}
			if (IsKeyDown(KEY_DOWN)) {
				rightPad.y += rightPad.speed * GetFrameTime();
			}

			if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, 
				rightPad.GetRect())) {

				if (ball.speedX > 0) {
					ball.speedX *= -1.2;
					ball.speedY = (ball.y - rightPad.y) / (rightPad.height / 2) * -ball.speedX;
				}
				
			}
			if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius,
				leftPad.GetRect())) {

				if (ball.speedX < 0) {
					ball.speedX *= -1.2;
					ball.speedY = (ball.y - leftPad.y) / (leftPad.height / 2) * ball.speedX;
				}
			
			}

			if (ball.x < 0) {
				winnerText = "Right Player Wins!";
			}

			if (ball.x > GetScreenWidth()) {
				winnerText = "Left Player Wins!";
			}

			BeginDrawing();
			ClearBackground(BLACK);

			ball.Draw();
			leftPad.Draw();
			rightPad.Draw();
			if (winnerText) {
				int textWidth = MeasureText(winnerText, 60);
				DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
			}
			if (winnerText && IsKeyPressed(KEY_SPACE)) {
				ball.x = GetScreenWidth() / 2;
				ball.y = GetScreenHeight() / 2;
				ball.speedX = 200;
				ball.speedY = 200;
				winnerText = nullptr;
			}

			DrawFPS(10, 10);
			EndDrawing();
		}

	CloseWindow();

	return 0;

}