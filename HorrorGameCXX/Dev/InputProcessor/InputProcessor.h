#include "godot_cpp/classes/input_event.hpp"

class InputProcessor{
	public:
		InputProcessor();
		~InputProcessor();

		void process_input(const godot::Ref<godot::InputEvent>& event);
};
