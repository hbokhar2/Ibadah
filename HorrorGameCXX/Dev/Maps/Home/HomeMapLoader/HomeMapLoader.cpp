#include "HomeMapLoader.h"
#include "godot_cpp/variant/utility_functions.hpp"

HomeMapLoader::HomeMapLoader(){

	m_homeInstance = nullptr;	

}

HomeMapLoader::~HomeMapLoader(){}

bool HomeMapLoader::Initialize(){

	m_homeScene = ResourceLoader::get_singleton() -> load("res://Scenes/Maps/Home.tscn");

	if(m_homeScene.is_null()){
		UtilityFunctions::print("Failed to load home scene.");
		return false;
	}

	m_homeInstance = m_homeScene->instantiate();

	if(!m_homeInstance){
		UtilityFunctions::print("Failed to instance home scene.");
		return false;
	}

	UtilityFunctions::print("Loaded home map.");

	add_child(m_homeInstance);

	return true;

}
