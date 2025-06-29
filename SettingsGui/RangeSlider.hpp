#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>


class RangeSlider : public Fl_Widget {
	double min_val, max_val;
	double low_val, high_val;
	bool dragging_low = false;
	bool dragging_high = false;
	int knob_width = 10;
	int lower_button_offset = 2;
	int knob_offset;

	int lx, hx;

public:
	RangeSlider(int X, int Y, int W, int H);
	void draw() override;
	int handle(int event) override;
	double low() const;
	double high() const;
	void set_low(double v);
	void set_high(double v);
	void set_bounds(double minv, double maxv);
	void maximum(double maximum);
	void minimum(double minimum);
	void XX();
};