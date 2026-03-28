#include "InputHandler.h"

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>

InputHandler::InputHandler()
	:
		input_log_(0x0000)
{
	input_ = godot::Input::get_singleton();
}

void InputHandler::log_inputs(){
	godot::InputMap* imap = godot::InputMap::get_singleton();
	if(input_ -> is_action_pressed("move_forward")) input_log_ |= INPUT_FORWARD;
	if(input_ -> is_action_pressed("move_backward")) input_log_ |= INPUT_BACKWARD;
	if(input_ -> is_action_pressed("move_right")) input_log_ |= INPUT_RIGHT;
	if(input_ -> is_action_pressed("move_left")) input_log_ |= INPUT_LEFT;
	if(input_ -> is_action_pressed("jump")) input_log_ |= INPUT_JUMP;
}

void InputHandler::clear_input_log(){
	input_log_ = 0x0000;
}

const InputLog& InputHandler::get_input_log() const{
	return input_log_;
}
