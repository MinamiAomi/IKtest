#pragma once
#include <Novice.h>

class Key {

private:

	static char keys[256];
	static char preKeys[256];

public:

	// キー入力を受け取る
	static inline void SetState() {
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
	}

	// キーが押された時
	static inline bool IsTrigger(char keycode) {
		return preKeys[keycode] == 0 && keys[keycode] != 0;
	}
	// キーを押しているとき
	static inline bool IsPressed(char keycode) {
		return keys[keycode] != 0;
	}
	// キーを離したとき
	static inline bool IsRelease(char keycode) {
		return preKeys[keycode] != 0 && keys[keycode] == 0;
	}

private:
	Key(){}

};

