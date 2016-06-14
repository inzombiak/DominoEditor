#include "Debug.h"


Debug::Debug()
{
	m_printFPS = true;
	m_frames = 0;
	m_lastTime = std::chrono::system_clock::now();
}

void Debug::PrintFPS()
{
	auto currentTime = std::chrono::system_clock::now();

	m_frames++;

	if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_lastTime).count() >= 1.0)
	{ 
		printf("%f ms/frame\n", 1000.0 / double(m_frames));

		m_frames = 0;

		m_lastTime = currentTime;
	}
}

bool Debug::m_printFPS;
std::chrono::system_clock::time_point Debug::m_lastTime;
double Debug::m_frames;