#ifndef __HVN__HAVEND_HOOK_H
#define __HVN__HAVEND_HOOK_H

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

#include <uuid/uuid.h>

#include "log.h"
#include "task/task.h"

#define HVN_HOOK_STACK_SIZE  32768

#define HVN_HOOK_ALT_NK  3

#define HVN_HOOK_ALT_APPEND_KEY  0
#define HVN_HOOK_ALT_EXIT_KEY    1
#define HVN_HOOK_ALT_VOTE_KEY    2

#define HVN_HOOK_APPEND_CHANNEL_BACKLOG  10
#define HVN_HOOK_VOTE_CHANNEL_BACKLOG  10

typedef struct HVN_hook_t {
    uuid_t remote_uuid;

    int remote_port;
    char* remote_address;

    int fd_append;
    int fd_vote;

    Channel* append_chan;
    Channel* vote_chan;
    Channel* exit_chan;
} HVN_hook_t;

void HVN_hook_task(HVN_hook_t* hook);
int HVN_hook_prepare(char* address, int port, int* fd, uint32_t mode);

int HVN_hook_init(HVN_hook_t** hook, uuid_t uuid, int port, char* address);
void HVN_hook_free(HVN_hook_t* hook);

#endif /* __HVN__HAVEND_HOOK_H */