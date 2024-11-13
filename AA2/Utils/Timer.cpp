#include "Timer.h"
#include <thread>
#include <windows.h>

void Timer::SleepThread(unsigned long timeRequiredMilisecons)
{
	Sleep(timeRequiredMilisecons);
}

void Timer::BlockThreadWhile(BlockCheck blockCheck, unsigned long timeRequiredMiliseconsToNextCheck)
{
	bool checkSuccess = false;

	while (!checkSuccess)
	{
		if (timeRequiredMiliseconsToNextCheck != 0)
		{
			Sleep(timeRequiredMiliseconsToNextCheck);
		}
		checkSuccess = blockCheck();
	}
}

void Timer::StartTimer(unsigned long timeRequiredMilisecons, OnTimeElapsed onTimeElapse)
{
	std::thread* thread = new std::thread([timeRequiredMilisecons, onTimeElapse]() {
		Sleep(timeRequiredMilisecons);
		onTimeElapse();
	});

	thread->detach();
}

void Timer::StartLoopTimer(unsigned long timeRequiredMilisecons, OnTimeElapsedWithLoop onTimeElapse)
{
	std::thread* thread = new std::thread([timeRequiredMilisecons, onTimeElapse]() {

		bool continueLoop = true;
		while (continueLoop)
		{
			Sleep(timeRequiredMilisecons);
			continueLoop = onTimeElapse();
		}

	});

	thread->detach();
}