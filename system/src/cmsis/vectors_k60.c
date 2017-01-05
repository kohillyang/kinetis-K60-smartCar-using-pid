//
// This file is part of the GNU ARM Eclipse Plug-ins distribution.
// Copyright (c) 2014 Liviu Ionescu
//

// ----------------------------------------------------------------------------

#include "cortexm/ExceptionHandlers.h"

// ----------------------------------------------------------------------------

void __attribute__((weak))
Default_Handler(void);

// Forward declaration of the specific IRQ handlers. These are aliased
// to the Default_Handler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions


// ----------------------------------------------------------------------------

extern unsigned int _estack;

typedef void
(* const pHandler)(void);

// ----------------------------------------------------------------------------

// The vector table.
// This relies on the linker script to place at correct location in memory.

#define VECTOR_PADDING  (pHandler)0xffffffff

/* Flash configuration field values below */
/* Please be careful when modifying any of
 * the values below as it can secure the
 * flash (possibly permanently): 0x400-0x409.
 */
#define CONFIG_1                (pHandler)0xffffffff
#define CONFIG_2                (pHandler)0xffffffff
#define CONFIG_3                (pHandler)0xffffffff
#define CONFIG_4                (pHandler)0xfffffffe //b5=1,b4=1,b0=1 div1 fast
//#define CONFIG_4      (pHandler)0xffffdffe //b5=0,b4=1,b0=1 div1 slow works
//#define CONFIG_4      (pHandler)0xffffcefe //b5=0,b4=0,b0=0;div8 slow
//#define CONFIG_4      (pHandler)0xffffeefe //b5=1,b4=0,b0=0 div8 fast
//#define CONFIG_4      (pHandler)0xffffcffe //b5=0,b4=0,b0=1;div4 slow
//#define CONFIG_4      (pHandler)0xffffeffe //b5=1,b4=0,b0=1;div4 fast
//#define CONFIG_4      (pHandler)0xfffffefe //b5=1,b4=1,b0=0;div2 fast
//#define CONFIG_4      (pHandler)0xffffdefe //b5=0,b4=1,b0=0;div2 slow
#define  default_isr Default_Handler
#define VECTOR_016      default_isr     // 0x0000_0040 16     0     DMA              DMA Channel 0 transfer complete
#define VECTOR_017      default_isr     // 0x0000_0044 17     1     DMA              DMA Channel 1 transfer complete
#define VECTOR_018      default_isr     // 0x0000_0048 18     2     DMA              DMA Channel 2 transfer complete
#define VECTOR_019      default_isr     // 0x0000_004C 19     3     DMA              DMA Channel 3 transfer complete
#define VECTOR_020      default_isr     // 0x0000_0050 20     4     DMA              DMA Channel 4 transfer complete
#define VECTOR_021      default_isr     // 0x0000_0054 21     5     DMA              DMA Channel 5 transfer complete
#define VECTOR_022      default_isr     // 0x0000_0058 22     6     DMA              DMA Channel 6 transfer complete
#define VECTOR_023      default_isr     // 0x0000_005C 23     7     DMA              DMA Channel 7 transfer complete
#define VECTOR_024      default_isr     // 0x0000_0060 24     8     DMA              DMA Channel 8 transfer complete
#define VECTOR_025      default_isr     // 0x0000_0064 25     9     DMA              DMA Channel 9 transfer complete
#define VECTOR_026      default_isr     // 0x0000_0068 26    10     DMA              DMA Channel 10 transfer complete
#define VECTOR_027      default_isr     // 0x0000_006C 27    11     DMA              DMA Channel 11 transfer complete
#define VECTOR_028      default_isr     // 0x0000_0070 28    12     DMA              DMA Channel 12 transfer complete
#define VECTOR_029      default_isr     // 0x0000_0074 29    13     DMA              DMA Channel 13 transfer complete
#define VECTOR_030      default_isr     // 0x0000_0078 30    14     DMA              DMA Channel 14 transfer complete
#define VECTOR_031      default_isr     // 0x0000_007C 31    15     DMA              DMA Channel 15 transfer complete
#define VECTOR_032      default_isr     // 0x0000_0080 32    16     DMA              DMA Error Interrupt Channels 0-15
#define VECTOR_033      default_isr     // 0x0000_0084 33    17     MCM              Normal interrupt
#define VECTOR_034      default_isr     // 0x0000_0088 34    18     Flash memory     Command Complete
#define VECTOR_035      default_isr     // 0x0000_008C 35    19     Flash memory     Read Collision
#define VECTOR_036      default_isr     // 0x0000_0090 36    20     Mode Controller  Low Voltage Detect,Low Voltage Warning, Low Leakage Wakeup
#define VECTOR_037      default_isr     // 0x0000_0094 37    21     LLWU
#define VECTOR_038      default_isr     // 0x0000_0098 38    22     WDOG
#define VECTOR_039      default_isr     // 0x0000_009C 39    23		RNGB
#define VECTOR_040      default_isr     // 0x0000_00A0 40    24     I2C0
#define VECTOR_041      default_isr     // 0x0000_00A4 41    25     I2C1
#define VECTOR_042      default_isr     // 0x0000_00A8 42    26     SPI0             Single interrupt vector for all sources
#define VECTOR_043      default_isr     // 0x0000_00AC 43    27     SPI1             Single interrupt vector for all sources
#define VECTOR_044      default_isr     // 0x0000_00B0 44    28     SPI2             Single interrupt vector for all sources
#define VECTOR_045      default_isr     // 0x0000_00B4 45    29     CAN0             OR'ed Message buffer (0-15)
#define VECTOR_046      default_isr     // 0x0000_00B8 46    30     CAN0             Bus Off
#define VECTOR_047      default_isr     // 0x0000_00BC 47    31     CAN0             Error
#define VECTOR_048      default_isr     // 0x0000_00C0 48    32     CAN0             Transmit Warning
#define VECTOR_049      default_isr     // 0x0000_00C4 49    33     CAN0             Receive Warning
#define VECTOR_050      default_isr     // 0x0000_00C8 50    34     CAN0             Wake Up
#define VECTOR_051      default_isr     // 0x0000_00CC 51    35     CAN0             Individual Matching Elements Update (IMEU)
#define VECTOR_052      default_isr     // 0x0000_00D0 52    36     CAN0             Lost receive
#define VECTOR_053      default_isr     // 0x0000_00D4 53    37     CAN1             OR'ed Message buffer (0-15)
#define VECTOR_054      default_isr     // 0x0000_00D8 54    38     CAN1             Bus off
#define VECTOR_055      default_isr     // 0x0000_00DC 55    39     CAN1             Error
#define VECTOR_056      default_isr     // 0x0000_00E0 56    40     CAN1             Transmit Warning
#define VECTOR_057      default_isr     // 0x0000_00E4 57    41     CAN1             Receive Warning
#define VECTOR_058      default_isr     // 0x0000_00E8 58    42     CAN1             Wake Up
#define VECTOR_059      default_isr     // 0x0000_00EC 59    43     CAN1             Individual Matching Elements Update (IMEU)
#define VECTOR_060      default_isr     // 0x0000_00F0 60    44     CAN1             Lost receive
#define VECTOR_061      default_isr     // 0x0000_00F4 61    45     UART0            Single interrupt vector for UART status sources
#define VECTOR_062      default_isr     // 0x0000_00F8 62    46     UART0            Single interrupt vector for UART error sources
#define VECTOR_063      default_isr     // 0x0000_00FC 63    47     UART1            Single interrupt vector for UART status sources
#define VECTOR_064      default_isr     // 0x0000_0100 64    48     UART1            Single interrupt vector for UART error sources
#define VECTOR_065      default_isr     // 0x0000_0104 65    49     UART2            Single interrupt vector for UART status sources
#define VECTOR_066      default_isr     // 0x0000_0108 66    50     UART2            Single interrupt vector for UART error sources
#define VECTOR_067      default_isr     // 0x0000_010C 67    51     UART3            Single interrupt vector for UART status sources
#define VECTOR_068      default_isr     // 0x0000_0110 68    52     UART3            Single interrupt vector for UART error sources
#define VECTOR_069      default_isr     // 0x0000_0114 69    53     UART4            Single interrupt vector for UART status sources
#define VECTOR_070      default_isr     // 0x0000_0118 70    54     UART4            Single interrupt vector for UART error sources
#define VECTOR_071      default_isr     // 0x0000_011C 71    55     UART5            Single interrupt vector for UART status sources
#define VECTOR_072      default_isr     // 0x0000_0120 72    56     UART5            Single interrupt vector for UART error sources
#define VECTOR_073      default_isr     // 0x0000_0124 73    57     ADC0
#define VECTOR_074      default_isr     // 0x0000_0128 74    58     ADC1
#define VECTOR_075      default_isr     // 0x0000_012C 75    59     CMP0             High-speed comparator
#define VECTOR_076      default_isr     // 0x0000_0130 76    60     CMP1
#define VECTOR_077      default_isr     // 0x0000_0134 77    61     CMP2
#define VECTOR_078      default_isr     // 0x0000_0138 78    62     FTM0 			 Single interrupt vector for all sources
#define VECTOR_079      default_isr     // 0x0000_013C 79    63     FTM1 			 Single interrupt vector for all sources
#define VECTOR_080      default_isr     // 0x0000_0140 80    64     FTM2 			 Single interrupt vector for all sources
#define VECTOR_081      default_isr     // 0x0000_0144 81    65     CMT
#define VECTOR_082      default_isr     // 0x0000_0148 82    66     RTC Timer interrupt
#define VECTOR_083      default_isr     // 0x0000_014C 83    67
#define VECTOR_084      default_isr     // 0x0000_0150 84    68     PIT Channel 0
#define VECTOR_085      default_isr     // 0x0000_0154 85    69     PIT Channel 1
#define VECTOR_086      default_isr     // 0x0000_0158 86    70     PIT Channel 2
#define VECTOR_087      default_isr     // 0x0000_015C 87    71     PIT Channel 3
#define VECTOR_088      default_isr     // 0x0000_0160 88    72     PDB
#define VECTOR_089      default_isr     // 0x0000_0164 89    73     USB OTG
#define VECTOR_090      default_isr     // 0x0000_0168 90    74     USB Charger Detect
#define VECTOR_091      default_isr     // 0x0000_016C 91    75		ENET			 IEEE 1588 Timer interrupt
#define VECTOR_092      default_isr     // 0x0000_0170 92    76		ENET			 Transmit interrupt
#define VECTOR_093      default_isr     // 0x0000_0174 93    77		ENET			 Receive interrupt
#define VECTOR_094      default_isr     // 0x0000_0178 94    78		ENET			 Error and miscellaneous interrupt
#define VECTOR_095      default_isr     // 0x0000_017C 95    79     I2S
#define VECTOR_096      default_isr     // 0x0000_0180 96    80     SDHC
#define VECTOR_097      default_isr     // 0x0000_0184 97    81     DAC0
#define VECTOR_098      default_isr     // 0x0000_0188 98    82     DAC1
#define VECTOR_099      default_isr     // 0x0000_018C 99    83     TSI 			 Single interrupt vector for all sources
#define VECTOR_100      default_isr     // 0x0000_0190 100   84     MCG
#define VECTOR_101      default_isr     // 0x0000_0194 101   85     Low Power Timer
#define VECTOR_102      default_isr     // 0x0000_0198 102   86     Segment LCD 	 Single interrupt vector for all sources
#define VECTOR_103      default_isr     // 0x0000_019C 103   87     Port control module Pin Detect (Port A)
#define VECTOR_104      default_isr     // 0x0000_01A0 104   88     Port control module Pin Detect (Port B)
#define VECTOR_105      default_isr     // 0x0000_01A4 105   89     Port control module Pin Detect (Port C)
#define VECTOR_106      default_isr     // 0x0000_01A8 106   90     Port control module Pin Detect (Port D)
#define VECTOR_107      default_isr     // 0x0000_01AC 107   91     Port control module Pin Detect (Port E)
#define VECTOR_108      default_isr     // 0x0000_01B0 108   92
#define VECTOR_109      default_isr     // 0x0000_01B4 109   93
#define VECTOR_110      default_isr     // 0x0000_01B8 110   94
#define VECTOR_111      default_isr     // 0x0000_01BC 111   95
#define VECTOR_112      default_isr     // 0x0000_01C0 112   96
#define VECTOR_113      default_isr     // 0x0000_01C4 113   97
#define VECTOR_114      default_isr     // 0x0000_01C8 114   98
#define VECTOR_115      default_isr     // 0x0000_01CC 115   99
#define VECTOR_116      default_isr     // 0x0000_01D0 116   100
#define VECTOR_117      default_isr     // 0x0000_01D4 117   101
#define VECTOR_118      default_isr     // 0x0000_01D8 118   102
#define VECTOR_119      default_isr     // 0x0000_01DC 119   103
#define VECTOR_120      default_isr     //
#define VECTOR_121      default_isr     //
#define VECTOR_122      default_isr     //
#define VECTOR_123      default_isr     //
#define VECTOR_124      default_isr     //
#define VECTOR_125      default_isr     //
#define VECTOR_126      default_isr     //
#define VECTOR_127      default_isr     //
#define VECTOR_128      default_isr     //
#define VECTOR_129      default_isr     //
#define VECTOR_130      default_isr     //
#define VECTOR_131      default_isr     //
#define VECTOR_132      default_isr     //
#define VECTOR_133      default_isr     //
#define VECTOR_134      default_isr     //
#define VECTOR_135      default_isr     //
#define VECTOR_136      default_isr     //
#define VECTOR_137      default_isr     //
#define VECTOR_138      default_isr     //
#define VECTOR_139      default_isr     //
#define VECTOR_140      default_isr     //
#define VECTOR_141      default_isr     //
#define VECTOR_142      default_isr     //
#define VECTOR_143      default_isr     //
#define VECTOR_144      default_isr     //
#define VECTOR_145      default_isr     //
#define VECTOR_146      default_isr     //
#define VECTOR_147      default_isr     //
#define VECTOR_148      default_isr     //
#define VECTOR_149      default_isr     //
#define VECTOR_150      default_isr     //
#define VECTOR_151      default_isr     //
#define VECTOR_152      default_isr     //
#define VECTOR_153      default_isr     //
#define VECTOR_154      default_isr     //
#define VECTOR_155      default_isr     //
#define VECTOR_156      default_isr     //
#define VECTOR_157      default_isr     //
#define VECTOR_158      default_isr     //
#define VECTOR_159      default_isr     //
#define VECTOR_160      default_isr     //
#define VECTOR_161      default_isr     //
#define VECTOR_162      default_isr     //
#define VECTOR_163      default_isr     //
#define VECTOR_164      default_isr     //
#define VECTOR_165      default_isr     //
#define VECTOR_166      default_isr     //
#define VECTOR_167      default_isr     //
#define VECTOR_168      default_isr     //
#define VECTOR_169      default_isr     //
#define VECTOR_170      default_isr     //
#define VECTOR_171      default_isr     //
#define VECTOR_172      default_isr     //
#define VECTOR_173      default_isr     //
#define VECTOR_174      default_isr     //
#define VECTOR_175      default_isr     //
#define VECTOR_176      default_isr     //
#define VECTOR_177      default_isr     //
#define VECTOR_178      default_isr     //
#define VECTOR_179      default_isr     //
#define VECTOR_180      default_isr     //
#define VECTOR_181      default_isr     //
#define VECTOR_182      default_isr     //
#define VECTOR_183      default_isr     //
#define VECTOR_184      default_isr     //
#define VECTOR_185      default_isr     //
#define VECTOR_186      default_isr     //
#define VECTOR_187      default_isr     //
#define VECTOR_188      default_isr     //
#define VECTOR_189      default_isr     //
#define VECTOR_190      default_isr     //
#define VECTOR_191      default_isr     //
#define VECTOR_192      default_isr     //
#define VECTOR_193      default_isr     //
#define VECTOR_194      default_isr     //
#define VECTOR_195      default_isr     //
#define VECTOR_196      default_isr     //
#define VECTOR_197      default_isr     //
#define VECTOR_198      default_isr     //
#define VECTOR_199      default_isr     //
#define VECTOR_200      default_isr     //
#define VECTOR_201      default_isr     //
#define VECTOR_202      default_isr     //
#define VECTOR_203      default_isr     //
#define VECTOR_204      default_isr     //
#define VECTOR_205      default_isr     //
#define VECTOR_206      default_isr     //
#define VECTOR_207      default_isr     //
#define VECTOR_208      default_isr     //
#define VECTOR_209      default_isr     //
#define VECTOR_210      default_isr     //
#define VECTOR_211      default_isr     //
#define VECTOR_212      default_isr     //
#define VECTOR_213      default_isr     //
#define VECTOR_214      default_isr     //
#define VECTOR_215      default_isr     //
#define VECTOR_216      default_isr     //
#define VECTOR_217      default_isr     //
#define VECTOR_218      default_isr     //
#define VECTOR_219      default_isr     //
#define VECTOR_220      default_isr     //
#define VECTOR_221      default_isr     //
#define VECTOR_222      default_isr     //
#define VECTOR_223      default_isr     //
#define VECTOR_224      default_isr     //
#define VECTOR_225      default_isr     //
#define VECTOR_226      default_isr     //
#define VECTOR_227      default_isr     //
#define VECTOR_228      default_isr     //
#define VECTOR_229      default_isr     //
#define VECTOR_230      default_isr     //
#define VECTOR_231      default_isr     //
#define VECTOR_232      default_isr     //
#define VECTOR_233      default_isr     //
#define VECTOR_234      default_isr     //
#define VECTOR_235      default_isr     //
#define VECTOR_236      default_isr     //
#define VECTOR_237      default_isr     //
#define VECTOR_238      default_isr     //
#define VECTOR_239      default_isr     //
#define VECTOR_240      default_isr     //
#define VECTOR_241      default_isr     //
#define VECTOR_242      default_isr     //
#define VECTOR_243      default_isr     //
#define VECTOR_244      default_isr     //
#define VECTOR_245      default_isr     //
#define VECTOR_246      default_isr     //
#define VECTOR_247      default_isr     //
#define VECTOR_248      default_isr     //
#define VECTOR_249      default_isr     //
#define VECTOR_250      default_isr     //
#define VECTOR_251      default_isr     //
#define VECTOR_252      default_isr     //
#define VECTOR_253      default_isr     //
#define VECTOR_254      default_isr     //
#define VECTOR_255      default_isr     //



#undef  VECTOR_003
#define VECTOR_003    HardFault_Handler   //发生硬件上访 （就是程序跑飞了）     推荐调试程序时，用个LED显示来指示程序跑飞了

extern void PendSV_Handler(void);         //可悬起的系统调用中断服务函数
extern void HardFault_Handler(void);      //发生硬件上访（程序跑飞）
extern void SysTick_Handler(void);        //滴答时钟(os 用到)


extern void PendSV_Handler(void);         //可悬起的系统调用中断服务函数
extern void HardFault_Handler(void);      //发生硬件上访（程序跑飞）
extern void SysTick_Handler(void);        //滴答时钟(os 用到)
extern void USART1_IRQHandler();          //串口1 中断接收函数
extern void PIT0_IRQHandler();            //PIT0 定时中断服务函数
extern void PIT1_IRQHandler();            //PIT1 定时中断服务函数
extern void PIT2_IRQHandler();            //PIT2 定时中断服务函数
extern void PORTD_IRQHandler();           //PORTD中断服务函数
extern void PORTB_IRQHandler();           //PORTB中断服务函数
extern void FTM0_IRQHandler();            //FTM0输入捕捉中断
extern void FTM1_IRQHandler();            //FTM0输入捕捉中断
extern void LPT_Handler(void);           //LPT脉冲中断
extern void DMA_CH0_Handler(void);
extern void DMA_CH4_Handler(void);              //DMA通道4的中断服务函数
extern void DMA_CH0_Handler();
extern void PORTD_IRQHandler();
extern void UART1_IRQHandler();



#undef  VECTOR_016
#define VECTOR_016    DMA_CH0_Handler     //DMA中断


#undef  VECTOR_063
#define VECTOR_063    UART1_IRQHandler      //UART1中断，接收字符


//#undef  VECTOR_078
//#define VECTOR_078    FTM0_IRQHandler     //FTM0输入捕捉中断

#undef  VECTOR_079
#define VECTOR_079    FTM1_IRQHandler     //FTM0输入捕捉中断

#undef  VECTOR_084
#define VECTOR_084    PIT0_IRQHandler     //重新定义84号中断为PIT0_IRQHandler中断

//#undef  VECTOR_085
//#define VECTOR_085    PIT1_IRQHandler     //重新定义85号中断为PIT1_IRQHandler中断
//
//#undef  VECTOR_086
//#define VECTOR_086    PIT2_IRQHandler     //重新定义86号中断为PIT2_IRQHandler中断

#undef  VECTOR_101
#define VECTOR_101    LPT_Handler        //LPT中断

//#undef  VECTOR_104
//#define VECTOR_104    PORTB_IRQHandler    //PORTB中断

#undef  VECTOR_106
#define VECTOR_106    PORTD_IRQHandler    //PORTD中断:行中断、场中断



__attribute__ ((section(".isr_vector"),used))
pHandler gHandlers[] =
  {
  // Core Level - CM0
      (pHandler) &_estack, // The initial stack pointer 							//0
      Reset_Handler, // The reset handler											//1
      NMI_Handler, // The NMI handler												//2
      HardFault_Handler, // The hard fault handler									//3
      MemManage_Handler,                        // The MPU fault handler			//4
      BusFault_Handler,                        // The bus fault handler				//5
      UsageFault_Handler,                        // The usage fault handler			//6
      0,                                        // Reserved							//7
      0,                                        // Reserved							//8
      0,                                        // Reserved							//9
      0,                                        // Reserved							//10
      SVC_Handler,                              // SVCall handler					//11
      DebugMon_Handler,                         // Debug monitor handler			//12
      0,                                        // Reserved 						//13
      PendSV_Handler, // The PendSV handler											//14
      SysTick_Handler, // The SysTick handler										//15
      // ----------------------------------------------------------------------
      // Chip Level - K60
	    VECTOR_016,
	    VECTOR_017,
	    VECTOR_018,
	    VECTOR_019,
	    VECTOR_020,
	    VECTOR_021,
	    VECTOR_022,
	    VECTOR_023,
	    VECTOR_024,
	    VECTOR_025,
	    VECTOR_026,
	    VECTOR_027,
	    VECTOR_028,
	    VECTOR_029,
	    VECTOR_030,
	    VECTOR_031,
	    VECTOR_032,
	    VECTOR_033,
	    VECTOR_034,
	    VECTOR_035,
	    VECTOR_036,
	    VECTOR_037,
	    VECTOR_038,
	    VECTOR_039,
	    VECTOR_040,
	    VECTOR_041,
	    VECTOR_042,
	    VECTOR_043,
	    VECTOR_044,
	    VECTOR_045,
	    VECTOR_046,
	    VECTOR_047,
	    VECTOR_048,
	    VECTOR_049,
	    VECTOR_050,
	    VECTOR_051,
	    VECTOR_052,
	    VECTOR_053,
	    VECTOR_054,
	    VECTOR_055,
	    VECTOR_056,
	    VECTOR_057,
	    VECTOR_058,
	    VECTOR_059,
	    VECTOR_060,
	    VECTOR_061,
	    VECTOR_062,
	    VECTOR_063,
	    VECTOR_064,
	    VECTOR_065,
	    VECTOR_066,
	    VECTOR_067,
	    VECTOR_068,
	    VECTOR_069,
	    VECTOR_070,
	    VECTOR_071,
	    VECTOR_072,
	    VECTOR_073,
	    VECTOR_074,
	    VECTOR_075,
	    VECTOR_076,
	    VECTOR_077,
	    VECTOR_078,
	    VECTOR_079,
	    VECTOR_080,
	    VECTOR_081,
	    VECTOR_082,
	    VECTOR_083,
	    VECTOR_084,
	    VECTOR_085,
	    VECTOR_086,
	    VECTOR_087,
	    VECTOR_088,
	    VECTOR_089,
	    VECTOR_090,
	    VECTOR_091,
	    VECTOR_092,
	    VECTOR_093,
	    VECTOR_094,
	    VECTOR_095,
	    VECTOR_096,
	    VECTOR_097,
	    VECTOR_098,
	    VECTOR_099,
	    VECTOR_100,
	    VECTOR_101,
	    VECTOR_102,
	    VECTOR_103,
	    VECTOR_104,
	    VECTOR_105,
	    VECTOR_106,
	    VECTOR_107,
	    VECTOR_108,
	    VECTOR_109,
	    VECTOR_110,
	    VECTOR_111,
	    VECTOR_112,
	    VECTOR_113,
	    VECTOR_114,
	    VECTOR_115,
	    VECTOR_116,
	    VECTOR_117,
	    VECTOR_118,
	    VECTOR_119,
	    VECTOR_120,
	    VECTOR_121,
	    VECTOR_122,
	    VECTOR_123,
	    VECTOR_124,
	    VECTOR_125,
	    VECTOR_126,
	    VECTOR_127,
	    VECTOR_128,
	    VECTOR_129,
	    VECTOR_130,
	    VECTOR_131,
	    VECTOR_132,
	    VECTOR_133,
	    VECTOR_134,
	    VECTOR_135,
	    VECTOR_136,
	    VECTOR_137,
	    VECTOR_138,
	    VECTOR_139,
	    VECTOR_140,
	    VECTOR_141,
	    VECTOR_142,
	    VECTOR_143,
	    VECTOR_144,
	    VECTOR_145,
	    VECTOR_146,
	    VECTOR_147,
	    VECTOR_148,
	    VECTOR_149,
	    VECTOR_150,
	    VECTOR_151,
	    VECTOR_152,
	    VECTOR_153,
	    VECTOR_154,
	    VECTOR_155,
	    VECTOR_156,
	    VECTOR_157,
	    VECTOR_158,
	    VECTOR_159,
	    VECTOR_160,
	    VECTOR_161,
	    VECTOR_162,
	    VECTOR_163,
	    VECTOR_164,
	    VECTOR_165,
	    VECTOR_166,
	    VECTOR_167,
	    VECTOR_168,
	    VECTOR_169,
	    VECTOR_170,
	    VECTOR_171,
	    VECTOR_172,
	    VECTOR_173,
	    VECTOR_174,
	    VECTOR_175,
	    VECTOR_176,
	    VECTOR_177,
	    VECTOR_178,
	    VECTOR_179,
	    VECTOR_180,
	    VECTOR_181,
	    VECTOR_182,
	    VECTOR_183,
	    VECTOR_184,
	    VECTOR_185,
	    VECTOR_186,
	    VECTOR_187,
	    VECTOR_188,
	    VECTOR_189,
	    VECTOR_190,
	    VECTOR_191,
	    VECTOR_192,
	    VECTOR_193,
	    VECTOR_194,
	    VECTOR_195,
	    VECTOR_196,
	    VECTOR_197,
	    VECTOR_198,
	    VECTOR_199,
	    VECTOR_200,
	    VECTOR_201,
	    VECTOR_202,
	    VECTOR_203,
	    VECTOR_204,
	    VECTOR_205,
	    VECTOR_206,
	    VECTOR_207,
	    VECTOR_208,
	    VECTOR_209,
	    VECTOR_210,
	    VECTOR_211,
	    VECTOR_212,
	    VECTOR_213,
	    VECTOR_214,
	    VECTOR_215,
	    VECTOR_216,
	    VECTOR_217,
	    VECTOR_218,
	    VECTOR_219,
	    VECTOR_220,
	    VECTOR_221,
	    VECTOR_222,
	    VECTOR_223,
	    VECTOR_224,
	    VECTOR_225,
	    VECTOR_226,
	    VECTOR_227,
	    VECTOR_228,
	    VECTOR_229,
	    VECTOR_230,
	    VECTOR_231,
	    VECTOR_232,
	    VECTOR_233,
	    VECTOR_234,
	    VECTOR_235,
	    VECTOR_236,
	    VECTOR_237,
	    VECTOR_238,
	    VECTOR_239,
	    VECTOR_240,
	    VECTOR_241,
	    VECTOR_242,
	    VECTOR_243,
	    VECTOR_244,
	    VECTOR_245,
	    VECTOR_246,
	    VECTOR_247,
	    VECTOR_248,
	    VECTOR_249,
	    VECTOR_250,
	    VECTOR_251,
	    VECTOR_252,
	    VECTOR_253,
	    VECTOR_254,
	    VECTOR_255,
	    CONFIG_1,        /* Flash configuration field values */
	    CONFIG_2,        /* Flash configuration field values */
	    CONFIG_3,        /* Flash configuration field values */
	    CONFIG_4,        /* Flash configuration field values */
    };

__attribute__ ((section(".cfmconfig")))
pHandler gConfigs[] =
  {
  CONFIG_1,
  CONFIG_2,
  CONFIG_3,
  CONFIG_4 //
    };

// ----------------------------------------------------------------------------

// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.

void __attribute__ ((section(".after_vectors")))
Default_Handler(void)
{
#if defined(DEBUG)
  __DEBUG_BKPT();
#endif
  while (1)
    {
    }
}

// ----------------------------------------------------------------------------
