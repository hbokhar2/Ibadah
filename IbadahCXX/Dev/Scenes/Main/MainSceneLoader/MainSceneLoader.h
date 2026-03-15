#pragma once

#include <godot_cpp/classes/node.hpp>

class MainSceneLoader{
	public:
		bool initialize();
		godot::Node* getCharacterInstance();
	private:
		godot::Node* m_characterInstance;

};
