### User-defined General Library 代码格式规范

#### 概述

为了保证代码的规范性和可读性，现在给自己留下一个小小的规范性说明，用于确定代码风格

#### 1. 注释

一份优秀的代码必然有相当质量的注释，在这个软件包中，代码注释分为以下几个部分，常用英语完成，因为懒得切换输入法

注释示例中的标注`optional`的或者括号内的部分是可选内容

1.  文件首尾注释

    首尾注释主要是为了展示文件的基本信息和确定文件是否结束，举例如下

    ```C++
    /**
     * Title	Note of Function in This Code File(Header/Source)
     * REF		reference(optional)
     * Author	Stark Zhang
     * Date		2017-xx-xx
     * Debug	None/ongoing/Passed
    **/

    ...
        
    //EOF
    ```

2. 分段注释

   分段注释是为了确定不同功能模块代码的起止，一般下个模块的开头注释即为上个模块的起止注释，常用多行注释，单行注释为多行注释的次级单元，示例如下

   ```C++
   /* This is a Module Start Annotations, and it is Last Module Ending Annotations */

   //This is Apart Annotations
   ```

   分段注释使得代码层次清晰，易于阅读，不过这种用法常见于`includes.h`文件，下面是一段该文件的内容

   ```C++
   /* Cortex-M SoftWare Modules Header Files */

   //ARM Math Library
   #if defined(ARM_MATH_CM0) || defined(ARM_MATH_CM0PLUS) || defined(ARM_MATH_CM3) || defined(ARM_MATH_CM4) || defined(ARM_MATH_CM7)

   #include "arm_math.h"

   #endif /*ARM_MATH_CMx*/

   //FatFS
   #ifdef __FatFS_USED

   #include "./inc/ugl_fatfs.h"

   #endif /*__FatFS_USED*/

   //Malloc of User
   #ifdef __Usr_Malloc

   #include "./inc/ugl_malloc.h"

   #endif /*__Usr_Malloc*/

   /* Cortex-M HardWare Modules Header Files */

   //GPIO
   #ifdef HAL_GPIO_MODULE_ENABLED

   #include "./inc/ugl_gpio.h"

   #endif /*HAL_GPIO_MODULE_ENABLED*/
   ```

   上文中的多行注释（不包括`#endif`之后的）和所有的单行注释即为分段注释

3. 函数功能注释

   函数功能注释多见于Source File，是对该函数的一个整体性说明，示例如下

   ```C++
   /**
    * @brief	Function Abstracted
    * @param	uint8_t* param1
    				Note of param1
    * @param	bool param2
    				Note of param2
    * @return	void
    				Data type which will be returned
    * @note	Note of this function
   **/
   void function1(uint8_t* param1, bool param2)
   {
       ;
   }
   ```

   若无参数、返回值和注意事项，则应该标注None

4. 函数内注释  

    函数内注释主要说明一些关键部分的问题，只能使用单行注释，无示例

5. 其他注释

   主要为条件编译注释，见上文分注释

   如果有其他需要注释的，统一用单行注释

#### 2. 语句格式
1. 普通语句  
    普通语句包括赋值语句，函数引用语句等，具体表现为运算符两侧添加空格，逗号、分号之后如有其他内容也添加空格，示例如下  
    ```value = function(param1, param2, param3...);```  
2. 语句块  
    语句块主要指分支/循环结构，以及结构体/联合体/枚举等类型定义
    ```C++
    //for loop
    for(uint8_t i = 0; i <= 8; i++)
    {
        ...
    }

    //enum
    typedef enum
    {
        param_1 = 0,
        paramm_2,
    }example_typedef;
    ```
    即使用花括号进行语句块分块时，花括号要另起一行，此外还有一些特殊的分支循环结构如下
    ```C++
    //a sentence follows if-else
    if(...)
        function1();
    else
        function2();

    //empty while/for loop
    while(expression)
        ;

    for(uint8_t i = 0; i <= 8; i++)
        ;
    ```
    对于if-else分支后只跟一个程序语句时，可以舍去花括号，但是要另起一行；对于空的循环结构，可以舍去花括号，但是空语句要另起一行
3. 赋值语句  
    赋值语句的数据类型只能使用以下关键字：`uint8_t/int8_t`，`int16_t/uint16_t`，`int32_t/uint32_t`，`int64_t/uint64_t`，`float/double` 以及其他自定义的数据类型；  
    可用的修饰符：`short/long/long long`，`signed/unsigned`，`const/extern/static`，注意适用范围
4. 特殊格式  
    a) 运算符不需要两侧加空格的情形  
    自增/自减运算符，数组/指针的下标，函数中表达式做参数
    ```C++
    i++;

    *(p+1) = arr[i+1];

    function(i+1, arr);
    ```
    b) 指针的定义与引用  
    在定义指针或者函数形参为指针时，推荐以下写法：
    ```C++
    uint8_t* p = 0;
    funtion(const char* arg, uint8_t size);
    ```
    不推荐以下写法：  
    ```C++
    uint8_t *p = 0;
    ```
    在指针引用时，*做解地址运算符，写法如下：
    ```C++
    *(p+1) = arr[i];
    ```

*待补充*

Copyright &copy; 张璞 长江大学电子信息学院 保留所有权利	2017.11

