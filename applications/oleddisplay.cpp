/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-04     Administrator       the first version
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <U8g2lib.h>
#include "oleddisplay.h"
#define OLED_I2C_PIN_SCL                    22  // PB6
#define OLED_I2C_PIN_SDA                    23  // PB7

// Check https://github.com/olikraus/u8g2/wiki/u8g2setupcpp for all supported devices
static U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0,\
                                         /* clock=*/ OLED_I2C_PIN_SCL,\
                                         /* data=*/ OLED_I2C_PIN_SDA,\
                                         /* reset=*/ U8X8_PIN_NONE);
                                         // All Boards without Reset of the Display

static void name()
{
    u8g2.begin();
    u8g2.clearBuffer();                         // clear the internal memory
    u8g2.setFont(u8g2_font_helvR24_tf);            // choose a suitable font
    u8g2.drawStr(0, 33, "oo~");   // write something to the internal memory
    u8g2.sendBuffer();                          // transfer internal memory to the display
    //u8g2.setFont(u8g2_font_unifont_t_symbols);
   // u8g2.drawGlyph(112, 56, 0x2603 );
    //u8g2.sendBuffer();
}
MSH_CMD_EXPORT(name,name);

static void chinese()
{
    u8g2.begin();
    u8g2.enableUTF8Print();
    u8g2.clearBuffer();    // clear the internal memory
    u8g2.setFont(u8g2_font_unifont_t_chinese2);
    u8g2.setCursor(0, 40);
    u8g2.print("中文");
    //u8g2.sendBuffer();                          // transfer internal memory to the display
    //u8g2.setFont(u8g2_font_unifont_t_symbols);
   // u8g2.drawGlyph(112, 56, 0x2603 );
    u8g2.sendBuffer();
}
MSH_CMD_EXPORT(chinese,chinese print);

 extern void timeoled(){
    u8g2.begin();
    char mstr[3];
                   char hstr[3];
                   char sstr[3];
   struct tm *p;
   int min = 0, hour = 0,sec=0;
   time_t now;
    while(1){

        now = time(RT_NULL);
        p=gmtime((const time_t*) &now);
        hour = p->tm_hour;
        min = p->tm_min;
        sec=p->tm_sec;
        sprintf(mstr, "%02d", min);
        sprintf(hstr, "%02d", hour);
        sprintf(sstr, "%02d", sec);
        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_5x7_tf);
        u8g2.drawStr(0,10,sstr);
        u8g2.setFont(u8g2_font_helvR24_tf);
        u8g2.drawStr(0,63,hstr);
        u8g2.drawStr(50,63,":");
        u8g2.drawStr(67,63,mstr);
        u8g2.sendBuffer();
        rt_thread_mdelay(1000);


}
}
MSH_CMD_EXPORT(timeoled,time print);
