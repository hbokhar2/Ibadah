#include "GDExtension.h"

#include <godot_cpp/classes/engine.hpp>
#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "Scenes/Main/Main.h"

void initialize_module(godot::ModuleInitializationLevel p_level){
	if(p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) return;

	//Register SnapshotService as a global object.
	/*GDREGISTER_CLASS(SnapshotService);
	snapshotServiceSingleton = memnew(SnapshotService);
	godot::Engine::get_singleton() -> register_singleton("SnapshotService", snapshotServiceSingleton);*/

	godot::ClassDB::register_runtime_class<Main>();
	godot::ClassDB::register_runtime_class<Player>();
}

void uninitialize_module(godot::ModuleInitializationLevel p_level){
	if(p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) return;
}

extern "C" {
	GDExtensionBool GDE_EXPORT ibadah_gd_init(
			GDExtensionInterfaceGetProcAddress p_get_proc_address,
			GDExtensionClassLibraryPtr p_library,
			GDExtensionInitialization* r_initialization
			){
		godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
		init_obj.register_initializer(initialize_module);
		init_obj.register_terminator(uninitialize_module);
		init_obj.set_minimum_library_initialization_level(godot::MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}
