#pragma once

#include "InputManager.h"

typedef struct{
	InputManager *pInputManager;
}SysObjs;

class Systems {
public:
	Systems();
	~Systems() = default;

	static Systems& getInstance();

	const SysObjs& getSystemObjs(); 

private:
	SysObjs sysObjs_;

};
