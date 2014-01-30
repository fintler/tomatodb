#ifndef __HVN__COMMON_PACK_PACK_H_
#define __HVN__COMMON_PACK_PACK_H_

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

/* Overall protocol version. */
#define HVN_PROTOCOL_VERSION            0x01
#define HVN_PROTOCOL_MAGIC              0xDECAFBAD

/* Message packing schemes. */
#define HVN_PROTO_PACK_TYPE_RAW         0x01
#define HVN_PROTO_PACK_TYPE_MSGPACK     0x03

/* Client request msg types. */
#define HVN_PROTO_MSG_TYPE_APPEND       0x01
#define HVN_PROTO_MSG_TYPE_CONNECT      0x03
#define HVN_PROTO_MSG_TYPE_CONTROL      0x02
#define HVN_PROTO_MSG_TYPE_DATA         0x06
#define HVN_PROTO_MSG_TYPE_DISCOVER     0x07
#define HVN_PROTO_MSG_TYPE_HEARTBEAT    0x05
#define HVN_PROTO_MSG_TYPE_VOTE         0x04

/* Server response msg types. */
#define HVN_PROTO_MSG_TYPE_APPEND_R     0x0C
#define HVN_PROTO_MSG_TYPE_CONNECT_R    0x0D
#define HVN_PROTO_MSG_TYPE_CONTROL_R    0x0F
#define HVN_PROTO_MSG_TYPE_DATA_R       0x0E
#define HVN_PROTO_MSG_TYPE_DISCOVER_R   0x0A
#define HVN_PROTO_MSG_TYPE_HEARTBEAT_R  0x0B
#define HVN_PROTO_MSG_TYPE_VOTE_R       0x09

#include "msgpack_helper.h"

int HVN_proto_pack(int type, \
                   int scheme, \
                   void* msg_struct, \
                   size_t* len, \
                   char** msg);

int HVN_proto_unpack(int type, \
                     int scheme, \
                     void* msg_struct, \
                     size_t len, \
                     char* msg);

#endif /* __HVN__COMMON_PACK_PACK_H_ */