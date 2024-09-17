# AT24CXX


## 使用示例

### STM32

* STM32F407ZGT6
* HAL 库, STM32CubeMX
* I2C1
* AT24C02


```C
#include "at24cxx.h"
void at24cxx_test(void)
{
    uint8_t read_data[128] = {0};
    uint8_t write_data[128] = "abc 123 落霞孤鹜";
    uint8_t ret = 0;

    af_i2c_t af_i2c1 = {
        .hi2c = &hi2c1,
    };
    at24cxx_dev_t * at24c02 = at24cxx_open(af_i2c1, 0x50, AT24C02);
    if(at24c02 == NULL)
    {
        printf("at24cxx open failed\r\n");
        return;
    }

    ret = at24cxx_write(at24c02, 0x00, write_data, sizeof(write_data));
    if (ret)
    {
        printf("at24cxx write failed\r\n");
        return;
    }

    ret = at24cxx_read(at24c02, 0x00, read_data, sizeof(read_data));
    if (ret)
    {
        printf("at24cxx read failed\r\n");
        return;
    }

    /* 打印读出的数据 */
    printf("read data str: %s\r\n", read_data);
    printf("read data arr:");
    for(int i = 0; i < sizeof(read_data); i++)
    {
        printf("%c ", read_data[i]);
    }
    printf("\r\n");

    at24cxx_close(at24c02);
}
/**
 * 输出结果：
# RECV ASCII/342 <<<
read data str: abc 123 落霞孤鹜
read data arr: 97 98 99 32 49 50 51 32 232 144 189 233 156 158 229 173 164 233 185 156 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 

*/
```