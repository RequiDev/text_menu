#pragma once
#include "ID3DMenuItem.hpp"
#include <sstream>
#include <iomanip>

class D3DMenuFloatItem : public ID3DMenuItem
{
public:
	D3DMenuFloatItem(const std::string& _name, float& value_ptr, const float _min, const float _max, const float _steps, const bool is_sub_item = false):
		ID3DMenuItem(_name, is_sub_item), value(value_ptr), min_value(_min), max_value(_max), step_value(_steps) {}

	std::string get_value_text() const override
	{
		std::ostringstream out;
		out << "<" << std::setprecision(2) << value << ">";
		return out.str();
	}
	
	void handle_left() override
	{
		value -= step_value;
		if (value < min_value)
			value = min_value;
	}
	
	void handle_right() override
	{
		value += step_value;
		if (value > max_value)
			value = max_value;
	}

private:
	float& value;
	float min_value;
	float max_value;
	float step_value;
};
