#### ��������ʹ��˵��

1. ��Բ���ģ���ṩ����������ֵ��ע�����ʹ������ʱ����ugl_conf.h�н���Ӧģ�鿪��

2. �ĵ�Լ��  
    a) ��������ֻ�ṩmain.c�ļ���������main�ļ����ִ��룬���ಿ��ʹ��α�������  
    b) �ĵ���ʹ�õ�α����ʾ�����£�
    ```C++
    /* main.c example */

    //HAL Header Files
    #include "stm32xx_hal_.h"

    int main(void)
    {
        
        stm32_init();   //STM32 HAL_Init()...

        //Example Code Begin    1

        LED_On();       //User GPIO OUTPUT

        if(Key() == 0)  //User GPIO INPUT
        {
            __no_operation();
        }

        //Example Code End      1   

        while(1)
        {
            //Example Code Begin    2

            //Example Code End      2   
        }

    }

    ```

Copyright &copy; ��� ������ѧ������ϢѧԺ ��������Ȩ��2017.10