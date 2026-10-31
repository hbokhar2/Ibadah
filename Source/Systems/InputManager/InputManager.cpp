#include "InputManager.h"

#include <godot_cpp/classes/input_event_mouse_motion.hpp>

InputManager::InputManager(){
	mouseDelta_ = godot::Vector2();

	inputFrame_.buttons = 0x00;
	inputFrame_.cameraDelta = godot::Vector2();

	producerIndex_ = 0;
	consumerIndex_ = 0;
}

void InputManager::processInputPoll(){
	godot::Input* inputEvent = godot::Input::get_singleton();

	if(inputEvent -> is_action_pressed("move_forward")) inputFrame_.buttons |= INPUT_FORWARD;
	if(inputEvent -> is_action_pressed("move_backward")) inputFrame_.buttons|= INPUT_BACKWARD;
	if(inputEvent -> is_action_pressed("move_right")) inputFrame_.buttons |= INPUT_RIGHT;
	if(inputEvent -> is_action_pressed("move_left")) inputFrame_.buttons |= INPUT_LEFT;

	if(inputEvent -> is_action_pressed("jump")) inputFrame_.buttons |= INPUT_JUMP;
	if(inputEvent -> is_action_pressed("sprint_hold")) inputFrame_.buttons |= INPUT_SPRINT;
}

void InputManager::processInputEvent(const godot::Ref<godot::InputEvent>& pEvent){
	godot::Ref<godot::InputEventMouseMotion> mouseMotion = pEvent;

	if(mouseMotion.is_valid())
		inputFrame_.cameraDelta += mouseMotion -> get_relative();
}

void InputManager::commitInputFrame(){
	inputLog_[producerIndex_] = inputFrame_;
	producerIndex_ = (producerIndex_ + 1) % inputLog_.size();

	inputFrame_.buttons = 0x0000; 
	inputFrame_.cameraDelta = godot::Vector2();
}

//This relies on commit_input_frame() being executed before this function.
//Ideally commit_input_frame() and get_unprocessed_frame() should be ran in
//any order.
InputFrame& InputManager::getUnprocessedInputFrame(){
	InputFrame& retVal = inputLog_[consumerIndex_];
	consumerIndex_ = (consumerIndex_ + 1) % inputLog_.size();

	return retVal;
}
