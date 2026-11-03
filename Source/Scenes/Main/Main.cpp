#include "Main.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include "Systems.h"

Main::Main()
	:
		characterInstance_(nullptr)
{
}

void Main::_ready() {
	Systems::getInstance(); //Runs "Systems" constructor on startup.
					
	godot::Input::get_singleton() -> set_mouse_mode(godot::Input::MOUSE_MODE_CAPTURED); //Traps mouse cursor.

	spawnCharacter("res://Scenes/Characters/ClientCharacter.tscn");
}

void Main::_bind_methods(){
}

void Main::spawnCharacter(const godot::String characterScenePath)
{
	godot::Ref<godot::PackedScene> characterScene = godot::ResourceLoader::get_singleton() -> load(characterScenePath);
	if(characterScene.is_null()){
		godot::UtilityFunctions::print("[ERROR] Main.cpp:29 | Could not find character resources.");
		return;
	}

	characterInstance_ = characterScene -> instantiate();
	add_child(characterInstance_);
}
