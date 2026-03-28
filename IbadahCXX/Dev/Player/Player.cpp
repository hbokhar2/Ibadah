#include "Player.h"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

Player::Player()
	:
		posn_(godot::Vector3(0, 0, 0)),
		direction_(godot::Vector3(0, 0, 0)),
		velocity_(0, 0, 0),
		walk_speed_(0.75),
		run_speed_(1.15),
		character_instance_(nullptr),
		input_handler_(nullptr)
{
}

void Player::exec_player_inputs(){

	direction_ = godot::Vector3(0, 0, 0);
	input_handler_ -> clear_input_log();

	input_handler_ -> log_inputs();
	if(input_handler_ -> get_input_log() & INPUT_FORWARD) direction_.x = 1;
	if(input_handler_ -> get_input_log() & INPUT_BACKWARD) direction_.x = -1;
	if(input_handler_ -> get_input_log() & INPUT_RIGHT) direction_.z = 1;
	if(input_handler_ -> get_input_log() & INPUT_LEFT) direction_.z = -1;

	if(direction_.length() > 0){
		direction_.normalize();
		velocity_.x = direction_.x * walk_speed_;
		velocity_.z = direction_.z * walk_speed_;
	}else{
		velocity_.x = 0;
		velocity_.z = 0;
	}

	set_velocity(velocity_);
	move_and_slide();

}

void Player::_ready(){
	input_handler_ = memnew(InputHandler);
}

void Player::_physics_process(double delta){
	this -> exec_player_inputs();
}

void Player::_bind_methods(){}
