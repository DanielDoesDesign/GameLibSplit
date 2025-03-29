#ifndef PARALLELTASK_H
#define PARALLELTASK_H

#include <thread>
#include <mutex>
//lock.h?
#include <SFML/System/Clock.hpp>

class ParallelTask
{
public:
						ParallelTask();
	void				execute();
	bool				isFinished();
	float				getCompletion();

private:
	void				runTask();

private:
	std::thread			mThread;
	bool				mFinished;
	sf::Clock			mElapsedTime;
	std::mutex			mMutex;
};

#endif // PARALLELTASK_H