#include "LinearFeedbackShift.h"

#include <limits>

LinearFeedbackShift::LinearFeedbackShift() {
}

float LinearFeedbackShift::RandF() {
	//unsigned int state = seed;
	unsigned int out = 0;

	// 32,22,2,1
	for (int i = 31; i >= 0; i--) {
		out = out | ((LinearFeedbackShift::Seed & 0b1) << i);

		int newbit = LinearFeedbackShift::Seed ^ (LinearFeedbackShift::Seed >> 1) ^ (LinearFeedbackShift::Seed >> 2) ^ (LinearFeedbackShift::Seed >> 22);
		newbit = newbit & 0b1;

		LinearFeedbackShift::Seed = (LinearFeedbackShift::Seed >> 0b1) | (newbit << 31);
	}

	return (float)out / (float)UINT_MAX;
}

float LinearFeedbackShift::RandFRange(const float min, const float max) {
	float difference = max - min;
	float random = LinearFeedbackShift::RandF();
	return (difference * random) + min;
}

int LinearFeedbackShift::RandInt() {
	int out = 0;

	// 32,22,2,1
	for (int i = 31; i >= 0; i--) {
		out = out | ((LinearFeedbackShift::Seed & 0b1) << i);

		int newbit = LinearFeedbackShift::Seed ^ (LinearFeedbackShift::Seed >> 1) ^ (LinearFeedbackShift::Seed >> 2) ^ (LinearFeedbackShift::Seed >> 22);
		newbit = newbit & 0b1;

		LinearFeedbackShift::Seed = (LinearFeedbackShift::Seed >> 0b1) | (newbit << 31);
	}

	return out;
}

unsigned int LinearFeedbackShift::RandUInt() {
	unsigned int out = 0;

	// 32,22,2,1
	for (int i = 31; i >= 0; i--) {
		out = out | ((LinearFeedbackShift::Seed & 0b1) << i);

		unsigned int newbit = LinearFeedbackShift::Seed ^ (LinearFeedbackShift::Seed >> 1) ^ (LinearFeedbackShift::Seed >> 2) ^ (LinearFeedbackShift::Seed >> 22);
		newbit = newbit & 0b1;

		LinearFeedbackShift::Seed = (LinearFeedbackShift::Seed >> 0b1) | (newbit << 31);
	}
	return out;
}

LinearFeedbackShift::~LinearFeedbackShift() {
}