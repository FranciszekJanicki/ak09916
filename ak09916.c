#include "ak09916.h"
#include "ak09916_config.h"
#include "ak09916_registers.h"
#include <assert.h>
#include <string.h>

static ak09916_err_t ak09916_bus_init(ak09916_t const* ak09916)
{
    return ak09916->interface.bus_init ? ak09916->interface.bus_init(ak09916->interface.user)
                                       : AK09916_ERR_NULL;
}

static ak09916_err_t ak09916_bus_deinit(ak09916_t const* ak09916)
{
    return ak09916->interface.bus_deinit ? ak09916->interface.bus_deinit(ak09916->interface.user)
                                         : AK09916_ERR_NULL;
}

static ak09916_err_t ak09916_bus_write(ak09916_t const* ak09916,
                                       uint8_t address,
                                       uint8_t const* data,
                                       size_t data_size)
{
    return ak09916->interface.bus_write
               ? ak09916->interface.bus_write(ak09916->interface.user, address, data, data_size)
               : AK09916_ERR_NULL;
}

static ak09916_err_t ak09916_bus_read(ak09916_t const* ak09916,
                                      uint8_t address,
                                      uint8_t* data,
                                      size_t data_size)
{
    return ak09916->interface.bus_read
               ? ak09916->interface.bus_read(ak09916->interface.user, address, data, data_size)
               : AK09916_ERR_NULL;
}

ak09916_err_t ak09916_initialize(ak09916_t* ak09916,
                                 ak09916_config_t const* config,
                                 ak09916_interface_t const* interface)
{
    assert(ak09916 && config && interface);

    memset(ak09916, 0, sizeof(*ak09916));
    memcpy(&ak09916->config, config, sizeof(*config));
    memcpy(&ak09916->interface, interface, sizeof(*interface));

    return ak09916_bus_init(ak09916);
}

ak09916_err_t ak09916_deinitialize(ak09916_t* ak09916)
{
    assert(ak09916);

    ak09916_err_t err = ak09916_bus_deinit(ak09916);

    memset(ak09916, 0, sizeof(*ak09916));

    return err;
}

ak09916_err_t ak09916_get_mag_data_x_scaled(ak09916_t const* ak09916, float32_t* scaled)
{
    assert(ak09916 && scaled);

    int16_t raw = {};

    ak09916_err_t err = ak09916_get_mag_data_x_raw(ak09916, &raw);

    *scaled = (float32_t)raw * ak09916->config.scale;

    return err;
}

ak09916_err_t ak09916_get_mag_data_y_scaled(ak09916_t const* ak09916, float32_t* scaled)
{
    assert(ak09916 && scaled);

    int16_t raw = {};

    ak09916_err_t err = ak09916_get_mag_data_y_raw(ak09916, &raw);

    *scaled = (float32_t)raw * ak09916->config.scale;

    return err;
}

ak09916_err_t ak09916_get_mag_data_z_scaled(ak09916_t const* ak09916, float32_t* scaled)
{
    assert(ak09916 && scaled);

    int16_t raw = {};

    ak09916_err_t err = ak09916_get_mag_data_z_raw(ak09916, &raw);

    *scaled = (float32_t)raw * ak09916->config.scale;

    return err;
}

ak09916_err_t ak09916_get_mag_data_scaled(ak09916_t const* ak09916, vec3_float32_t* scaled)
{
    assert(ak09916 && scaled);

    vec3_int16_t raw = {};

    ak09916_err_t err = ak09916_get_mag_data_raw(ak09916, &raw);

    scaled->x = (float32_t)raw.x * ak09916->config.scale;
    scaled->y = (float32_t)raw.y * ak09916->config.scale;
    scaled->z = (float32_t)raw.z * ak09916->config.scale;

    return err;
}

ak09916_err_t ak09916_get_mag_data_x_raw(ak09916_t const* ak09916, int16_t* raw)
{
    assert(ak09916 && raw);

    ak09916_xout_reg_t reg = {};

    ak09916_err_t err = ak09916_get_xout_reg(ak09916, &reg);

    *raw = reg.xout;

    return err;
}

ak09916_err_t ak09916_get_mag_data_y_raw(ak09916_t const* ak09916, int16_t* raw)
{
    assert(ak09916 && raw);

    ak09916_yout_reg_t reg = {};

    ak09916_err_t err = ak09916_get_yout_reg(ak09916, &reg);

    *raw = reg.yout;

    return err;
}

ak09916_err_t ak09916_get_mag_data_z_raw(ak09916_t const* ak09916, int16_t* raw)
{
    assert(ak09916 && raw);

    ak09916_zout_reg_t reg = {};

    ak09916_err_t err = ak09916_get_zout_reg(ak09916, &reg);

    *raw = reg.zout;

    return err;
}

ak09916_err_t ak09916_get_mag_data_raw(ak09916_t const* ak09916, vec3_int16_t* raw)
{
    assert(ak09916 && raw);

    ak09916_out_reg_t reg = {};

    ak09916_err_t err = ak09916_get_out_reg(ak09916, &reg);

    raw->x = reg.xout;
    raw->y = reg.yout;
    raw->z = reg.zout;

    return err;
}

ak09916_err_t ak09916_get_who_am_1_reg(ak09916_t const* ak09916, ak09916_who_am_i_1_reg_t* reg)
{
    assert(ak09916 && reg);

    uint8_t data = {};

    ak09916_err_t err = ak09916_bus_read(ak09916, AK09916_REG_ADDR_WHO_AM_I_1, &data, sizeof(data));

    reg->wia1 = data & 0xFFU;

    return err;
}

ak09916_err_t ak09916_get_who_am_2_reg(ak09916_t const* ak09916, ak09916_who_am_i_2_reg_t* reg)
{
    assert(ak09916 && reg);

    uint8_t data = {};

    ak09916_err_t err = ak09916_bus_read(ak09916, AK09916_REG_ADDR_WHO_AM_I_2, &data, sizeof(data));

    reg->wia2 = data & 0xFFU;

    return err;
}

ak09916_err_t ak09916_get_status_1_reg(ak09916_t const* ak09916, ak09916_status_1_reg_t* reg)
{
    assert(ak09916 && reg);

    uint8_t data = {};

    ak09916_err_t err = ak09916_bus_read(ak09916, AK09916_REG_ADDR_STATUS_1, &data, sizeof(data));

    reg->dor = (data >> 1U) & 0x01U;
    reg->drdy = data & 0x01U;

    return err;
}

ak09916_err_t ak09916_get_xout_reg(ak09916_t const* ak09916, ak09916_xout_reg_t* reg)
{
    assert(ak09916 && reg);

    uint8_t data[2] = {};

    ak09916_err_t err = ak09916_bus_read(ak09916, AK09916_REG_ADDR_XOUT_L, data, sizeof(data));

    reg->xout = (int16_t)(((data[0] & 0xFF) << 8) | (data[1] & 0xFF));

    return err;
}

ak09916_err_t ak09916_get_yout_reg(ak09916_t const* ak09916, ak09916_yout_reg_t* reg)
{
    assert(ak09916 && reg);

    uint8_t data[2] = {};

    ak09916_err_t err = ak09916_bus_read(ak09916, AK09916_REG_ADDR_YOUT_L, data, sizeof(data));

    reg->yout = (int16_t)(((data[0] & 0xFF) << 8) | (data[1] & 0xFF));

    return err;
}

ak09916_err_t ak09916_get_zout_reg(ak09916_t const* ak09916, ak09916_zout_reg_t* reg)
{
    assert(ak09916 && reg);

    uint8_t data[2] = {};

    ak09916_err_t err = ak09916_bus_read(ak09916, AK09916_REG_ADDR_ZOUT_L, data, sizeof(data));

    reg->zout = (int16_t)(((data[0] & 0xFF) << 8) | (data[1] & 0xFF));

    return err;
}

ak09916_err_t ak09916_get_out_reg(ak09916_t const* ak09916, ak09916_out_reg_t* reg)
{
    assert(ak09916 && reg);

    uint8_t data[6] = {};

    ak09916_err_t err = ak09916_bus_read(ak09916, AK09916_REG_ADDR_XOUT_L, data, sizeof(data));

    reg->xout = (int16_t)(((data[0] & 0xFF) << 8) | (data[1] & 0xFF));
    reg->yout = (int16_t)(((data[2] & 0xFF) << 8) | (data[3] & 0xFF));
    reg->zout = (int16_t)(((data[4] & 0xFF) << 8) | (data[5] & 0xFF));

    return err;
}

ak09916_err_t ak09916_get_status_2_reg(ak09916_t const* ak09916, ak09916_status_2_reg_t* reg)
{
    assert(ak09916 && reg);

    uint8_t data = {};

    ak09916_err_t err = ak09916_bus_read(ak09916, AK09916_REG_ADDR_STATUS_2, &data, sizeof(data));

    reg->hofl = (data >> 3U) & 0x01U;

    return err;
}

ak09916_err_t ak09916_get_control_2_reg(ak09916_t const* ak09916, ak09916_control_2_reg_t* reg)
{
    assert(ak09916 && reg);

    uint8_t data = {};

    ak09916_err_t err = ak09916_bus_read(ak09916, AK09916_REG_ADDR_CONTROL_2, &data, sizeof(data));

    reg->mode = data & 0x1FU;

    return err;
}

ak09916_err_t ak09916_set_control_2_reg(ak09916_t const* ak09916,
                                        ak09916_control_2_reg_t const* reg)
{
    assert(ak09916 && reg);

    uint8_t data = {};

    ak09916_err_t err = ak09916_bus_read(ak09916, AK09916_REG_ADDR_CONTROL_2, &data, sizeof(data));

    data &= ~0x1FU;

    data |= (reg->mode & 0x1FU);

    err |= ak09916_bus_write(ak09916, AK09916_REG_ADDR_CONTROL_2, &data, sizeof(data));

    return err;
}

ak09916_err_t ak09916_get_control_3_reg(ak09916_t const* ak09916, ak09916_control_3_reg_t* reg)
{
    assert(ak09916 && reg);

    uint8_t data = {};

    ak09916_err_t err = ak09916_bus_read(ak09916, AK09916_REG_ADDR_CONTROL_3, &data, sizeof(data));

    reg->srst = data & 0x01U;

    return err;
}

ak09916_err_t ak09916_set_control_3_reg(ak09916_t const* ak09916,
                                        ak09916_control_3_reg_t const* reg)
{
    assert(ak09916 && reg);

    uint8_t data = {};

    ak09916_err_t err = ak09916_bus_read(ak09916, AK09916_REG_ADDR_CONTROL_3, &data, sizeof(data));

    data &= ~0x01U;

    data |= reg->srst & 0x01U;

    err |= ak09916_bus_write(ak09916, AK09916_REG_ADDR_CONTROL_3, &data, sizeof(data));

    return err;
}
