#pragma once
#include "nvapi.h"

class __declspec(dllexport) ColorChanger {
public:
	ColorChanger();
	~ColorChanger();

	bool ChangePortColor(char color, char port);
	bool ChangeRGB(char r, char g, char b);
private:
	NvAPI_QueryInterface_t NvQueryInterface = 0;
	NvAPI_Initialize_t NvInit = 0;
	NvAPI_Unload_t NvUnload = 0;
	NvAPI_EnumPhysicalGPUs_t NvEnumGPUs = 0;
	NvAPI_DLL_I2CWriteEx_t NvAPI_DLL_I2CWriteEx = 0;
	NvAPI_DLL_I2CReadEx_t NvAPI_DLL_I2CReadEx = 0;

	int nGPU = 0;
	int *hdlGPU[64] = { 0 };
};