#include "RangeSlider.hpp"

#include <iostream>

	RangeSlider::RangeSlider(int X, int Y, int W, int H): Fl_Widget(X, Y, W, H), min_val(0), max_val(100), low_val(20), high_val(80), lx(0), hx(0){
		knob_offset = (knob_width / w()) * max_val;
	}

	void RangeSlider::XX() {
		double value_size_ratio = (w() - knob_width * 2 - 4) / (max_val - min_val);
		lx = x() + value_size_ratio * low_val + 2;
		hx = x() + value_size_ratio * high_val + knob_width + 2;
	}


	void RangeSlider::draw() {
		// background
		fl_draw_box(FL_DOWN_BOX, x(), y(), w(), h(), FL_BACKGROUND_COLOR);

		// low and high end selector location
		XX();

		// selected range
		fl_color(136);
		fl_rectf(lx + knob_width, y() + lower_button_offset, hx - lx - lower_button_offset, h()-4);

		// selectors
		if (hx < lx + knob_width) {
			hx = lx + knob_width;
		}
		fl_draw_box(FL_UP_BOX, lx, y() + lower_button_offset, knob_width, h()-4, FL_LIGHT2);
		fl_draw_box(FL_UP_BOX, hx, y() + lower_button_offset, knob_width, h()-4, FL_LIGHT2);
	}

	int RangeSlider::handle(int event) {
		int mx = Fl::event_x();
		XX();
		int lx_offset = knob_width / 2;
	
		double val = 0;
		switch (event) {
			case FL_PUSH:
				val = min_val + (mx - x()) * (max_val - min_val) / w();
				if (abs(mx - lx) < abs(mx - hx)) {
					std::cout << abs(mx - lx - knob_width) << std::endl;
					dragging_low = true;
					low_val = val;
				} else {
					dragging_high = true;
					high_val = val;
				}
				redraw();
				do_callback();
				return 1;
			case FL_DRAG:
				if (dragging_low || dragging_high) {
					val = min_val + (mx - x()) * (max_val - min_val) / w();
					if (val < min_val) {
						val = min_val;
					}
					if (val > max_val) {
						val = max_val;
					}
					if (dragging_low) {
						if (val > high_val) {
							val = high_val;
						}
						low_val = val;
					} else {
						if (val < low_val) {
							val = low_val;
						}
						high_val = val;
					}
					std::cout << val << std::endl;
					redraw();
					do_callback(); // notify changes
				}
				return 1;
			case FL_RELEASE:
				dragging_low = dragging_high = false;
				return 1;
		}
		return 0;
	}

	double RangeSlider::low() const {
		return low_val;
	}

	double RangeSlider::high() const {
		return high_val;
	}

	void RangeSlider::set_low(double v) {
		if (v <= high_val && v >= min_val) {
			low_val = v;
			redraw();
		}
	}

	void RangeSlider::set_high(double v) {
		if (v >= low_val && v <= max_val) {
			high_val = v;
			redraw();
		}
	}

	void RangeSlider::set_bounds(double minv, double maxv) {
		min_val = minv;
		max_val = maxv;
		if (low_val < minv) low_val = minv;
		if (high_val > maxv) high_val = maxv;
		redraw();
	}


	void RangeSlider::maximum(double maximum) {
		max_val = maximum;
		knob_offset = (knob_width / w()) * max_val;
		if (high_val >= max_val) {
			high_val = max_val;
			redraw();
		}
	}

	void RangeSlider::minimum(double minimum) {
		min_val = minimum;
		if (low_val <= min_val) {
			low_val = min_val;
			redraw();
		}
	}