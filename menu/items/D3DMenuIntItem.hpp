#pragma once
#include "ID3DMenuItem.hpp"

class D3DMenuIntItem : public ID3DMenuItem
{
public:
	D3DMenuIntItem(const std::string& _name, int* value_ptr, const int _min, const int _max, const int _steps, const bool is_sub_item = false)
	{
		name = _name;
		sub_item = is_sub_item;
		value = value_ptr;
		min_value = _min;
		max_value = _max;
		step_value = _steps;
		selected = false;
	}

	std::string get_value_text() const override
	{
		return XorStr("<") + std::to_string(*value) + XorStr(">");
	}

	void handle_left() override
	{
		*value -= step_value;
		if (*value < min_value)
			*value = min_value;
	}

	void handle_right() override
	{
		*value += step_value;
		if (*value > max_value)
			*value = max_value;
	}

private:
	int* value;
	int min_value;
	int max_value;
	int step_value;
};