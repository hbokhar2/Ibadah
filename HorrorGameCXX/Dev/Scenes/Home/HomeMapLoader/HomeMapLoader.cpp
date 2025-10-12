#include "HomeMapLoader.h"
#include "godot_cpp/variant/utility_functions.hpp"

HomeMapLoader::HomeMapLoader(){
	m_homeInstance = nullptr;	
	m_character1Instance = nullptr;
}

HomeMapLoader::~HomeMapLoader(){}

Node* HomeMapLoader::get_home_instance() const{
	return m_homeInstance;
}

Node* HomeMapLoader::get_character_instance() const{
	return m_character1Instance;
}

bool HomeMapLoader::initialize(){
	m_homeScene = ResourceLoader::get_singleton() -> load("res://Scenes/Maps/Home.tscn");
	m_characterScene = ResourceLoader::get_singleton() -> load("res://Scenes/Characters/character_1.tscn");

	if(m_homeScene.is_null() || m_characterScene.is_null()){
		UtilityFunctions::print("HomeMapLoader.cpp Line 15. Failed to load home scene.");
		return false;
	}

	m_homeInstance = m_homeScene -> instantiate();
	m_character1Instance = m_characterScene -> instantiate();

	if(!m_homeInstance || !m_character1Instance){
		UtilityFunctions::print("HomeMapLoader.cpp Line 16. Failed to instance home scene.");
		return false;
	}

	UtilityFunctions::print("Loaded home map.");

	return true;
}

