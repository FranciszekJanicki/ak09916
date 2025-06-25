#ifndef AK09916_AK09916_CONFIG_H
#define AK09916_AK09916_CONFIG_H

#include <stddef.h>
#include <stdint.h>

#define AK09916_DEV_ADDRESS 0b0001100
#define AK09916_COMPANY_ID 0b01001000
#define AK09916_DEVICE_ID 0b00001001
#define AK09916_SCALE 6666666.6666F

typedef float float32_t;

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} vec3_int16_t;

typedef struct {
    float32_t x;
    float32_t y;
    float32_t z;
} vec3_float32_t;

typedef enum {
    AK09916_ERR_OK = 0,
    AK09916_ERR_FAIL = 1 << 0,
    AK09916_ERR_NULL = 1 << 1,
} ak09916_err_t;

typedef enum {
    AK09916_REG_ADDR_WHO_AM_I_1 = 0x00,
    AK09916_REG_ADDR_WHO_AM_I_2 = 0x01,
    AK09916_REG_ADDR_STATUS_1 = 0x10,
    AK09916_REG_ADDR_XOUT_L = 0x11,
    AK09916_REG_ADDR_XOUT_H = 0x12,
    AK09916_REG_ADDR_YOUT_L = 0x13,
    AK09916_REG_ADDR_YOUT_H = 0x14,
    AK09916_REG_ADDR_ZOUT_L = 0x15,
    AK09916_REG_ADDR_ZOUT_H = 0x16,
    AK09916_REG_ADDR_TMPS = 0x17,
    AK09916_REG_ADDR_STATUS_2 = 0x18,
    AK09916_REG_ADDR_CONTROL_1 = 0x30,
    AK09916_REG_ADDR_CONTROL_2 = 0x31,
    AK09916_REG_ADDR_CONTROL_3 = 0x32,
    AK09916_REG_ADDR_TEST_1 = 0x33,
    AK09916_REG_ADDR_TEST_2 = 0x34,
} ak09916_reg_addr_t;

typedef enum {
    AK09916_MODE_POWER_DOWN = 0b00000,
    AK09916_MODE_SINGLESHOT = 0b00001,
    AK09916_MODE_CONTINUOUS_1 = 0b0010,
    AK09916_MODE_CONTINUOUS_2 = 0b00100,
    AK09916_MODE_CONTINUOUS_3 = 0b00110,
    AK09916_MODE_CONTINUOUS_4 = 0b01000,
    AK09916_MODE_SELF_TEST = 0b10000,
} ak09916_mode_t;

typedef struct {
    float32_t scale;
} ak09916_config_t;

typedef struct {
    void* user;
    ak09916_err_t (*bus_initialize)(void*);
    ak09916_err_t (*bus_deinitialize)(void*);
    ak09916_err_t (*bus_write_data)(void*, uint8_t, uint8_t const*, size_t);
    ak09916_err_t (*bus_read_data)(void*, uint8_t, uint8_t*, size_t);
} ak09916_interface_t;

#endif // AK09916_AK09916_CONFIG_H