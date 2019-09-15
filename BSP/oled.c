#include "oled.h"
#include "oled_iic.h"

#include "oled_font.h"

void OLED_WriteCmd(u8 command)
{
    OLED_IIC_Start();
    OLED_IIC_Send_Byte(0x78);//OLED地址
    OLED_IIC_Wait_Ack();
    OLED_IIC_Send_Byte(0x00);//寄存器地址
    OLED_IIC_Wait_Ack();
    OLED_IIC_Send_Byte(command);
    OLED_IIC_Wait_Ack();
    OLED_IIC_Stop();
}

void OLED_WriteData(u8 data)
{
    OLED_IIC_Start();
    OLED_IIC_Send_Byte(0x78);//OLED地址
    OLED_IIC_Wait_Ack();
    OLED_IIC_Send_Byte(0x40);//寄存器地址
    OLED_IIC_Wait_Ack();
    OLED_IIC_Send_Byte(data);
    OLED_IIC_Wait_Ack();
    OLED_IIC_Stop();
}
void OLED_WriteData2(u8 data)
{
    OLED_IIC_Start();
    OLED_IIC_Send_Byte(0x78);//OLED地址
    OLED_IIC_Wait_Ack();
    OLED_IIC_Send_Byte(0x40);//寄存器地址
    OLED_IIC_Wait_Ack();
    OLED_IIC_Send_Byte(~data);
    OLED_IIC_Wait_Ack();
    OLED_IIC_Stop();
}
//设置对比度
void OLED_SetContrast(u8 con)
{
    OLED_WriteCmd(0x81);	 //对比度设置
    OLED_WriteCmd(con); 	 //1~255;默认0X7F (亮度设置,越大越亮)
}



void OLED_Clear(void)		//全部是黑色的.没有点亮
{
    u8 i, n;
    for(i = 0; i < 8; i++)
    {
        OLED_WriteCmd (0xb0 + i); //设置页地址（0~7）
        OLED_WriteCmd (0x00);     //设置显示位置—列低地址
        OLED_WriteCmd (0x10);     //设置显示位置—列高地址
        for(n = 0; n < 128; n++)	//每行128个点
            OLED_WriteData(0);		//熄灭像素点
    }
}
void OLED_Init(void)
{
	OLED_IIC_Init();

//    delay_ms(100); 

    OLED_WriteCmd(0xAE); //关闭显示
    OLED_WriteCmd(0xD5); //设置时钟分频因子,震荡频率
    OLED_WriteCmd(0x80);  //[3:0],分频因子;[7:4],震荡频率
    OLED_WriteCmd(0xA8); //设置驱动路数
    OLED_WriteCmd(0X3F); //默认0X3F(1/64)
    OLED_WriteCmd(0xD3); //设置显示偏移
    OLED_WriteCmd(0X00); //默认为0
    OLED_WriteCmd(0x40); //设置显示开始行 [5:0],行数.
    OLED_WriteCmd(0x8D); //电荷泵设置
    OLED_WriteCmd(0x14); //bit2，开启/关闭
    OLED_WriteCmd(0x20); //设置内存地址模式
    OLED_WriteCmd(0x02); //[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;
    OLED_WriteCmd(0xA1); //0xa0左右反置 0xa1正常
    OLED_WriteCmd(0xC8); //0xc0上下反置 0xc8正常
    OLED_WriteCmd(0xDA); //设置COM硬件引脚配置
    OLED_WriteCmd(0x12); //[5:4]配置
    OLED_WriteCmd(0x81); //对比度设置
    OLED_WriteCmd(0x7f); //1~255;默认0X7F (亮度设置,越大越亮)
    OLED_WriteCmd(0xD9); //设置预充电周期
    OLED_WriteCmd(0xf1); //[3:0],PHASE 1;[7:4],PHASE 2;
    OLED_WriteCmd(0xDB); //设置VCOMH 电压倍率
    OLED_WriteCmd(0x30); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
    OLED_WriteCmd(0xA4); //全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)
    OLED_WriteCmd(0xA6); //设置显示方式;bit0:1-0xa7反相显示;0xa6正常显示
    OLED_WriteCmd(0xAF); //开启显示

    OLED_Clear();
    OLED_SetCursor(0, 0);
}

void OLED_ON(void)
{
    OLED_WriteCmd(0X8D);  //设置电荷泵
    OLED_WriteCmd(0X14);  //开启电荷泵
    OLED_WriteCmd(0XAF);  //OLED唤醒
}


/**
 * @brief  OLED_SetCursor，设置光标
 * @param  x,光标x位置
   *                   y，光标y位置
 * @retval 无
 */
void OLED_SetCursor(unsigned char x, unsigned char y) //设置起始点坐标
{
    OLED_WriteCmd(0xb0 + (y >> 3));
//    OLED_WriteCmd(0xb0 + y);
    OLED_WriteCmd(((x & 0xf0) >> 4) | 0x10);
    OLED_WriteCmd((x & 0x0f) | 0x01);
}

/**
 * @brief  OLED_Fill，填充整个屏幕
 * @param  fill_Data:要填充的数据
   * @retval 无
 */
void OLED_Fill(unsigned char fill_Data)//全屏填充
{
    unsigned char m, n;
    for(m = 0; m < 8; m++)
    {
        OLED_WriteCmd(0xb0 + m);     //page0-page1
        OLED_WriteCmd(0x00);     //low column start address
        OLED_WriteCmd(0x10);     //high column start address
        for(n = 0; n < 128; n++)
        {
            OLED_WriteData(fill_Data);
        }
    }
}

void OLED_CLS(void)//清屏
{
    OLED_Fill(0x00);
}

#if 1		//16*32数字，像素坐标显示
//显示字符,16*32字体,x：0-127，y：0-63
void OLED_DisChar_F16X32(u8 x, u8 y, u8 ch)
{
    u8 c, i;
	if(ch == ':')
		c = 10;
	else
		c = ch - '0';		//地址偏移
    //一次显示四分之一
	OLED_SetCursor(x, y);		//上1/4
    for(i = 0; i < 16; i++)		
        OLED_WriteData(F16X32[c][i]);			
	OLED_SetCursor(x, y+8);
	for(i = 0; i < 16; i++)		
        OLED_WriteData(F16X32[c][i+16]);	//上2/4
		OLED_SetCursor(x, y+16);
	for(i = 0; i < 16; i++)		
        OLED_WriteData(F16X32[c][i+32]);	//2/4
	OLED_SetCursor(x, y+24);
	for(i = 0; i < 16; i++)		
        OLED_WriteData(F16X32[c][i+48]);	//上2/4
/*	
	//动态效果
	OLED_SetCursor(x, y+16);
	for(i = 0; i < 16; i++)		
        OLED_WriteData(F16X32[c][i+32]);	//2/4
	OLED_SetCursor(x, y+24);
	for(i = 0; i < 16; i++)		
        OLED_WriteData(F16X32[c][i+48]);	//上2/4
	delay_ms(105);
	
	OLED_SetCursor(x, y);		//上1/4
    for(i = 0; i < 16; i++)		
        OLED_WriteData(F16X32[c][i]);			
	OLED_SetCursor(x, y+8);
	for(i = 0; i < 16; i++)		
        OLED_WriteData(F16X32[c][i+16]);	//上2/4
	*/
}
/*显示字符串,16X32字体*/
void OLED_DisString_F16X32(u8 x, u8 y, u8 *str)
{
    while (*str != '\0')
    {
        OLED_DisChar_F16X32(x, y, *str++);
        x += 16;
    }
}
/*显示两位数字，8X16字体，x：0-14，y：0-3*/
void OLED_DisNumber_F16X32(u8 x, u8 y, u8 num)
{
    //调用字符函数显示
    OLED_DisChar_F16X32(x, y, num / 10 + 0x30);
    OLED_DisChar_F16X32(x + 16, y, num % 10 + 0x30);
}

#endif



#if 1		//8x16字体,行列坐标显示,x：0-15，y：0-3

//显示字符,8*16字体,x：0-15，y：0-3
void OLED_DisChar_F8X16(u8 x, u8 y, u8 ch)
{
    u8 c, i;
    c = ch - ' ';
    OLED_SetCursor(x * 8, y * 16);
    for(i = 0; i < 8; i++)					//显示上半部分8*8
        OLED_WriteData(F8X16[c][i]);		//每一行的前8个
    OLED_SetCursor(x * 8, y * 16 + 8);			//显示下半部分8*8
    for(i = 0; i < 8; i++)
        OLED_WriteData(F8X16[c][i + 8]);	//每一行的后8个
}
//显示8*16字符反显,x：0-15，y：0-3
void OLED_CharInverse_F8X16(u8 x, u8 y, u8 ch)
{
    u8 c, i;
    c = ch - ' ';
    OLED_SetCursor(x * 8, y * 16);
    for(i = 0; i < 8; i++)
        OLED_WriteData2(F8X16[c][i]);
    OLED_SetCursor(x * 8, y * 16 + 8);
    for(i = 0; i < 8; i++)
        OLED_WriteData2(F8X16[c][i + 8]);
}
//显示8x16字符闪烁
void OLED_CharBlink_F8X16(u8 x, u8 y, u8 ch)
{
    OLED_CharInverse_F8X16(x, y, ch);
    delay_ms(400);
    OLED_DisChar_F8X16(x, y, ch);
    delay_ms(400);
}
//显示两位数字，8X16字体，x：0-14，y：0-3
void OLED_DisNumber_F8X16(u8 x, u8 y, u8 num)
{
    //调用字符函数显示
    OLED_DisChar_F8X16(x, y, num / 10 + 0x30);
    OLED_DisChar_F8X16(x + 1, y, num % 10 + 0x30);

}
void OLED_ShowNumber_F8X16(u8 x, u8 y, u32 num, u8 n)
{
	u8 i;
	for( i = 0; i < n; i++)
	{
		OLED_DisChar_F8X16(x + n-1, y, num % 10 + 0x30);
		num = num / 10;
		x--;
	}
}


//显示两位数字反显,8*16字体,x：0-14，y：0-3
void OLED_NumberInverse_F8X16(u8 x, u8 y, u8 num)
{
    OLED_CharInverse_F8X16(x, y, num / 10 + 0x30);
    OLED_CharInverse_F8X16(x + 1, y, num % 10 + 0x30);
}
//显示两位数字闪烁:正常和反显交替
void OLED_NumberBlink_F8X16(u8 x, u8 y, u8 num)
{
    OLED_NumberInverse_F8X16(x, y, num);
    delay_ms(100);
    OLED_DisNumber_F8X16(x, y, num);
    delay_ms(100);
}
//显示字符串,8X16字体，x：0-15，y：0-3
void OLED_DisString_F8X16(u8 x, u8 y, u8 *str)
{
    while (*str != '\0')
    {
        OLED_DisChar_F8X16(x, y, *str++);
        x++;
    }
}
//指定位置显示8*16黑块字符
void OLED_DisBlack_F8X16(u8 x, u8 y)		//指定位置显示字符黑块
{
    u8 i;
    OLED_SetCursor(x * 8, y * 16);
    for(i = 0; i < 8; i++)
        OLED_WriteData(0);			//熄灭像素点
    OLED_SetCursor(x * 8, y * 16 + 8);
    for(i = 0; i < 8; i++)
        OLED_WriteData(0);
}
//指定位置显示8*16白块字符
void OLED_DisWhite_F8X16(u8 x, u8 y)		//指定位置显示字符白块
{
    u8 i;
    OLED_SetCursor(x * 8, y * 16);
    for(i = 0; i < 8; i++)
        OLED_WriteData2(0);			//点亮像素点
    OLED_SetCursor(x * 8, y * 16 + 8);
    for(i = 0; i < 8; i++)
        OLED_WriteData2(0);
}
#endif


#if 0		//8x16字体,像素坐标显示,x：0-127，y：0-63

/*显示字符,8X16字体,x：0-127，y：0-63*/
void OLED_DisChar_F8X16(u8 x, u8 y, u8 ch)
{
    u8 c, i;
    c = ch - ' ';		//地址偏移
    OLED_SetCursor(x, y);
    for(i = 0; i < 8; i++)		//显示上半部分8*8
        OLED_WriteData(F8X16[c][i]);			//每一行的前8个
    OLED_SetCursor(x, y + 8);		//显示下半部分8*8
    for(i = 0; i < 8; i++)
        OLED_WriteData(F8X16[c][i + 8]);		//每一行的后8个
}
void OLED_DisString_F8X16(u8 x, u8 y, u8 *str)
{
    while (*str != '\0')
    {
        OLED_DisChar_F8X16(x, y, *str++);
        x += 8;
    }
}
/*显示两位数字，8X16字体，x：0-14，y：0-3*/
void OLED_DisNumber_F8X16(u8 x, u8 y, u8 num)
{
    //调用字符函数显示
    OLED_DisChar_F8X16(x, y, num / 10 + 0x30);
    OLED_DisChar_F8X16(x + 8, y, num % 10 + 0x30);
}

#endif



void OLED_Set_Pos(u8 x, u8 y)	 //汉字显示，设置显示坐标
{
    OLED_WriteCmd(0xb0 + y);
    OLED_WriteCmd(((x & 0xf0) >> 4) | 0x10);
    OLED_WriteCmd((x & 0x0f) | 0x01);
}
void OLED_DisChinese(u8 x, u8 y, u8 Num)
{
	u8 i;
    OLED_SetCursor(x, y);
    for(i = 0; i < 16; i++)
        OLED_WriteData(CHN[Num][i]);	
	
    OLED_SetCursor(x, y + 8);
    for(i = 0; i < 16; i++)
        OLED_WriteData(CHN[Num][i + 16]);
}

#if 1		//6x8字体,行列坐标,x：0-20，y：0-7

/*显示字符：6X8字体，x：0-20，y：0-7*/
void OLED_DisChar_F6X8(u8 x, u8 y, u8 ch)
{
    u8 c = 0, i = 0;
    c = ch - ' ';
    OLED_SetCursor(x * 6, y * 8);
    for(i = 0; i < 6; i++)
        OLED_WriteData(F6X8[c][i]);
}
/*显示字符串，6X8字体,长度不能超过21个字符*/
void OLED_DisString_F6X8(u8 x, u8 y, u8 *str)
{
    while (*str != '\0')
    {
        OLED_DisChar_F6X8(x, y, *str++);
        x++;
    }
}
/*显示两位数字,6X8字体,x：0-19，y:0-7*/
void OLED_DisNumber_F6X8(u8 x, u8 y, u8 num)
{
    //调用字符函数显示
    OLED_DisChar_F6X8(x, y, num / 10 + 0x30);
    OLED_DisChar_F6X8(x + 1, y, num % 10 + 0x30);

}
void OLED_ShowNumber_F6X8(u8 x, u8 y, u32 num, u8 n)
{
	u8 i;
	for( i = 0; i < n; i++)
	{
		OLED_DisChar_F6X8(x + n-1, y, num % 10 + 0x30);
		num = num / 10;
		x--;
	}
}
#endif

#if 0		//6x8字体,像素坐标显示,x：0-127，y：0-63

/*显示字符：6X8字体，x：0-127，y：0-36*/
void OLED_DisChar_F6X8(u8 x, u8 y, u8 ch)
{
    u8 c = 0, i = 0;
    c = ch - ' ';
    OLED_SetCursor(x, y);
    for(i = 0; i < 6; i++)
        OLED_WriteData(F6X8[c][i]);
}
/*显示字符串，6X8字体,长度不能超过21个字符*/
void OLED_DisString_F6X8(u8 x, u8 y, u8 *str)
{
    while (*str != '\0')
    {
        OLED_DisChar_F6X8(x, y, *str++);
        x += 6;
    }
}
/*显示两位数字,6X8字体,x：0-19，y:0-7*/
void OLED_DisNumber_F6X8(u8 x, u8 y, u8 num)
{
    //调用字符函数显示
    OLED_DisChar_F6X8(x, y, num / 10 + 0x30);
    OLED_DisChar_F6X8(x + 6, y, num % 10 + 0x30);
}

#endif


void Display_LOGO(void)
{
    u8 n;

    OLED_DrawBMP(0, 0, 128, 8, TOSHIBA);    //东芝LOGO全屏显示

    OLED_DisString_F8X16(0, 3, "Starting...");  
    for( n = 5; n > 0; n--)
    {
        OLED_DisNumber_F8X16(12, 3, n);     //启动倒计时
        delay_ms(800);
    }
    OLED_Clear();//清屏
	OLED_DrawBMP(0, 0, 128, 8, TT_M3HQ);    //TT_M3HQ全屏显示
    delay_ms(200);
    OLED_Clear();//清屏
	OLED_DrawBMP(0, 0, 128, 8, THUNDER);    //中科创达LOGO全屏显示
    delay_ms(200);
    OLED_Clear();//清屏
	OLED_DrawBMP(0, 0, 128, 8, MBB);        //面包板社区LOGO全屏显示
    delay_ms(800);
    OLED_Clear();//清屏
	OLED_DrawBMP(0, 0, 128, 2, BAR);	    //上1/4仿手机状态栏显示	
}

//显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～8
void OLED_DrawBMP(u8 x0, u8 y0, u8 x1, u8 y1,const u8 BMPx[])
{
    u16 j = 0;
    u8 x, y;

    if(y1 % 8 == 0) y = y1 / 8;
    else y = y1 / 8 + 1;
    for(y = y0; y < y1; y++)
    {
        OLED_Set_Pos(x0, y);
        for(x = x0; x < x1; x++)
        {
            OLED_WriteData(BMPx[j++]);
        }
    }
}

void OLED_DisTime(u8 hour, u8 min, u8 sec)
{
	OLED_DisNumber_F16X32(0, 32, hour);
	OLED_DisChar_F16X32(32, 32, ':');  //:
	OLED_DisNumber_F16X32(48, 32, min);
	OLED_DisChar_F16X32(80, 32, ':');  //:
	OLED_DisNumber_F16X32(96, 32, sec);	
}


void OLED_DisDate(u8 mon, u8 day, u8 week)
{
	u8 date_tmp[10];
	sprintf((char *)date_tmp, "%d/%d", mon, day);
	OLED_DisString_F8X16(0, 1, "     ");

	OLED_DisString_F8X16(0, 1, date_tmp);
	OLED_DisChinese(96 + 16, 16, week);	//汉字"四"

}
