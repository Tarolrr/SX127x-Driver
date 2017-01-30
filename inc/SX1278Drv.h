
#ifndef SX1276_7_8_H
#define SX1276_7_8_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "SX127xCfg.h"

#ifdef SX127X_LIB

#include "external_Decl.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_spi.h"
#include "SX127xReg.h"

#define EXPORT

#else
#define EXPORT extern
#endif

#define LoRaMaxMessageLength 25
#define LoRaAddressCount 6

extern const uint8_t NetworkID;
extern const uint16_t LoRaAddress;

#define LoRaGUIDSize				16
#define LoRaNetworkIDSize			1
#define LoRaAddressSize				2
#define SX1278Drv_FrequencyStep 61.03516

struct{
	uint16_t address;
	uint8_t payload[LoRaMaxMessageLength];
	uint8_t payloadLength;
} typedef LoRa_Message;

extern const uint64_t GUID[];

EXPORT bool			SX1278Drv_GetCADResult(void);
EXPORT int16_t		SX1278Drv_LoRaGetRSSI(void);
EXPORT void 		SX1278Drv_Init(SX1278Drv_LoRaConfiguration *cfg);
EXPORT void 		SX1278Drv_Config();
EXPORT void			SX1278Drv_LoRaRxCallback(LoRa_Message *msg);
EXPORT void 		SX1278Drv_LoRaRxError(void);
EXPORT void 		SX1278Drv_LoRaTxCallback(LoRa_Message *msg);
EXPORT void			SX1278Drv_SendMessage(LoRa_Message *msg);
EXPORT void			SX1278Drv_SetAdresses(uint8_t first, uint16_t *adresses, uint8_t count);
EXPORT void			SX1278Drv_Suspend();
EXPORT void			SX1278Drv_Resume();
EXPORT bool			SX1278Drv_IsBusy();
EXPORT uint16_t		SX1278Drv_GetRandomDelay(uint16_t from, uint16_t to);
#endif
