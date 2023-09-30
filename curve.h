#ifndef Curve_h
#define Curve_h

#include "dsp.h"

class Curve {

public:

	static inline float expo(float phase) {
		return phase * phase;
	}

	static inline float inv_expo(float phase) {
		return 1.0f - expo(1.0f - phase);
	}

	static inline float bend(float phase, float shape) {
		return Dsp::cross_fade(expo(phase), inv_expo(phase), shape);
	}

	static inline float triangle(float phase) {
		return phase < 0.5f ? phase * 2.f : (1.f - phase) * 2.f;
	}

};

#endif
