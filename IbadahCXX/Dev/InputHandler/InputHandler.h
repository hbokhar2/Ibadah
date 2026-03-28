/***
 *
 *
 * */

#pragma once

#include <cstdint>

#include <godot_cpp/classes/input.hpp>

#define INPUT_FORWARD (1u)
#define INPUT_BACKWARD (1u << 1)
#define INPUT_RIGHT (1u << 2)
#define INPUT_LEFT (1u << 3)
#define INPUT_JUMP (1u << 4)
#define INPUT_CROUCH (1u << 5)
#define INPUT_INTERACT (1u << 6)
#define INPUT_PLACE (1u << 7)
#define INPUT_RECORD_MIC (1u << 8)

using InputLog = uint16_t;

class InputHandler{

	public:
		InputHandler();

		void rebind_key();

		void log_inputs();
		void clear_input_log();
		const InputLog& get_input_log() const;
	
	private:
		InputLog input_log_;
		godot::Input* input_;

};
