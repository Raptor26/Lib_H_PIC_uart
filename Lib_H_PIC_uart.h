/**
 * File:   Lib_H_PIC_uart.h
 * Author: Isaev
 *
 * Created on 8 октября 2017 г., 17:19
 */

#ifndef LIB_H_PIC_UART_H
#define	LIB_H_PIC_UART_H

//******************************************************************************
// Секция include (подключаем заголовочные файлы используемых модулей)
//------------------------------------------------------------------------------
//  Стандартные библиотеки языка С
#include <stdint.h>
#include <stdio.h>
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//  Библиотеки для работы с периферией микроконтроллера
#include <xc.h>
#include <uart.h>
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//  Внешние модули
//------------------------------------------------------------------------------
//******************************************************************************


//******************************************************************************
// Секция определения констант
//******************************************************************************


//******************************************************************************
// Секция определения типов
//******************************************************************************


//******************************************************************************
// Секция определения глобальных переменных
//******************************************************************************


//******************************************************************************
// Секция прототипов глобальных функций

// ############### //
// <UART 1 module> //
// ############### //
#if defined (__PIC24H__) || defined(__dsPIC33E__) || defined(__PIC24E__)
extern void PIC_Init_USART_1_1StopBit_8BitData_RxIntEnBufFul_TxIntEnBufEmpt(unsigned long fcy,
        unsigned long baudrate);

extern void PIC_Init_USART_1_1StopBit_8BitData_RxIntEnChar_TxIntEnBufEmpt(unsigned long fcy,
        unsigned long baudrate);

extern void PIC_Init_USART_1_1StopBit_8BitData_RxIntEnBufFul_TxIntEnBufEmpt_HighSpeed(unsigned long fcy,
        unsigned long baudrate);

extern void PIC_USART_1_TransmitPackageWithOutInterrupt(uint8_t *pDataArr,
        size_t cnt);

extern size_t PIC_USART_1_Rx_OverflowCheck(void);
#endif //   (__PIC24H__) || defined(__dsPIC33E__) || defined(__PIC24E__)


// ############### //
// <UART 2 module> //
// ############### //
#if defined(__dsPIC33E__) || defined(__PIC24E__)
extern void PIC_Init_USART_2_1StopBit_8BitData_RxIntEnChar_TxIntEnChar(unsigned long fcy,
        unsigned long baudrate);
extern void PIC_Init_USART_2_1StopBit_8BitData_RxIntEnChar_TxIntEnLastChar(unsigned long fcy,
        unsigned long baudrate);
extern void PIC_USART_2_TransmitPackageWithOutInterrupt(uint8_t *pDataArr,
        size_t cnt);
#endif //   (__dsPIC33E__) || defined(__PIC24E__)


// ############### //
// <UART 3 module> //
// ############### //
#if defined(__dsPIC33E__) || defined(__PIC24E__)
extern void PIC_Init_USART_3_1StopBit_8BitData_RxIntEnChar_TxIntEnChar(unsigned long fcy,
        unsigned long baudrate);
extern void PIC_Init_USART_3_1StopBit_8BitData_RxIntEnChar_TxIntEnLastChar(unsigned long fcy,
        unsigned long baudrate);
#endif //   (__dsPIC33E__) || defined(__PIC24E__)


// ############### //
// <UART 4 module> //
// ############### //
#if defined(__dsPIC33E__) || defined(__PIC24E__)
extern void PIC_Init_USART_4_1StopBit_8BitData_RxIntEnBufFul_TxIntEnBufEmpt(unsigned long fcy,
        unsigned long baudrate);
extern void PIC_Init_USART_4_1StopBit_8BitData_RxIntEnChar_TxIntEnChar(unsigned long fcy,
        unsigned long baudrate);
extern void PIC_Init_USART_4_1StopBit_8BitData_RxIntEnChar_TxIntEnLastChar(unsigned long fcy,
        unsigned long baudrate);
extern void PIC_USART_4_TransmitPackageWithOutInterrupt(uint8_t *pDataArr,
        size_t cnt);
#endif //   (__dsPIC33E__) || defined(__PIC24E__)
//==============================================================================
//******************************************************************************


//******************************************************************************
// Секция определения макросов
//******************************************************************************

#endif	/* LIB_H_PIC_UART_H */

////////////////////////////////////////////////////////////////////////////////
// END OF FILE
////////////////////////////////////////////////////////////////////////////////
