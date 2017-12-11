#pragma once
#include <string>

class ID3DMenuItem
{
public:
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
		return this->subfolder;
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
	bool subfolder = false;
	bool selected = false;
	bool sub_item = false;
};