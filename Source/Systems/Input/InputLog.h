#pragma once

#include <cstdint>
#include <vector>

#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_key.hpp>

#define INPUT_FORWARD (1u)
#define INPUT_BACKWARD (1u << 1)
#define INPUT_RIGHT (1u << 2)
#define INPUT_LEFT (1u << 3)
#define INPUT_JUMP (1u << 4)
#define INPUT_CROUCH (1u << 5)
#define INPUT_INTERACT (1u << 6)
#define INPUT_PLACE (1u << 7)
#define INPUT_RECORD_MIC (1u << 8)

using Log = std::vector<uint16_t>;

class InputLog
{
	public:
		InputLog();

		void update_input_hashmap();

		void record_input(godot::Ref<godot::InputEvent>& p_event);
		void clear_input_log();
		const Log& get_input_log() const;
	
	private:
		Log input_log_;
		godot::TypedArray<godot::StringName> input_map_;
};
