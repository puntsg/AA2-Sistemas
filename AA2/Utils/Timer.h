#pragma once
#include <mutex>
#include <functional>

static class Timer
{
public:
	typedef std::function<bool()> BlockCheck;

	typedef std::function<void()> OnTimeElapsed;
	typedef std::function<bool()> OnTimeElapsedWithLoop;

	static void SleepThread(unsigned long timeRequired);
	static void BlockThreadWhile(BlockCheck blockCheck, unsigned long timeRequiredMiliseconsToNextCheck = 0);

	static void StartTimer(unsigned long timeRequired, OnTimeElapsed onTimeElapse);
	static void StartLoopTimer(unsigned long timeRequired, OnTimeElapsedWithLoop onTimeElapse);
};
