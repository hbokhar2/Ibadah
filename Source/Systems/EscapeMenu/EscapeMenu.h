#pragma once

#include <godot_cpp/classes/control.hpp>

class EscapeMenu : public godot::Control {
	GDCLASS(EscapeMenu, godot::Control)

protected:
	static void _bind_methods();
};
