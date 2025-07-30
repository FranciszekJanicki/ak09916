#ifndef AK09916_AK09916_REGISTERS_H
#define AK09916_AK09916_REGISTERS_H

#include <stdint.h>

typedef struct WHO_AM_I_1 {
  uint8_t wia1 : 8;
} ak09916_who_am_i_1_reg_t;

typedef struct {
  uint8_t wia2 : 8;
} ak09916_who_am_i_2_reg_t;

typedef struct {
  uint8_t dor : 1;
  uint8_t drdy : 1;
} ak09916_status_1_reg_t;

typedef struct {
  int16_t xout : 16;
} ak09916_xout_reg_t;

typedef struct {
  int16_t yout : 16;
} ak09916_yout_reg_t;

typedef struct {
  int16_t zout : 16;
} ak09916_zout_reg_t;

typedef struct {
  int16_t xout : 16;
  int16_t yout : 16;
  int16_t zout : 16;
} ak09916_out_reg_t;

typedef struct {
  uint8_t hofl : 1;
} ak09916_status_2_reg_t;

typedef struct {
  uint8_t mode : 5;
} ak09916_control_2_reg_t;

typedef struct {
  uint8_t srst : 1;
} ak09916_control_3_reg_t;

#endif // AK09916_AK09916_REGISTERS_H