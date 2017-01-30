#include "stm32f1xx_hal_spi.h"
#include "pin_description.h"

enum{
	SX1278Drv_RegPaConfig_PaSelect = 0x80,
	SX1278Drv_RegPaConfig_MaxPowerMask = 0x70,
	SX1278Drv_RegPaConfig_OutputPowerMask = 0x0F
} typedef SX1278Drv_RegPaConfig_;

enum{
	SX1278Drv_RegOcp_OcpOn = 0x20,
	SX1278Drv_RegOcp_OcpTrimMask = 0x1F
} typedef SX1278Drv_RegOcp_;

enum{
	SX1278Drv_RegLna_GainMask = 0xE0,
	SX1278Drv_RegLna_LnaBoostLfOff = 0x00,
	SX1278Drv_RegLna_LnaBoostHfOff = 0x00,
	SX1278Drv_RegLna_LnaBoostHfOn = 0x03
} typedef SX1278Drv_RegLna_;

enum{
	SX1278Drv_RegLoRaIrqFlagsMask_RxTimeout = 0x80,
	SX1278Drv_RegLoRaIrqFlagsMask_RxDone = 0x40,
	SX1278Drv_RegLoRaIrqFlagsMask_PayloadCrcError = 0x20,
	SX1278Drv_RegLoRaIrqFlagsMask_ValidHeader = 0x10,
	SX1278Drv_RegLoRaIrqFlagsMask_TxDone = 0x08,
	SX1278Drv_RegLoRaIrqFlagsMask_CadDone = 0x04,
	SX1278Drv_RegLoRaIrqFlagsMask_FhssChangeChannel = 0x02,
	SX1278Drv_RegLoRaIrqFlagsMask_CadDetected = 0x01
} typedef SX1278Drv_RegLoRaIrqFlagsMask_;

enum{
	SX1278Drv_RegLoRaIrqFlags_RxTimeout = 0x80,
	SX1278Drv_RegLoRaIrqFlags_RxDone = 0x40,
	SX1278Drv_RegLoRaIrqFlags_PayloadCrcError = 0x20,
	SX1278Drv_RegLoRaIrqFlags_ValidHeader = 0x10,
	SX1278Drv_RegLoRaIrqFlags_TxDone = 0x08,
	SX1278Drv_RegLoRaIrqFlags_CadDone = 0x04,
	SX1278Drv_RegLoRaIrqFlags_FhssChangeChannel = 0x02,
	SX1278Drv_RegLoRaIrqFlags_CadDetected = 0x01
} typedef SX1278Drv_RegLoRaIrqFlags_;

enum{
	SX1278Drv_RegLoRaModemStat_RxCodingRateMask = 0xE0,
	SX1278Drv_RegLoRaModemStat_ModemClear = 0x10,
	SX1278Drv_RegLoRaModemStat_HeaderInfoValid = 0x08,
	SX1278Drv_RegLoRaModemStat_RxOnGoing = 0x04,
	SX1278Drv_RegLoRaModemStat_SignalSynchronized = 0x02,
	SX1278Drv_RegLoRaModemStat_SignalDetected = 0x01
} typedef SX1278Drv_RegLoRaModemStat_;

enum{
	SX1278Drv_RegLoRaHopChannel_PllTimeout = 0x80,
	SX1278Drv_RegLoRaHopChannel_CrcOnPayload = 0x40,
	SX1278Drv_RegLoRaHopChannel_FhssPresentChannelMask = 0x3F,
} typedef SX1278Drv_RegLoRaHopChannel_;


enum{
	SX1278Drv_RegLoRaModemConfig1_BW_7_8  = 0x00,
	SX1278Drv_RegLoRaModemConfig1_BW_10_4 = 0x10,
	SX1278Drv_RegLoRaModemConfig1_BW_15_6 = 0x20,
	SX1278Drv_RegLoRaModemConfig1_BW_20_8 = 0x30,
	SX1278Drv_RegLoRaModemConfig1_BW_31_2 = 0x40,
	SX1278Drv_RegLoRaModemConfig1_BW_41_7 = 0x50,
	SX1278Drv_RegLoRaModemConfig1_BW_62_5 = 0x60,
	SX1278Drv_RegLoRaModemConfig1_BW_125  = 0x70,
	SX1278Drv_RegLoRaModemConfig1_BW_250  = 0x80,
	SX1278Drv_RegLoRaModemConfig1_BW_500  = 0x90,
} typedef SX1278Drv_RegLoRaModemConfig1_BW;

static const uint32_t SX1278Drv_RegLoRaModemConfig1_BW_Values[] = {
	7800, 10400, 15600, 20800, 31200, 41700, 62500, 125000, 250000, 500000
};

enum{
	SX1278Drv_RegLoRaModemConfig1_CR_4_5 = 0x02,
	SX1278Drv_RegLoRaModemConfig1_CR_4_6 = 0x04,
	SX1278Drv_RegLoRaModemConfig1_CR_4_7 = 0x06,
	SX1278Drv_RegLoRaModemConfig1_CR_4_8 = 0x08,
} typedef SX1278Drv_RegLoRaModemConfig1_CR;

enum{
	SX1278Drv_RegLoRaModemConfig1_HdrMode_Explicit = 0x00,
	SX1278Drv_RegLoRaModemConfig1_HdrMode_Implicit = 0x01
} typedef SX1278Drv_RegLoRaModemConfig1_HdrMode;

enum{
	SX1278Drv_RegLoRaModemConfig2_SF_6  = 0x60,
	SX1278Drv_RegLoRaModemConfig2_SF_7  = 0x70,
	SX1278Drv_RegLoRaModemConfig2_SF_8  = 0x80,
	SX1278Drv_RegLoRaModemConfig2_SF_9  = 0x90,
	SX1278Drv_RegLoRaModemConfig2_SF_10 = 0xA0,
	SX1278Drv_RegLoRaModemConfig2_SF_11 = 0xB0,
	SX1278Drv_RegLoRaModemConfig2_SF_12 = 0xC0
} typedef SX1278Drv_RegLoRaModemConfig2_SF;

enum{
	SX1278Drv_RegLoRaModemConfig2_PayloadCrc_OFF = 0x00,
	SX1278Drv_RegLoRaModemConfig2_PayloadCrc_ON = 0x04
} typedef SX1278Drv_RegLoRaModemConfig2_PayloadCrc;

enum{
	SX1278Drv_RegLoRaModemConfig3_LowDataRateOptimize = 0x08,
	SX1278Drv_RegLoRaModemConfig3_AgcAutoOn = 0x04,
} typedef SX1278Drv_RegLoRaModemConfig3_;

enum{
	SX1278Drv_RegLoRaDetectOptimize_SF7toSF12 = 0xC3,
	SX1278Drv_RegLoRaDetectOptimize_SF6 = 0xC5,
} typedef SX1278Drv_RegLoRaDetectOptimize_;

enum{
	SX1278Drv_RegLoRaInvertIQ_Normal = 0x27,
	SX1278Drv_RegLoRaInvertIQ_Invert = 0x67,
} typedef SX1278Drv_RegLoRaInvertIQ_;

enum{
	SX1278Drv_RegLoRaDetectThreshold_SF7toSF12 = 0x0A,
	SX1278Drv_RegLoRaDetectThreshold_SF6 = 0x0C,
} typedef SX1278Drv_RegLoRaDetectThreshold_;

enum{
	SX1278Drv_RegOpMode_LoRa		= 0x80,
	SX1278Drv_RegOpMode_LowFreq		= 0x08,
	SX1278Drv_RegOpMode_Sleep		= 0x00,
	SX1278Drv_RegOpMode_Standby		= 0x01,
	SX1278Drv_RegOpMode_FSTX		= 0x02,
	SX1278Drv_RegOpMode_TX			= 0x03,
	SX1278Drv_RegOpMode_FSRX		= 0x04,
	SX1278Drv_RegOpMode_RX_Cont		= 0x05,
	SX1278Drv_RegOpMode_RX_Single	= 0x06,
	SX1278Drv_RegOpMode_CAD			= 0x07,
	SX1278Drv_RegOpMode_ModeMask	= 0x07
} typedef SX1278Drv_RegOpMode_;

struct{
	SX1278Drv_RegLoRaModemConfig1_BW			bw;
	SX1278Drv_RegLoRaModemConfig1_CR			cr;
	SX1278Drv_RegLoRaModemConfig1_HdrMode		hdrMode;
	SX1278Drv_RegLoRaModemConfig2_SF			sf;
	SX1278Drv_RegLoRaModemConfig2_PayloadCrc	crc;
	uint16_t									preambleLength;
	uint8_t										power;
	double										frequency;
	SPI_HandleTypeDef							*spi;
	PinDescription								*spi_css_pin;
	PinDescription								*tx_led;
	PinDescription								*rx_led;
	PinDescription								*tx_en;
	PinDescription								*rx_en;
	bool										sleepInIdle;
} typedef SX1278Drv_LoRaConfiguration;
