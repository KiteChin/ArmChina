#include "MSi001.h"
#include "delay.h"
static void sendbit(u8 b)
{
    delay_us(1);
    MSI001_CLK(0);
    if (b)
        MSI001_DATA(1);
    else
        MSI001_DATA(0);
    delay_us(1);
    MSI001_CLK(1);
    
}

void MSI_Write(u32 data, u8 addr)
{
    MSI001_EN(1);
    MSI001_CLK(0);
    delay_ms(1);
    MSI001_EN(0);
    for (int i = 0; i < 20; i++)
    {
        sendbit(data & 0x80000);
        data = data << 1;
    }
    for (int i = 0; i < 4; i++)
    {
        sendbit(addr & 0x8);
        addr = addr << 1;
    }
    MSI001_EN(1);
    // delay > 300nm
    delay_us(1);
}

void MSI_Init(void)
{

    MSI_Write(0x20001, MSI001_Reg6);
    MSI_Write(0x28bb8, MSI001_Reg5);
    MSI_Write(0x04342, MSI001_Reg0);
    MSI_Write(0x00FA0, MSI001_Reg3);
    MSI_Write(0x21000, MSI001_Reg2);
    MSI_Write(0x00c0A, MSI001_Reg1);
}

void MSI_ChangeChannel(double MSI_FRF)
{
    double temp = MSI_FRF * LOdiv / (4 * MSI_REFERENCE_FRE);
    uint32_t MSI_INT = (uint32_t)temp;
    uint32_t MSI_FRAC = (uint32_t)((temp - MSI_INT) * MSI_THRESH);
    uint32_t data = (MSI_INT<<12) + (MSI_FRAC);
    MSI_Write(data, MSI001_Reg2);
}
