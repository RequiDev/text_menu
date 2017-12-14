#pragma once
#include "ID3DMenuItem.hpp"

class D3DMenuBoolItem : public ID3DMenuItem
{
public:
	D3DMenuBoolItem(const std::string& _name, bool& value_ptr, const bool is_sub_item = false) :
		ID3DMenuItem(_name, is_sub_item), value(value_ptr) { }

	std::string get_value_text() const override
	{
		return value ? "<On>" : "<Off>";
	}

	void handle_left() override
	{
		value = !value;
	}

	void handle_right() override
	{
		value = !value;
	}

private:
	bool& value;
};
