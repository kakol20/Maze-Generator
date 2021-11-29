#include "LinearFeedbackShift.h"

#include <limits>

LinearFeedbackShift::LinearFeedbackShift() {
}

float LinearFeedbackShift::RandFloat(unsigned int bitCount) {
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

float LinearFeedbackShift::RandFRange(const float min, const float max, unsigned int bitCount) {
	float difference = max - min;
	float random = LinearFeedbackShift::RandFloat(bitCount);
	return (difference * random) + min;
}

int LinearFeedbackShift::RandInt(const unsigned int bitCount) {
	int out = 0;

	unsigned int count = bitCount > 32 ? 32 : bitCount;
	count = count < 2 ? 2 : bitCount;

	unsigned int negative = RandUInt(1);

	for (int i = bitCount - 2; i >= 0; i--) {
		out = out | (LinearFeedbackShift::RandUInt(1) << i);
	}

	if (negative == 0b1) out = -out;

	return out;
}

unsigned int LinearFeedbackShift::RandUInt() {
	return LinearFeedbackShift::RandUInt(32);
}

unsigned int LinearFeedbackShift::RandUInt(const unsigned int bitCount) {
	unsigned count = bitCount > 32 ? 32 : bitCount;
	unsigned int out = 0;

	for (int i = bitCount - 1; i >= 0; i--) {
		out = out | ((LinearFeedbackShift::Seed & 0b1) << i);

		unsigned int newBit = LinearFeedbackShift::Seed & (LinearFeedbackShift::Seed >> 1) ^ (LinearFeedbackShift::Seed >> 2) ^ (LinearFeedbackShift::Seed >> 22);
		newBit = newBit & 1;

		LinearFeedbackShift::Seed = (LinearFeedbackShift::Seed >> 1) | (newBit << 31);
	}
	return out;
}

LinearFeedbackShift::~LinearFeedbackShift() {
}