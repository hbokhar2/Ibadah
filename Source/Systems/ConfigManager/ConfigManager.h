#pragma once

#include <godot_cpp/core/object.hpp>
#include <godot_cpp/classes/config_file.hpp>

class ConfigManager{
	public:
		ConfigManager();
		~ConfigManager();

		void addSetting(const godot::String &section, const godot::String &name, const godot::Variant value);
		godot::Variant loadSetting(const godot::String &section, const godot::String &name);	

	private:
		constexpr godot::String kfilePath = "user://pref.cfg";
		godot::Ref<ConfigFile> configFile_;
};
