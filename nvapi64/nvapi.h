#pragma once
typedef unsigned __int64 	NvU64;
typedef unsigned long 	NvU32;
typedef unsigned char 	NvU8;

enum NV_I2C_SPEED {
	NVAPI_I2C_SPEED_DEFAULT, NVAPI_I2C_SPEED_3KHZ, NVAPI_I2C_SPEED_10KHZ, NVAPI_I2C_SPEED_33KHZ,
	NVAPI_I2C_SPEED_100KHZ, NVAPI_I2C_SPEED_200KHZ, NVAPI_I2C_SPEED_400KHZ
} MODE;

struct NV_I2C_INFO_EX
{
	NvU32        version;
	NvU32        displayMask;        // Display Mask of the concerned display.
	NvU8         bIsDDCPort;         // indicates either the DDC port (TRUE) or the communication port (FALSE) of the concerned display.
	NvU8         i2cDevAddress;      // address of the I2C slave.  The address should be shifted left by one. 0x50 -> 0xA0.
	NvU8*        pbI2cRegAddress;    // I2C target register address.  May be NULL, which indicates no register address should be sent.
	NvU32        regAddrSize;        // size in bytes of target register address.  If pbI2cRegAddress is NULL, this field must be 0.
	NvU8*        pbData;             // buffer of data which is to be read or written (depending on the command).
	NvU32        cbRead;             // bytes to read ??? seems required on write too
	NvU32        cbSize;             // full size of the data buffer, pbData, to be read or written.
	enum NV_I2C_SPEED i2cSpeedKhz;        // target speed of the transaction in (kHz) (Chosen from the enum NV_I2C_SPEED).
	NvU8         portId;             // portid on which device is connected (remember to set bIsPortIdSet if this value is set)
	NvU32        bIsPortIdSet;       // set this flag on if and only if portid value is set

};

enum NVAPI_STATUS {
	NVIAPI_STATUS_OK = 0
};

const char RGB_PORT_R = 0x09;
const char RGB_PORT_G = 0x0A;
const char RGB_PORT_B = 0x0B;

typedef void *(*NvAPI_QueryInterface_t)(unsigned int offset);
typedef int(*NvAPI_Initialize_t)();
typedef int(*NvAPI_Unload_t)();
typedef int(*NvAPI_EnumPhysicalGPUs_t)(int **handles, int *count);
typedef int(*NvAPI_DLL_I2CWriteEx_t)(int *handle, NV_I2C_INFO_EX *i2c, NvU32 *exData);
typedef int(*NvAPI_DLL_I2CReadEx_t)(int *handle, NV_I2C_INFO_EX *i2c, NvU32 *exData);
