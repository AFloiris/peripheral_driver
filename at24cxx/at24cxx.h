#ifndef __AF_AT24CXX_H__
#define __AF_AT24CXX_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct at24cxx_dev     at24cxx_dev_t;
typedef enum at24cxx_type      at24cxx_type_t;
typedef enum at24cxx_page_size at24cxx_page_size_t;

/* at24cxx 类型，每个类型对应存储空间的大小(字节) */
enum at24cxx_type {
    AT24C01  = 128,
    AT24C02  = 256,
    AT24C04  = 512,
    AT24C08  = 1024,
    AT24C16  = 2048,
    AT24C32  = 4096,
    AT24C64  = 8192,
    AT24C128 = 16384,
    AT24C256 = 32768,
    AT24C512 = 65536,
    AT24CM01 = 131072,
    AT24CM02 = 262144,
};
/* at24cxx 页大小(字节) */
enum at24cxx_page_size {
    AT24C01_PAGE_SIZE  = 8,
    AT24C02_PAGE_SIZE  = 8,
    AT24C08_PAGE_SIZE  = 16,
    AT24C16_PAGE_SIZE  = 16,
    AT24C04_PAGE_SIZE  = 16,
    AT24C32_PAGE_SIZE  = 32,
    AT24C64_PAGE_SIZE  = 32,
    AT24C128_PAGE_SIZE = 64,
    AT24C256_PAGE_SIZE = 64,
    AT24C512_PAGE_SIZE = 128,
    AT24CM01_PAGE_SIZE = 256,
    AT24CM02_PAGE_SIZE = 256,
};

struct at24cxx_dev {
    uint8_t             id;        /* 设备 id */
    uint8_t             addr;      /* i2c 地址 */
    at24cxx_type_t      type;      /* at24cxx 类型 */
    at24cxx_page_size_t page_size; /* at24cxx 页大小 */
};

/**
 * @brief 打开 at24cxx 设备
 *
 * @param addr  i2c 地址
 * @param type  at24cxx 类型
 * @return at24cxx_dev_t* at24cxx 设备
 */
at24cxx_dev_t *at24cxx_open(uint8_t addr, at24cxx_type_t type);

/**
 * @brief 关闭 at24cxx 设备
 *
 * @param dev  at24cxx 设备
 * @return uint8_t  0: 成功,其他: 失败
 */
uint8_t at24cxx_close(at24cxx_dev_t *dev);

/**
 * @brief at24cxx 设备写入
 *
 * @param dev  at24cxx 设备
 * @param mem_addr  at24cxx 设备的目标地址
 * @param data  数据
 * @param len  数据长度
 * @return uint8_t  0: 写入成功，其他: 写入失败
 */
uint8_t at24cxx_write(at24cxx_dev_t *dev, uint16_t mem_addr, uint8_t *data, uint16_t len);

/**
 * @brief at24cxx 设备读取
 *
 * @param dev  at24cxx 设备
 * @param mem_addr  at24cxx 设备的目标地址
 * @param data  数据
 * @param len  数据长度
 * @return uint8_t  0: 读取成功，其他: 读取失败
 */
uint8_t at24cxx_read(at24cxx_dev_t *dev, uint16_t mem_addr, uint8_t *data, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif /* __AF_AT24CXX_H__ */
