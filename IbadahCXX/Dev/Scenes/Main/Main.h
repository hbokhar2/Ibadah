#pragma once

#include <godot_cpp/classes/node.hpp>

#include "Player/Player.h"

class Main : public godot::Node {
	GDCLASS(Main, Node);

	public:
		void _ready() override;
		void _physics_process(double delta) override;

		static void _bind_methods();
	
	private:
		Player* local_player_;
};
