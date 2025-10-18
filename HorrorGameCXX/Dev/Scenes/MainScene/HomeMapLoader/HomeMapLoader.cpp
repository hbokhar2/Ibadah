#include "HomeMapLoader.h"

HomeMapLoader::HomeMapLoader(){
	m_character1Instance = nullptr;
}

HomeMapLoader::~HomeMapLoader(){}

godot::Node* HomeMapLoader::get_character_instance() const{
	return m_character1Instance;
}

bool HomeMapLoader::initialize(){
	m_characterScene = godot::ResourceLoader::get_singleton() -> load("res://Scenes/Characters/character_1.tscn");

	if(m_characterScene.is_null()){
		godot::UtilityFunctions::print("HomeMapLoader.cpp Line 19. Failed to load resources.");
		return false;
	}

	m_character1Instance = m_characterScene -> instantiate();

	if(!m_character1Instance){
		godot::UtilityFunctions::print("HomeMapLoader.cpp Line 26. Failed to instance resources.");
		return false;
	}

	godot::UtilityFunctions::print("Loaded home map.");

	return true;
}
