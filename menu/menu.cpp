#include "menu.hpp"
#include "settings.hpp"
#include "../overlay/overlay.hpp"
#include "items/ID3DMenuItem.hpp"
#include "items/D3DMenuBoolItem.hpp"
#include "items/D3DMenuSubFolderItem.hpp"
#include "items/D3DMenuFlagItem.hpp"
#include "items/D3DMenuIntItem.hpp"
#include "items/D3DMenuFloatItem.hpp"

text_menu::text_menu()
{
	auto esp = std::make_shared<D3DMenuSubFolderItem>("ESP");
	esp->add_sub_item(std::make_shared<D3DMenuBoolItem>("Draw Players", settings::esp::player, true));
	esp->add_sub_item(std::make_shared<D3DMenuBoolItem>("Draw Skeletons", settings::esp::skeleton, true));
	esp->add_sub_item(std::make_shared<D3DMenuBoolItem>("Draw Boxes", settings::esp::boxes, true));
	esp->add_sub_item(std::make_shared<D3DMenuIntItem>("Max Distance", settings::esp::distance, 50, 1000, 50, true));
	esp->add_sub_item(std::make_shared<D3DMenuBoolItem>("Draw Loot", settings::esp::loot, true));
	esp->add_sub_item(std::make_shared<D3DMenuBoolItem>("Draw Vehicle", settings::esp::vehicle, true));

	auto loot = std::make_shared<D3DMenuSubFolderItem>("Loot Mode", true);
	loot->add_sub_item(std::make_shared<D3DMenuFlagItem>("All", settings::esp::loot_mode, LootMode::ALL, true));
	loot->add_sub_item(std::make_shared<D3DMenuFlagItem>("Weapon", settings::esp::loot_mode, LootMode::WEAPONS, true));
	loot->add_sub_item(std::make_shared<D3DMenuFlagItem>("Ammo", settings::esp::loot_mode, LootMode::AMMO, true));
	loot->add_sub_item(std::make_shared<D3DMenuFlagItem>("Medical", settings::esp::loot_mode, LootMode::MEDIC, true));
	loot->add_sub_item(std::make_shared<D3DMenuFlagItem>("Equipment", settings::esp::loot_mode, LootMode::EQUIPMENT, true));
	loot->add_sub_item(std::make_shared<D3DMenuFlagItem>("Attachment", settings::esp::loot_mode, LootMode::ATTACHMENTS, true));

	esp->add_sub_item(loot);

	auto player_speed = std::make_shared<D3DMenuFloatItem>("Player Speed", settings::player_speed, 0.1f, 3.0f, 0.1f);

	menu_items.emplace_back(esp);
	menu_items.emplace_back(player_speed);

	menu_items.at(0)->is_selected() = true;

	font_height = overlay->get_string_height("MENU_STRING_TO_DETERMINE_HEIGHT");
	overlay->add_callback(std::bind(&text_menu::render, this));
}

void text_menu::render()
{
	menu_height = -static_cast<int>(font_height * 0.75f);

	// BattlEye doesn't like LL keyboard hooks.
	if (GetAsyncKeyState(VK_LEFT) & 1)
		handle_left();
	else if (GetAsyncKeyState(VK_RIGHT) & 1)
		handle_right();
	else if (GetAsyncKeyState(VK_UP) & 1)
		handle_up();
	else if (GetAsyncKeyState(VK_DOWN) & 1)
		handle_down();

	for (const auto& item : menu_items)
	{
		draw_menu_item(item);
	}

	overlay->draw_gradient_box_outline({ 0, 0 }, 150, static_cast<int>(menu_height + font_height * 1.5f + 3), D3DCOLOR_XRGB(41, 43, 54), D3DCOLOR_XRGB(25, 26, 32), true);
}

void text_menu::draw_menu_item(std::shared_ptr<ID3DMenuItem> item, const float padding)
{
	auto color = D3DCOLOR_XRGB(255, 255, 255);
	if (item->is_selected())
		color = D3DCOLOR_XRGB(60, 140, 255);

	auto name = item->get_name();

	if (item->is_subfolder())
	{
		const auto folder = std::static_pointer_cast<D3DMenuSubFolderItem>(item);

		if (folder->is_opened())
			name = "[ – ] " + item->get_name();
		else
			name = "[ + ] " + item->get_name();
	}

	overlay->draw_string({ 5 + padding, 3.f + static_cast<float>(menu_height += font_height) }, FONT_LEFT, color, "%s %s", name.c_str(), item->get_value_text().c_str());

	if (item->is_subfolder() && std::static_pointer_cast<D3DMenuSubFolderItem>(item)->is_opened())
	{
		static auto length = overlay->get_string_width("[ - ] ");
		
		for(const auto& sub : std::static_pointer_cast<D3DMenuSubFolderItem>(item)->get_sub_items())
		{
			draw_menu_item(sub, padding + length + 6.f);
		}
	}
}

std::vector<std::shared_ptr<ID3DMenuItem>> text_menu::get_all_visible_items()
{
	std::vector<std::shared_ptr<ID3DMenuItem>> ret;

	std::function<void(const std::vector<std::shared_ptr<ID3DMenuItem>>& list)> add_folder_items;
	add_folder_items = [&](const std::vector<std::shared_ptr<ID3DMenuItem>>& list)
	{
		for (const auto& item : list)
		{
			ret.emplace_back(item);

			if (item->is_subfolder())
			{
				auto folder = std::static_pointer_cast<D3DMenuSubFolderItem>(item);

				if (folder->is_opened())
					add_folder_items(folder->get_sub_items());
			}
		}
	};

	add_folder_items(menu_items);

	return ret;
}

std::shared_ptr<ID3DMenuItem> text_menu::get_current_selected()
{
	auto items = get_all_visible_items();
	for (const auto& item : items)
	{
		if (item->is_selected()) return item;
	}

	return nullptr;
}

void text_menu::handle_left()
{
	auto current = get_current_selected();
	if (!current) return;
	current->handle_left();
}

void text_menu::handle_right()
{
	auto current = get_current_selected();
	if (!current) return;
	current->handle_right();
}

void text_menu::handle_up()
{
	auto items = get_all_visible_items();

	auto current = get_current_selected();
	auto index = std::find(items.begin(), items.end(), current) - items.begin();

	if (index == 0)
		return;

	index--;

	auto indexed = items[index];
	current->is_selected() = false;
	indexed->is_selected() = true;
}

void text_menu::handle_down()
{
	auto items = get_all_visible_items();

	auto current = get_current_selected();
	auto index = std::find(items.begin(), items.end(), current) - items.begin();

	if (index >= static_cast<int>(items.size() - 1))
		return;

	index++;

	auto indexed = items[index];
	current->is_selected() = false;
	indexed->is_selected() = true;
}
