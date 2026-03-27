#include "Main.h"

void Main::_ready(){

	local_player_ = memnew(Player);
	add_child(local_player_);
	local_player_ -> instantiate_player("res://Scenes/Characters/Duck.tscn");

}

void Main::_physics_process(double delta){

	local_player_ -> exec_player_inputs();

}

void Main::_bind_methods(){
}
