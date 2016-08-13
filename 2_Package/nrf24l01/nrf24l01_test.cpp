/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
*
* FileName: nrf24l01_test.cpp
*
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke      2015.10.1    V1.0          creat this file
*
* Description:   这是一个测试NRF速度的程序  实际使用不用包含
***********************************************************************************************************************/

#include "nrf24l01_test.h"

float NRF_RxPacket_ID , NRF_Tx_Packet_ID ;                  //NRF当前接收到的包的ID号  和发送包的ID号
float LAST_RX_PACK_ID ;	

void NRF_RX_Test(void)
{

    unsigned char i, checksum;
    static unsigned short int RXNUM;

    nrf24L01.NRF_Driver_Call();
    if(	nrf24L01.NRF_RxPacket_Update == 1)
    {
        nrf24L01.NRF_RxPacket_Update = 0;

        RXNUM++;
        if( RXNUM >= 100 )
        {
            RXNUM=0;
            HF_Set_Led_State(1,2);
#if SYSTEM_SUPPORT_NRF_Debug >0u
            printf("\r\n error package %f  \r\n" , nrf24L01.NRF_RxPacket_Error_Num );
            printf("\r\n right package %f  \r\n" , nrf24L01.NRF_RxPacket_Right_Num);
#endif
        }
        LAST_RX_PACK_ID = NRF_RxPacket_ID ;
        memcpy(&NRF_RxPacket_ID , nrf24L01.NRF24L01_2_RXDATA ,4);
        if( ( NRF_RxPacket_ID - LAST_RX_PACK_ID ) != 1 )	   //package ID error
        {
            nrf24L01.NRF_RxPacket_Error_Num++;
        }
        else
        {
            checksum=0;
            for(i=0 ; i<=30 ;i++)
            {
                checksum+=nrf24L01.NRF24L01_2_RXDATA[i];
            }
            if( checksum != nrf24L01.NRF24L01_2_RXDATA[31] )   //package data error
            {
                nrf24L01.NRF_RxPacket_Error_Num++;
            }
            else
            {
                nrf24L01.NRF_RxPacket_Right_Num++;
            }
        }
        for(i=0 ; i<32 ;i++)  //clear buffer
        {
            nrf24L01.NRF24L01_2_RXDATA[i]=0;
        }

    }
}


void NRF_TX_One_Pack(void)
{

    static u8 i,j;
    u8 checksum;

    NRF_Tx_Packet_ID++;
    memcpy( nrf24L01.NRF24L01_2_TXDATA , &NRF_Tx_Packet_ID ,4);
    for(i=4 ; i<=30 ;i++)
    {
        nrf24L01.NRF24L01_2_TXDATA[i]=j;
        j++;
    }

    checksum=0;
    for(i=0 ; i<=30 ;i++)
    {
        checksum+=nrf24L01.NRF24L01_2_TXDATA[i];
    }
    nrf24L01.NRF24L01_2_TXDATA[31]=	checksum ;

    nrf24L01.NRF_Tx_Packet(nrf24L01.NRF24L01_2_TXDATA ,32);
}




