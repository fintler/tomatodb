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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmd.h"
#include "common.h"
#include "task/task.h"

#include "cmd_help.h"

void TDB_cmd_task(char* cmd)
{
    if(strncmp(cmd, "help", 4) == 0) {
        TDB_cmd_help(cmd);
    } else if(strncmp(cmd, "exit", 4) == 0) {
        exit(EXIT_SUCCESS); 
    } else {
        printf("Unknown command. Try 'help'.\n");
    }
}

/* EOF */
