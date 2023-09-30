#ifndef Hash_h
#define Hash_h

// Westlicht fnvHash

class Hash {

public:

	void init() {
		hash_ = 0x811c9dc5;
		prime_ = 0x1000193;
	}

	uint32_t read() {
		return hash_;
	}

	void write(void *data, uint32_t size) {
		uint8_t *data_ = static_cast<uint8_t *>(data);
		while (size--) {
			hash_ ^= *data_++;
			hash_ *= prime_;
		}
	}

private:
	 uint32_t hash_;
	 uint32_t prime_;
};

#endif
