#ifndef Que_h
#define Que_h

#include "stmf4lib.h"

// Circular Que (kMaxSize must be pow2)

template <typename T, const uint16_t kMaxSize>
class Que {
public:

	inline void init() {
		write_pos_ = 0;
		read_pos_ = 0;
	}

	inline bool writeable() {
		return ((write_pos_ + 1) & (kMaxSize - 1)) != read_pos_;
	}

	inline bool readable() {
		return write_pos_ != read_pos_;
	}

	inline uint16_t size() {
		return (write_pos_ - read_pos_) & (kMaxSize - 1);
	}

	inline uint16_t available_size() {
		return kMaxSize - size();
	}

	inline void clear() {
		write_pos_ = read_pos_;
	}

	inline void write(T value) {
		uint16_t pos = write_pos_;
		data[pos] = value;
		write_pos_ = (pos + 1) & (kMaxSize - 1);
	}

	inline T read() {
		uint16_t pos = read_pos_;
		T value = data[pos];
		read_pos_ = (pos + 1) & (kMaxSize - 1);
		return value;
	}

	inline T peek(uint16_t pos = 0) {
		return data[(read_pos_ + pos) & (kMaxSize - 1)];
	}

	inline T* pointer() {
		return &data[read_pos_];
	}

	inline void swallow() {
		if (readable()) {
			uint16_t pos = read_pos_;
			read_pos_ = (pos + 1) & (kMaxSize - 1);
		}
	}

private:
	volatile uint16_t write_pos_ = 0;
	volatile uint16_t read_pos_ = 0;
	T data[kMaxSize];
};

#endif
