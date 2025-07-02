#pragma once
class Time
{
public:
	inline static double DeltaTime {0.0};

	static void Update();

private:
	inline static double lastFrame {0.0}; // Time of last frame
};

