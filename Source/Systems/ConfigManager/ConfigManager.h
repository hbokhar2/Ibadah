#pragma once

#include <godot_cpp/classes/config_file.hpp>

class ConfigManager
{
public:
	ConfigManager() = default;
	~ConfigManager() = default;

	void loadConfig();
	void modifyConfig(const godot::String &section, const godot::String &key, const godot::Variant &value);
	
private:
	godot::Ref<godot::ConfigFile> config_;
	godot::String configPath_ = "user://config.cfg";
};
