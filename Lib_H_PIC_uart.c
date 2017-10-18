/** 
 * File:   Lib_H_PIC_uart.c
 * Author: Isaev
 *
 * Created on 8 октября 2017 г., 17:19
 */

//******************************************************************************
// Секция include: здесь подключается заголовочный файл к модулю
#include "Lib_H_PIC_uart.h"
//******************************************************************************


//******************************************************************************
//------------------------------------------------------------------------------
// Глобальные переменные
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Локальные переменные
//------------------------------------------------------------------------------
//******************************************************************************


//******************************************************************************
// Секция прототипов локальных функций
//******************************************************************************


//******************************************************************************
// Секция описания функций (сначала глобальных, потом локальных)
//==============================================================================

//------------------------------------------------------------------------------
#if defined(__dsPIC33F__) || defined(__PIC24H__) || defined(__dsPIC33E__) || defined(__PIC24E__) || \
    defined(__dsPIC30F1010__) || defined(__dsPIC30F2020__) || defined(__dsPIC30F2023__)

void PIC_Init_USART_1_1StopBit_8BitData_RxIntEnChar_TxIntEn(unsigned long fcy,
                                                           unsigned long baudrate)
{
    unsigned int U_MODE = UART_EN
            & UART_IDLE_CON
            & UART_IrDA_DISABLE
            & UART_MODE_FLOW
            & UART_UEN_00
            & UART_DIS_WAKE
            & UART_DIS_LOOPBACK
            & UART_DIS_ABAUD
            & UART_UXRX_IDLE_ONE
            & UART_BRGH_SIXTEEN
            & UART_NO_PAR_8BIT
            & UART_1STOPBIT;

    unsigned int UxSTA = UART_INT_TX
            & UART_IrDA_POL_INV_ZERO
            & UART_SYNC_BREAK_DISABLED
            & UART_TX_ENABLE
            & UART_INT_RX_BUF_FUL
            & UART_ADR_DETECT_DIS
            & UART_RX_OVERRUN_CLEAR;

    OpenUART1(U_MODE, UxSTA, ((fcy / baudrate) / 16) - 1);

    ConfigIntUART1(UART_RX_INT_EN & UART_RX_INT_PR4
                   & UART_TX_INT_EN & UART_TX_INT_PR4);
}

void PIC_Init_USART_4_1StopBit_8BitData_RxIntEnChar_TxIntEn(long fcy,
                                                           unsigned long baudrate)
{
    unsigned int U_MODE = UART_EN
            & UART_IDLE_CON
            & UART_IrDA_DISABLE
            & UART_MODE_FLOW
            & UART_UEN_00
            & UART_DIS_WAKE
            & UART_DIS_LOOPBACK
            & UART_DIS_ABAUD
            & UART_UXRX_IDLE_ONE
            & UART_BRGH_SIXTEEN
            & UART_NO_PAR_8BIT
            & UART_1STOPBIT;

    unsigned int UxSTA = UART_INT_TX
            & UART_IrDA_POL_INV_ZERO
            & UART_SYNC_BREAK_DISABLED
            & UART_TX_ENABLE
            & UART_INT_RX_BUF_FUL
            & UART_ADR_DETECT_DIS
            & UART_RX_OVERRUN_CLEAR;

    OpenUART4(U_MODE, UxSTA, ((fcy / baudrate) / 16) - 1);

    ConfigIntUART4(UART_RX_INT_EN & UART_RX_INT_PR4
                   & UART_TX_INT_EN & UART_TX_INT_PR4);
}

void PIC_USART_1_TransmitPackageWithOutInterrupt(uint8_t *pDataArr,
                                                 size_t cnt)
{
    size_t i;
    for (i = 0; i < cnt; i++)
    {
        //  Ждем пока бит не будет сброшен в "0";
        while (U1STAbits.UTXBF != 0);

        //  Копируем в буфер UART_transmit байт данных;
        U1TXREG = *pDataArr;
    }
}

void PIC_USART_4_TransmitPackageWithOutInterrupt(uint8_t *pDataArr,
                                                 size_t cnt)
{
    size_t i;
    for (i = 0; i < cnt; i++)
    {
        //  Ждем пока бит не будет сброшен в "0";
        while (U4STAbits.UTXBF != 0);

        //  Копируем в буфер UART_transmit байт данных;
        U4TXREG = *pDataArr++;
    }
}
#endif //   defined(__dsPIC33F__) || defined(__PIC24H__) || defined(__dsPIC33E__) || defined(__PIC24E__) || 
//   defined(__dsPIC30F1010__) || defined(__dsPIC30F2020__) || defined(__dsPIC30F2023__)
//------------------------------------------------------------------------------


//==============================================================================
//******************************************************************************


////////////////////////////////////////////////////////////////////////////////
// END OF FILE
////////////////////////////////////////////////////////////////////////////////
