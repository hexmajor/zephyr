/* ENC28J60 Stand-alone Ethernet Controller with SPI
 *
 * Copyright (c) 2016 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <nanokernel.h>
#include <gpio.h>

#ifndef _ENC28J60_
#define _ENC28J60_

/* Any Bank Registers */
#define ENC28J60_REG_EIE   0x1B
#define ENC28J60_REG_EIR   0x1C
#define ENC28J60_REG_ESTAT 0x1D
#define ENC28J60_REG_ECON2 0x1E
#define ENC28J60_REG_ECON1 0x1F

/* Register Encoding
 * Byte 3  : 0x0 ETH Register
 *           0x1 MAC Register
 *           0x2 MII Register
 * Byte 2  : Bank number
 * Byte 1-0: Register address
 */

/* Bank 0 Registers */
#define ENC28J60_REG_ERDPTL   0x0000
#define ENC28J60_REG_ERDPTH   0x0001
#define ENC28J60_REG_EWRPTL   0x0002
#define ENC28J60_REG_EWRPTH   0x0003
#define ENC28J60_REG_ETXSTL   0x0004
#define ENC28J60_REG_ETXSTH   0x0005
#define ENC28J60_REG_ETXNDL   0x0006
#define ENC28J60_REG_ETXNDH   0x0007
#define ENC28J60_REG_ERXSTL   0x0008
#define ENC28J60_REG_ERXSTH   0x0009
#define ENC28J60_REG_ERXNDL   0x000A
#define ENC28J60_REG_ERXNDH   0x000B
#define ENC28J60_REG_ERXRDPTL 0x000C
#define ENC28J60_REG_ERXRDPTH 0x000D
#define ENC28J60_REG_ERXWRPTL 0x000E
#define ENC28J60_REG_ERXWRPTH 0x000F
#define ENC28J60_REG_EDMASTL  0x0010
#define ENC28J60_REG_EDMASTH  0x0011
#define ENC28J60_REG_EDMANDL  0x0012
#define ENC28J60_REG_EDMANDH  0x0013
#define ENC28J60_REG_EDMADSTL 0x0014
#define ENC28J60_REG_EDMADSTH 0x0015
#define ENC28J60_REG_EDMACSL  0x0016
#define ENC28J60_REG_EDMACSH  0x0017

/* Bank 1 Registers */
#define ENC28J60_REG_EHT0    0x0100
#define ENC28J60_REG_EHT1    0x0101
#define ENC28J60_REG_EHT2    0x0102
#define ENC28J60_REG_EHT3    0x0103
#define ENC28J60_REG_EHT4    0x0104
#define ENC28J60_REG_EHT5    0x0105
#define ENC28J60_REG_EHT6    0x0106
#define ENC28J60_REG_EHT7    0x0107
#define ENC28J60_REG_EPMM0   0x0108
#define ENC28J60_REG_EPMM1   0x0109
#define ENC28J60_REG_EPMM2   0x010A
#define ENC28J60_REG_EPMM3   0x010B
#define ENC28J60_REG_EPMM4   0x010C
#define ENC28J60_REG_EPMM5   0x010D
#define ENC28J60_REG_EPMM6   0x010E
#define ENC28J60_REG_EPMM7   0x010F
#define ENC28J60_REG_EPMCSL  0x0110
#define ENC28J60_REG_EPMCSH  0x0111
#define ENC28J60_REG_EPMOL   0x0114
#define ENC28J60_REG_EPMOH   0x0115
#define ENC28J60_REG_EWOLIE  0x0116
#define ENC28J60_REG_EWOLIR  0x0117
#define ENC28J60_REG_ERXFCON 0x0118
#define ENC28J60_REG_EPKTCNT 0x0119

/* Bank 2 Registers */
#define ENC28J60_REG_MACON1   0x1200
#define ENC28J60_REG_MACON3   0x1202
#define ENC28J60_REG_MACON4   0x1203
#define ENC28J60_REG_MABBIPG  0x1204
#define ENC28J60_REG_MAIPGL   0x1206
#define ENC28J60_REG_MAIPGH   0x1207
#define ENC28J60_REG_MACLCON1 0x1208
#define ENC28J60_REG_MACLCON2 0x1209
#define ENC28J60_REG_MAMXFLL  0x120A
#define ENC28J60_REG_MAMXFLH  0x120B
#define ENC28J60_REG_MAPHSUP  0x120C
#define ENC28J60_REG_MICON    0x2211
#define ENC28J60_REG_MICMD    0x2212
#define ENC28J60_REG_MIREGADR 0x2214
#define ENC28J60_REG_MIWRL    0x2216
#define ENC28J60_REG_MIWRH    0x2217
#define ENC28J60_REG_MIRDL    0x2218
#define ENC28J60_REG_MIRDH    0x2219

/* Bank 3 Registers */
#define ENC28J60_REG_MAADR1   0x1300
#define ENC28J60_REG_MAADR0   0x1301
#define ENC28J60_REG_MAADR3   0x1302
#define ENC28J60_REG_MAADR2   0x1303
#define ENC28J60_REG_MAADR5   0x1304
#define ENC28J60_REG_MAADR4   0x1305
#define ENC28J60_REG_EBSTSD   0x0306
#define ENC28J60_REG_EBSTCON  0x0307
#define ENC28J60_REG_EBSTCSL  0x0308
#define ENC28J60_REG_EBSTCSH  0x0309
#define ENC28J60_REG_MISTAT   0x230A
#define ENC28J60_REG_EREVID   0x0312
#define ENC28J60_REG_ECOCON   0x0315
#define ENC28J60_REG_EFLOCON  0x0317
#define ENC28J60_REG_EPAUSL   0x0318
#define ENC28J60_REG_EPAUSH   0x0319

/* PHY Registers */
#define ENC28J60_PHY_PHCON1  0x00
#define ENC28J60_PHY_PHSTAT1 0x01
#define ENC28J60_PHY_PHID1   0x02
#define ENC28J60_PHY_PHID2   0x03
#define ENC28J60_PHY_PHCON2  0x10
#define ENC28J60_PHY_PHSTAT2 0x11
#define ENC28J60_PHY_PHIE    0x12
#define ENC28J60_PHY_PHIR    0x13
#define ENC28J60_PHY_PHLCON  0x14

/* SPI Instruction Opcodes */
#define  ENC28J60_SPI_RCR (0x0)
#define  ENC28J60_SPI_RBM (0x3A)
#define  ENC28J60_SPI_WCR (0x2 << 5)
#define  ENC28J60_SPI_WBM (0x7A)
#define  ENC28J60_SPI_BFS (0x4 << 5)
#define  ENC28J60_SPI_BFC (0x5 << 5)
#define  ENC28J60_SPI_SC  (0xFF)

/* Significant bits */
#define ENC28J60_BIT_MICMD_MIIRD   (0x01)
#define ENC28J60_BIT_MISTAT_BUSY   (0x01)
#define ENC28J60_BIT_ESTAT_CLKRDY  (0x01)
#define ENC28J60_BIT_MACON1_MARXEN (0x01)
#define ENC28J60_BIT_MACON1_RXPAUS (0x04)
#define ENC28J60_BIT_MACON1_TXPAUS (0x08)
#define ENC28J60_BIT_MACON1_MARXEN (0x01)
#define ENC28J60_BIT_MACON2_MARST  (0x80)
#define ENC28J60_BIT_MACON3_FULDPX (0x01)
#define ENC28J60_BIT_ECON1_TXRST   (0x80)
#define ENC28J60_BIT_ECON1_TXRTS   (0x08)
#define ENC28J60_BIT_ECON1_RXEN    (0x04)
#define ENC28J60_BIT_ECON2_PKTDEC  (0x40)
#define ENC28J60_BIT_EIR_PKTIF     (0x40)
#define ENC28J60_BIT_EIE_TXIE      (0x08)
#define ENC28J60_BIT_EIE_PKTIE     (0x40)
#define ENC28J60_BIT_EIE_INTIE     (0x80)
#define ENC28J60_BIT_EIR_PKTIF     (0x40)
#define ENC28J60_BIT_EIR_DMAIF     (0x20)
#define ENC28J60_BIT_EIR_LINKIF    (0x10)
#define ENC28J60_BIT_EIR_TXIF      (0x08)
#define ENC28J60_BIT_EIR_WOLIF     (0x04)
#define ENC28J60_BIT_EIR_TXERIF    (0x02)
#define ENC28J60_BIT_EIR_RXERIF    (0x01)
#define ENC28J60_BIT_ESTAT_TXABRT  (0x02)
#define ENC28J60_BIT_ESTAT_LATECOL (0x10)
#define ENC28J60_BIT_PHCON1_PDPXMD (0x0100)
#define ENC28J60_BIT_PHCON2_HDLDIS (0x0001)

/* Driver Static Configuration */

/*  Receive filters enabled:
 *  - Unicast
 *  - Broadcast
 *  - CRC Check
 */
#define ENC28J60_RECEIVE_FILTERS 0xA1

/*  MAC configuration:
 *  - Automatic Padding
 *  - Automatic CRC
 *  - Frame Length Checking
 */
#define ENC28J60_MAC_CONFIG   0x32
#define ENC28J60_MAC_BBIPG_HD 0x12
#define ENC28J60_MAC_BBIPG_FD 0x15
#define ENC28J60_MAC_NBBIPGL  0x12
#define ENC28J60_MAC_NBBIPGH  0x0C
#define ENC28J60_PHY_LEDCONF  0x3422
/* Status Vector size plus per packet control byte: 8 bytes */
#define ENC28J60_SV_SIZE 8
/* Per Packet Control Byte configured to follow MACON3 configuration */
#define ENC28J60_PPCTL_BYTE 0x0

/* Start of RX buffer, (must be zero, Rev. B4 Errata point 5) */
#define ENC28J60_RXSTART 0x0000
/* End of RX buffer, room for 2 packets */
#define ENC28J60_RXEND 0x0BFF

/* Start of TX buffer, room for 1 packet */
#define ENC28J60_TXSTART 0x0C00
/* End of TX buffer */
#define ENC28J60_TXEND 0x11FF

/* Status vectors array size */
#define TSV_SIZE 7
#define RSV_SIZE 4

/* Fiber Configuration */
#define ENC28J60_FIBER_STACK_SIZE 512
#define ENC28J60_FIBER_PRIORITY   100

/* Microchip's OUI*/
#define MICROCHIP_OUI_B0 0x00
#define MICROCHIP_OUI_B1 0x04
#define MICROCHIP_OUI_B2 0xA3

struct eth_enc28j60_config {
	const char *gpio_port;
	uint8_t gpio_pin;
	const char *spi_port;
	uint32_t spi_freq;
	uint8_t spi_slave;
	uint8_t full_duplex;
};

struct eth_enc28j60_runtime {
	char __stack fiber_stack[ENC28J60_FIBER_STACK_SIZE];
	struct device *gpio;
	struct device *spi;
	struct gpio_callback gpio_cb;
	uint8_t  tx_tsv[TSV_SIZE];
	uint8_t  rx_rsv[RSV_SIZE];
	struct nano_sem tx_sem;
	struct nano_sem int_sem;
	struct nano_sem spi_sem;
	void (*receive_callback)(uint8_t *buffer, uint16_t len);
};

#endif /*_ENC28J60_*/
