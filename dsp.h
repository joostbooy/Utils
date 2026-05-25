#ifndef Dsp_h
#define Dsp_h

#include <cmath>

class Dsp {

public:

	static inline float one_pole_filter(float in, float out, float coeff = 0.01f) {
		return out += (coeff) * ((in) - out);
	}

	template <typename type>
	static inline type cross_fade(type a, type b, float mix) {
		return a + (b - a) * mix;
	}

	template <typename type>
	static inline type cross_fade(type a, type b, type c, float mix) {
		return mix < 0.5f ? cross_fade(a, b, mix * 2.f) : cross_fade(b, c, (mix - 0.5f) * 2.f);
	}

	template<typename T>
	static inline void hysterisis(T in, T *out, const T step_size) {
		T diff = *out >= in ? *out - in : in - *out;
		if (diff >= step_size) {
			*out = in;
		}
	}

	template <typename type>
	static inline void pan(type* left, type* right, float pan) {
		float amp_left;
		float amp_right;
		type left_ = *left;
		type right_ = *right;

		if (pan < 0.5f) {
			amp_left = 1.0f;
			amp_right = 2.0f * pan;
		} else {
			amp_right = 1.0f;
			amp_left = 2.0f * (1.0f - pan);
		}

		*left = left_ * amp_left + right_ * (1.0f - amp_right);
		*right = right_ * amp_right + left_ * (1.0f - amp_left);
	}
};

#endif
