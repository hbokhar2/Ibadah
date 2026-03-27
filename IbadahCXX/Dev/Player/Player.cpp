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
		input_logger_(nullptr)
{
}

void Player::_ready(){

	input_logger_ = memnew(InputLogger);

}

void Player::_bind_methods(){}

/**
 *@brief Instantiates player instance provided a Godot path to the character scene.
 */
bool Player::instantiate_player(const godot::String resource_path){

	godot::Ref<godot::PackedScene> characterScene = godot::ResourceLoader::get_singleton() -> load(resource_path);
	if(characterScene.is_null()){
		godot::UtilityFunctions::print("Failed to load: ", resource_path);	
		return false;
	}

	character_instance_ = characterScene -> instantiate();
	if(!character_instance_){
		godot::UtilityFunctions::print("Failed to instantiate: ", resource_path);
		return false;
	}

	add_child(character_instance_);

	return true;

}

void Player::exec_player_inputs(){

	direction_ = godot::Vector3(0, 0, 0);
	input_logger_ -> zero_input_log();

	input_logger_ -> read_cont_inputs();
	if(input_logger_ -> get_input_log().continuous_inputs & INPUT_FORWARD){
		direction_.x = 1;
	}
	if(input_logger_ -> get_input_log().continuous_inputs & INPUT_BACKWARD){
		direction_.x = -1;
	}
	if(input_logger_ -> get_input_log().continuous_inputs & INPUT_RIGHT){
		direction_.z = 1;
	}
	if(input_logger_ -> get_input_log().continuous_inputs & INPUT_LEFT){
		direction_.z = -1;
	}

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
