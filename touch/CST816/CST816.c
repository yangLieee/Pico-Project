#include <stdio.h>
#include <stdlib.h>
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "CST816.h" 
#include "touch_interface.h"
 
#define TOUCH_OFFSET_Y 15
#define REVERSE 0

static touch_info_t info;

/*
*********************************************************************************************************
*	函 数 名: CST816_IIC_ReadREG
*	功能说明: 读取触摸屏单个寄存器的数据
*	形    参：reg：  寄存器地址
*	          value: 存储数据的指针
*	          len:   读取数据的长度
*	返 回 值: 返回寄存器存储的数据
*********************************************************************************************************
*/
static inline void CST816_IIC_ReadREG(uint8_t addr, uint8_t* value, int len)
{
    i2c_write_blocking(TOUCH_IIC_PORT, Device_Addr, &addr, 1, true); // true to keep master control of bus
    i2c_read_blocking(TOUCH_IIC_PORT, Device_Addr, value, len, false);
}

/*
*********************************************************************************************************
*	函 数 名: CST816_IIC_WriteREG
*	功能说明: 向触摸屏的寄存器写入数据
*	形    参：addr： 寄存器地址
*	          value: 写入的数据
*	返 回 值: 返回寄存器存储的数据
*********************************************************************************************************
*/
static inline void CST816_IIC_WriteREG_oneByte(uint8_t addr, uint8_t value)
{
    uint8_t buf[2] = {addr, value};
    i2c_write_blocking (TOUCH_IIC_PORT, Device_Addr, buf, 2, false);
}


/*
*********************************************************************************************************
*	函 数 名: gpio_callback
*	功能说明: 触摸中断
*	形    参：gpio:   触发中断的GPIO
*             events: 哪一种事件触发的中断 
*	返 回 值: none
*********************************************************************************************************
*/
static touch_irq_cb touch_irq_default_cb = NULL;
static void gpio_callback(uint gpio, uint32_t events) {
    touch_get_xy_axis(&info.x_pos, &info.y_pos);
    CST816_IIC_ReadREG(GestureID, &info.event, 1);
    if(touch_irq_default_cb != NULL) {
        touch_irq_default_cb(&info);
    }
}

/*
*********************************************************************************************************
*	函 数 名: CST816_GPIO_Init
*	功能说明: CST816 GPIO口初始化
*	形    参：none
*	返 回 值: none
*********************************************************************************************************
*/
static inline void CST816_GPIO_Init(void)
{	
    i2c_init(TOUCH_IIC_PORT, TOUCH_IIC_BAUDRATE);

    /* Init IIC */
    gpio_set_function(TOUCH_IIC_SDA, GPIO_FUNC_I2C);
    gpio_set_function(TOUCH_IIC_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(TOUCH_IIC_SDA);
    gpio_pull_up(TOUCH_IIC_SCL);

    /* Init RST INT */
    gpio_init(TOUCH_RST_PIN);
    gpio_init(TOUCH_INT_PIN);
    gpio_set_dir(TOUCH_RST_PIN, true);
    gpio_set_dir(TOUCH_INT_PIN, false);
    gpio_set_irq_enabled_with_callback(TOUCH_INT_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
}
 
/*
*********************************************************************************************************
*	函 数 名: TOUCH_RESET
*	功能说明: 触摸屏复位
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static inline void CST816_RESET(void)
{
    gpio_put(TOUCH_RST_PIN, 0);
    sleep_ms(10);
    gpio_put(TOUCH_RST_PIN, 1);
    sleep_ms(100);
}


/*
*********************************************************************************************************
*	函 数 名: CST816_Get_FingerNum
*	功能说明: 读取触摸屏的手指触摸个数,0xFF为睡眠
*	形    参：无
*	返 回 值: 返回芯片ID
*********************************************************************************************************
*/
uint8_t CST816_Get_FingerNum(void)
{
    uint8_t num = 0;
    CST816_IIC_ReadREG(FingerNum, &num, 1);
	return num;
}
 
/*
*********************************************************************************************************
*	函 数 名: CST816_Config_MotionMask
*	功能说明: 使能连续动作（连续左右滑动，连续上下滑动，双击）
*	形    参：mode：模式(5种)
*	返 回 值: 无
*	注    意：使能连续动作会增加响应时间
*********************************************************************************************************
*/
void CST816_Config_MotionMask(uint8_t mode)
{
	CST816_IIC_WriteREG_oneByte(MotionMask, mode);
}
 
/*
*********************************************************************************************************
*	函 数 名: CST816_Config_AutoSleepTime
*	功能说明: 规定time内无触摸，自动进入低功耗模式
*	形    参：time：时间(s)
*	返 回 值: 无
*********************************************************************************************************
*/
void CST816_Config_AutoSleepTime(uint8_t time)
{
	CST816_IIC_WriteREG_oneByte(AutoSleepTime, time);
}
 
/*
*********************************************************************************************************
*	函 数 名: CST816_Sleep
*	功能说明: 进入睡眠，无触摸唤醒功能
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void CST816_Sleep(void)
{
	CST816_IIC_WriteREG_oneByte(SleepMode, 0x03);
}
 
/*
*********************************************************************************************************
*	函 数 名: CST816_Wakeup
*	功能说明: 唤醒
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void CST816_Wakeup(void)
{
	CST816_RESET();
}
 
/*
*********************************************************************************************************
*	函 数 名: CST816_Config_MotionSlAngle
*	功能说明: 手势检测滑动分区角度控制。Angle=tan(c)*10 c为以x轴正方向为基准的角度。
*	形    参：x_right_y_up_angle：角度值
*	返 回 值: 无
*********************************************************************************************************
*/
void CST816_Config_MotionSlAngle(uint8_t x_right_y_up_angle)
{
	CST816_IIC_WriteREG_oneByte(MotionSlAngle, x_right_y_up_angle);
}
 
/*
*********************************************************************************************************
*	函 数 名: CST816_Config_NorScanPer
*	功能说明: 正常快速检测周期配置函数。
*						此值会影响到LpAutoWakeTime和AutoSleepTime。 
*						单位10ms，可选值：1～30。默认值为1。
*	形    参：Period：周期值
*	返 回 值: 无
*********************************************************************************************************
*/
void CST816_Config_NorScanPer(uint8_t Period)
{
	if(Period >= 30)
		Period = 30;
	CST816_IIC_WriteREG_oneByte(NorScanPer, Period);
}
 
/*
*********************************************************************************************************
*	函 数 名: CST816_Config_IrqPluseWidth
*	功能说明: 中断低脉冲输出宽度配置函数
*	形    参：Period：周期值
*	返 回 值: 无
*********************************************************************************************************
*/
void CST816_Config_IrqPluseWidth(uint8_t Width)
{
	if(Width >= 200)
		Width = 200;
	CST816_IIC_WriteREG_oneByte(IrqPluseWidth, Width);
}
 
/*
*********************************************************************************************************
*	函 数 名: CST816_Config_NorScanPer
*	功能说明: 低功耗扫描唤醒门限配置函数。越小越灵敏。默认值48
*	形    参：TH：门限值
*	返 回 值: 无
*********************************************************************************************************
*/
void CST816_Config_LpScanTH(uint8_t TH)
{
	CST816_IIC_WriteREG_oneByte(LpScanTH, TH);
}




/*
 * API
 */
void touch_init(void)
{
    uint8_t id = 0;
	CST816_GPIO_Init();
    CST816_RESET();
	CST816_IIC_ReadREG(ChipID, &id, 1);
	CST816_Config_AutoSleepTime(5);
    printf("CST816 TOUCH Init Ok CHIPID[0x%x] \n", id);
}

void touch_set_irq_callback(touch_irq_cb cb)
{
    if(cb != NULL) {
        touch_irq_default_cb = cb;
    }
}

void touch_get_xy_axis(uint16_t* x_pos, uint16_t* y_pos)
{
	uint8_t DAT[4];
    CST816_IIC_ReadREG(XposH, DAT, 4);
	*x_pos=((DAT[0]&0x0F)<<8)|DAT[1];                      //(temp[0]&0X0F)<<4|
	*y_pos=(((DAT[2]&0x0F)<<8)|DAT[3]) + TOUCH_OFFSET_Y;   //(temp[2]&0X0F)<<4|
	#if REVERSE
		*x_pos = 239 - CST816_Instance.X_Pos;
		*y_pos = 279 - CST816_Instance.Y_Pos;
	#endif
}

