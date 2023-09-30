#ifndef EntryManager_h
#define EntryManager_h

#include "stmf4lib.h"

// Entry indexes are linear and the indexes can change, id's are fixed and linked to an entry

template<typename type, const size_t kEntrySize, const uint8_t kMaxEntries>
class EntryManager {

public:

	void init(void* EntryBase) {
		entry = static_cast<type*>(EntryBase);

		num_entries = 0;

		for (uint8_t i = 0; i < kMaxEntries; ++i) {
			id_to_entry[i] = -1;
			id_pool[i] = i;
		}
	}

	uint8_t num_of_entries() {
		return num_entries;
	}

	uint8_t num_available() {
		return kMaxEntries - num_entries;
	}

	bool write(type* data) {
		if (num_available() == 0) {
			return false;
		}

		uint8_t e_idx = num_entries;
		uint8_t id = id_pool[num_entries];
		id_to_entry[id] = e_idx;
		entry_to_id[e_idx] = id;

		memcpy(&entry[e_idx], data, kEntrySize);

		++num_entries;
		return true;
	}

	bool write(type* data, uint8_t id) {
		if (num_available() == 0 || remove_id_from_pool(id) == false) {
			return false;
		}

		uint8_t e_idx = num_entries;
		id_to_entry[id] = e_idx;
		entry_to_id[e_idx] = id;

		memcpy(&entry[e_idx], data, kEntrySize);

		++num_entries;
		return true;
	}

	bool overwrite(uint8_t e_idx, type* data) {
		if (e_idx >= num_entries) {
			return false;
		}
		memcpy(&entry[e_idx], data, kEntrySize);
		return true;
	}

	bool remove(uint8_t e_idx) {
		if (e_idx >= num_entries) {
			return false;
		}

		--num_entries;

		uint8_t id = entry_to_id[e_idx];
		id_to_entry[id] = -1;
		id_pool[num_entries] = id;

		for (uint8_t e = e_idx; e < num_entries; ++e) {
			memcpy(&entry[e], &entry[e + 1], kEntrySize);
			entry_to_id[e] = entry_to_id[e + 1];

			id = entry_to_id[e];
			id_to_entry[id] = e;
		}
		return true;
	}

	type* read(uint8_t e_idx) {
		if (e_idx >= num_entries) {
			return NULL;
		} else {
			return &entry[e_idx];
		}
	}

	type* read_by_id(uint8_t id) {
		int16_t e_index = id_to_entry[id];
		if (e_index >= 0) {
			return &entry[e_index];
		}
		return NULL;
	}

	int16_t entry_id(uint8_t e) {
		return entry_to_id[e];
	}

	bool id_is_valid(uint8_t id) {
		return id_to_entry[id] >= 0;
	}

private:
	type* entry;
	uint8_t num_entries;	// also acts as id_pool pointer
	uint8_t id_pool[kMaxEntries];
	uint8_t entry_to_id[kMaxEntries];
	int16_t id_to_entry[kMaxEntries];

	int find_id(uint8_t id) {
		int index = -1;
		for (int i = num_entries; i < kMaxEntries; ++i) {
			if (id_pool[i] == id) {
				index = i;
				break;
			}
		}
		return index;
	}

	bool remove_id_from_pool(uint8_t id) {
		int index;
		if ((index = find_id(id)) < 0) {
			return false;
		}

		if (num_entries != index) {
			id_pool[index] = id_pool[num_entries];
		}
		return true;
	}

};

#endif
