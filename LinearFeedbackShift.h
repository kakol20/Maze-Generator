#ifndef LINEARFEEDBACKSHIFT_H
#define LINEARFEEDBACKSHIFT_H

class LinearFeedbackShift {
public:
	LinearFeedbackShift();

	static float RandF();
	static float RandFRange(const float min, const float max);
	static int RandInt();
	static unsigned int RandUInt();

	static unsigned int Seed;

	~LinearFeedbackShift();

private:
};

#endif // !LINEARFEADBACKSHIFT_H
