#ifndef Reciprocal_h
#define Reciprocal_h

template<size_t kSize>
class Reciprocal {

public:

	Reciprocal() {
		value_[0] = 0.f;
		for (size_t i = 1; i < kSize; ++i) {
			value_[i] = 1.f / i;
		}
	}

	inline float operator()(size_t number) {
		return value_[number];
	}

private:
	float value_[kSize];
};

#endif
