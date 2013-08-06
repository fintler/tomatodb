#ifndef __HAVEN_COMMON_XARRAY_H
#define __HAVEN_COMMON_XARRAY_H

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

#include <stddef.h>
#include <stdint.h>

typedef struct HAVEN_xarray_t {
    size_t size;
    intptr_t** data;
    int index;
} HAVEN_xarray_t;

int HAVEN_xarray_init(HAVEN_xarray_t** array, size_t initial_size);
int HAVEN_xarray_free(HAVEN_xarray_t* array);
int HAVEN_xarray_realloc(HAVEN_xarray_t* array, size_t new_size);
int HAVEN_xarray_push(HAVEN_xarray_t* array, void* data);
int HAVEN_xarray_pop(HAVEN_xarray_t* array, void** data);
void* HAVEN_xarray_peek(HAVEN_xarray_t* array);

#endif /* __HAVEN_COMMON_XARRAY_H */