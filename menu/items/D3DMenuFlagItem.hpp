#pragma once
#include "ID3DMenuItem.hpp"

class D3DMenuFlagItem : public ID3DMenuItem
{
public:
	D3DMenuFlagItem(const std::string& _name, int& value_ptr, const int _flag, const bool is_sub_item = false) :
		ID3DMenuItem(_name, is_sub_item), flag(_flag), value(value_ptr) { }

	std::string get_value_text() const override
	{
		return (value & flag) == flag ? "<On>" : "<Off>";
	}

	void handle_left() override
	{
		if ((value & flag) == flag)
			value &= ~flag;
		else
			value |= flag;

	}

	void handle_right() override
	{
		if ((value & flag) == flag)
			value &= ~flag;
		else
			value |= flag;
	}

private:
	int flag;
	int& value;
};
