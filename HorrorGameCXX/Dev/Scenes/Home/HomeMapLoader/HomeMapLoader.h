#pragma once

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/node.hpp>

using namespace godot;

class HomeMapLoader {
	public:
		HomeMapLoader();
		~HomeMapLoader();

		bool initialize();

		Node* get_character_instance() const;
		Node* get_home_instance() const;

	private:
		Ref<PackedScene> m_homeScene;
		Node* m_homeInstance;

		Ref<PackedScene> m_characterScene;
		Node* m_character1Instance;
};
