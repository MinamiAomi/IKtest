#pragma once
#include <Novice.h>

class Key {

private:

	static char keys[256];
	static char preKeys[256];

public:

	// �L�[���͂��󂯎��
	static inline void SetState() {
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
	}

	// �L�[�������ꂽ��
	static inline bool IsTrigger(char keycode) {
		return preKeys[keycode] == 0 && keys[keycode] != 0;
	}
	// �L�[�������Ă���Ƃ�
	static inline bool IsPressed(char keycode) {
		return keys[keycode] != 0;
	}
	// �L�[�𗣂����Ƃ�
	static inline bool IsRelease(char keycode) {
		return preKeys[keycode] != 0 && keys[keycode] == 0;
	}

private:
	Key(){}

};

