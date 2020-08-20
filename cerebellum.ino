#include    "typedef.h"

#define         bit_read(portdat, portconf)          ((portdat & portconf) ? 1 : 0)  
#define         bit_write(portdat, portconf, hilo)   (portdat = (hilo ? (portdat | portconf) : (portdat & ~portconf)))  
#define         RCVTIMEOUT      (500)
/*
PIN CONF
*/

#define         PIN_INTR_STR    (0)
#define         PIN_INTR_ESC    (45)

// STR_PCV = PA0
#define         PINDIR_STR      (VPORTA.DIR) 
#define         PINRAM_STR      (VPORTA.IN) 
#define         PIN_STRRSV      (0x01)

// ESC_RCV = PF5
#define         PINDIR_ESC      (VPORTF.DIR) 
#define         PINRAM_ESC      (VPORTF.IN) 
#define         PIN_ESCRSV      (0x20)

// RELAY = PC6
#define         PINDIR_RELAY    (VPORTC.DIR) 
#define         PINRAM_RELAY    (VPORTC.OUT) 
#define         PIN_RELAY       (0x40)

// TESTLED = PE2
#define         PINDIR_TEST     (VPORTE.DIR) 
#define         PINRAM_TEST     (VPORTE.OUT) 
#define         PIN_TEST        (0x04)

// DBGLED0 = PB0
#define         PINDIR_LDB0     (VPORTB.DIR) 
#define         PINRAM_LDB0     (VPORTB.OUT) 
#define         PIN_LDB0        (0x01)
#define         LED0_GRN_ON     (bit_write(PINRAM_LDB0, PIN_LDB0, 0))
#define         LED0_GRN_OFF    (bit_write(PINRAM_LDB0, PIN_LDB0, 1))

// DBGLED1 = PB1
#define         PINDIR_LDB1     (VPORTB.DIR) 
#define         PINRAM_LDB1     (VPORTB.OUT) 
#define         PIN_LDB1        (0x02)
#define         LED1_ORG_ON     (bit_write(PINRAM_LDB1, PIN_LDB1, 0))
#define         LED1_ORG_OFF    (bit_write(PINRAM_LDB1, PIN_LDB1, 1))

volatile u4     u4s_pwStr;
volatile u4     u4s_pwEsc;
volatile u4     u4s_cntRd;
volatile u1     u1s_bit;
volatile u4     u4s_time;
#if 0
void setup()
{
    bit_write(PINDIR_STR,   PIN_STRRSV, 0);
    bit_write(PINDIR_ESC,   PIN_ESCRSV, 0);
    bit_write(PINDIR_TEST,  PIN_TEST,   1);
    bit_write(PINDIR_RELAY, PIN_RELAY,  1);
    bit_write(PINDIR_LDB0,  PIN_LDB0,   1);
    bit_write(PINDIR_LDB1,  PIN_LDB1,   1);

    LED0_GRN_ON;
    LED1_ORG_ON;
    delay(500);
    LED0_GRN_OFF;
    LED1_ORG_OFF;
    delay(500);
    LED0_GRN_ON;
    LED1_ORG_OFF;
    delay(500);
    LED0_GRN_OFF;
    LED1_ORG_ON;
    delay(500);
    LED0_GRN_OFF;
    LED1_ORG_OFF;
    //attachInterrupt(PIN_INTR_STR, vdg_intr_irqStr, RISING);
    //attachInterrupt(PIN_INTR_ESC, vdg_intr_irqEsc, RISING);
    Serial.begin(115200);
}
void loop()
{
    int t1, t2;
    u4 u4t_cnt;
    //t2 = pulseIn(3,HIGH,3000);
    //t1 = pulseIn(2,HIGH,3000);
/*
    u4t_cnt = 0;
    u4s_pwStr = 0;
    u4s_pwEsc = 0; 

    LED0_GRN_ON;
    LED1_ORG_ON;
    noInterrupts();
    while ((bit_read(PINRAM_STR,PIN_STRRSV) ||  bit_read(PINRAM_ESC,PIN_ESCRSV)) && (u4t_cnt < RCVTIMEOUT))
    {
        if (!bit_read(PINRAM_STR,PIN_STRRSV) && u4s_pwStr == 0)
        {
            u4s_pwStr = u4t_cnt;
            LED0_GRN_OFF;
        }
        if (!bit_read(PINRAM_ESC,PIN_ESCRSV) && u4s_pwEsc == 0)
        {
            u4s_pwEsc = u4t_cnt;
            LED1_ORG_OFF;
        }
        u4t_cnt++;
        delayMicroseconds(8);
    }
    interrupts(); */
    u4t_cnt = 0;
    u4s_pwStr = 0;

    LED0_GRN_ON;
    noInterrupts();
    while (bit_read(PINRAM_STR,PIN_STRRSV) && (u4t_cnt < RCVTIMEOUT))
    {
        u4t_cnt++;
        delayMicroseconds(8);
    }
    interrupts();
    u4s_pwStr = u4t_cnt;
    LED0_GRN_OFF;
   /*
    if (t1 != 0)
    {
        u4s_pwStr = t1;
    }
    if (t2 != 0)
    {
        u4s_pwEsc = t2; 
    }
    */
    Serial.print("time =");
    Serial.print(u4s_time);
    Serial.print(",\tcnt = ");
    Serial.print(u4t_cnt);
    Serial.print(",\tStr = ");
    Serial.print(u4s_pwStr);
    Serial.print(",\tESC = ");
    Serial.print(u4s_pwEsc);
    Serial.println();
    u4s_time++;
/*     
    if (bit_read(PINRAM_STR,PIN_STRRSV))
    {
        LED0_GRN_ON;
    }
    else
    {
        LED0_GRN_OFF;
    }
    
     
    if (bit_read(PINRAM_ESC,PIN_ESCRSV))
    {
        LED1_ORG_ON;
    }
    else
    {
        LED1_ORG_OFF;
    }
     */
}
void vdg_intr_irqStr()
{
    u4 cnt = 0;
    u4s_pwStr = 0; 
    LED0_GRN_ON;
    noInterrupts();
    while (cnt < RCVTIMEOUT)
    {
        cnt++;
        delayMicroseconds(8);
        if ( bit_read(PINRAM_STR,PIN_STRRSV) )
        {
            break;
        }
    }
    /*
    while ( (u4s_pwStr == 0) && (cnt < RCVTIMEOUT) )
    {
        if (bit_read(PINRAM_STR,PIN_STRRSV) && u4s_pwStr == 0)
        {
            u4s_pwStr = cnt;
        }
        cnt++;
        delayMicroseconds(8);
    }
    */

    interrupts();
    u4s_pwStr = cnt;
}

void vdg_intr_irqEsc()
{
    u4 cnt;
    u4s_pwEsc = 0; 
    LED1_ORG_ON;
    noInterrupts();
    while ( (u4s_pwEsc == 0) && (cnt < RCVTIMEOUT) )
    {
        if (bit_read(PINRAM_ESC,PIN_ESCRSV) && u4s_pwEsc == 0)
        {
            u4s_pwEsc = cnt;
        }
        cnt++;
        delayMicroseconds(8);
    }
    interrupts();
}
#endif

void setup()
{
    bit_write(PINDIR_STR,   PIN_STRRSV, 0);
    bit_write(PINDIR_ESC,   PIN_ESCRSV, 0);
    bit_write(PINDIR_TEST,  PIN_TEST,   1);
    bit_write(PINDIR_RELAY, PIN_RELAY,  1);
    bit_write(PINDIR_LDB0,  PIN_LDB0,   1);
    bit_write(PINDIR_LDB1,  PIN_LDB1,   1);

    LED0_GRN_ON;
    LED1_ORG_ON;
    delay(500);
    LED0_GRN_OFF;
    LED1_ORG_OFF;
    delay(500);
    LED0_GRN_ON;
    LED1_ORG_OFF;
    delay(500);
    LED0_GRN_OFF;
    LED1_ORG_ON;
    delay(500);
    LED0_GRN_OFF;
    LED1_ORG_OFF;
    //attachInterrupt(PIN_INTR_STR, vdg_intr_irqStr, RISING);
    attachInterrupt(PIN_INTR_ESC, vdg_intr_irqEsc, RISING);
    Serial.begin(115200);
}
void loop() {
    // put your main code here, to run repeatedly:
    Serial.print("time =");
    Serial.print(u4s_time);
    Serial.print(", Str = ");
    Serial.print(u4s_pwStr);
    Serial.print(",\tESC = ");
    Serial.print(u4s_pwEsc);
    Serial.println();
    if (bit_read(PINRAM_STR, PIN_STRRSV))
    {
        bit_write(PINRAM_LDB0, PIN_LDB0, 0);
    }
    else
    {
        bit_write(PINRAM_LDB0, PIN_LDB0, 1);
    }
    
    if (bit_read(PINRAM_ESC, PIN_ESCRSV))
    {
        bit_write(PINRAM_LDB1, PIN_LDB1, 0);
    }
    else
    {
        bit_write(PINRAM_LDB1, PIN_LDB1, 1);
    }
    
   if ((u4s_time % 100) == 0)
    {
        if (u1s_bit)
        {
            u1s_bit = 0;
            //bit_write(PINRAM_TEST, PIN_TEST, 1);
            bit_write(PINRAM_RELAY, PIN_RELAY, 1);
        }
        else
        {
            u1s_bit = 1;
            //bit_write(PINRAM_TEST, PIN_TEST, 0);
            bit_write(PINRAM_RELAY, PIN_RELAY, 0);
        }
    }
    u4s_time++;
    delay(100);
}
void vdg_intr_irqEsc(void)
{
    int cnt = 0;
    
    bit_write(PINRAM_TEST, PIN_TEST, 1);
    u4s_cntRd++;
    if (u4s_cntRd < 5)
    {
        return;
    }
    else
    {
        u4s_cntRd = 0;
    }
    u4s_cntRd = 0;
    
    u4s_pwEsc = 0;
    u4s_pwStr = 0;
    noInterrupts();
    while ( (u4s_pwEsc == 0 || u4s_pwStr == 0) && (cnt < RCVTIMEOUT) )
    {
        if (bit_read(PINRAM_STR,PIN_STRRSV) && u4s_pwStr == 0)
        {
            u4s_pwStr = cnt;
        }
        if (bit_read(PINRAM_ESC,PIN_ESCRSV) && u4s_pwEsc == 0)
        {
            u4s_pwEsc = cnt;
        }
        cnt++;
        delayMicroseconds(8);
    }
    interrupts();
    bit_write(PINRAM_TEST, PIN_TEST, 0);
}