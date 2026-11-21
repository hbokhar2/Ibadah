#include "ConfigManager.h"

#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/input_event_key.hpp>

void ConfigManager::loadConfig() 
{
	config_.instantiate();
	godot::Error err = config_ -> load(configPath_);

	if(err != godot::OK)
	{

		modifyConfig("meta", "default", true);

		modifyConfig("settings", "mouse_sens", 0.0010);

		modifyConfig("settings", "move_forward", "W");
		modifyConfig("settings", "move_backward", "S");
		modifyConfig("settings", "move_right", "D");
		modifyConfig("settings", "move_left", "A");
		modifyConfig("settings", "jump", "Space");
		modifyConfig("settings", "sprint", "Shift");
		modifyConfig("settings", "toggle_sprint", false);
		modifyConfig("settings", "hold_sprint", true);

		config_ -> save(configPath_);
	}

	godot::InputMap *inputMap = godot::InputMap::get_singleton();

	auto bind = [&](const godot::String &action, const godot::String &configKey, const godot::String &fallback)
	{
		godot::String keyString = config_ -> get_value("settings", configKey, fallback);

		godot::Key keycode = (godot::Key)godot::OS::get_singleton() -> find_keycode_from_string(keyString);

		if (!inputMap -> has_action(action)) 
		{
			inputMap -> add_action(action);
		}

		inputMap -> action_erase_events(action);

		godot::Ref<godot::InputEventKey> ev;
		ev.instantiate();
		ev -> set_keycode(keycode);
		ev -> set_pressed(true);

		inputMap -> action_add_event(action, ev);
	};

	bind("move_forward", "move_forward", "W");
	bind("move_backward", "move_backward", "S");
	bind("move_right", "move_right", "D");
	bind("move_left", "move_left", "A");
	bind("jump", "jump", "Space");
	bind("sprint_hold", "sprint", "Shift");

}

void ConfigManager::modifyConfig(const godot::String &section, const godot::String &key, const godot::Variant &value)
{
	if(!config_ -> has_section_key(section, key)) 
	{
		config_ -> set_value(section, key, value);
	}
}
