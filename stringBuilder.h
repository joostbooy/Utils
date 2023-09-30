#ifndef StringBuilder_h
#define StringBuilder_h

#include "stmf4lib.h"

class StringBuilder {

public:

	StringBuilder(char* ptr, int kMax) {
		char_buff_ = ptr;
		kMax_ = kMax;
		clear();
	}

	void clear() {
		pos = 0;
		char_buff_[0] = '\0';
	}

	uint8_t length() {
		return pos;
	}

	const char* read()  {
		return char_buff_;
	}

	void truncate(uint8_t last) {
		if (last < pos) {
			pos = last;
			char_buff_[pos] = '\0';
		}
	}

	// Char
	const char* append(const char* txt) {
		copy(&char_buff_[pos], txt);
		return read();
	}

	const char* prepend(const char* txt) {
		char copy_buff[kMax_];
		for (int i = 0; i <= pos; ++i) {
			copy_buff[i] = char_buff_[i];
		}
		write(txt, &copy_buff[0]);
		return read();
	}

	// Int
	const char* append(int32_t value) {
		char int_buffer[kMax_];
		itoa(value, int_buffer, 10);
		copy(&char_buff_[pos], int_buffer);
		return read();
	}

	const char* prepend(int32_t value) {
		char copy_buff[kMax_];
		for (int i = 0; i <= pos; ++i) {
			copy_buff[i] = char_buff_[i];
		}
		write(value, &copy_buff[0]);
		return read();
	}

	// Builders
	template <typename type_a>
	const char* write(type_a a) {
		clear();
		append(a);
		return read();
	}

	template <typename type_a, typename type_b>
	const char* write(type_a a, type_b b) {
		clear();
		append(a);
		append(b);
		return read();
	}

	template <typename type_a, typename type_b, typename type_c>
	const char* write(type_a a, type_b b, type_c c) {
		clear();
		append(a);
		append(b);
		append(c);
		return read();
	}

	template <typename type_a, typename type_b, typename type_c, typename type_d>
	const char* write(type_a a, type_b b, type_c c, type_d d) {
		clear();
		append(a);
		append(b);
		append(c);
		append(d);
		return read();
	}

	template <typename type_a, typename type_b, typename type_c, typename type_d, typename type_e>
	const char* write(type_a a, type_b b, type_c c, type_d d, type_e e) {
		clear();
		append(a);
		append(b);
		append(c);
		append(d);
		append(e);
		return read();
	}

	template <typename type_a, typename type_b, typename type_c, typename type_d, typename type_e, typename type_f>
	const char* write(type_a a, type_b b, type_c c, type_d d, type_e e, type_f f) {
		clear();
		append(a);
		append(b);
		append(c);
		append(d);
		append(e);
		append(f);
		return read();
	}

private:
	uint8_t pos = 0;
	char* char_buff_;
	int kMax_;

	void copy(char* dest, const char* src) {
		if (pos >= kMax_) { return; }

		while (*src != '\0') {
			*dest++ = *src++;
			if (++pos >= kMax_){
				break;
			}
		}
		*dest = '\0';
	}
};


template <const uint8_t kMax>
class StringBuilderBase : public StringBuilder {

public:
	StringBuilderBase() : StringBuilder(char_buff, kMax) {};

private:
	char char_buff[kMax + 1];
};


#endif
