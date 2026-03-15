#include "Main.h"

#include "godot_cpp/variant/utility_functions.hpp"

void Main::_init(){}

void Main::_ready(){

	if(m_mainSceneLoader.initialize()){
		godot::UtilityFunctions::print("Initialized Main scene!");
		add_child(m_mainSceneLoader.getCharacterInstance());
	}else{
		godot::UtilityFunctions::print("Failed to initialize main scene.");
	}

}

void Main::_process(double delta){}

void Main::_bind_methods(){
}
