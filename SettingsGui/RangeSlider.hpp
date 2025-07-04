#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Value_Input.H>
#include "Settings.hpp"
#include <cmath>

class RangeSlider : public Fl_Widget {
	double min_val, max_val;
	int low_val, high_val;
	bool dragging_low = false;
	bool dragging_high = false;
	int knob_width = 10;
	int lower_button_offset = 2;
	int knob_offset;
	int lx, hx;
	double temphval;
	double templval;
	bool habove = false;
	bool lunder = false;
	double stepval;

	bool value_shoving = false;

	Fl_Value_Input* low_input = NULL;
	Fl_Value_Input* high_input = NULL;

	static void set_low_val(Fl_Widget* w, void* data);
	static void set_high_val(Fl_Widget* w, void* data);

	void limit_vals();
	void reset_val_limiting();

	public:
	void tooltip(const char* text);
	void value(double min, double max);
	RangeSlider(int X, int Y, int W, int H, const char* name, Settings* sett);
	void draw() override;
	int handle(int event) override;
	void set_low(double v);
	void set_high(double v);
	double get_low_value();
	double get_high_value();
	void set_bounds(double minv, double maxv);
	void maximum(double maximum);
	void minimum(double minimum);
	void CalculateKnobPosition();
	void UpdateValueInputs();
	void step(double step);
};