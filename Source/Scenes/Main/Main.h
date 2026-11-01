#pragma once

#include <godot_cpp/classes/node.hpp>

#include "Player.h"
#include "Systems.h"

class Main : public godot::Node {
	GDCLASS(Main, Node);

	public:
		Main();
		~Main() = default;

		void _ready() override;
		static void _bind_methods();
	
	private:
		void spawnCharacter(const godot::String characterScenePath);

		godot::Node *characterInstance_;
};
