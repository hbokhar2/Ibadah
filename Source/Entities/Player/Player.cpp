#include "Player.h"

#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include "Input/InputHandler.h"

Player::Player()
	:
		direction_(godot::Vector3(0, 0, 0)),
		velocity_(0, 0, 0),
		walk_speed_(0.75),
		run_speed_(1.15),
		jump_speed_(1.75),
		character_instance_(nullptr),
		input_handler_(nullptr),
		gravity_(7)
{
}

void Player::_input(const godot::Ref<godot::InputEvent>& event)
{
}

void Player::_ready()
{
	set_velocity(godot::Vector3(0, 0, 0));
	set_position(godot::Vector3(0, 1, 0));

	//This works for now but InputHandler should be a singleton when co-op capabilities are being added.
	input_handler_ = memnew(InputHandler);
}

void Player::_physics_process(double delta)
{
	this -> exec_player_inputs(delta);
}

void Player::_bind_methods(){}

void Player::exec_player_inputs(double delta)
{
	godot::Vector3 velocity = get_velocity();

	direction_ = godot::Vector3();

	input_handler_ -> clear_input_log();
	input_handler_ -> log_inputs();

	//WASD Movements
	if(input_handler_ -> get_input_log() & INPUT_FORWARD)
		direction_.x = 1;

	if(input_handler_ -> get_input_log() & INPUT_BACKWARD)
		direction_.x = -1;

	if(input_handler_ -> get_input_log() & INPUT_RIGHT)
		direction_.z = 1;

	if(input_handler_ -> get_input_log() & INPUT_LEFT)
		direction_.z = -1;

	if(direction_.length() > 0 && is_on_floor())
	{
		direction_.normalize();
		velocity.x = direction_.x * walk_speed_;
		velocity.z = direction_.z * walk_speed_;
	}
	else if(is_on_floor())
	{
		velocity.x = 0;
		velocity.z = 0;
	}

	//Jumping
	if((input_handler_ -> get_input_log() & INPUT_JUMP) && is_on_floor())
	{
		velocity.y = jump_speed_;
	}

	if(!is_on_floor())
	{
		velocity.y -= gravity_ * delta;
	}

	set_velocity(velocity);
	move_and_slide();
}

player_state_t Player::get_player_state(void)
{
	return player_state_;
}
