/* Copyright (c) 2014 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

#include <stdlib.h>
#include <string.h>
#include "ble_app.h"
#include "ble_serialization.h"
#include "ble_struct_serialization.h"
#include "cond_field_serialization.h"
#include "app_util.h"


uint32_t ble_enable_req_enc(ble_enable_params_t * p_ble_enable_params,
                            uint8_t * const       p_buf,
                            uint32_t * const      p_buf_len)
{
    uint32_t index    = 0;
    uint32_t err_code = NRF_SUCCESS;

    SER_ASSERT_NOT_NULL(p_buf);
    SER_ASSERT_NOT_NULL(p_buf_len);

    SER_ASSERT_LENGTH_LEQ(index + 2, *p_buf_len);

    p_buf[index++] = SD_BLE_ENABLE;
    
    err_code = cond_field_enc(p_ble_enable_params, p_buf, *p_buf_len, &index, ble_enable_params_t_enc);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    *p_buf_len = index;

    return err_code;
}


uint32_t ble_enable_rsp_dec(uint8_t const * const p_buf,
                            uint32_t              packet_len,
                            uint32_t * const      p_result_code)
{
    return ser_ble_cmd_rsp_dec(p_buf, packet_len, SD_BLE_ENABLE, p_result_code);
}
