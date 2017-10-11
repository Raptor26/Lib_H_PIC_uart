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
// Функции для микроконтроллера серии "PIC24H"
#if defined (__PIC24H__)

/**
 *  @brief  Функция выполняет конфигурирование модуля USART1 микроконтроллера 
 *          серии PIC24H со следующими параметрами:
 *              
 *  @param  *u_modeAddr:    Указатель на адрес регистра "UxMODE"
 *  @param  *u_staAddr:     Указатель на адрес регистра "UxSTA"
 *  @param  *u_brg:         Указатель на адрес регистра "UxBRG"
 *  @param  fcy:            Частота работы тактового генератора микроконтроллера
 *  @param  baudrate:       Желаемая скорость работы модуля UART
 */
void PIC_Init_USART1_1StopBit_8BitData_RxIntEnBufFul_TxIntEnBufFul(unsigned long fcy,
                                                                   unsigned long baudrate)
{
    //  Конфигурируем регистр UxMode
    size_t U_MODE = UART_EN
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

    //  Конфигурируем регистр UxSTA
    size_t U_STA = UART_INT_TX
            & UART_IrDA_POL_INV_ZERO
            & UART_SYNC_BREAK_DISABLED
            & UART_TX_ENABLE
            & UART_INT_RX_BUF_FUL
            & UART_ADR_DETECT_DIS
            & UART_RX_OVERRUN_CLEAR;

    //  Делаем расчет скорости работы модуля UART
    size_t U_BRG = ((fcy / baudrate) / 16) - 1;

    OpenUART1(U_MODE, U_STA, U_BRG);
    ConfigIntUART1(UART_RX_INT_EN & UART_RX_INT_PR4
                   & UART_TX_INT_EN & UART_TX_INT_PR4);

    //    *u_modeAddr = U_MODE; //        Переносим переменную конфигурации в регистр UxMODE
    //    *u_staAddr = U_STA; //          Переносим переменную конфируации в регистр UxSTA
    //    *u_brg = U_BRG; //              Переносим переменную конфируации в регистр UxBRG
}

/**
 *  @brief  Функция выполняет проверку переполнения RX буфера USART1 и возвращает 
 *          "1" если было обнаружено переполнение, иначе возвращает "0"
 *  @return "1" - если было обнаружено переполнение RX буфера USART1,
 *          "0" - если переполнение не было обнаружено
 */
size_t PIC_USART1_Rx_OverflowCheck(void)
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
#endif
//------------------------------------------------------------------------------


//==============================================================================
//******************************************************************************


////////////////////////////////////////////////////////////////////////////////
// END OF FILE
////////////////////////////////////////////////////////////////////////////////
