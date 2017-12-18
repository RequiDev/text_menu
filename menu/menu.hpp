#pragma once
#include <vector>
#include <memory>

class ID3DMenuItem;

class text_menu
{
public:
	text_menu();
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