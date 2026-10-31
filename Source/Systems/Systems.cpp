#include "Systems.h"

Systems::Systems(){
	sysObjs_.pInputManager = memnew(InputManager);
}

Systems& Systems::getInstance(){
	static Systems retVal;
	return retVal;
}

const SysObjs& Systems::getSystemObjs(){
	return sysObjs_;
}
