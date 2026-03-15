#pragma once

#include <godot_cpp/classes/node.hpp>

#include "MainSceneLoader/MainSceneLoader.h"

class Main : public godot::Node {
	GDCLASS(Main, Node);

	public:
		void _init();
		void _ready() override;
		void _process(double delta) override;

		static void _bind_methods();
	
	private:
		MainSceneLoader m_mainSceneLoader;	
};
