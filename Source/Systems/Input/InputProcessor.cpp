#include "InputProcessor.h"

#include <godot_cpp/classes/input_event_mouse_motion.hpp>

Input::InputProcessor::InputProcessor(uint8_t playerId)
{
	m_mouseDelta = godot::Vector2();

	m_inputFrame.buttons = 0x00;
	m_inputFrame.cameraDelta = godot::Vector2();

	m_producerIndex = 0;
	m_consumerIndex = 0;

	m_playerId = playerId;
}

void Input::InputProcessor::processInputPoll()
{
	godot::Input* inputEvent = godot::Input::get_singleton();

	if(inputEvent -> is_action_pressed("move_forward")) m_inputFrame.buttons |= INPUT_FORWARD;
	if(inputEvent -> is_action_pressed("move_backward")) m_inputFrame.buttons|= INPUT_BACKWARD;
	if(inputEvent -> is_action_pressed("move_right")) m_inputFrame.buttons |= INPUT_RIGHT;
	if(inputEvent -> is_action_pressed("move_left")) m_inputFrame.buttons |= INPUT_LEFT;
	if(inputEvent -> is_action_pressed("jump")) m_inputFrame.buttons |= INPUT_JUMP;
}

void Input::InputProcessor::processInputEvent(const godot::Ref<godot::InputEvent>& p_event)
{
	godot::Ref<godot::InputEventMouseMotion> motion = p_event;

	if(motion.is_valid())
		m_inputFrame.cameraDelta += motion -> get_relative();
}

void Input::InputProcessor::commitInputFrame()
{
	m_inputLog[m_producerIndex] = m_inputFrame;
	m_producerIndex = (m_producerIndex + 1) % m_inputLog.size();

	m_inputFrame.buttons = 0x0000; 
	m_inputFrame.cameraDelta = godot::Vector2();
}

//This relies on commit_input_frame() being executed before this function.
//Ideally commit_input_frame() and get_unprocessed_frame() should be ran in
//any order.
Input::InputFrame& Input::InputProcessor::getUnprocessedFrame()
{
	InputFrame& m_inputFrame = m_inputLog[m_consumerIndex];
	m_consumerIndex = (m_consumerIndex + 1) % m_inputLog.size();
	return m_inputFrame;
}
