#ifndef StringUtils_h
#define StringUtils_h

class StringUtils {

public:

	static int length(const char* text) {
		int length_ = 0;
		while (*text++ != '\0') {
			++length_;
		}
		return length_;
	}

	static void copy(char* dest, char* src, int max_length) {
		while (--max_length > 0 && *src != '\0') {
			*dest++ = *src++;
		}
		*dest = '\0';
	}

	static bool has_extension(const char* name, const char* extension) {
		while (*name != '.') {
			if (*name++ == '\0') {
				return false;
			}
		}
		return StringUtils::text_is_equal(name, extension);
	}

	static bool text_is_equal(const char* a, const char* b) {
		while ((*a != '\0') && (*b != '\0')) {
			if (*a++ != *b++) {
				return false;
			}
		}
		return (*a == '\0') && (*b == '\0');
	}

	static void split_extension(const char* text, char* to_path, char* to_extension) {
		while (*text != '\0' && *text != '.') {
			*to_path++ = *text++;
		}

		*to_path++ = '\0';

		while (*text != '\0') {
			*to_extension++ = *text++;
		}

		*to_extension++ = '\0';
	}

	static void get_file_name_from_path(char* path, char* to_name) {
		bool has_file = false;
		int length_ = StringUtils::length(path);
		char* path_ = path + length_;

		while (length_--) {
			if (*path_ == '.') {
				has_file = true;
			} else if (*path_ == '/' && has_file == true) {
				while (*path_++ != '\0') {
					*to_name++ = *path_;
				}
				break;
			}
			--path_;
		}

		*to_name = '\0';
	}

};

#endif
