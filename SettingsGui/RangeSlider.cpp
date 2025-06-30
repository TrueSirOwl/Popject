#include "RangeSlider.hpp"

#include <iostream>

	RangeSlider::RangeSlider(int X, int Y, int W, int H): Fl_Widget(X, Y, W, H), min_val(0), max_val(100), low_val(20), high_val(80), lx(0), hx(0){
		knob_offset = (knob_width / w()) * max_val;
		low_input = new Fl_Value_Input(x() - 50, y(), 50, h());
		high_input = new Fl_Value_Input(x() + w(), y(), 50, h());
		low_input->when(FL_WHEN_RELEASE);
		low_input->callback(set_low_val,this);
		high_input->callback(set_high_val,this);
	}

	void RangeSlider::CalculateKnobPosition() {
		double value_size_ratio = (w() - knob_width * 2 - 4) / (max_val - min_val);
		lx = x() + value_size_ratio * low_val + 2;
		hx = x() + value_size_ratio * high_val + knob_width + 2;
	}

	void RangeSlider::draw() {
		// background
		fl_draw_box(FL_DOWN_BOX, x(), y(), w(), h(), FL_BACKGROUND_COLOR);

		// low and high end selector location
		if (high_val > max_val) {
			high_val = max_val;
		}
		if (low_val < min_val) {
			low_val = min_val;
		}

		CalculateKnobPosition();

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

	void RangeSlider::UpdateValueInputs() {
		low_input->value(low_val);
		high_input->value(high_val);
	}

	void RangeSlider::set_low_val(Fl_Widget* w, void* data) {
		RangeSlider* slider = static_cast<RangeSlider*>(data);
		if (slider->low_input->value() < slider->high_val) {
			slider->low_val = slider->low_input->value();
		} else {
			slider->low_val = slider->high_val;
			slider->low_input->value(slider->high_val);
		}
		slider->redraw();
	}

	void RangeSlider::set_high_val(Fl_Widget* w, void* data) {
		RangeSlider* slider = static_cast<RangeSlider*>(data);
		if (slider->high_input->value() > slider->low_val) {
			slider->high_val = slider->high_input->value();
		} else {
			slider->high_val = slider->low_val;
			slider->high_input->value(slider->low_val);
		}
		slider->redraw();
	}

	void RangeSlider::value(double min, double max) {
		this->low_val = min;
		this->high_val = max;
		this->low_input->value(min);
		this->high_input->value(max);
		redraw();
	}

	void RangeSlider::tooltip(const char* text) {
		this->low_input->tooltip(text);
		this->high_input->tooltip(text);
	}

	int RangeSlider::handle(int event) {
		int mx = Fl::event_x();
		CalculateKnobPosition();
		int lx_offset = knob_width / 2;
	
		double val = 0;
		switch (event) {
			case FL_PUSH:
				val = min_val + (mx - x()) * (max_val - min_val) / w();
				if (abs(mx - lx) < abs(mx - hx)) {
					dragging_low = true;
					low_val = val;
				} else {
					dragging_high = true;
					high_val = val;
				}
				redraw();
				do_callback();
				UpdateValueInputs();
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
				UpdateValueInputs();
				return 1;
			case FL_RELEASE:
				dragging_low = dragging_high = false;
				return 1;
		}
		return 0;
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