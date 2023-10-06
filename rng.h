#ifndef rng_h
#define rng_h

//Random number generation

#include <stdint.h>

class Rng {

public:

	static inline void seed(uint16_t value) {
		seed_ = value;
		if (seed_ == 0) {
			seed_ = 1;
		}
	}

	static inline uint16_t u16() {
		seed_ ^= seed_ << 7;
		seed_ ^= seed_ >> 11;
		seed_ ^= seed_ << 2;
		return seed_;
	}

	static inline float reciprocal() {
		return (1.0f / 65535.0f) * u16();
	}

	static inline uint16_t u16(uint16_t min, uint16_t max) {
		if (min > max) {
			swap(min, max);
		}
		return (reciprocal() * (max - min + 1)) + min;
	}

private:
	static uint16_t seed_;

	static inline void swap(uint16_t &a, uint16_t &b) {
		uint16_t temp = a;
		a = b;
		b = temp;
	}

};

#endif
