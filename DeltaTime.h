#pragma once
#include <time.h>

class DeltaTime {
private:
	static clock_t nowTime;
	static clock_t oldTime;
	static float deltaTime;


public:
	static void CalcDeltaTime();
	static float Get() { return deltaTime; }

private:
	DeltaTime(){}

};