#include "DeltaTime.h"

clock_t DeltaTime::nowTime = clock();
clock_t DeltaTime::oldTime = nowTime;
float DeltaTime::deltaTime = 0.0f;

void DeltaTime::CalcDeltaTime() {
	while (!((oldTime + 16) - clock() <= 0))
		;
	nowTime = clock();
	deltaTime = static_cast<float>(nowTime - oldTime) / CLOCKS_PER_SEC;
	deltaTime = deltaTime > 0.05f ? 0.05f : deltaTime;
	oldTime = nowTime;
}	