### UGL ʹ��˵�� (v0.8.7 alpha)

#### ����(2017.10.01)
1. ������/Ӳ��֧�ְ�д��STM32F407ƽ̨��������֧��STM32ȫϵ�е�ͨ�ù��ܣ���Դ�����ʽ����
2. ��Դ�������HAL�ĳ�ʼ������Ҫʹ������������ʹ��STM32CubeMX��ʼ����Ӧ����
3. ��Դ�������Ʋο���STM32 HAL�⣬��һ���ɲü������޸ĵ������������ͬ���ܵ�HAL���Ӱ�죬��Դ�����Щ���������ȱ�ݣ����磬SPI�޷�����16λ����������
4. ��Դ��������HAL���Ĵ����ͻ���̣�ע�⣬��ಿ�֣���ugl_iar.h/c��ugl_mdk.h/.c��ugl_gcc.h/.c�Ƿ�֧��STM32F407�����оƬ��δ��֤����ʹ���г���������Ų�����
5. ��Դ��������ļ���Ҫ�ԣ�������Ҫ�Բ�ͬ��Ϊ�����������Ե�һ��Ϊ����Ҫ

#### ʹ��˵��(2017.10.03)
1. Դ����ļ���֯�ṹ  

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
    > ����__modulexx__�Ǿ����ģ�����ƣ�����ugl_gpio.h/.c  

2. ��Ҫʹ�ô�Դ���������Ҫ��STM32CubeMX�н��г�ʼ��

3. ��ʼ���������ɺ󣬽���Դ�����Ŀ¼��incĿ¼���Ϊͷ�ļ��İ���Ŀ¼����ʹ�õ���Դ�ļ������IDE��δʹ�õ��Ŀ��Բ���ӻ���ֱ��ɾ��

4. �ļ��ּ�  

    a. һ���ļ������������ֱ�Ϊugl.h/ugl_conf.h������ʹ�ú���ģ�飬�������ļ��Ǳز����ٵ�  

        1) ugl.h -- ������λ�����������stm32f4xx_hal_conf.h��ugl_conf.h��ǰ����STM32F4ϵ��HAL���ģ�����������������Ǵ�Դ�����ģ����������  
        2) ugl_conf.h -- Դ�����ģ��������������Ҫ������ģ�飬����FatFS��User Malloc���Լ�ͨ����������λ����ӡ������Ϣ����������
    b. �����ļ�����һ����Ϊugl.c�����ļ���ugl.h��������ͨ�ú����Ķ��壬����ʹ��ͨ�ú������ɲ�������  		��ɾ�����ļ�

    c. �����ļ�Ϊ��ģ���ͷ�ļ���Դ�ļ�������ugl_gpio.h/.c����ϸ���ݼ��ļ���

    d. includes.h�ļ����������Ϸ��࣬����һ��Ϊ�������������õ�ͷ�ļ���������Դ��������е�ͷ�ļ���ֻӦ�����������ڰ������ͷ�ļ����߲�ʹ���������˲����ر��Ƽ�ʹ�ø��ļ�

    e. ����ʹ��includes.h�ļ�����Ӧ�������������ΰ������õ���ͷ�ļ������ڶ�Ӧģ���а�������ʾ��ʹ��

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

5. ��ֲ

    ��Դ���Ӧ���Ǳ�����ֲ�ģ�����ʾ����ugl.h�Ĳ���Դ��

    ```C++
    #include "stm32f4xx_hal.h"
    #include "stm32f4xx_hal_conf.h"
    #include "main.h"
    #include "stdlib.h"
    #include "ugl_conf.h"

    ...
    ```

    ������Ŀ�ʼ�������й�HAL���ͷ�ļ��������ɣ������Ⲣ�������Դ������������ݶ�����һ��оƬ�����ã����磬STM32L452RE��STM32F407ZGͬ��Cortex-M4F�ܹ�������STM32L452ӵ��QSPI�ӿڣ���STM32F407ȴ�������˽ӿڣ������������ֲ����Դ�������֧��Ӳ��ԭ��û�еĹ��ܣ���Ϊ��Դ����ǻ���HAL���Ӳ����ʼ������֮�ϵ�

6.  ��Բ�ͬ�������Ĵ���

    һ����ΪARMƽ̨��Ҫ�����������õı��������ֱ�ΪGCC for ARM��ARMCC��IARCC�������߶�Ӧר�е�IDE��Keil-MDK��IAR for ARM�����ڱ�������ʵ�ֲ�ͬ�������漰������Ҫ��Ӳ�ͬ������������ʱ��Ӧ������Դ�������Ϊ�˼�С��д������������Ի�ຯ�����˷��ļ���д����User_Malloc���������ݱ�������ͬ�����������룬��ʵ�ϣ���ᷢ���ڴ�Դ�������������ʮ�ֳ���������Ҫ��Ϊ�˱�֤����Ŀɲü���

#### ��ֲ˵��(2017.10.04) 

��Ȼ������֧��STM32ȫϵ�е�ͨ�ù��ܣ�������ʹ��ʱ��ȻҪ��һЩСС�ĸĶ�������ʾ�����£�

1. �޸�ugl.h�е�ͷ�ļ���������������ֲһ��

2. ����ugl_uart.h/.c����ֲ����STM32F407xxƽ̨Ĭ��ʹ��USART1��ɶԱ�׼����������ض��򣬸ýڴ�������

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

   �˴�������ĺ��������е�USART1Ϊ�û��Զ����UART/USART���ɣ��粻ʹ����ɺ���

3.  ��Բ�ͬƽ̨����ѧ�⣬�˽���ugl_conf.h�ж��壬��Ӧ��Դ������

    ```C++
    /* ugl_conf.h */
    /* STM32 HAL Macros */
    /**
        * Defination for ARM Math Library
    **/
    /*#define   ARM_MATH_CM0*/          	//ARM Math for Cortex-M0
    /*#define   ARM_MATH_CM0PLUS*/      	//ARM Math for Cortex-M0+
    /*#define   ARM_MATH_CM3*/          	//ARM Math for Cortex-M3
    #define     ARM_MATH_CM4            	//ARM Math for Cortex-M4F(default)
    /*#define   ARM_MATH_CM7*/          	//ARM Math for Cortex-M7
    ```

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

    �ɴ˿��Կ���������Cortex-Mϵ�У�ֻ���Ӧ��`ARM_MATH_CMx`��ע��ȡ��������ʹ����Ӧ����ѧ�⣬ͬʱugl_conf.h�й�����ѧ��ĺ꣬ͬʱֻ����һ��ȡ��ע�ͻ��߶�ע�͵�

4. ����ugl_malloc.h/.c���ݲ�֧�ֳ�STM32F407������ͺ�

5. LuaJIT�����У���Ҫ���ö�ջ�����������ó���Ҫ��ջ����Сֵ����STM32CubeMX�п���Ԥ�����ջ��С

#### ����˵��(2017.10.07)

?	���ڸ�Դ������ܻ����һЩƫ������ķ������������ڽ���ʵ���LuaJIT������������һ������˵������

#### ����˵��(2017.10.01)

*���еĺ����������Ը���֮ǰ��дSTM32��ʵ��/��Ŀ���룬�ļ��б�ע������2017.10.02֮ǰ�Ľ�Ϊ�������ڶ��Ǳ�д����*

version 0.0.9��2017.08.26��

1.  ���ugl.h/.c��`UGL_Delay_us()`��`UGL_Float2String()`�������ο�[����ԭ��](http://www.openedv.com/)������λ�������궨��
2.  ���ugl_gpio.h/.c

version 0.1.5��2017.09.02��

1.  ���ugl_spi.h/.c�����SPI��ѯģʽ�ķ�װ�������շ���λ���ݣ�����һ���ֽڣ���֧�ֶ�̬����SPI�Ĳ�����

version 0.2.0��2017.09.06��

1.  �޸�ugl_spi.h/.c�ж�̬���ò����ʵ�bug���������������ʧЧ������
2.  ���ugl_rcc.h/.c�����ⲿʹ��`extern`�ؼ��������Ͷ�����ʱ�Ӱ�ȫϵͳ�жϻص����ԼĴ�����ʽʵ�֣�֧���ⲿʱ��HSE/LSIʧЧʱ���л����ڲ�ʱ��HSI/LSI��30MHz/Ĭ��Ƶ�ʣ�

version 0.2.6��2017.09.16��

1.  ���ڸ��ͺ�оƬ��HSI��ͬ���޷��Ϻõ�֧��MSIʱ�ӣ��˺����޷��ﵽԤ��Ҫ�������ʱ�Ƴ�ugl_rcc.h/.c
2.  �����ITģʽ��SPI�Ķ�д����

version 0.3.0��2017.09.24��

1.  �����includes.hͷ�ļ������������ṩһ��ͳһ�Ľӿ�
2.  �����ugl_iar.h/.c�ļ���֧�ֲ��ֻ��ָ�����֤��

version 0.3.1��2017.09.26��

1. �����DMAģʽ��SPI�Ķ�д����
2. ��ʼ����ugl_mdk.h/.c��ugl_gcc.h/.c�����ʱ��δ��

version 0.4.1��2017.10.01��

1.  ���֮ǰ��д�������������ugl_conf.h��ȷ��Դ����Ľṹ�ͱ�����֯��ʽ
2.  ���C����`printf()`�����ײ������ض���ʹоƬ����ͨ�����ڴ�ӡ������Ϣ�����USART/UART���Ӱ�죬���ã�
3.  ȷ����FatFS���з�װ���Ա�ʹ�ã�ͬʱ��ʼ��дugl_malloc.h/.c�������¸��汾����


version 0.6.5��2017.10.05��

1.  �޸�ugl_conf.h�ж����û��Զ������õĿ�����������ȡ��ע�ͱ�ΪԤ����0��رգ�Ԥ����1����
2.  �޸��˲���ͷ�ļ��İ�����ϵ����arm_math.h����ugl.h�ļ����������
3.  ugl_malloc.h/.c���룬���ǽ�֧��STM32F407ZGTx+ISSI62WV51216(SRAM 1MiB)��ͬʱʹ��HAL��궨�����������룬��������
4.  ����ugl_uart.h/.c�ķ�װ����֧�ֵ��ֽڷ���


version 0.7.0 alpha ��2017.10.06��

1. ɾ��ugl_spi.h/.c�ж���ITģʽ��DMAģʽ�ĺ�����װ������Pollingģʽ�����ǽ�֧�ֵ��ֽڷ��ͽ���
2. ��װͨ�Žӿ�����ĺ��������ⲻ�Ǵ���HAL��ԭ��������������ĳЩ����¿�������ָ��������ʹ��HAL API�����Ƕ����������ʽ���շ��������Ƽ�ʹ��HAL

version 0.7.0 beta ��2017.10.07��

1.  ��ֲLua�������л�����STM32��ugl_lua.h/.c��ͬʱ��conf�ļ��м����������Lua���ĺ궨��


version 0.7.1 (2017.10.15)

1.  ��ʱ�Ƴ���GCC for ARM��ARMCC�Ļ��ָ��֧��

version 0.7.5 (2017.10.29)

1.  �����������ΪUGL(User-defined General Library)���Ա��HAL����FatFS�������Լ�RTOS��BSP������
2.  ��README��������Ӧ�޸� 

version 0.8.0 alpha (2017.11.04)

1. ��ugl.h��ͨ�ú����������ͻ���������˶��ڸ�������֧��(������ʵ��)
2. ��ugl_spi.h/.c��ugi\_uart.h/.c������˶Ե����ȸ�����(float)����ķ��ͺ���

version 0.8.5 alpha (2017.11.06)

1. ����ugl_cortex.h/.c��֧�������ʱ���������ĿĬ��Ϊ4���������Զ���
2. ��cortex����У�֧���û��Զ��庯����������systick�ж���ִ��
3. ��ugl_conf.h�м������µ�Ԥ����꣬�����¸��汾�ж�Ԥ������������ͬʱ�ṩ�����ʱ���Ĳ���������ʹ��˵��
4. ��ugl.h/.c�м���`void asser_failed_callback(uint8_t* file, uint32_t line)`��������Ϊ`assert_failed()`�Ļص����� 

version 0.8.5 (2017.11.07)  

1. �޸���ugl_cortexģ���������ʱ����Bug
2. ����ugl_cortex�Ĳ������������testĿ¼����ʹ��˵��

version 0.8.7 alpha (2017.11.07)

1. �޸���STIM����״̬��ö�ٶ���
2. ��ugl.h/.c�м��븡����������ת���ĺ����������ù����彫���������ڴ��еĶ����Ʊ�ʾȡ��/�Żأ�ʵ������ת�����Ա�ͨ�Žӿڷ���/���ո�����

Copyright &copy; ��� ������ѧ������ϢѧԺ ��������Ȩ��2017.10

