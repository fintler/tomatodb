#ifndef __HVN__HAVEND_CLIENT_PROTOCOL_CONNECT_MSG_H_
#define __HVN__HAVEND_CLIENT_PROTOCOL_CONNECT_MSG_H_

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

#include <stdint.h>

typedef struct HVN_msg_client_connect_t {
    uint32_t magic;
    uint16_t version;
} HVN_msg_client_connect_t;

typedef struct HVN_msg_client_connect_resp_t {
    uint8_t success;
    uint8_t err_code;
    uint16_t version;
} HVN_msg_client_connect_resp_t;

int HVN_clnt_proto_pack_connect_msgpack(HVN_msg_client_connect_t* data, \
                                        size_t* len, \
                                        char** msg);
int HVN_clnt_proto_unpack_connect_msgpack(HVN_msg_client_connect_t* data, \
        size_t len, \
        char* msg);
int HVN_clnt_proto_pack_connect_resp_msgpack(HVN_msg_client_connect_resp_t* data, \
        size_t* len, \
        char** msg);
int HVN_clnt_proto_unpack_connect_resp_msgpack(HVN_msg_client_connect_resp_t* data, \
        size_t len, \
        char* msg);

int HVN_clnt_proto_pack_connect(HVN_msg_client_connect_t* data, \
                                int scheme, \
                                size_t* len, \
                                char** msg);
int HVN_clnt_proto_unpack_connect(HVN_msg_client_connect_t* data, \
                                  int scheme, \
                                  size_t len, \
                                  char* msg);
int HVN_clnt_proto_pack_connect_resp(HVN_msg_client_connect_resp_t* data, \
                                     int scheme, \
                                     size_t* len, \
                                     char** msg);
int HVN_clnt_proto_unpack_connect_resp(HVN_msg_client_connect_resp_t* data, \
                                       int scheme, \
                                       size_t len, \
                                       char* msg);

int HVN_proto_receive_connect_msg(int fd);
int HVN_proto_send_connect_resp_msg(int fd);
int HVN_proto_handle_connect_msg(int fd);

#endif /* __HVN__HAVEND_CLIENT_PROTOCOL_CONNECT_MSG_H_ */