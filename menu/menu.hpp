#pragma once
#include <vector>
#include <memory>
#include "items/ID3DMenuItem.hpp"

class text_menu
{
public:
	void setup();
private:
	void render();
	void draw_menu_item(std::shared_ptr<ID3DMenuItem> item, float padding = 0.f);
	std::vector<std::shared_ptr<ID3DMenuItem>> get_all_visible_items();
	std::shared_ptr<ID3DMenuItem> get_current_selected();

	void handle_left();
	void handle_right();
	void handle_up();
	void handle_down();

	int font_height;
	int menu_height = 5;

	std::vector<std::shared_ptr<ID3DMenuItem>> menu_items;
};