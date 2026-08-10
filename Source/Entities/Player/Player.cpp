#include "Player.h"

#include <algorithm>
#include <cmath>

#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

//This is just a temporary way to quickly set my mouse sensitivity.
//This value should not be defined here. In the future it should of course
//be modified in a settings menu.
#define MOUSE_SENS 0.005

Player::Player()
	:
		direction_(godot::Vector3(0, 0, 0)),
		velocity_(0, 0, 0),
		walk_speed_(0.75),
		run_speed_(1.15),
		jump_speed_(1.75),
		character_instance_(nullptr),
		input_log_(nullptr),
		gravity_(7),
		yaw_(0),
		pitch_(0)
{
}

void Player::_input(const godot::Ref<godot::InputEvent>& event)
{
	input_log_ -> process_input_event(event);
}

void Player::_ready()
{
	set_velocity(godot::Vector3(0, 0, 0));
	set_position(godot::Vector3(0, 1, 0));

	//This works for now but InputLog should be a singleton when co-op capabilities are being added.
	input_log_ = memnew(InputLog);
	camera_ = get_node<godot::Camera3D>("Camera3D");
}

void Player::_physics_process(double delta)
{
	input_log_ -> process_input_poll();
	input_log_ -> commit_input_frame();
	this -> exec_player_inputs(input_log_-> get_unprocessed_frame() ,delta);
}

void Player::_bind_methods(){}

void Player::exec_player_inputs(const InputFrame& input_frame, double delta)
{
	yaw_ -= input_frame.camera_delta.x * MOUSE_SENS;
	pitch_ -= input_frame.camera_delta.y * MOUSE_SENS;
	pitch_ = std::clamp(pitch_, -1.55334f, 1.55334f);

	set_rotation(godot::Vector3(0, yaw_, 0));
	camera_->set_rotation(godot::Vector3(pitch_, 0, 0));

	godot::Vector3 velocity = get_velocity();
	direction_ = godot::Vector3();

	godot::Vector3 forward = -get_global_transform().basis.get_column(2);
	godot::Vector3 right = get_global_transform().basis.get_column(0);

	forward.y = 0;
	right.y = 0;
	forward.normalize();
	right.normalize();

	if (input_frame.buttons & INPUT_FORWARD)
		direction_ += forward; 

	if (input_frame.buttons & INPUT_BACKWARD)
		direction_ -= forward;

	if (input_frame.buttons & INPUT_RIGHT)
		direction_ += right;

	if (input_frame.buttons & INPUT_LEFT)
		direction_ -= right;

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
	if((input_frame.buttons & INPUT_JUMP) && is_on_floor())
	{
		velocity.y = jump_speed_;
	}

	if(!is_on_floor())
	{
		velocity.y -= gravity_ * delta;
	}

	set_rotation(godot::Vector3(0, yaw_, 0));
	camera_ -> set_rotation(godot::Vector3(pitch_, 0, 0));
	set_velocity(velocity);
	move_and_slide();
}

player_state_t Player::get_player_state(void)
{
	return player_state_;
}
