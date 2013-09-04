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

#include <msgpack.h>

#include "log.h"
#include "common.h"

#include "pack.h"
#include "vote_msg.h"

/** The debug stream to write log messages to. */
extern FILE* HVN_debug_stream;

/** The log level to write messages for. */
extern HVN_loglevel HVN_debug_level;

int HVN_proto_pack_vote_msgpack(HVN_msg_vote_t* data, \
                                size_t* len, \
                                char** msg)
{
    msgpack_sbuffer sbuf;
    msgpack_sbuffer_init(&sbuf);

    msgpack_packer pk;
    msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

    msgpack_pack_array(&pk, 5);
    msgpack_pack_uint16(&pk, HVN_PROTO_MSG_TYPE_VOTE);
    msgpack_pack_uint16(&pk, data->action);

    // TODO: pack the rest of the struct.

    *msg = (char*) malloc(sizeof(char) * sbuf.size);
    memcpy(*msg, sbuf.data, sbuf.size);
    *len = sbuf.size;

    // FIXME: double free here?
    //msgpack_sbuffer_free(&sbuf);
    //msgpack_packer_free(&pk);

    return HVN_SUCCESS;
}

int HVN_proto_unpack_vote_msgpack(HVN_msg_vote_t* data, \
                                  size_t len, \
                                  char* msg)
{
    msgpack_unpacked unpacked;
    msgpack_unpacked_init(&unpacked);
    int16_t msg_type = 0;

    if(msgpack_unpack_next(&unpacked, msg, len, NULL)) {
        msgpack_object root = unpacked.data;

        if(root.type == MSGPACK_OBJECT_ARRAY && root.via.array.size == 6) {
            msg_type = root.via.array.ptr[0].via.u64;

            data->action = root.via.array.ptr[1].via.u64;
            data->mode = root.via.array.ptr[2].via.u64;
//FIXME:     data->time = root.via.array.ptr[3].via.array;

            data->key = (char*) malloc(sizeof(char) * \
                                       (root.via.array.ptr[4].via.raw.size + 1));
            //FIXME: SECURITY HOLE! check bounds below!
            memcpy(data->key, root.via.array.ptr[4].via.raw.ptr, \
                   root.via.array.ptr[4].via.raw.size);
            *(data->key + root.via.array.ptr[4].via.raw.size) = '\0';

            data->value = (char*) malloc(root.via.array.ptr[4].via.raw.size);
            //FIXME: SECURITY HOLE! check bounds below!
            memcpy(data->value, root.via.array.ptr[5].via.raw.ptr, \
                   root.via.array.ptr[5].via.raw.size);
            data->value_len = root.via.array.ptr[5].via.raw.size;
        }
    }

    if(msg_type != HVN_PROTO_MSG_TYPE_VOTE) {
        LOG(HVN_LOG_ERR, "Unexpected msg type when unpacking a vote message (%d).", msg_type);
        return HVN_ERROR;
    }

    msgpack_unpacked_destroy(&unpacked);
    return HVN_SUCCESS;
}

int HVN_proto_pack_vote_resp_msgpack(HVN_msg_vote_resp_t* data, \
                                     size_t* len, \
                                     char** msg)
{
    msgpack_sbuffer sbuf;
    msgpack_sbuffer_init(&sbuf);

    msgpack_packer pck;
    msgpack_packer_init(&pck, &sbuf, msgpack_sbuffer_write);
    msgpack_pack_array(&pck, 2);

    msgpack_pack_uint8(&pck, data->success);
    msgpack_pack_uint8(&pck, data->err_code);

    *len = sbuf.size;
    *msg = (char*) malloc(sizeof(char) * sbuf.size);
    memcpy(*msg, sbuf.data, sbuf.size);

    msgpack_sbuffer_destroy(&sbuf);
    return HVN_SUCCESS;
}

int HVN_proto_unpack_vote_resp_msgpack(HVN_msg_vote_resp_t* data, \
        size_t len, \
        char* msg)
{
    HVN_INTENTIONALLY_UNUSED_VARIABLE(data);
    HVN_INTENTIONALLY_UNUSED_VARIABLE(len);
    HVN_INTENTIONALLY_UNUSED_VARIABLE(msg);

    return HVN_ERROR;
}

int HVN_proto_pack_vote(HVN_msg_vote_t* data, \
                        int scheme, \
                        size_t* len, \
                        char** msg)
{
    int result;

    switch(scheme) {
        case HVN_PROTO_PACK_TYPE_MSGPACK:
            result = HVN_proto_pack_vote_msgpack(data, len, msg);
            break;
        default:
            LOG(HVN_LOG_WARN, "Pack scheme `%d' not recognized.", scheme);
            result = HVN_ERROR;
    }

    return result;
}

int HVN_proto_unpack_vote(HVN_msg_vote_t* data, \
                          int scheme, \
                          size_t len, \
                          char* msg)
{
    int result;

    switch(scheme) {
        case HVN_PROTO_PACK_TYPE_MSGPACK:
            result = HVN_proto_unpack_vote_msgpack(data, len, msg);
            break;
        default:
            LOG(HVN_LOG_WARN, "Unpack scheme `%d' not recognized.", scheme);
            result = HVN_ERROR;
    }

    return result;
}

int HVN_proto_pack_vote_resp(HVN_msg_vote_resp_t* data, \
                             int scheme, \
                             size_t* len, \
                             char** msg)
{
    int result;

    switch(scheme) {
        case HVN_PROTO_PACK_TYPE_MSGPACK:
            result = HVN_proto_pack_vote_resp_msgpack(data, len, msg);
            break;
        default:
            LOG(HVN_LOG_WARN, "Pack scheme `%d' not recognized.", scheme);
            result = HVN_ERROR;
    }

    return result;
}

int HVN_proto_unpack_vote_resp(HVN_msg_vote_resp_t* data, \
                               int scheme, \
                               size_t len, \
                               char* msg)
{
    int result;

    switch(scheme) {
        case HVN_PROTO_PACK_TYPE_MSGPACK:
            result = HVN_proto_unpack_vote_resp_msgpack(data, len, msg);
            break;
        default:
            LOG(HVN_LOG_WARN, "Unpack scheme `%d' not recognized.", scheme);
            result = HVN_ERROR;
    }

    return result;
}

int HVN_receive_vote_msg(int fd, \
                         HVN_msg_vote_t* vote_msg_data)
{
    size_t len = 0;
    char* msg;

    if(HVN_msgpack_fdread(fd, &len, &msg) != HVN_SUCCESS) {
        LOG(HVN_LOG_ERR, "Failed to read a vote message from the socket.");
        return HVN_ERROR;
    }

    if(HVN_proto_unpack(HVN_PROTO_MSG_TYPE_VOTE, \
                        HVN_PROTO_PACK_TYPE_MSGPACK, \
                        vote_msg_data, len, msg) != HVN_SUCCESS) {
        LOG(HVN_LOG_ERR, "Failed to unpack a vote message.");
        return HVN_ERROR;
    }

    free(msg);
    return HVN_SUCCESS;
}

int HVN_proto_send_vote_resp_msg(int fd)
{
    HVN_msg_vote_resp_t vote_resp_msg_data;
    size_t len = 0;
    char* msg;

    if(HVN_proto_pack(HVN_PROTO_MSG_TYPE_VOTE_R, \
                      HVN_PROTO_PACK_TYPE_MSGPACK, \
                      &vote_resp_msg_data, &len, &msg) != HVN_SUCCESS) {
        LOG(HVN_LOG_ERR, "Failed to pack a vote message response.");
        return HVN_ERROR;
    }

    if(HVN_msgpack_fdwrite(fd, len, msg) != HVN_SUCCESS) {
        LOG(HVN_LOG_ERR, "Failed to write a vote message to the socket.");
        return HVN_ERROR;
    }

    free(msg);
    return HVN_SUCCESS;
}

void HVN_proto_print_vote_msg(HVN_msg_vote_t* data)
{
    //TODO
}

/* EOF */
