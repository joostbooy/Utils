#ifndef SerialisedBuffer_h
#define SerialisedBuffer_h

template<const size_t kMax>
class SerialisedBuffer {

public:

	void clear() {
		w_pos_ = 0;
		reset();
	}

	void reset() {
		r_pos_ = 0;
	}

	size_t w_pos() { return w_pos_; }
	size_t r_pos() { return r_pos_; }

	size_t readable() { return w_pos_ - r_pos_; }
	size_t writeable() { return kMax - w_pos_; }

	template<typename T>
	bool write(T &value) {
		size_t size_ = sizeof(T);
		if (writeable() >= size_) {
			transfer(&value, &data_[w_pos_], size_);
			w_pos_ += size_;
			return true;
		}
		return false;
	}

	template<typename T>
	bool read(T &value) {
		size_t size_ = sizeof(T);
		if (readable() >= size_) {
			transfer(&data_[r_pos_], &value, size_);
			r_pos_ += size_;
			return true;
		}
		return false;
	}

private:
	size_t w_pos_;
	size_t r_pos_;
	uint8_t data_[kMax];

	void transfer(void *src, void *dest, size_t i) {
		uint8_t *src_ = static_cast<uint8_t*>(src);
		uint8_t *dest_ = static_cast<uint8_t*>(dest);
		while (i--) {
			*dest_++ = *src_++;
		}
	}
};

#endif
