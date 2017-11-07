#### 测试样例使用说明

1. 针对部分模块提供测试样例，值得注意的是使用样例时需在ugl_conf.h中将对应模块开启

2. 文档约定  
    a) 测试样例只提供main.c文件，仅包含main文件部分代码，其余部分使用伪代码代替  
    b) 文档中使用的伪代码示例如下：
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

Copyright &copy; 张璞 长江大学电子信息学院 保留所有权利2017.10