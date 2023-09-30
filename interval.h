#ifndef Interval_h
#define Interval_h


template <typename T>
class Interval {

public:

	void reset(T curr_tick = 0){
		last_update = curr_tick;
	}

	void set(T interval) {
		update_interval = interval;
	}

	bool update(T curr_tick) {
		if (T(curr_tick - last_update) >= update_interval) {
			last_update += update_interval;
			return 1;
		}
		return 0;
	}

	T get(T curr_tick) {
		T res = curr_tick - last_update;
		last_update = curr_tick;
		return res;
	}

private:
	T last_update = 0;
	T update_interval = 0;
};


#endif
