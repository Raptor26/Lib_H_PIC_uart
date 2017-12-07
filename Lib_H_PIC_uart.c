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
//==============================================================================
//  Функции, относящиеся к модулю USART 1
#if defined (__PIC24H__) || defined(__dsPIC33E__) || defined(__PIC24E__)

void PIC_Init_USART_1_1StopBit_8BitData_RxIntEnBufFul_TxIntEnBufEmpt(unsigned long fcy,
                                                                     unsigned long baudrate)
{
    CloseUART1();

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

    unsigned int U_STA = UART_INT_TX_BUF_EMPTY
            & UART_IrDA_POL_INV_ZERO
            & UART_SYNC_BREAK_DISABLED
            & UART_TX_ENABLE
            & UART_INT_RX_BUF_FUL
            & UART_ADR_DETECT_DIS
            & UART_RX_OVERRUN_CLEAR;

    //  Делаем расчет скорости работы модуля UART
    unsigned int U_BRG = ((fcy / baudrate) / 16) - 1;

    OpenUART1(U_MODE, U_STA, U_BRG);

    ConfigIntUART1(UART_RX_INT_EN & UART_RX_INT_PR4
                   & UART_TX_INT_EN & UART_TX_INT_PR4);
}

void PIC_Init_USART_1_1StopBit_8BitData_RxIntEnChar_TxIntEnBufEmpt(unsigned long fcy,
                                                                   unsigned long baudrate)
{
    CloseUART1();

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

    unsigned int U_STA = UART_INT_TX_BUF_EMPTY
            & UART_IrDA_POL_INV_ZERO
            & UART_SYNC_BREAK_DISABLED
            & UART_TX_ENABLE
            & UART_INT_RX_CHAR
            & UART_ADR_DETECT_DIS
            & UART_RX_OVERRUN_CLEAR;

    //  Делаем расчет скорости работы модуля UART
    unsigned int U_BRG = ((fcy / baudrate) / 16) - 1;

    OpenUART1(U_MODE, U_STA, U_BRG);

    ConfigIntUART1(UART_RX_INT_EN & UART_RX_INT_PR4
                   & UART_TX_INT_EN & UART_TX_INT_PR4);
}

/**
 *  @brief  Функция выполняет конфигурирование модуля UART 1 в высокоскоротном 
 *          режиме.
 *          Параметры работы модуля USART 1 смотри в переменных "U_MODE" и "U_STA";
 *  @param  fcy:    Частота работы микроконтроллера;
 *  @param  baudrate:   Желаемая скорость работы модуля UART 1;
 *  @retval None;
 */
void PIC_Init_USART_1_1StopBit_8BitData_RxIntEnBufFul_TxIntEnBufEmpt_HighSpeed(unsigned long fcy,
                                                                                unsigned long baudrate)
{
    CloseUART1();

    unsigned int U_MODE = UART_EN
            & UART_IDLE_CON
            & UART_IrDA_DISABLE
            & UART_MODE_FLOW
            & UART_UEN_00
            & UART_DIS_WAKE
            & UART_DIS_LOOPBACK
            & UART_DIS_ABAUD
            & UART_UXRX_IDLE_ONE
            & UART_BRGH_FOUR
            & UART_NO_PAR_8BIT
            & UART_1STOPBIT;

    unsigned int U_STA = UART_INT_TX_BUF_EMPTY
            & UART_IrDA_POL_INV_ZERO
            & UART_SYNC_BREAK_DISABLED
            & UART_TX_ENABLE
            & UART_INT_RX_BUF_FUL
            & UART_ADR_DETECT_DIS
            & UART_RX_OVERRUN_CLEAR;

    //  Делаем расчет скорости работы модуля UART
    unsigned int U_BRG = ((fcy / baudrate) / 4) - 1;

    OpenUART1(U_MODE, U_STA, U_BRG);

    ConfigIntUART1(UART_RX_INT_EN & UART_RX_INT_PR4
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
        U1TXREG = *pDataArr++;
    }
}

/**
 *  @brief  Функция выполняет проверку переполнения RX буфера USART1 и возвращает 
 *          "1" если было обнаружено переполнение, иначе возвращает "0"
 *  @return "1" - если было обнаружено переполнение RX буфера USART1,
 *          "0" - если переполнение не было обнаружено
 */
size_t PIC_USART_1_Rx_OverflowCheck(void)
{
    if (U1STAbits.OERR == 1)
    {
        return 1; //            Если было обнаружено переполнение;
    }
    else
    {
        return 0; //            Если переполнения нет;
    }
}

#endif //   (__PIC24H__) || defined(__dsPIC33E__) || defined(__PIC24E__)
//==============================================================================


//==============================================================================
#if defined(__dsPIC33E__) || defined(__PIC24E__)
//  Функции, относящиеся к модулю USART 2

void PIC_Init_USART_2_1StopBit_8BitData_RxIntEnChar_TxIntEnChar(unsigned long fcy,
                                                                unsigned long baudrate)
{
    CloseUART2();

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

    unsigned int U_STA = UART_INT_TX
            & UART_IrDA_POL_INV_ZERO
            & UART_SYNC_BREAK_DISABLED
            & UART_TX_ENABLE
            & UART_INT_RX_CHAR
            & UART_ADR_DETECT_DIS
            & UART_RX_OVERRUN_CLEAR;

    //  Делаем расчет скорости работы модуля UART
    unsigned int U_BRG = ((fcy / baudrate) / 16) - 1;

    OpenUART2(U_MODE, U_STA, U_BRG);

    ConfigIntUART2(UART_RX_INT_EN & UART_RX_INT_PR4
                   & UART_TX_INT_EN & UART_TX_INT_PR4);
}

void PIC_Init_USART_2_1StopBit_8BitData_RxIntEnChar_TxIntEnLastChar(unsigned long fcy,
                                                                    unsigned long baudrate)
{
    CloseUART2();

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

    unsigned int U_STA = UART_INT_TX_LAST_CH
            & UART_IrDA_POL_INV_ZERO
            & UART_SYNC_BREAK_DISABLED
            & UART_TX_ENABLE
            & UART_INT_RX_CHAR
            & UART_ADR_DETECT_DIS
            & UART_RX_OVERRUN_CLEAR;

    //  Делаем расчет скорости работы модуля UART
    unsigned int U_BRG = ((fcy / baudrate) / 16) - 1;

    OpenUART2(U_MODE, U_STA, U_BRG);

    ConfigIntUART2(UART_RX_INT_EN & UART_RX_INT_PR4
                   & UART_TX_INT_EN & UART_TX_INT_PR4);
}

void PIC_USART_2_TransmitPackageWithOutInterrupt(uint8_t *pDataArr,
                                                 size_t cnt)
{
    size_t i;
    for (i = 0; i < cnt; i++)
    {
        //  Ждем пока бит не будет сброшен в "0";
        while (U2STAbits.UTXBF != 0);

        //  Копируем в буфер UART_transmit байт данных;
        U2TXREG = *pDataArr++;
    }
}

//  Функции, относящиеся к модулю USART 3

void PIC_Init_USART_3_1StopBit_8BitData_RxIntEnChar_TxIntEnLastChar(unsigned long fcy,
                                                                    unsigned long baudrate)
{
    CloseUART3();

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

    unsigned int U_STA = UART_INT_TX_LAST_CH
            & UART_IrDA_POL_INV_ZERO
            & UART_SYNC_BREAK_DISABLED
            & UART_TX_ENABLE
            & UART_INT_RX_CHAR
            & UART_ADR_DETECT_DIS
            & UART_RX_OVERRUN_CLEAR;

    //  Делаем расчет скорости работы модуля UART
    unsigned int U_BRG = ((fcy / baudrate) / 16) - 1;

    OpenUART2(U_MODE, U_STA, U_BRG);

    ConfigIntUART3(UART_RX_INT_EN & UART_RX_INT_PR4
                   & UART_TX_INT_EN & UART_TX_INT_PR4);
}

//  Функции, относящиеся к модулю USART 4

void PIC_Init_USART_4_1StopBit_8BitData_RxIntEnBufFul_TxIntEnBufEmpt(unsigned long fcy,
                                                                     unsigned long baudrate)
{
    CloseUART4();
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

    unsigned int U_STA = UART_INT_TX_BUF_EMPTY
            & UART_IrDA_POL_INV_ZERO
            & UART_SYNC_BREAK_DISABLED
            & UART_TX_ENABLE
            & UART_INT_RX_BUF_FUL
            & UART_ADR_DETECT_DIS
            & UART_RX_OVERRUN_CLEAR;

    //  Делаем расчет скорости работы модуля UART
    unsigned int U_BRG = ((fcy / baudrate) / 16) - 1;

    OpenUART4(U_MODE, U_STA, U_BRG);

    ConfigIntUART4(UART_RX_INT_EN & UART_RX_INT_PR4
                   & UART_TX_INT_EN & UART_TX_INT_PR4);
}

void PIC_Init_USART_4_1StopBit_8BitData_RxIntEnChar_TxIntEnChar(unsigned long fcy,
                                                                unsigned long baudrate)
{
    CloseUART4();

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

    unsigned int U_STA = UART_INT_TX
            & UART_IrDA_POL_INV_ZERO
            & UART_SYNC_BREAK_DISABLED
            & UART_TX_ENABLE
            & UART_INT_RX_CHAR
            & UART_ADR_DETECT_DIS
            & UART_RX_OVERRUN_CLEAR;

    //  Делаем расчет скорости работы модуля UART
    unsigned int U_BRG = ((fcy / baudrate) / 16) - 1;

    OpenUART4(U_MODE, U_STA, U_BRG);

    ConfigIntUART4(UART_RX_INT_EN & UART_RX_INT_PR4
                   & UART_TX_INT_EN & UART_TX_INT_PR4);
}

void PIC_Init_USART_4_1StopBit_8BitData_RxIntEnChar_TxIntEnLastChar(unsigned long fcy,
                                                                    unsigned long baudrate)
{
    CloseUART4();

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

    unsigned int U_STA = UART_INT_TX_LAST_CH
            & UART_IrDA_POL_INV_ZERO
            & UART_SYNC_BREAK_DISABLED
            & UART_TX_ENABLE
            & UART_INT_RX_CHAR
            & UART_ADR_DETECT_DIS
            & UART_RX_OVERRUN_CLEAR;

    //  Делаем расчет скорости работы модуля UART
    unsigned int U_BRG = ((fcy / baudrate) / 16) - 1;

    OpenUART4(U_MODE, U_STA, U_BRG);

    ConfigIntUART4(UART_RX_INT_EN & UART_RX_INT_PR4
                   & UART_TX_INT_EN & UART_TX_INT_PR4);
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
#endif //   (__dsPIC33E__) || defined(__PIC24E__)
//==============================================================================
//------------------------------------------------------------------------------


//==============================================================================
//******************************************************************************


////////////////////////////////////////////////////////////////////////////////
// END OF FILE
////////////////////////////////////////////////////////////////////////////////
