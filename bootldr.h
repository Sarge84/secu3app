 /****************************************************************
 *       SECU-3  - An open source, free engine control unit
 *    Designed by Alexey A. Shabelnikov. Ukraine, Gorlovka 2007.
 *       Microprocessors systems - design & programming.
 *    contacts:
 *              http://secu-3.narod.ru
 *              ICQ: 405-791-931
 ****************************************************************/

#ifndef _BOOTLDR_H_
#define _BOOTLDR_H_

//���������� ������ ������ ���������� � ����������� �� ��������� ���������
#ifdef __ATmega16__
 #define BOOT_LOADER_SIZE  512    //<--second
#elif __ATmega32__
 #define BOOT_LOADER_SIZE  512    //<--first
#elif __ATmega64__
 #define BOOT_LOADER_SIZE  1024   //<--first 
#else
 #error "Not supported platform!"  
#endif 

//���������� ��������� ����� ���������� � �������� (� ������)
//FLASHEND ���������� � ioavr.h
#define SECU3BOOTSTART ((((unsigned int)FLASHEND) + 1) - BOOT_LOADER_SIZE)

//����� ����� � ��������� �� ��������� (����� �������� ���������)
#define boot_loader_start() ((void (*)())(SECU3BOOTSTART+0xA))()

//���� ������ ����� � ������ ��������� ���������� �� ���� ������������ �� ��� ���
#pragma object_attribute=__root 
__flash const uint8_t BootLoader[BOOT_LOADER_SIZE]@SECU3BOOTSTART =
{
#ifdef __ATmega16__
0xF8,0x94,0x00,0x24,0x04,0xBA,0x9B,0x99,0xFB,0xC0,0xF8,0x94,0x8F,0xE5,0x94,0xE0,
0x8D,0xBF,0x9E,0xBF,0x87,0xE6,0x89,0xB9,0x88,0xE1,0x8A,0xB9,0x70,0xD0,0x01,0x32,
0xE9,0xF7,0x6D,0xD0,0x00,0x35,0xD9,0xF4,0x9D,0xD0,0xAC,0xD0,0x13,0xE0,0xB0,0xD0,
0x11,0xE1,0xAE,0xD0,0x44,0x27,0x80,0xE8,0x95,0xD0,0x00,0x2E,0x40,0x27,0x92,0xD0,
0x10,0x2E,0x40,0x27,0x11,0xE0,0xA4,0xD0,0x32,0x96,0x82,0x50,0xA9,0xF7,0xE0,0x58,
0xF0,0x40,0x15,0xE0,0x9D,0xD0,0x50,0xD0,0x04,0x2F,0x79,0xD0,0xDF,0xCF,0x02,0x35,
0x79,0xF4,0x80,0xD0,0x8F,0xD0,0x48,0xD0,0x11,0xE1,0x92,0xD0,0x44,0x27,0x80,0xE8,
0x05,0x91,0x40,0x27,0x6C,0xD0,0x81,0x50,0xD9,0xF7,0x04,0x2F,0x68,0xD0,0xCE,0xCF,
0x0A,0x34,0x69,0xF4,0x39,0xD0,0x44,0x27,0xAA,0x27,0xBB,0x27,0x11,0xE0,0x88,0xD0,
0x40,0x27,0x5D,0xD0,0xB2,0x30,0xD9,0xF7,0x04,0x2F,0x59,0xD0,0xBF,0xCF,0x07,0x35,
0x71,0xF4,0x44,0x27,0xAA,0x27,0xBB,0x27,0x16,0xE0,0x5C,0xD0,0x0D,0xBB,0x78,0xD0,
0x40,0x27,0xB2,0x30,0xD1,0xF7,0x20,0xD0,0x04,0x2F,0x49,0xD0,0xAF,0xCF,0x04,0x35,
0x61,0xF4,0x1A,0xD0,0x00,0xE4,0x1F,0xD0,0x5D,0x9B,0xFE,0xCF,0x07,0xB7,0x06,0xFF,
0x97,0xC0,0x11,0xE1,0x5D,0xD0,0xFA,0xCF,0xA1,0xCF,0x09,0x34,0x49,0xF4,0x0C,0xD0,
0xE4,0xEB,0xFF,0xE3,0x05,0x91,0x00,0x23,0x11,0xF0,0x0D,0xD0,0xFB,0xCF,0x96,0xCF,
0x03,0xD0,0x0F,0xE3,0x08,0xD0,0x92,0xCF,0x0C,0xE3,0x05,0xD0,0x08,0x95,0x5F,0x9B,
0xFE,0xCF,0x0C,0xB1,0x08,0x95,0x5D,0x9B,0xFE,0xCF,0x0C,0xB9,0x08,0x95,0x2F,0x93,
0x10,0x2F,0x12,0x95,0x1F,0x70,0x1A,0x30,0x10,0xF0,0x27,0xE0,0x12,0x0F,0x20,0xE3,
0x12,0x0F,0x0F,0x70,0x0A,0x30,0x10,0xF0,0x27,0xE0,0x02,0x0F,0x20,0xE3,0x02,0x0F,
0x2F,0x91,0x08,0x95,0x1F,0x93,0x0A,0x33,0x08,0xF0,0x07,0x50,0x00,0x53,0x1A,0x33,
0x08,0xF0,0x17,0x50,0x10,0x53,0x12,0x95,0x01,0x2B,0x1F,0x91,0x08,0x95,0x0F,0x93,
0x1F,0x93,0xDD,0xDF,0x0F,0x93,0x01,0x2F,0xD6,0xDF,0x0F,0x91,0xD4,0xDF,0x1F,0x91,
0x0F,0x91,0x08,0x95,0x1F,0x93,0xCB,0xDF,0x01,0x32,0x41,0xF0,0x10,0x2F,0xC7,0xDF,
0x01,0x32,0x21,0xF0,0x0E,0x94,0x9A,0x1F,0x1F,0x91,0x08,0x95,0x1F,0x91,0x0F,0x91,
0x0F,0x91,0x4F,0xCF,0xF0,0x2F,0xF6,0x95,0xEE,0x27,0x00,0xFB,0xE7,0xF9,0x08,0x95,
0x07,0xB7,0x00,0xFD,0xFD,0xCF,0xE1,0x99,0xFE,0xCF,0x17,0xBF,0xE8,0x95,0x08,0x95,
0xAE,0xBB,0xBF,0xBB,0x11,0x96,0x11,0xFD,0xE2,0x9A,0x1C,0xBB,0xE1,0x99,0xFE,0xCF,
0x0D,0xB3,0x08,0x95,0x42,0x6F,0x6F,0x74,0x20,0x6C,0x6F,0x61,0x64,0x65,0x72,0x20,
0x76,0x31,0x2E,0x31,0x2E,0x5B,0x30,0x35,0x2E,0x30,0x38,0x5D,0x00,0x00,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
#elif __ATmega32__
 #error "Not implemented yet!"
#elif __ATmega64__
 #error "Not implemented yet!"
#else
 #error "Not supported platform!"
#endif
};


#endif //_BOOTLDR_H_
