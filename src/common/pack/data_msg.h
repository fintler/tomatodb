#ifndef __HVN__COMMON_PACK_DATA_MSG_H_
#define __HVN__COMMON_PACK_DATA_MSG_H_

/*
 * Copyright 2013 Los Alamos National Security, LLC.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Jon Bringhurst <jon@bringhurst.org>
 */

#include <stddef.h>
#include <stdint.h>

#include "database.h"
#include "xtime.h"

/* Client requests. */
#define HVN_PROTO_DATA_VERB_READ     0x01
#define HVN_PROTO_DATA_VERB_WRITE    0x03
#define HVN_PROTO_DATA_VERB_DELETE   0x06
#define HVN_PROTO_DATA_VERB_WATCH    0x07
#define HVN_PROTO_DATA_VERB_UNWATCH  0x05
#define HVN_PROTO_DATA_TRANSACTION   0x04

/* Client request modes. */
#define HVN_PROTO_DATA_MODE_RW       0x0C
#define HVN_PROTO_DATA_MODE_RO       0x0D
#define HVN_PROTO_DATA_MODE_RB       0x1D
#define HVN_PROTO_DATA_MODE_RT       0x1C

/* Server responses. */
#define HVN_PROTO_DATA_R_OK          0x14
#define HVN_PROTO_DATA_R_ERR         0x34

typedef struct HVN_db_op_t HVN_msg_data_t;

typedef struct HVN_msg_data_resp_t {
    uint8_t success;
    uint8_t err_code;
} HVN_msg_data_resp_t;

int HVN_proto_pack_data_msgpack(HVN_msg_data_t* data, \
                                size_t* len, \
                                char** msg);

int HVN_proto_unpack_data_msgpack(HVN_msg_data_t* data, \
                                  size_t len, \
                                  char* msg);

int HVN_proto_pack_data_resp_msgpack(HVN_msg_data_resp_t* data, \
                                     size_t* len, \
                                     char** msg);

int HVN_proto_unpack_data_resp_msgpack(HVN_msg_data_resp_t* data, \
                                       size_t len, \
                                       char* msg);

int HVN_proto_pack_data(HVN_msg_data_t* data, \
                        int scheme, \
                        size_t* len, \
                        char** msg);

int HVN_proto_unpack_data(HVN_msg_data_t* data, \
                          int scheme, \
                          size_t len, \
                          char* msg);

int HVN_proto_pack_data_resp(HVN_msg_data_resp_t* data, \
                             int scheme, \
                             size_t* len, \
                             char** msg);

int HVN_proto_unpack_data_resp(HVN_msg_data_resp_t* data, \
                               int scheme, \
                               size_t len, \
                               char* msg);

int HVN_proto_receive_data_msg(int fd, \
                               HVN_msg_data_t* data_msg_data);

int HVN_proto_send_data_resp_msg(int fd, HVN_msg_data_resp_t* resp);

void HVN_proto_print_data_msg(HVN_msg_data_t* data);

#endif /* __HVN__COMMON_PACK_DATA_MSG_H_ */
