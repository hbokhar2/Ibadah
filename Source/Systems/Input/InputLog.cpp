#include "InputLog.h"

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

InputLog::InputLog()
{
}

void InputLog::update_input_hashmap()
{
	input_map_ = godot::InputMap::get_singleton() -> get_actions();
}

void InputLog::record_input(godot::Ref<godot::InputEvent>& p_event)
{
	if(p_event -> is_class("InputEventKey"))
	{
		godot::Ref<godot::InputEventKey> key_event = p_event;

	}

	/*Map input to in game action, and log it here.*/

	if(input_log_.size() == 32)
	{
		input_log_.pop_back();
	}
}

void InputLog::clear_input_log()
{
	input_log_.clear();
}

const Log& InputLog::get_input_log() const{
	return input_log_;
}
