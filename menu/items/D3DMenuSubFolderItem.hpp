#pragma once
#include "ID3DMenuItem.hpp"
#include <vector>

class D3DMenuSubFolderItem : public ID3DMenuItem
{
public:
	D3DMenuSubFolderItem(const std::string& _name, const bool is_sub_item = false)
	{
		subfolder = true;

		name = _name;
		sub_item = is_sub_item;
		selected = false;
	}

	std::string get_value_text() const override
	{
		return "";
	}

	void handle_left() override
	{
		opened = !opened;
	}

	void handle_right() override
	{
		opened = !opened;
	}

	void add_sub_item(std::shared_ptr<ID3DMenuItem> item)
	{
		sub_items.emplace_back(item);
	}

	std::vector<std::shared_ptr<ID3DMenuItem>> get_sub_items() const
	{
		return this->sub_items;
	}

	bool is_opened() const
	{
		return this->opened;
	}

private:
	std::vector<std::shared_ptr<ID3DMenuItem>> sub_items;
	bool opened = false;
};
