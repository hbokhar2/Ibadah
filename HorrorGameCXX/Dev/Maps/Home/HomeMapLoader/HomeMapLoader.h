#pragma once

#include "godot_cpp/classes/wrapped.hpp"
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/node.hpp>

using namespace godot;

class HomeMapLoader : public Node{

	GDCLASS(HomeMapLoader, Node);

	public:

		HomeMapLoader();
		~HomeMapLoader();

	protected:

		bool Initialize();

	private:

		Ref<PackedScene> m_homeScene;
		Node* m_homeInstance;

};
