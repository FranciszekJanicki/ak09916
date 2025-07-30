#ifndef AK09916_AK09916_H
#define AK09916_AK09916_H

#include "ak09916_config.h"
#include "ak09916_registers.h"

typedef struct {
  ak09916_config_t config;
  ak09916_interface_t interface;
} ak09916_t;

ak09916_err_t ak09916_initialize(ak09916_t *ak09916,
                                 ak09916_config_t const *config,
                                 ak09916_interface_t const *interface);
ak09916_err_t ak09916_deinitialize(ak09916_t *ak09916);

ak09916_err_t ak09916_get_mag_data_x_scaled(ak09916_t const *ak09916,
                                            float32_t *scaled);
ak09916_err_t ak09916_get_mag_data_y_scaled(ak09916_t const *ak09916,
                                            float32_t *scaled);
ak09916_err_t ak09916_get_mag_data_z_scaled(ak09916_t const *ak09916,
                                            float32_t *scaled);
ak09916_err_t ak09916_get_mag_data_scaled(ak09916_t const *ak09916,
                                          vec3_float32_t *scaled);

ak09916_err_t ak09916_get_mag_data_x_raw(ak09916_t const *ak09916,
                                         int16_t *raw);
ak09916_err_t ak09916_get_mag_data_y_raw(ak09916_t const *ak09916,
                                         int16_t *raw);
ak09916_err_t ak09916_get_mag_data_z_raw(ak09916_t const *ak09916,
                                         int16_t *raw);
ak09916_err_t ak09916_get_mag_data_raw(ak09916_t const *ak09916,
                                       vec3_int16_t *raw);

ak09916_err_t ak09916_get_who_am_1_reg(ak09916_t const *ak09916,
                                       ak09916_who_am_i_1_reg_t *reg);

ak09916_err_t ak09916_get_who_am_2_reg(ak09916_t const *ak09916,
                                       ak09916_who_am_i_2_reg_t *reg);

ak09916_err_t ak09916_get_status_1_reg(ak09916_t const *ak09916,
                                       ak09916_status_1_reg_t *reg);

ak09916_err_t ak09916_get_xout_reg(ak09916_t const *ak09916,
                                   ak09916_xout_reg_t *reg);
ak09916_err_t ak09916_get_yout_reg(ak09916_t const *ak09916,
                                   ak09916_yout_reg_t *reg);
ak09916_err_t ak09916_get_zout_reg(ak09916_t const *ak09916,
                                   ak09916_zout_reg_t *reg);
ak09916_err_t ak09916_get_out_reg(ak09916_t const *ak09916,
                                  ak09916_out_reg_t *reg);

ak09916_err_t ak09916_get_status_2_reg(ak09916_t const *ak09916,
                                       ak09916_status_2_reg_t *reg);

ak09916_err_t ak09916_get_control_2_reg(ak09916_t const *ak09916,
                                        ak09916_control_2_reg_t *reg);
ak09916_err_t ak09916_set_control_2_reg(ak09916_t const *ak09916,
                                        ak09916_control_2_reg_t const *reg);

ak09916_err_t ak09916_get_control_3_reg(ak09916_t const *ak09916,
                                        ak09916_control_3_reg_t *reg);
ak09916_err_t ak09916_set_control_3_reg(ak09916_t const *ak09916,
                                        ak09916_control_3_reg_t const *reg);

#endif // AK09916_AK09916_H