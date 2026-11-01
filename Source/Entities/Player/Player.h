#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/camera3d.hpp>

#include "Systems.h"

typedef struct {
	float yaw;
	float pitch;
}MousePosition;

typedef struct {
	godot::Vector3 direction;
	godot::Vector3 velocity;
}PlayerMotion;

enum PlayerState {
	Alive,
	Dead
};

class Player : public godot::CharacterBody3D{
	GDCLASS(Player, CharacterBody3D)

public:
	Player();

	void _ready() override;
	void _physics_process(double delta) override;
	void _input(const godot::Ref<godot::InputEvent>& event) override;
	static void _bind_methods();

	PlayerState getPlayerState(void);

private:
	static constexpr float kWalkSpeed = 0.5f;
	static constexpr float kRunSpeed = 0.8f;
	static constexpr float kJumpSpeed = 1.75f;
	static constexpr float kGravity = 7.0f;

	bool instantiatePlayer(const godot::String resourcePath);

	void runPlayerInputs(const InputFrame& inputFrame, double delta);
	void updateLook(const InputFrame& inputFrame);
	void updateMovement(const InputFrame& inputFrame);
	void gravity(double delta);

	godot::Node* characterInstance_;

	PlayerState playerState_;

	godot::Camera3D *pCamera_;
	Systems *pSystems_;

	PlayerMotion playerMotion_;
	MousePosition mousePos_;
};
