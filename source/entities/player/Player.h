#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/variant/vector3.hpp>

#include "input/InputHandler.h"

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
		static void _bind_methods();

		bool instantiate_player(const godot::String resource_path);
		void exec_player_inputs(void);

		player_state_t get_player_state(void);

	private:
		godot::Node* character_instance_;

		godot::Vector3 posn_;
		godot::Vector3 direction_;
		godot::Vector3 velocity_;
		float walk_speed_;
		float run_speed_;

		InputHandler* input_handler_;
		
		player_state_t player_state_;
};
