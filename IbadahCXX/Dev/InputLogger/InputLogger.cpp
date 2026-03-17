#include "InputLogger.h"

#include <godot_cpp/classes/input.hpp>

void InputLogger::readContinuousInputs(void){
	godot::Input* input = godot::Input::get_singleton();

	if(input -> is_key_pressed(godot::KEY_W)) m_inputLogs.continuousInputs |= INPUT_FORWARD;
	if(input -> is_key_pressed(godot::KEY_S)) m_inputLogs.continuousInputs |= INPUT_BACKWARD;
	if(input -> is_key_pressed(godot::KEY_D)) m_inputLogs.continuousInputs |= INPUT_RIGHT;
	if(input -> is_key_pressed(godot::KEY_A)) m_inputLogs.continuousInputs |= INPUT_LEFT;
	if(input -> is_key_pressed(godot::KEY_V)) m_inputLogs.continuousInputs |= INPUT_PUSHTOTALK;
}

void InputLogger::zeroOutInputLog(void){
	m_inputLogs.continuousInputs = 0x00;
	m_inputLogs.interruptInputs = 0x00;
}

void InputLogger::readInterruptInputs(void){
	
}

InputLogs InputLogger::getInputLogs() const{
	return m_inputLogs;
}
