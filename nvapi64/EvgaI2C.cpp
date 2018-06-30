#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <inttypes.h>
#include "nvapi.h"
#include "ColorChanger.h"

ColorChanger::ColorChanger() {
	NvQueryInterface = (NvAPI_QueryInterface_t)(void*)GetProcAddress(LoadLibrary("nvapi64.dll"), "nvapi_QueryInterface");

	NvInit = (NvAPI_Initialize_t)NvQueryInterface(0x0150E828);
	NvUnload = (NvAPI_Unload_t)NvQueryInterface(0xD22BDD7E);
	NvEnumGPUs = (NvAPI_EnumPhysicalGPUs_t)NvQueryInterface(0xE5AC921F);
	NvAPI_DLL_I2CWriteEx = (NvAPI_DLL_I2CWriteEx_t)NvQueryInterface(0x283AC65A);
	NvAPI_DLL_I2CReadEx = (NvAPI_DLL_I2CReadEx_t)NvQueryInterface(0x4D7B0709);

	NvInit();
	NvEnumGPUs(hdlGPU, &nGPU);
}


ColorChanger::~ColorChanger() {
	NvUnload();
}

bool ColorChanger::ChangePortColor(char color, char port) {
	int* handle = hdlGPU[0];

	NV_I2C_INFO_EX *i2cInfo;
	i2cInfo = (struct NV_I2C_INFO_EX*) malloc(sizeof(NV_I2C_INFO_EX));

	NvU32 datw[2] = { 0, 0 };
	unsigned char rgb_port[1] = { port };
	unsigned char rgb_color[1] = { color };

	i2cInfo->version = 196672; // hardcoded version. may not work on other gpus.
	i2cInfo->displayMask = 0;
	i2cInfo->bIsDDCPort = 0x00;
	i2cInfo->i2cDevAddress = 146;
	i2cInfo->pbI2cRegAddress = (NvU8*)(&rgb_port[0]);
	i2cInfo->regAddrSize = 1;
	i2cInfo->pbData = (NvU8*)(&rgb_color[0]);
	i2cInfo->cbRead = 1;
	i2cInfo->cbSize = 65535;
	i2cInfo->i2cSpeedKhz = NVAPI_I2C_SPEED_DEFAULT;
	i2cInfo->portId = 1;
	i2cInfo->bIsPortIdSet = 1;

	int ret = NvAPI_DLL_I2CWriteEx(handle, i2cInfo, datw);

	return ret == NVIAPI_STATUS_OK;
}

bool ColorChanger::ChangeRGB(char r, char g, char b) {
	return ChangePortColor(r, RGB_PORT_R) && ChangePortColor(g, RGB_PORT_G) && ChangePortColor(b, RGB_PORT_B);
}