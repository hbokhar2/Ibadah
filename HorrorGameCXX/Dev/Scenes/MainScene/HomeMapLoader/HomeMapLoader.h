#pragma once

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/node.hpp>

class HomeMapLoader {
	public:
		HomeMapLoader();
		~HomeMapLoader();

		bool initialize();

		godot::Node* get_character_instance() const;

	private:
		godot::Ref<godot::PackedScene> m_characterScene;
		godot::Node* m_character1Instance;
};
