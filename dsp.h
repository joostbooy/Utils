#ifndef Dsp_h
#define Dsp_h

class Dsp {

public:

	static inline float one_pole_filter(float in, float out, float coeff = 0.01f) {
		return out += (coeff) * ((in) - out);
	}

	template <typename type>
	static inline type cross_fade(type a, type b, float mix) {
		return a + (b - a) * mix;
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

	// Laurent de Sora & Pinchenettes
	static inline float ReadHermite(int16_t* data, uint32_t integral, float fractional) {
		float xm1 = data[integral];
		float x0 = data[integral + 1];
		float x1 = data[integral + 2];
		float x2 = data[integral + 3];
		float scale = 1.0f / 32768.0f;

		const float c = (x1 - xm1) * 0.5f;
		const float v = x0 - x1;
		const float w = c + v;
		const float a = w + v + (x2 - x0) * 0.5f;
		const float b_neg = w + a;
		return ((((a * fractional) - b_neg) * fractional + c) * fractional + x0) * scale;
	}
};


// Pinchenettes
template<typename type>
class Limiter {
public:

	inline void init() {
		peak_ = 0.5f;
	}

	inline void process(type* data, int size, const int alligment = 1) {
		while (size--) {
			type s = *data;
			float error = fabsf(s) - peak_;
			peak_ += (error > 0 ? 0.05f : 0.00002f) * error;
			float gain = (peak_ <= 1.0f ? 1.0f : 1.0f / peak_);
			*data = s * gain * 0.8f;
			data += alligment;
		}
	}

private:
	float peak_ = 0.5f;
};

#endif
