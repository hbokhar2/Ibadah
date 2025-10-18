#include "Main.h"

#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/variant/vector3.hpp"

Main::Main(){
	character1 = nullptr;
}

Main::~Main(){}

void Main::_bind_methods(){
}

void Main::_init(){}

void Main::_ready(){
	if(MapLoader.initialize()){
		add_child(MapLoader.get_character_instance());
		
		character1 = Object::cast_to<Node3D> (MapLoader.get_character_instance());
		if(character1){
			character1 -> set_position(Vector3(0,0,0));
		}
	}
}

void Main::_process(double delta){}

void Main::_input(const Ref<InputEvent>& event){
	if(event -> is_class("InputEventKey")){
		InputEventKey* keyEvent = Object::cast_to<InputEventKey>(event.ptr());
		if(keyEvent && keyEvent -> is_pressed()){
			if(keyEvent -> get_keycode() == Key::KEY_W){
				UtilityFunctions::print("W");
			}
		}
	}
}
