#pragma once
class Timer
{
private:

	float deltaTime;
	float elapsedTime;

public:

	void Reset();

	float DeltaTime() { return deltaTime; }


	void Update();

	// private functions
private:

	// con and dest funcs
	Timer();
	~Timer();
};

