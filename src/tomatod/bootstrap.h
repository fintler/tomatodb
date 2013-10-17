#ifndef __HVN__HAVEND_BOOTSTRAP_H
#define __HVN__HAVEND_BOOTSTRAP_H

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

#include "replica.h"

int HVN_bootstrap_follower(HVN_replica_t* replica, \
                           HVN_ctx_t* ctx, \
                           uuid_t* uuid);

int HVN_bootstrap_replica_db(HVN_replica_t* replica);
int HVN_bootstrap_replicas_from_disk(HVN_ctx_t* ctx);

#endif /* __HVN__HAVEND_BOOTSTRAP_H */