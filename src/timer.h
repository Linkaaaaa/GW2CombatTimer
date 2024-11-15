#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>
#include <vector>

struct TimeInfo {
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;
};

extern struct TimeInfo current;
extern std::vector<TimeInfo> previous;

namespace timer {
	void Start();
	void Stop();
	void Update();
	std::string GetCombatTime(const std::chrono::system_clock::duration&);
	std::string GetTotalCombatTime(const std::vector<TimeInfo>&);
	std::string GetDate(const std::chrono::system_clock::time_point&);
};

#endif