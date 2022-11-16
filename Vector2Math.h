#pragma once
#include "Vector2.h"
#include <math.h>

#pragma region 演算子

inline Vector2 operator+(const Vector2& v1, const Vector2& v2) {
	return { v1.x + v2.x, v1.y + v2.y };
}
inline Vector2 operator-(const Vector2& v1, const Vector2& v2) {
	return { v1.x - v2.x, v1.y - v2.y };
}
inline Vector2 operator*(const Vector2& v1, float s) {
	return { v1.x * s, v1.y * s };
}
inline Vector2 operator/(const Vector2& v1, float s) {
	return { v1.x / s, v1.y / s };
}
inline Vector2 operator*(float s, const Vector2& v1) {
	return { s * v1.x, s * v1.y };
}
inline Vector2 operator*(const Vector2& v1, const Vector2& v2) {
	return { v1.x * v2.x, v1.y * v2.y };
}

#pragma endregion


// Vector2の計算
namespace Vector2Math {
	// 内積
	inline float Dot(const Vector2& v1, const Vector2& v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	// 外積
	inline float Cross(const Vector2& v1, const Vector2& v2) {
		return v1.x * v2.y - v1.y * v2.x;
	}
	// 長さの二乗
	inline float LengthSquare(const Vector2& v) {
		return Dot(v, v);
	}
	// 長さ
	inline float Length(const Vector2& v) {
		return sqrtf(LengthSquare(v));
	}
	// 他ベクトルとの距離
	inline float Distance(const Vector2& v1, const Vector2& v2) {
		return Length(v2 - v1);
	}
	// なす角
	inline float Angle(const Vector2& v) {
		return atan2f(v.y, v.x);
	}
	// 正規化
	inline Vector2 Normalized(const Vector2& v) {
		float len = Length(v);
		return len != 0 ? v / len : v; // 長さが0出ないか確認
	}
	// 法線
	inline Vector2 Normal(const Vector2& v) {
		return { -v.y, v.x };
	}
	// 回転
	inline Vector2 Rotated(const Vector2& v, float theta) {
		float s = sinf(theta);
		float c = cosf(theta);
		return { v.x * c + v.y * -s, v.x * s + v.y * c };
	}
	// 拡縮
	inline Vector2 Magnituded(const Vector2& v, float length) {
		return Normalized(v) * length;
	}
	// 反射ベクトル
	// 第二引数は壁の法線を正規化したベクトル
	inline Vector2 Reflected(const Vector2& v, const Vector2& normal) {
		return Dot(normal, -v) * 2 * normal + v;
	}
	// 壁ずりベクトル
	// 第二引数は壁の法線を正規化したベクトル
	inline Vector2 AlongWall(const Vector2& v, const Vector2& normal) {
		return Dot(normal, -v) * normal + v;
	}
	// ゼロにする
	inline void SetZero(Vector2& v) {
		v.x = 0;
		v.y = 0;
	}
	// ゼロであるか
	inline bool IsZero(const Vector2& v) {
		return { v.x == 0.0f && v.y == 0.0f };
	}
}