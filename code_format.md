### Board Support Package 代码格式规范

##### 概述

为了保证代码的规范性和可读性，现在给自己留下一个小小的规范性说明，用于确定代码风格

##### 1. 注释

一份优秀的代码必然有相当质量的注释，在此Board Support Package中，代码注释分为以下几个部分，常用英语完成，因为懒得切换输入�?

注释示例中的标注`optional`的或者括号内的部分是可选内�?

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

   分段注释是为了确定不同功能模块代码的起止，一般下个模块的开头注释即为上个模块的起止注释，常用多行注释，单行注释为多行注释的次级单元，示例如�?

   ```C++
   /* This is a Module Start Annotations, and it is Last Module Ending Annotations */

   //This is Apart Annotations
   ```

   分段注释使得代码层次清晰，易于阅读，不过这种用法常见于`includes.h`文件，下面是一段该文件的内�?

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

   上文中的多行注释（不包括`#endif`之后的）和所有的单行注释即为分段注释�?

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

4. 函数内注�?

   函数内注释主要说明一些关键部分的问题，只能使用单行注释，无示�?

5. 其他注释

   主要为条件编译注释，见上文分段注�?

   如果有其他需要注释的，统一用单行注�?

##### 2. 函数语句格式

##### 3. 



