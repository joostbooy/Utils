#ifndef Bits_h
#define Bits_h

class Bits {

public:

	template<typename T>
	static inline void set(T *reg, int bit) {
		T reg_ = *reg;
		*reg = reg_ | (1 << bit);
	}

	template<typename T>
	static inline void clear(T *reg, int bit) {
		T reg_ = *reg;
		*reg = reg_ & ~(1 << bit);
	}

	template<typename T>
	static inline void toggle(T *reg, int bit) {
		T reg_ = *reg;
		*reg = reg_ ^ (1 << bit);
	}

	template<typename T>
	static inline void write(T *reg, int bit, bool state) {
		state ? set(reg, bit) : clear(reg, bit);
	}

	template<typename T>
	static inline bool read(T *reg, int bit) {
		T reg_ = *reg;
		return reg_ & (1 << bit);
	}

	template<typename T>
	static inline T rotate_left(T data, const int size) {
		return (data << 1) | (data >> (size - 1));
	}

	template<typename T>
	static inline T rotate_right(T data,  const int size) {
		return (data >> 1) | (data << (size - 1));
	}

	template<typename T>
	static inline T swap(T data, int pos_1, int pos_2) {
		T bit_1 = (data >> pos_1) & 1;
		T bit_2 = (data >> pos_2) & 1;
		T x = (bit_1 ^ bit_2);
		x = (x << pos_1) | (x << pos_2);
		return data ^ x;
	}
};

#endif
