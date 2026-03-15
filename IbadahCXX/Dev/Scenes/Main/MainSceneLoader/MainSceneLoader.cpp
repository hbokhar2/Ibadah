#include "MainSceneLoader.h"

#include "godot_cpp/classes/resource_loader.hpp"
#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/variant/utility_functions.hpp"

godot::Node* MainSceneLoader::getCharacterInstance(){ 
	return m_characterInstance;
}

bool MainSceneLoader::initialize(){

	godot::Ref<godot::PackedScene> characterScene = godot::ResourceLoader::get_singleton() -> load("res://Scenes/Characters/duck.tscn");
	if(characterScene.is_null()){
		godot::UtilityFunctions::print("Failed to load duck.tscn: MainSceneLoader.cpp:12.");	
		return false;
	}

	m_characterInstance = characterScene -> instantiate();
	if(!m_characterInstance){
		godot::UtilityFunctions::print("Failed to instantiate duck.tscn: MainSceneLoader.cpp:17.");
		return false;
	}

	return true;

}
