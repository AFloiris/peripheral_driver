#include "mqx.h"
#include "mqx_platform.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

static uint8_t mqx_init(mqx_dev_t *dev) { return mqx_platform_init(dev); }

static uint8_t mqx_deinit(mqx_dev_t *dev) { return mqx_platform_deinit(dev); }

static uint8_t mqx_adc_read(mqx_dev_t *dev) { return mqx_platform_adc_read(dev, &dev->adc_value); }

static uint8_t mqx_calc_mq5(mqx_dev_t *dev, uint8_t calc_type)
{
    float vrl = dev->voltage;
    float rl  = (float)dev->rl;

    if (calc_type == 0)
    {
        dev->r0 = (uint32_t)(5.0f / vrl - 1) * rl;
    }
    else
    {
        dev->rs  = (5.0f / vrl - 1) * rl;
        dev->ppm = pow((11.54f * dev->rs / dev->r0), 0.65f);
    }

    return 0;
}

mqx_dev_t *mqx_open(mqx_type_t type, float ref_voltage, uint32_t rl)
{
    mqx_dev_t *dev = (mqx_dev_t *)malloc(sizeof(mqx_dev_t));
    if (dev == NULL)
        return NULL;

    memset(dev, 0, sizeof(mqx_dev_t));
    dev->type        = type;
    dev->ref_voltage = ref_voltage;
    dev->rl          = rl;

    if (mqx_init(dev) != 0)
    {
        free(dev);
        return NULL;
    }

    return dev;
}

uint8_t mqx_close(mqx_dev_t *dev)
{

    if (dev == NULL)
        return 1;

    if (mqx_deinit(dev) != 0)
        return 2;

    memset(dev, 0, sizeof(mqx_dev_t));

    free(dev);
    return 0;
}

uint8_t mqx_reset(mqx_dev_t *dev)
{
    if (dev == NULL)
        return 1;

    mqx_adc_read(dev);
    dev->voltage = (float)dev->adc_value * dev->ref_voltage / 4095.0f;

    if (dev->type == MQ5 && (mqx_calc_mq5(dev, 0) != 0))
        return 2;

    return 0;
}

uint8_t mqx_read(mqx_dev_t *dev)
{
    if (dev == NULL)
        return 1;

    mqx_adc_read(dev);
    dev->voltage = (float)dev->adc_value * dev->ref_voltage / 4095.0f;

    if (dev->type == MQ5 && (mqx_calc_mq5(dev, 2) != 0))
        return 2;

    return 0;
}
