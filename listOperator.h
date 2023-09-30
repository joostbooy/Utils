#ifndef ListOperator_h
#define ListOperator_h


class ListOperator {

public:

	void init(void *pool, void *size, int max) {
		*size = 0;
		for (int i = 0; i < max; ++i) {
			pool[i] = i;
		}
	}

	size_t add(void *list, void *pool, void *size) {
		int size_ = *size;
		int index = pool[size_];
		list[size_] = index;
		*size = size_ + 1;
		return index;
	}

	void swap_with_left(void *list, int list_index) {
		int left = list[list_index - 1];
		list[list_index - 1] = list[list_index];
		list[list_index] = left;
	}

	void swap_with_right(void *list, int list_index) {
		int right = list[list_index + 1];
		list[list_index + 1] = list[list_index];
		list[list_index] = right;
	}

	int find(void *list, int value) {
		int list_index = -1;
		for (int i = 0; i < *size; ++i) {
			if (list[i] == value) {
				list_index = i;
				break;
			}
		}
		return list_index;
	}

	void remove(void *list, void *pool, void *size, int list_index) {
		*size -= 1;
		int index = list[list_index];
		pool[*size] = index;

		for (int i = list_index; i < *size; ++i) {
			list[i] = list[i + 1];
		}
	}

};


class SortedListOperator {

public:

	void init(size_t *size) {
		*size = 0;
	}

	void add(void *list, void *size, int value) {
		size_t size_ = *size;
		size_t index = *size;

		while(index > 0 && list[index - 1] >= value) {
			list[index] = list[index - 1];
			--index;
		}
		list[index] = value;

		*size = size_ + 1;
	}

	void remove(void *list, void *size, int value) {
		size_t size_ = *size;
		for (size_t i = 0; i < size_; ++i) {
			if (list[i] == value) {
				for (size_t j = i; j < size_; ++j) {
					list[i] = list[i + 1];
				}
				*size = size_ - 1;
				return;
			}
		}
	}

};


#endif
