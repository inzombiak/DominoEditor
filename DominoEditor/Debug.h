#pragma once

#include <chrono>
#include <ctime>

class Debug
{
public:
	Debug();

	static void PrintFPS();

private:

	static bool m_printFPS;
	static std::chrono::system_clock::time_point m_lastTime;
	static double m_frames;
};

