#ifndef UTILITY_H
#define UTILITY_H



const int UPDATE_FREQUENCY = 60;
const float CYCLE_TIME = 1.0f / UPDATE_FREQUENCY;

struct Timer
{
	Uint64 previous_ticks;
	float elapsed_seconds;

	void tick()
	{
		const Uint64 current_ticks{ SDL_GetPerformanceCounter() };
		const Uint64 delta{ current_ticks - previous_ticks };
		previous_ticks = current_ticks;
		static const Uint64 TICKS_PER_SECOND{ SDL_GetPerformanceFrequency() };
		elapsed_seconds = delta / static_cast<float>(TICKS_PER_SECOND);
	}
};

static Timer system_timer;
float accumulated_seconds = 0.0f;

#endif // !UTILITY_H
