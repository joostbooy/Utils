#ifndef Hash_h
#define Hash_h

// Westlicht fnvHash
#include <cstdint>
#include <cstddef>

class Hash {

public:

	void init() {
		hash_ = 0x811c9dc5;
	}

	uint32_t read() {
		return hash_;
	}

	template<typename T>
	void write(T& data) {
		write(&data, sizeof(T));
	}

	void write(void *data, size_t size) {
		uint8_t *data_ = static_cast<uint8_t *>(data);
		while (size--) {
			hash_ ^= *data_++;
			hash_ *= prime_;
		}
	}

private:
	 uint32_t hash_;
	 static const size_t prime_ = 0x1000193;
};

#endif
