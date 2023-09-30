#ifndef Allocator_h
#define Allocator_h

#include "stmf4lib.h"

template<typename type, const uint8_t kMaxEntries>
class Allocator {

public:

	void init(void* buffer_, const uint32_t kBufferSize_) {
		buffer = static_cast<type*>(buffer_);
		kBufferSize = kBufferSize_ / sizeof(type);

		entries = 0;
		free = kBufferSize;

		for (uint8_t i = 0; i < kMaxEntries; ++i){
			entry[i].ptr = nullptr;
			entry[i].size = 0;
		}
	}

	uint8_t num_entries() {
		return entries;
	}

	uint32_t used() {
		return kBufferSize - free;
	}

	uint32_t available() {
		return free;
	}

	bool available(uint32_t requested_size) {
		return free > requested_size;
	}

	type* entry_ptr(uint8_t slot) {
		if (slot >= entries) {
			return nullptr;
		} else {
			return entry[slot].ptr;
		}
	}

	uint32_t entry_size(uint8_t slot) {
		if (slot >= entries) {
			return 0;
		} else {
			return entry[slot].size;
		}
	}

	type* allocate(uint32_t size) {
		if ((free <= size) || (entries >= kMaxEntries)) {
			return nullptr;
		}

		type* ptr = block_tail();
		entry[entries].ptr = ptr;
		entry[entries].size = size;

		free -= size;
		++entries;

		return ptr;
	}

	void remove(uint8_t slot) {
		if (slot >= entries) {
			return;
		}

		free += entry[slot].size;
		--entries;

		if (slot == entries) {
			return;
		}

		for (uint8_t i = slot; i < entries; ++i) {
			entry[i].ptr = entry[i + 1].ptr;
			entry[i].size = entry[i + 1].size;
		}

		reallign_left(slot);
	}

	void resize(uint8_t slot, uint32_t start, uint32_t end) {
		if ((slot >= entries) || (start > end) || (start + (end - start) > entry[slot].size)) {
			return;
		}

		uint32_t new_size = end - start;
		type* write_ptr = entry[slot].ptr;
		type* read_ptr = write_ptr + start;

		free += (entry[slot].size - new_size);
		entry[slot].size = new_size;

		while (new_size--) {
			*write_ptr++ = *read_ptr++;
		}

		reallign_left(slot + 1);
	}

private:

	struct Entry {
		type* ptr;
		uint32_t size;
	};

	type* buffer= nullptr;
	uint32_t kBufferSize = 0;

	Entry entry[kMaxEntries];
	uint32_t free = 0;
	uint32_t entries = 0;


	type* block_tail() {
		if (entries == 0) {
			return &buffer[0];
		} else {
			return entry[entries - 1].ptr + entry[entries - 1].size;
		}
	}

	void reallign_left(uint8_t slot) {
		if (slot >= entries) {
			return;
		}

		uint32_t size;
		type* write_ptr;
		type* read_ptr = entry[slot].ptr;

		if (slot == 0) {
			write_ptr = &buffer[0];
		} else {
			write_ptr = entry[slot - 1].ptr + entry[slot - 1].size;
		}

		if (write_ptr >= read_ptr) {
			return;
		}

		for (uint8_t i = slot; i < entries; ++i) {
			entry[i].ptr = write_ptr;
			size = entry[i].size;
			while (size--) {
				*write_ptr++ = *read_ptr++;
			}
		}
	}

};

#endif
