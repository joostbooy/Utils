#ifndef Stack_h
#define Stack_h


template <typename T, const uint8_t kMaxSize>
class Stack {

public:

    inline void clear(){
        size_ = 0;
    }

    inline uint8_t size(){
        return size_;
    }

    inline bool readable(){
        return size_ > 0;
    }

    inline bool writeable(){
        return size_ < kMaxSize;
    }

	inline uint8_t available() {
		return kMaxSize - size_;
	}

    //Reading
    inline T pop(){
        --size_;
        return data[size_];
    }

    inline T pull(){
        T value = data[0];
        remove_indexed(0);
        return value;
    }

	// -1 if not found
    inline int find(T value){
        int idx = -1;
        for (uint8_t i = 0; i < size_; ++i) {
            if(data[i] == value){
                idx = i;
                break;
            }
        }
        return idx;
    }

    inline T read(uint8_t idx){
        return data[idx];
    }

	inline T* pointer(){
        return &data[0];
    }

    //Writing
    inline void push(T value){
        data[size_] = value;
        ++size_;
    }

    inline void replace(uint8_t idx, T value){
        data[idx] = value;
    }

	inline bool remove_value(T value) {
		int idx = find(value);
		if (idx >= 0) {
			remove_indexed(idx);
		}
		return idx >= 0;
	}

    inline void remove_indexed(uint8_t idx){
        for (int i = idx; i < size_; ++i) {
            data[i] = data[i + 1];
        }
        --size_;
    }

    inline void insert(uint8_t idx, T value){
        for (int i = size_; i > idx; --i) {
            data[i] = data[i - 1];
        }
        data[idx] = value;
        ++size_;
    }

    //Ascending order. Only sorts the inserted value
    inline void sort(T value){
        uint8_t idx = size_;

        while((idx) && (data[idx - 1] >= value)) {
            data[idx] = data[idx - 1];
            --idx;
        }

        data[idx] = value;
        ++size_;
    }

private:
    uint8_t size_ = 0;
    T data[kMaxSize];
};

#endif
