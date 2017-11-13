### UGL 使用说明 (v0.8.7 alpha)

#### 概述(2017.10.01)
1. 这个软件/硬件支持包写于STM32F407平台，理论上支持STM32全系列的通用功能，以源码包形式发布
2. 此源码包基于HAL的初始化，若要使用它，请首先使用STM32CubeMX初始化相应外设
3. 此源码包的设计参考了STM32 HAL库，是一个可裁剪，可修改的自由软件，但同样受到HAL库的影响，该源码包有些不尽人意的缺陷，例如，SPI无法发送16位二进制数据  
4. ~~此源码包混合了HAL、寄存器和汇编编程，注意，汇编部分，即ugl_iar.h/c、ugl_mdk.h/.c和ugl_gcc.h/.c是否支持STM32F407以外的芯片并未验证，若使用中出现问题则概不负责~~  
5. 此源码包区分文件重要性，依据重要性不同分为三级，其中以第一级为最重要

#### 使用说明(2017.10.03)
1. 源码包文件组织结构  

        User-defined General Library
                  |  
                  +-- inc  
                  |------\ ugl.h    
                  |------\ ugl_conf.h  
                  |------\ ugl_modulexx.h   
                  +-- src  
                  |------\ ugl.c    
                  |------\ ugl_modulexx.c   
                  +- \ includes.h  
    > 其中__modulexx__是具体的模块名称，例如ugl_gpio.h/.c  

2. 若要使用此源码包，首先要在STM32CubeMX中进行初始化

3. 初始化代码生成后，将此源码包根目录和inc目录添加为头文件的包含目录，将使用到的源文件添加至IDE，未使用到的可以不添加或者直接删除

4. 文件分级  

    a. 一级文件仅有两个，分别为ugl.h/ugl_conf.h，无论使用何种模块，这两个文件是必不可少的  

        1) ugl.h -- 包含了位带操作定义和stm32f4xx_hal_conf.h和ugl_conf.h，前者是STM32F4系列HAL库的模块启用声明，后者是此源码包的模块启用声明  
        2) ugl_conf.h -- 源码包的模块启用声明，主要针对软件模块，例如FatFS和User Malloc，以及通过串口向上位机打印调试信息的启用声明
    b. 二级文件仅有一个，为ugl.c，该文件是ugl.h中声明的通用函数的定义，若不使用通用函数，可不包含或  		者删除此文件

    c. 三级文件为各模块的头文件与源文件，例如ugl_gpio.h/.c，详细内容见文件内

    d. includes.h文件不属于以上分类，它是一个为方便主函数调用的头文件，包含了源码包内所有的头文件，只应该在主函数内包含这个头文件或者不使用它，个人并不特别推荐使用该文件

    e. 若不使用includes.h文件，则应在主函数中依次包含所用到的头文件，并在对应模块中按照以下示例使用

    ```C++
    /**
     * User_modulexx.h(such as STM32F407ZG)
    **/

    #ifndef __User_Modulexx
    #define __User_Modulexx

    #include "ugl.h"
    #include "ugl_modulexx.h"		//Module functions in ugl
    #include "ugl_modulexx2.h"		//Another Module but will be used in this file

    //define User's definations
    #define ...

    //User functions
    void User_Modulexx_Init(void);
    ...

    #endif /*__User_Modulexx*/

    ```

5. 移植

    该源码包应该是便于移植的，以下示例是ugl.h的部分源码

    ```C++
    #include "stm32f4xx_hal.h"
    #include "stm32f4xx_hal_conf.h"
    #include "main.h"
    #include "stdlib.h"
    #include "ugl_conf.h"

    ...
    ```

    仅需更改开始的两个有关HAL库的头文件包含即可，但是这并不代表此源码包内所有内容对任意一款芯片都适用，例如，STM32L452RE和STM32F407ZG同属Cortex-M4F架构，但是STM32L452拥有QSPI接口，而STM32F407却不包含此接口，即无论如何移植，此源码包都不支持硬件原本没有的功能，因为此源码包是基于HAL库的硬件初始化代码之上的

6.  ~~针对不同编译器的处理~~

    ~~一般认为ARM平台主要是有三个常用的编译器，分别为GCC for ARM、ARMCC和IARCC，后两者对应专有的IDE：Keil-MDK和IAR for ARM，由于编译器宏实现不同，所以涉及到可能要跨接不同编译器的问题时，应当针对性处理，但是为了减小编写工作量，仅针对汇编函数做了分文件编写，而User_Malloc部分则依据编译器不同而做条件编译，事实上，你会发现在此源码包中条件编译十分常见，这主要是为了保证代码的可裁剪性~~

#### 移植说明(2017.10.04) 

虽然理论上支持STM32全系列的通用功能，但是在使用时依然要做一些小小的改动，具体示例如下：

1. 修改ugl.h中的头文件包含，见上文移植一节

2. 关于ugl_uart.h/.c的移植，在STM32F407xx平台默认使用USART1完成对标准输出函数的重定向，该节代码如下

   ```C++
   /* Retarget C Library */
   #if (__Usr_UART_Debug == 1)

   #ifdef __GNUC__
   /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printfset to 'Yes') calls __io_putchar() */
   #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
   #else
   #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
   #endif /*__GNUC__*/

   /**
    * @brief   Retargets the C library printf function to the USART.
    * @param   Not Care
    * @return  None
    * @note    Only for USART1(in Asynchronous mode)
   **/
   PUTCHAR_PROTOTYPE
   {
   	while((USART1->SR & 0X40) == 0)
   		;
   	USART1->DR = (uint8_t)ch;
   	return ch;
   }

   #endif /*__Usr_UART_Debug == 1*/
   ```

   此处仅需更改函数定义中的USART1为用户自定义的UART/USART即可，如不使用则可忽略

3.  针对不同平台的数学库，此节在ugl_conf.h中定义，对应的源码如下

    ```C++
    /* ugl.h */
    #include "stm32f4xx_hal.h"
    #include "stm32f4xx_hal_conf.h"
    #include "main.h"
    #include "stdlib.h"
    #include "ugl_conf.h"

    //ARM Math Library
    #if defined(ARM_MATH_CM0) || defined(ARM_MATH_CM0PLUS) || defined(ARM_MATH_CM3) || defined(ARM_MATH_CM4) || defined(ARM_MATH_CM7)

    #include "arm_math.h"

    #endif /*ARM_MATH_CMx*/
    ```

    由此可以看到，对于Cortex-M系列，只需在程序预处理器(Preprocesser)中添加对应的`ARM_MATH_CMx`即可使用相应的数学库，同时只能存在一个宏

4. 关于ugl_malloc.h/.c，暂不支持除STM32F407以外的型号

5. LuaJIT的运行，需要设置堆栈，将在试验后得出需要堆栈的最小值，在STM32CubeMX中可以预定义堆栈大小

#### 其他说明(2017.10.07)

?	鉴于该源码包可能会加入一些偏门左道的方法，比如正在进行实验的LuaJIT，所以增加这一个其他说明部分

#### 更新说明(2017.10.01)

*所有的函数均整理自个人之前编写STM32的实验/项目代码，文件中标注日期在2017.10.02之前的仅为整理日期而非编写日期*

version 0.0.9（2017.08.26）

1.  完成ugl.h/.c中`UGL_Delay_us()`和`UGL_Float2String()`函数，参考[正点原子](http://www.openedv.com/)加入了位带操作宏定义
2.  添加ugl_gpio.h/.c

version 0.1.5（2017.09.02）

1.  添加ugl_spi.h/.c，完成SPI轮询模式的封装（仅能收发八位数据，仅限一个字节），支持动态设置SPI的波特率

version 0.2.0（2017.09.06）

1.  修复ugl_spi.h/.c中动态设置波特率的bug，解决波特率设置失效的问题
2.  添加ugl_rcc.h/.c，在外部使用`extern`关键字声明和定义了时钟安全系统中断回调，以寄存器方式实现，支持外部时钟HSE/LSI失效时，切换到内部时钟HSI/LSI（30MHz/默认频率）

version 0.2.6（2017.09.16）

1.  由于各型号芯片的HSI不同且无法较好的支持MSI时钟，此函数无法达到预期要求，因此暂时移除ugl_rcc.h/.c
2.  添加了IT模式下SPI的读写函数

version 0.3.0（2017.09.24）

1.  添加了includes.h头文件，对主函数提供一个统一的接口
2.  ~~添加了ugl_iar.h/.c文件，支持部分汇编指令（待验证）~~

version 0.3.1（2017.09.26）

1. 添加了DMA模式下SPI的读写函数
2. ~~开始整理ugl_mdk.h/.c和ugl_gcc.h/.c，完成时间未定~~

version 0.4.1（2017.10.01）

1.  完成之前编写函数的整理，添加ugl_conf.h，确定源码包的结构和编译组织方式
2.  添加C语言`printf()`函数底层的输出重定向，使芯片可以通过串口打印调试信息（会对USART/UART造成影响，慎用）
3.  确定对FatFS进行封装，以便使用，同时开始编写ugl_malloc.h/.c，将在下个版本加入


version 0.6.5（2017.10.05）

1.  修改ugl_conf.h中对于用户自定义配置的开启方法，从取消注释变为预定义0则关闭，预定义1则开启
2.  修改了部分头文件的包含关系，将arm_math.h移入ugl.h文件，方便调用
3.  ugl_malloc.h/.c加入，但是仅支持STM32F407ZGTx+ISSI62WV51216(SRAM 1MiB)，同时使用HAL库宏定义做条件编译，避免误用
4.  加入ugl_uart.h/.c的封装，仅支持单字节发送


version 0.7.0 alpha （2017.10.06）

1. 删除ugl_spi.h/.c中对于IT模式和DMA模式的函数封装，保留Polling模式，但是仅支持单字节发送接收
2. 封装通信接口外设的函数，本意不是代替HAL库原生函数，而是在某些情况下可以脱离指针更方便的使用HAL API，但是对于数组等形式的收发，依旧推荐使用HAL

version 0.7.0 beta （2017.10.07）

1.  移植Lua语言运行环境到STM32，ugl_lua.h/.c，同时在conf文件中加入对于启用Lua与否的宏定义


version 0.7.1 (2017.10.15)

1.  暂时移除对GCC for ARM和ARMCC的汇编指令支持

version 0.7.5 (2017.10.29)

1.  该软件包更名为UGL(User-defined General Library)，以便和HAL库中FatFS的驱动以及RTOS的BSP相区别
2.  此README亦做出相应修改 

version 0.8.0 alpha (2017.11.04)

1. 对ugl.h中通用函数做出类型划分且添加了对于浮点数的支持(联合体实现)
2. 在ugl_spi.h/.c和ugi\_uart.h/.c中添加了对单精度浮点型(float)数组的发送函数

version 0.8.5 alpha (2017.11.06)

1. 加入ugl_cortex.h/.c，支持软件定时器，最大数目默认为4个，可以自定义
2. 在cortex组件中，支持用户自定义函数，用于在systick中断中执行
3. 在ugl_conf.h中加入了新的预编译宏，将在下个版本中对预编译宏进行整理，同时提供软件定时器的测试样例和使用说明
4. 在ugl.h/.c中加入`void asser_failed_callback(uint8_t* file, uint32_t line)`函数，作为`assert_failed()`的回调函数 

version 0.8.5 (2017.11.07)  

1. 修复了ugl_cortex模块中软件定时器的Bug
2. 加入ugl_cortex的测试样例，详见test目录及其使用说明

version 0.8.7 alpha (2017.11.07)

1. 修改了STIM工作状态的枚举定义
2. 在ugl.h/.c中加入浮点数和整形转换的函数，即利用共用体将浮点数在内存中的二进制表示取出/放回，实现类型转换，以便通信接口发送/接收浮点流
3. 修改了使用DSP库的bug, 修改关于ARM DSP库的使用说明

version 0.8.7 beta (2017.11.09)

1. 重构了STIM的相关代码，修复部分bug

version 0.9.0 alpha (2017.11.13)
1. 删除了汇编代码支持，所有汇编代码均可在intrinsic.h中找到，后期会考虑对此做出整理
2. 重构了ugl.c中部分代码，对某些函数添加了内联支持
3. 考虑到在HAL中，对Systick的初始化有非常大的灵活性，故删除之前未提交之修改的ugl_cortex部分代码
4. 废弃部分使用说明

Copyright &copy; 张璞 长江大学电子信息学院 保留所有权利2017.10

