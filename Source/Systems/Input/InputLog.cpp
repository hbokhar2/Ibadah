#include "InputLog.h"

#include <godot_cpp/classes/input_event_mouse_motion.hpp>

InputLog::InputLog()
{
	mouse_delta_ = godot::Vector2();

	input_frame_.buttons = 0x00;
	input_frame_.camera_delta = godot::Vector2();

	producer_index_ = 0;
	consumer_index_ = 0;
}

void InputLog::process_input_poll()
{
	godot::Input* input_event = godot::Input::get_singleton();

	if(input_event -> is_action_pressed("move_forward")) input_frame_.buttons |= INPUT_FORWARD;
	if(input_event -> is_action_pressed("move_backward")) input_frame_.buttons|= INPUT_BACKWARD;
	if(input_event -> is_action_pressed("move_right")) input_frame_.buttons |= INPUT_RIGHT;
	if(input_event -> is_action_pressed("move_left")) input_frame_.buttons |= INPUT_LEFT;
	if(input_event -> is_action_pressed("jump")) input_frame_.buttons |= INPUT_JUMP;
}

void InputLog::process_input_event(const godot::Ref<godot::InputEvent>& p_event)
{
	godot::Ref<godot::InputEventMouseMotion> motion = p_event;

	if(motion.is_valid())
		input_frame_.camera_delta += motion -> get_relative();
}

void InputLog::commit_input_frame()
{
	input_log_[producer_index_] = input_frame_;
	producer_index_ = (producer_index_ + 1) % input_log_.size();

	input_frame_.buttons = 0x0000; 
	input_frame_.camera_delta = godot::Vector2();
}

//This relies on commit_input_frame() being executed before this function.
//Ideally commit_input_frame() and get_unprocessed_frame() should be ran in
//any order.
InputFrame& InputLog::get_unprocessed_frame()
{
	InputFrame& input_frame = input_log_[consumer_index_];
	consumer_index_ = (consumer_index_ + 1) % input_log_.size();
	return input_frame;
}
