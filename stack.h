#ifndef Stack_h
#define Stack_h

template <typename T, const size_t kMaxSize>
class Stack {

public:

	inline void clear() {
		size_ = 0;
	}

	inline uint8_t size() {
		return size_;
	}

	inline bool readable() {
		return size_ > 0;
	}

	inline bool writeable() {
		return size_ < kMaxSize;
	}

	inline uint8_t available() {
		return kMaxSize - size_;
	}

	//Reading
	inline T pop() {
		--size_;
		return data_[size_];
	}

	inline T pull() {
		T value = data_[0];
		remove_by_index(0);
		return value;
	}

	// -1 if not found
	inline int find(T value) {
		int idx = -1;
		for (size_t i = 0; i < size_; ++i) {
			if(data_[i] == value){
				idx = i;
				break;
			}
		}
		return idx;
	}

	inline T read(size_t idx) {
		return data_[idx];
	}

	inline T* pointer() {
		return &data_[0];
	}

	//Writing
	inline void push(T value) {
		data_[size_] = value;
		++size_;
	}

	inline void replace(size_t idx, T value) {
		data_[idx] = value;
	}

	inline void swap(size_t index_a, size_t index_b) {
		T a = data_[index_a];
		data_[index_a] = data_[index_b];
		data_[index_b] = a;
	}

	inline bool remove_by_value(T value) {
		int idx = find(value);
		if (idx >= 0) {
			remove_by_index(idx);
		}
		return idx >= 0;
	}

	inline void remove_by_index(size_t idx) {
		for (size_t i = idx; i < size_; ++i) {
			data_[i] = data_[i + 1];
		}
		--size_;
	}

	inline void insert(size_t idx, T value) {
		for (size_t i = size_; i > idx; --i) {
			data_[i] = data_[i - 1];
		}
		data_[idx] = value;
		++size_;
	}

	//Ascending order. Only sorts the inserted value
	inline void sort(T value){
		size_t idx = size_;

		while((idx) && (data_[idx - 1] >= value)) {
			data_[idx] = data_[idx - 1];
			--idx;
		}

		data_[idx] = value;
		++size_;
	}

private:
	size_t size_ = 0;
	T data_[kMaxSize];
};

#endif
