#pragma once

#include <godot_cpp/classes/node.hpp>

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse.hpp>
#include <godot_cpp/classes/input_event_key.hpp>

#include "HomeMapLoader/HomeMapLoader.h"
#include "godot_cpp/classes/node3d.hpp"

using namespace godot;

class Main : public Node {
	GDCLASS(Main, Node);

	public:
		Main();
		~Main();

		void _init();                   
		void _ready() override;        
		void _process(double delta) override;  
		void _input(const Ref<InputEvent>& event) override;

		static void _bind_methods();

	private:
		HomeMapLoader MapLoader;
		Node3D* character1;
};
