#include "Main.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

void Main::_ready() {

	godot::Ref<godot::PackedScene> character_scene = godot::ResourceLoader::get_singleton() -> load("res://Scenes/Characters/Duck.tscn");
	if(character_scene.is_null()) godot::UtilityFunctions::print("Incorrect scene path.");

	godot::Node* character_instance = character_scene -> instantiate();

	if(!character_instance) godot::UtilityFunctions::print("Could not instantiate character.");
	add_child(character_instance);

}

void Main::_bind_methods(){
}
