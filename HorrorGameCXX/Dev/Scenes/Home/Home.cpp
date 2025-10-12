#include "Home.h"

#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/variant/vector3.hpp"

Home::Home(){
	character1 = nullptr;
}

Home::~Home(){}

void Home::_bind_methods(){
}

void Home::_init(){}

void Home::_ready(){
	if(m_mapLoader.initialize()){
		add_child(m_mapLoader.get_home_instance());
		add_child(m_mapLoader.get_character_instance());
		
		character1 = Object::cast_to<Node3D> (m_mapLoader.get_character_instance());
		if(character1){
			character1 -> set_position(Vector3(0,0,0));
		}
	}
}

void Home::_process(double delta){}

void Home::_input(const Ref<InputEvent>& event){
	if(event -> is_class("InputEventKey")){
		InputEventKey* keyEvent = Object::cast_to<InputEventKey>(event.ptr());
		if(keyEvent && keyEvent -> is_pressed()){
			if(keyEvent -> get_keycode() == Key::KEY_W){
				UtilityFunctions::print("W");
			}
		}
	}
}
