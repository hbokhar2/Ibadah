#pragma once

#include "InputManager.h"
#include "ConfigManager/ConfigManager.h"

typedef struct
{
	InputManager *pInputManager;
	ConfigManager *pConfManager;
}SysObjs;

class Systems 
{
public:
	Systems();
	~Systems() = default;

	static Systems* getInstance();

	const SysObjs& getSystemObjs(); 

private:
	SysObjs sysObjs_;

};
