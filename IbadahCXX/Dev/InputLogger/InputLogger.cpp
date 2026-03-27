#include "InputLogger.h"

#include <godot_cpp/classes/input.hpp>

void InputLogger::read_cont_inputs(void){
	godot::Input* input = godot::Input::get_singleton();

	if(input -> is_key_pressed(godot::KEY_W)) input_logs_.continuous_inputs |= INPUT_FORWARD;
	if(input -> is_key_pressed(godot::KEY_S)) input_logs_.continuous_inputs |= INPUT_BACKWARD;
	if(input -> is_key_pressed(godot::KEY_D)) input_logs_.continuous_inputs |= INPUT_RIGHT;
	if(input -> is_key_pressed(godot::KEY_A)) input_logs_.continuous_inputs |= INPUT_LEFT;
	if(input -> is_key_pressed(godot::KEY_V)) input_logs_.continuous_inputs |= INPUT_PUSHTOTALK;
}

void InputLogger::read_interupt_inputs(void){
	
}

void InputLogger::zero_input_log(){
	input_logs_.continuous_inputs = 0x00;
	input_logs_.interrupt_inputs = 0x00;
}

const InputLog& InputLogger::get_input_log() const{
	return input_logs_;
}
