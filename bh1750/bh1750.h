#ifndef __AF_BH1750_H__
#define __AF_BH1750_H__

#include <stdint.h>

#define BH1750_CMD_POWER_ON  0x01 /* 打开 */
#define BH1750_CMD_POWER_OFF 0x00 /* 关闭 */
#define BH1750_CMD_RESET     0x07 /* 复位 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bh1750_dev     bh1750_dev_t;
typedef enum bh1750_read_mode bh1750_read_mode_t;

enum bh1750_read_mode {
    BH1750_READ_CONTINUOUS_HIGH_RES_MODE  = 0x10, /* 连续测量，高分辨率模式 */
    BH1750_READ_CONTINUOUS_HIGH_RES_MODE2 = 0x11, /* 连续测量，高分辨率模式2 */
    BH1750_READ_CONTINUOUS_LOW_RES_MODE   = 0x13, /* 连续测量，低分辨率模式 */
    BH1750_READ_ONE_TIME_HIGH_RES_MODE    = 0x20, /* 单次测量，高分辨率模式 */
    BH1750_READ_ONE_TIME_HIGH_RES_MODE2   = 0x21, /* 单次测量，高分辨率模式2 */
    BH1750_READ_ONE_TIME_LOW_RES_MODE     = 0x23, /* 单次测量，低分辨率模式 */
};

struct bh1750_dev {
    uint8_t id;          /* 设备 id */
    uint8_t i2c_addr;    /* i2c 地址 */
    uint8_t raw_data[2]; /* 原始数据 */
    float   lux;         /* 光照强度 */
};

/**
 * @brief 打开 bh1750 设备
 *
 * @param i2c_addr i2c 地址
 * @return bh1750_dev_t* bh1750 设备句柄
 */
bh1750_dev_t *bh1750_open(uint8_t i2c_addr);

/**
 * @brief 关闭 bh1750 设备
 *
 * @param dev bh1750 设备句柄
 * @return uint8_t 0: 成功; 其他: 失败
 */
uint8_t bh1750_close(bh1750_dev_t *dev);

/**
 * @brief 读取 bh1750 光照强度
 *
 * @param dev bh1750 设备句柄
 * @param mode 读取模式
 * @return uint8_t 0: 成功; 其他: 失败
 */
uint8_t bh1750_raed(bh1750_dev_t *dev, bh1750_read_mode_t mode);

#ifdef __cplusplus
}
#endif

#endif /* __AF_BH1750_H__ */
