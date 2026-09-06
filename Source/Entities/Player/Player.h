#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/camera3d.hpp>

#include "InputProcessor.h"

enum class PlayerState{
	Dead,
	Alive,
	Downed
};

class Player : public godot::CharacterBody3D{
	GDCLASS(Player, CharacterBody3D)

public:
	Player();

	void _ready() override;
	void _physics_process(double delta) override;
	void _input(const godot::Ref<godot::InputEvent>& event) override;
	static void _bind_methods();

	bool instantiatePlayer(const godot::String resourcePath);
	void execPlayerInputs(const Input::InputFrame& inputFrame, double delta);

	uint8_t getPlayerId();

private:
	static inline uint8_t m_playerInstance = 0;
	uint8_t m_playerId;
	
	godot::Node* m_characterInstance;
	bool m_isHost;

	godot::Camera3D* m_camera;
	Input::InputProcessor* m_inputProcessor;
	godot::Vector3 m_direction, m_velocity;
	float m_yaw, m_pitch;
};
