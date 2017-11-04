### Board Support Package �����ʽ�淶

#### ����

Ϊ�˱�֤����Ĺ淶�ԺͿɶ��ԣ����ڸ��Լ�����һ��СС�Ĺ淶��˵��������ȷ��������

#### 1. ע��

һ������Ĵ����Ȼ���൱������ע�ͣ��ڴ�Board Support Package�У�����ע�ͷ�Ϊ���¼������֣�����Ӣ����ɣ���Ϊ�����л����뷨

ע��ʾ���еı�ע`optional`�Ļ��������ڵĲ����ǿ�ѡ����

1.  �ļ���βע��

    ��βע����Ҫ��Ϊ��չʾ�ļ��Ļ�����Ϣ��ȷ���ļ��Ƿ��������������

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

2. �ֶ�ע��

   �ֶ�ע����Ϊ��ȷ����ͬ����ģ��������ֹ��һ���¸�ģ��Ŀ�ͷע�ͼ�Ϊ�ϸ�ģ�����ֹע�ͣ����ö���ע�ͣ�����ע��Ϊ����ע�͵Ĵμ���Ԫ��ʾ������

   ```C++
   /* This is a Module Start Annotations, and it is Last Module Ending Annotations */

   //This is Apart Annotations
   ```

   �ֶ�ע��ʹ�ô����������������Ķ������������÷�������`includes.h`�ļ���������һ�θ��ļ�������

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

   �����еĶ���ע�ͣ�������`#endif`֮��ģ������еĵ���ע�ͼ�Ϊ�ֶ�ע��

3. ��������ע��

   ��������ע�Ͷ����Source File���ǶԸú�����һ��������˵����ʾ������

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

   ���޲���������ֵ��ע�������Ӧ�ñ�עNone

4. ������ע��  

    ������ע����Ҫ˵��һЩ�ؼ����ֵ����⣬ֻ��ʹ�õ���ע�ͣ���ʾ��

5. ����ע��

   ��ҪΪ��������ע�ͣ������ķ�ע��

   �����������Ҫע�͵ģ�ͳһ�õ���ע��

#### 2. ����ʽ
1. ��ͨ���  
    ��ͨ��������ֵ��䣬�����������ȣ��������Ϊ�����������ӿո񣬶��š��ֺ�֮��������������Ҳ��ӿո�ʾ������  
    ```value = function(param1, param2, param3...);```  
2. ����  
    ������Ҫָ��֧/ѭ���ṹ���Լ��ṹ��/������/ö�ٵ����Ͷ���
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
    ��ʹ�û����Ž�������ֿ�ʱ��������Ҫ����һ�У����⻹��һЩ����ķ�֧ѭ���ṹ����
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
    ����if-else��֧��ֻ��һ���������ʱ��������ȥ�����ţ�����Ҫ����һ�У����ڿյ�ѭ���ṹ��������ȥ�����ţ����ǿ����Ҫ����һ��
3. ��ֵ���  
    ��ֵ������������ֻ��ʹ�����¹ؼ��֣�`uint8_t/int8_t`��`int16_t/uint16_t`��`int32_t/uint32_t`��`int64_t/uint64_t`��`float/double` �Լ������Զ�����������ͣ�  
    ���õ����η���`short/long/long long`��`signed/unsigned`��`const/extern/static`��ע�����÷�Χ
4. �����ʽ  
    a) ���������Ҫ����ӿո������  
    ����/�Լ������������/ָ����±꣬�����б��ʽ������
    ```C++
    i++;

    *(p+1) = arr[i+1];

    function(i+1, arr);
    ```
    b) ָ��Ķ���������  
    �ڶ���ָ����ߺ����β�Ϊָ��ʱ���Ƽ�����д����
    ```C++
    uint8_t* p = 0;
    funtion(const char* arg, uint8_t size);
    ```
    ���Ƽ�����д����  
    ```C++
    uint8_t *p = 0;
    ```
    ��ָ������ʱ��*�����ַ�������д�����£�
    ```C++
    *(p+1) = arr[i];
    ```

*������*

Copyright &copy; ��� ������ѧ������ϢѧԺ ��������Ȩ��	2017.11

