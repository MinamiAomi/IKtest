#include <Novice.h>
#include "Matrix33.h"
#include "Vector2Math.h"
#include <assert.h>
#include "Key.h"
#include "DeltaTime.h"
#include <math.h>

#include <vector>

const char kWindowTitle[] = "学籍番号";

constexpr float Pi = 3.14159265359f;
constexpr float TwoPi = 2.0f * Pi;

static Matrix33 scrMat;
constexpr float kWorldOrigin = 720.0f;

Vector2 ChangeScreen(const Vector2& vec);

Vector2 TransForm(const Vector2& vec, const Matrix33& mat);

struct Quad {
	Vector2 LeftTop;
	Vector2 RightTop;
	Vector2 LeftBottom;
	Vector2 RightBottom;

	Quad MultplyMatrix(const Matrix33& mat) const;
	void DrawScreen(int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color);
};

void DrawLine(const Vector2& a, const Vector2& b) {
	Vector2 aa = ChangeScreen(a);
	Vector2 bb = ChangeScreen(b);
	Novice::DrawLine((int)aa.x, (int)aa.y, (int)bb.x, (int)bb.y, WHITE); 
}

void DrawCircle(const Vector2& a, float r, unsigned int color) {
	Vector2 aa = ChangeScreen(a);
	Novice::DrawEllipse((int)aa.x, (int)aa.y, (int)r, (int)r, 0.0f, color, kFillModeSolid);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);


	float boneLen = 50;


	
	std::vector<Vector2> pos(4);

	for (int i = 0; i < pos.size();i++) {
		pos[i] = { 300 + i * boneLen,300 };
	}

	
	int cycic = 10;


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();
		DeltaTime::CalcDeltaTime();
		// キー入力を受け取る
		Key::SetState();

		int x, y;
		Novice::GetMousePosition(&x, &y);
		Vector2 mouse((float)x, (float)y);
		
		///
		/// ↓更新処理ここから
		///
		

		//Vector2 linearVec = kobusi - kata;
		//
		//float A = Vector2Math::Length(linearVec);
		//
		//linearVec = Vector2Math::Normalized(linearVec);
		//
		//float angleFromX = atan2f(linearVec.y, linearVec.x);
		//float theta = acosf((A * A + boneLen * boneLen - boneLen * boneLen) / (2.0f * A * boneLen));
		//angleFromX += theta;
		//
		//if (A < boneLen * 2) {
		//	hizi = kata + Vector2(cosf(angleFromX), sinf(angleFromX)) * boneLen;
		//}
		//else {
		//	hizi = kata + linearVec * boneLen;
		//	kobusi = kata + linearVec * boneLen * 2;
		//}


		for (int i = 0; i < cycic; i++) {

			auto rit = pos.rbegin();

			++rit;

			for (; rit != pos.rend(); ++rit) {

				Vector2 vecToEnd = pos.back() - *rit;

				Vector2 vecToTarget = mouse - *rit;

				auto tarLen = Vector2Math::Length(vecToTarget);

				auto endLen = Vector2Math::Length(vecToEnd);

				if (tarLen == 0.0f) {
					continue;
				}
				if (endLen == 0.0f) {
					continue;
				}

				vecToTarget = Vector2Math::Normalized(vecToTarget);
				vecToEnd = Vector2Math::Normalized(vecToEnd);

				float angle = atan2f(
					Vector2Math::Cross(vecToEnd, vecToTarget),
					Vector2Math::Dot(vecToEnd, vecToTarget));

				if (angle == 0.0f) {
					continue;
				}

				Matrix33 mat = Matrix33::MakeTranslation(-*rit) *
					Matrix33::MakeRotation(angle) * Matrix33::MakeTranslation(*rit);

				auto it = rit.base();
				for (; it != pos.end(); ++it) {
					*it = *it * mat;
				}

			}

			if (Vector2Math::Length(pos.back() - mouse) < 0.001f) {
				break;
			}


		}


		

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		

		for (int i = 0; i < pos.size() - 1; i++) {
			DrawLine(pos[i], pos[i+1]);
			DrawCircle(pos[i], 20, WHITE);
		}
		DrawCircle(pos[pos.size() - 1], 20, WHITE);
	
		//Novice::DrawLine();
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (Key::IsTrigger(DIK_ESCAPE)) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

Vector2 ChangeScreen(const Vector2& vec) {
	return vec * scrMat;
}

Vector2 TransForm(const Vector2& vec, const Matrix33& mat) {
	Vector2 result;
	result.x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + 1.0f * mat.m[2][0];
	result.y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + 1.0f * mat.m[2][1];
	float  w = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + 1.0f * mat.m[2][2];
	assert(w != 0.0f);
	result /= w;
	return result;
}

Quad Quad::MultplyMatrix(const Matrix33& mat) const {
	return {
		TransForm(LeftTop, mat),
		TransForm(RightTop, mat),
		TransForm(LeftBottom, mat),
		TransForm(RightBottom, mat) };
}

void Quad::DrawScreen(int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color) {
	Quad scr = {
			{ ChangeScreen(LeftTop) },
			{ ChangeScreen(RightTop) },
			{ ChangeScreen(LeftBottom) },
			{ ChangeScreen(RightBottom) }
	};

	Novice::DrawQuad(
		(int)scr.LeftTop.x, (int)scr.LeftTop.y,
		(int)scr.RightTop.x, (int)scr.RightTop.y,
		(int)scr.LeftBottom.x, (int)scr.LeftBottom.y,
		(int)scr.RightBottom.x, (int)scr.RightBottom.y,
		srcX, srcY, srcW, srcH, textureHandle, color);
}