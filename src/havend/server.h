#ifndef __HAVEN_SERVER_H
#define __HAVEN_SERVER_H

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
 */

#include "havend.h"

#include <stdio.h>
#include <uuid/uuid.h>

#define INITIAL_SERVER_QUEUE_SIZE (100)
#define HAVEN_SERVER_STACK_SIZE (32768)

typedef struct HAVEN_server_t {
    HAVEN_ctx_t* ctx;
    HAVEN_db_t* consensus_db;
    HAVEN_xarray_t* consensus_log;
    char* listen_addr;
    int listen_port;
    int listen_fd;
    uuid_t uuid;
} HAVEN_server_t;

int HAVEN_init_server_queue(HAVEN_ctx_t* ctx);
int HAVEN_server_task(HAVEN_server_t* server);
int HAVEN_init_server_loop(HAVEN_ctx_t* ctx);

#endif /* __HAVEN_SERVER_H */
