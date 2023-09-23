#pragma once
#include <string.h>
#include <chrono>

class Timer {
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	std::chrono::nanoseconds duration;

public:
	void StartTimer() {
		start = std::chrono::steady_clock::now();
	}

	void EndTimer() {  
		end =  std::chrono::steady_clock::now();
	} 

	long long Duration() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	}

};

