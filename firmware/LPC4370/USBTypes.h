/*
 * This file is part of SPI Flash Programmer (SPIFP)
 * Copyright © 2014 Rachel Mant (dx-mon@users.sourceforge.net)
 *
 * SPIFP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SPIFP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef USBTypes_H
#define USBTypes_H

typedef enum
{
	USB_CTRL_STATE_WAIT,
	USB_CTRL_STATE_TX,
	USB_CTRL_STATE_RX
} usbCtrlState_t;

typedef enum
{
	USB_STATE_DETACHED,
	USB_STATE_ATTACHED,
	USB_STATE_POWERED,
	USB_STATE_WAITING,
	USB_STATE_ADDRESSING,
	USB_STATE_ADDRESSED,
	USB_STATE_CONFIGURED
} usbDeviceState;

typedef enum
{
	USB_PID_NONE,
	USB_PID_OUT,
	USB_PID_ACK,
	USB_PID_DATA0,
	USB_PID_PING,
	USB_PID_SOF,
	USB_PID_NYET,
	USB_PID_DATA2,
	USB_PID_SPLIT,
	USB_PID_IN,
	USB_PID_NAK,
	USB_PID_DATA1,
	USB_PID_PRE_ERROR,
	USB_PID_SETUP,
	USB_PID_STALL,
	USB_PID_MDATA
} usbPID_t;

typedef enum
{
	USB_REQUEST_GET_STATUS = 0,
	USB_REQUEST_CLEAR_FEATURE = 1,
	USB_REQUEST_SET_FEATURE = 3,
	USB_REQUEST_SET_ADDRESS = 5,
	USB_REQUEST_GET_DESCRIPTOR = 6,
	USB_REQUEST_SET_DESCRIPTOR = 7,
	USB_REQUEST_GET_CONFIGURATION = 8,
	USB_REQUEST_SET_CONFIGURATION = 9,
	USB_REQUEST_GET_INTERFACE = 10,
	USB_REQUEST_SET_INTERFACE = 11,
	USB_REQUEST_SYNC_FRAME = 12
} usbRequest_t;

typedef enum
{
	USB_REQUEST_TYPE_STANDARD,
	USB_REQUEST_TYPE_CLASS,
	USB_REQUEST_TYPE_VENDOR,
	USB_REQUEST_TYPE_RESERVED
} usbRequestType_t;

typedef enum
{
	USB_RECIPIENT_DEVICE,
	USB_RECIPIENT_INTERFACE,
	USB_RECIPIENT_ENDPOINT,
	USB_RECIPIENT_OTHER,
	USB_RECIPIENT_RESERVED
} usbRecipient_t;

typedef enum
{
	USB_FEATURE_ENDPOINT_STALL,
	USB_FEATURE_REMOTE_WAKEUP,
	USB_FEATURE_TEST_MODE
} usbFeature_t;

typedef struct
{
	union
	{
		uint8_t value;
		struct
		{
			uint8_t recipient : 5;
			uint8_t type : 2;
			uint8_t direction : 1;
		};
	} requestType;
	uint8_t request;
	union
	{
		uint16_t value;
		struct
		{
			uint8_t index;
			uint8_t type;
		} descriptor;
		struct
		{
			uint8_t addrL;
			uint8_t addrH;
		} address;
		struct
		{
			uint8_t value;
			uint8_t reserved;
		} config;
		struct
		{
			uint8_t value;
			uint8_t reserved;
		} feature;
	} value;
	union
	{
		uint16_t value;
		struct
		{
			uint8_t epNum : 4;
			uint8_t : 3;
			uint8_t epDir : 1;
			uint8_t;
		};
	} index;
	uint16_t length;
} usbSetupPacket_t;

typedef enum
{
	USB_STALL_STATE_IDLE,
	USB_STALL_STATE_ARM,
	USB_STALL_STATE_STALL
} usbStallState_t;

#define USB_CONF_ATTR_DEFAULT	0x80
#define USB_CONF_ATTR_SELFPWR	0x40
#define USB_CONF_ATTR_RWU		0x20
#define USB_CONF_ATTR_HNP		0x02
#define USB_CONF_ATTR_SRP		0x01

#define USB_CLASS_COMMS			0x02
#define USB_CLASS_DATA			0x0A
#define USB_CLASS_MSD			0x08
#define USB_CLASS_VENDOR		0xFF

#define USB_SUBCLASS_NONE		0x00
#define USB_SUBCLASS_ACM		0x02
#define USB_SUBCLASS_MSD		0x06
#define USB_SUBCLASS_VENDOR		0xFF

#define USB_PROTOCOL_NONE		0x00
#define USB_PROTOCOL_V25_AT		0x01
#define USB_PROTOCOL_TRANS		0x32
#define USB_PROTOCOL_BULK_ONLY	0x50
#define USB_PROTOCOL_CDC		0xFE
#define USB_PROTOCOL_VENDOR		0xFF

#define USB_EPTYPE_CTRL			0x00
#define USB_EPTYPE_ISO			0x01
#define USB_EPTYPE_BULK			0x02
#define USB_EPTYPE_INTR			0x03

typedef struct
{
	uint8_t length;
	uint8_t descriptorType;
	uint16_t usbVersion;
	uint8_t deviceClass;
	uint8_t deviceSubClass;
	uint8_t devicePRotocol;
	uint8_t maxPacketSize0;
	uint16_t vendorID;
	uint16_t productID;
	uint16_t deviceVersion;
	uint8_t strMfrIndex;
	uint8_t strProductIndex;
	uint8_t strSerialNoIndex;
	uint8_t numConfigurations;
} usbDeviceDescriptor_t;

typedef struct
{
	uint8_t length;
	uint8_t descriptorType;
	uint16_t totalLength;
	uint8_t numInterfaces;
	uint8_t configurationValue;
	uint8_t strConfigurationIndex;
	uint8_t attributes;
	uint8_t maxPower;
} usbConfigDescriptor_t;

typedef struct
{
	uint8_t length;
	uint8_t descriptorType;
	uint8_t interfaceNumber;
	uint8_t alternateSetting;
	uint8_t numEndpoints;
	uint8_t interfaceClass;
	uint8_t interfaceSubClass;
	uint8_t interfaceProtocol;
	uint8_t strInterfaceIdx;
} usbInterfaceDescriptor_t;

typedef struct
{
	uint8_t length;
	uint8_t descriptorType;
	uint8_t endpointAddress;
	uint8_t attributes;
	uint16_t maxPacketSize;
	uint8_t interval;
} usbEndpointDescriptor_t;

typedef struct
{
	uint8_t length;
	uint8_t descriptorType;
} usbStringDescBase_t;

typedef struct
{
	uint8_t length;
	uint8_t descriptorType;
	uint8_t firstInterface;
	uint8_t interfaceCount;
	uint8_t functionClass;
	uint8_t functionSubClass;
	uint8_t functionProtocol;
	uint8_t iFunction;
} usbInterfaceAssocDescriptor_t;

typedef enum
{
	USB_DESCRIPTOR_INVALID,
	USB_DESCRIPTOR_DEVICE,
	USB_DESCRIPTOR_CONFIGURATION,
	USB_DESCRIPTOR_STRING,
	USB_DESCRIPTOR_INTERFACE,
	USB_DESCRIPTOR_ENDPOINT,
	USB_DESCRIPTOR_DEVICE_QUALIFIER,
	USB_DESCRIPTOR_OTHER_SPEED,
	USB_DESCRIPTOR_INTERFACE_POWER,
	USB_DESCRIPTOR_OTG,
	USB_DESCRIPTOR_DEBUG,
	USB_DESCRIPTOR_INTERFACE_ASSOCIATION
} usbDescriptor_t;

#endif /*USBTypes_H*/
