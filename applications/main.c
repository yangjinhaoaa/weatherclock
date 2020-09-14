/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-04     RT-Thread    first version
 */

#include <rtthread.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#include <arpa/inet.h>         /* 包含 ip_addr_t 等地址相关的头文件 */
#include <netdev.h>            /* 包含全部的 netdev 相关操作接口函数 */
#include <ntp.h>
#include "oleddisplay.h"

extern void timeoled();
int main(void)
{
    //time_t ntp_sync_to_rtc(void);
    int count = 1;

    //获取网卡对象
    struct netdev* net = netdev_get_by_name("esp0");

    //阻塞判断当前网络是否正常连接
    while(netdev_is_internet_up(net) != 1)
    {
       rt_thread_mdelay(200);
    }
    //提示当前网络已就绪
    rt_kprintf("network is ok!\n");

    //NTP自动对时
    time_t cur_time;
    time_t now;
    cur_time = ntp_sync_to_rtc(NULL);
    if (cur_time)
    {
        rt_kprintf("Cur Time: %s", ctime((const time_t*) &cur_time));
    }
    else
    {
        rt_kprintf("NTP sync fail.\n");
    }
   now = time(RT_NULL);
    rt_kprintf("time is %s\n", ctime(&now));
    while (1)
    {
        //LOG_D("Hello RT-Thread!");
        timeoled();
        rt_thread_mdelay(1000);

  }

    return RT_EOK;
}
