#include "Player.h"

#include <algorithm>
#include <cmath>

#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

//This is just a temporary way to quickly set my mouse sensitivity.
//This value should not be defined here. In the future it should of course
//be modified in a settings menu.
#define MOUSE_SENS 0.0025

#define GRAVITY 7
#define WALK_SPEED 0.75
#define RUN_SPEED 1.15
#define JUMP_SPEED 1.75

Player::Player()
	:
		m_direction(godot::Vector3(0, 0, 0)),
		m_velocity(0, 0, 0),
		m_characterInstance(nullptr),
		m_inputProcessor(nullptr),
		m_yaw(0),
		m_pitch(0),
		m_isHost(false),
		m_playerId(0)
{
	m_playerInstance++;
	m_playerId = m_playerInstance;
}

void Player::_input(const godot::Ref<godot::InputEvent>& event)
{
	m_inputProcessor -> processInputEvent(event);
}

void Player::_ready()
{
	set_velocity(godot::Vector3(0, 0, 0));
	set_position(godot::Vector3(0, 1, 0));

	//This works for now but InputLog should be a singleton when co-op capabilities are being added.
	m_inputProcessor = memnew(Input::InputProcessor(m_playerId));
	m_camera = get_node<godot::Camera3D>("Camera3D");
}

void Player::_physics_process(double delta)
{
	m_inputProcessor -> processInputPoll();
	m_inputProcessor -> commitInputFrame();
	this -> execPlayerInputs(m_inputProcessor -> getUnprocessedFrame() ,delta);
}

void Player::_bind_methods(){}

void Player::execPlayerInputs(const Input::InputFrame& inputFrame, double delta)
{
	m_yaw -= inputFrame.cameraDelta.x * MOUSE_SENS;
	m_pitch -= inputFrame.cameraDelta.y * MOUSE_SENS;
	m_pitch = std::clamp(m_pitch, -1.55334f, 1.55334f);

	set_rotation(godot::Vector3(0, m_yaw, 0));
	m_camera ->set_rotation(godot::Vector3(m_pitch, 0, 0));

	godot::Vector3 velocity = get_velocity();
	m_direction = godot::Vector3();

	godot::Vector3 forward = -get_global_transform().basis.get_column(2);
	godot::Vector3 right = get_global_transform().basis.get_column(0);

	forward.y = 0;
	right.y = 0;
	forward.normalize();
	right.normalize();

	if (inputFrame.buttons & INPUT_FORWARD)
		m_direction += forward; 

	if (inputFrame.buttons & INPUT_BACKWARD)
		m_direction -= forward;

	if (inputFrame.buttons & INPUT_RIGHT)
		m_direction += right;

	if (inputFrame.buttons & INPUT_LEFT)
		m_direction -= right;

	if(m_direction.length() > 0 && is_on_floor())
	{
		m_direction.normalize();
		velocity.x = m_direction.x * WALK_SPEED;
		velocity.z = m_direction.z * WALK_SPEED;
	}
	else if(is_on_floor())
	{
		velocity.x = 0;
		velocity.z = 0;
	}

	//Jumping
	if((inputFrame.buttons & INPUT_JUMP) && is_on_floor())
	{
		velocity.y = JUMP_SPEED;
	}

	if(!is_on_floor())
	{
		velocity.y -= GRAVITY * delta;
	}

	set_rotation(godot::Vector3(0, m_yaw, 0));
	m_camera -> set_rotation(godot::Vector3(m_pitch, 0, 0));
	set_velocity(velocity);
	move_and_slide();
}

uint8_t Player::getPlayerId()
{
	return m_playerId;
}
