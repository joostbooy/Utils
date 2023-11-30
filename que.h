#ifndef Que_h
#define Que_h

#include "stmf4lib.h"

// Circular Que

template <typename T, const size_t kMaxSize>
class Que {
public:

	inline void init() {
		write_pos_ = 0;
		read_pos_ = 0;
	}

	inline bool writeable() {
		return ((write_pos_ + 1) % kMaxSize) != read_pos_;
	}

	inline bool readable() {
		return write_pos_ != read_pos_;
	}

	inline size_t size() {
		return (write_pos_ - read_pos_) % kMaxSize;
	}

	inline size_t available_size() {
		return kMaxSize - size();
	}

	inline void clear() {
		write_pos_ = read_pos_;
	}

	inline void write(T value) {
		size_t pos = write_pos_;
		data[pos] = value;
		write_pos_ = (pos + 1) % kMaxSize;
	}

	inline T read() {
		size_t pos = read_pos_;
		T value = data[pos];
		read_pos_ = (pos + 1) % kMaxSize;
		return value;
	}

	inline T peek(size_t pos = 0) {
		return data[(read_pos_ + pos) % kMaxSize];
	}

	inline T* pointer() {
		return &data[read_pos_];
	}

	inline void swallow() {
		if (readable()) {
			size_t pos = read_pos_;
			read_pos_ = (pos + 1) % kMaxSize;
		}
	}

private:
	volatile size_t write_pos_ = 0;
	volatile size_t read_pos_ = 0;
	T data[kMaxSize];
};

#endif
