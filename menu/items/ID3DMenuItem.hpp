#pragma once
#include <string>

class ID3DMenuItem
{
public:
	ID3DMenuItem(const std::string& _name, const bool is_sub_item = false, const bool is_subfolder = false) :
		name(_name), sub_folder(is_subfolder), selected(false), sub_item(is_sub_item) {}

	virtual ~ID3DMenuItem() {}
	virtual std::string get_value_text() const = 0;
	virtual void handle_left() = 0;
	virtual void handle_right() = 0;

	virtual std::string get_name() const
	{
		return this->name;
	}

	virtual bool is_subfolder() const
	{
		return this->sub_folder;
	}

	virtual bool& is_selected()
	{
		return this->selected;
	}

	virtual bool is_sub_item() const
	{
		return this->sub_item;
	}

protected:
	std::string name;
	bool sub_folder = false;
	bool selected = false;
	bool sub_item = false;
};