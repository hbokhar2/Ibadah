#include "Player.h"

#include <algorithm>
#include <cmath>

#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

//This is just a temporary way to quickly set my mouse sensitivity.
//This value should not be defined here. In the future it should of course
//be modified in a settings menu.
#define MOUSE_SENS 0.0010

Player::Player()
	:
		pCamera_(nullptr),
		pSystems_(nullptr)
{
	mousePos_ = {};
	playerMotion_ = {};

	pSystems_ = &Systems::getInstance();
}

void Player::_bind_methods(){}

void Player::_ready(){
	set_velocity(godot::Vector3(0, 0, 0));
	set_position(godot::Vector3(0, 1, 0));

	pCamera_ = get_node<godot::Camera3D>("Camera3D");
}

void Player::_physics_process(double delta){
	pSystems_ -> Systems::getSystemObjs().pInputManager -> processInputPoll();
	pSystems_ -> Systems::getSystemObjs().pInputManager -> commitInputFrame();

	runPlayerInputs(pSystems_ -> getSystemObjs().pInputManager-> getUnprocessedInputFrame() ,delta);
}

void Player::_input(const godot::Ref<godot::InputEvent>& event){
	pSystems_ -> Systems::getSystemObjs().pInputManager -> processInputEvent(event);
}

void Player::runPlayerInputs(const InputFrame& inputFrame, double delta) {
	updateLook(inputFrame); updateMovement(inputFrame);
	gravity(delta);
}

void Player::gravity(double delta){
	if(!is_on_floor()){
		playerMotion_.velocity.y -= kGravity * delta;
	}

	set_velocity(playerMotion_.velocity);
	move_and_slide();
}
	

void Player::updateLook(const InputFrame& inputFrame){
	mousePos_.yaw -= inputFrame.cameraDelta.x * MOUSE_SENS;
	mousePos_.pitch -= inputFrame.cameraDelta.y * MOUSE_SENS;
	mousePos_.pitch = std::clamp(mousePos_.pitch, -1.55334f, 1.55334f);

	set_rotation(godot::Vector3(0, mousePos_.yaw, 0));
	pCamera_ -> set_rotation(godot::Vector3(mousePos_.pitch, 0, 0));
}

void Player::updateMovement(const InputFrame& inputFrame){
	playerMotion_.velocity = get_velocity();
	playerMotion_.direction = godot::Vector3();

	godot::Vector3 forward = -get_global_transform().basis.get_column(2);
	godot::Vector3 right = get_global_transform().basis.get_column(0);

	forward.y = 0;
	right.y = 0;
	forward.normalize();
	right.normalize();

	//WASD
	if (inputFrame.buttons & INPUT_FORWARD)
		playerMotion_.direction += forward; 

	if (inputFrame.buttons & INPUT_BACKWARD)
		playerMotion_.direction -= forward;

	if (inputFrame.buttons & INPUT_RIGHT)
		playerMotion_.direction += right;

	if (inputFrame.buttons & INPUT_LEFT)
		playerMotion_.direction -= right;

	if(playerMotion_.direction.length() > 0 && is_on_floor()) {
		playerMotion_.direction.normalize();

		if(inputFrame.buttons & INPUT_SPRINT){
			playerMotion_.velocity.x = playerMotion_.direction.x * kRunSpeed;
			playerMotion_.velocity.z = playerMotion_.direction.z * kRunSpeed;
		}else{
			playerMotion_.velocity.x = playerMotion_.direction.x * kWalkSpeed;
			playerMotion_.velocity.z = playerMotion_.direction.z * kWalkSpeed;
		}

	}else if(is_on_floor()) { //Jump should not read inputs for WASD
		playerMotion_.velocity.x = 0;
		playerMotion_.velocity.z = 0;
	}

	//Jumping
	if((inputFrame.buttons & INPUT_JUMP) && is_on_floor()){
		playerMotion_.velocity.y = kJumpSpeed;
	}

	set_velocity(playerMotion_.velocity);
	move_and_slide();
}

PlayerState Player::getPlayerState(void) {
	return playerState_;
}
