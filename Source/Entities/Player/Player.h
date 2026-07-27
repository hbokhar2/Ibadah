#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/input_event.hpp>

#include "Input/InputHandler.h"

enum class player_state_t{
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

		bool instantiate_player(const godot::String resource_path);
		void exec_player_inputs(double delta);

		player_state_t get_player_state(void);

	private:
		godot::Node* character_instance_;

		godot::Vector3 direction_, velocity_;
		float walk_speed_, run_speed_, jump_speed_, gravity_;

		InputHandler* input_handler_;
		
		player_state_t player_state_;
};
