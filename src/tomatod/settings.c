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

#include "settings.h"
#include "log.h"
#include "common.h"

#include <unistd.h>
#include <uuid/uuid.h>
#include <stdlib.h>
#include <string.h>

/** The debug stream to write log messages to. */
extern FILE* TDB_debug_stream;

/** The log level to write messages for. */
extern TDB_loglevel TDB_debug_level;

int TDB_set_process_uuid(TDB_ctx_t* ctx)
{
    int result;
    char* uuid_file_path = (char*) malloc(sizeof(char) * _POSIX_PATH_MAX);

    sprintf(uuid_file_path, "%s%s%s", \
            TDB_BASE_STATE_DIR, TDB_SETTINGS_DB_PREFIX, \
            PROCESS_UUID_SETTINGS_PATH);

    if(access(uuid_file_path, F_OK) != -1) {
        result = TDB_get_uuid_from_file(ctx, uuid_file_path);
    }
    else {
        result = TDB_configure_new_process_uuid(ctx, uuid_file_path);
    }

    free(uuid_file_path);
    return result;
}

int TDB_get_uuid_from_file(TDB_ctx_t* ctx, char* uuid_file_path)
{
    char* buf = (char*) malloc(sizeof(char) * UUID_STR_LEN);
    FILE* fh = fopen(uuid_file_path, "rd");
    char* uuid_string = (char*) malloc(sizeof(char) * UUID_STR_LEN);

    if(fh == NULL) {
        LOG(TDB_LOG_ERR, "Could not open process UUID file at `%s'.", uuid_file_path);
        return TDB_ERROR;
    }

    if(fread(buf, 1, sizeof(char) * UUID_STR_LEN, fh) != UUID_STR_LEN) {
        LOG(TDB_LOG_ERR, "Failed to read a complete process UUID file at `%s'. " \
            "The process UUID file may be corrupt.", uuid_file_path);
        return TDB_ERROR;
    }

    if(ferror(fh) != 0) {
        LOG(TDB_LOG_ERR, "An error occurred while reading the process UUID file.");
        return TDB_ERROR;
    }

    if(uuid_parse(buf, ctx->process_uuid) != 0) {
        LOG(TDB_LOG_ERR, \
            "An error occurred while parsing the process UUID file at `%s' ",
            uuid_file_path);
        LOG(TDB_LOG_ERR, \
            "The file may be corrupt or has been incorrectly modified.");
        return TDB_ERROR;
    }

    uuid_unparse(ctx->process_uuid, uuid_string);
    //LOG(TDB_LOG_INFO, "Using existing UUID of `%s' for the process identifier.", uuid_string);

    fclose(fh);
    free(buf);
    free(uuid_string);

    return TDB_SUCCESS;
}

int TDB_generate_uuid(uuid_t* uuid)
{
    if(uuid_generate_time_safe(*uuid) != 0)  {
        LOG(TDB_LOG_ERR, "Could not safely generate a new UUID. " \
            "Please ensure that uuidd(8) is installed and working.");
        return TDB_ERROR;
    }

    return TDB_SUCCESS;
}

int TDB_configure_new_process_uuid(TDB_ctx_t* ctx, char* uuid_file_path)
{
    FILE* fh = NULL;
    int result = TDB_generate_uuid(&ctx->process_uuid);
    char* uuid_string = (char*) malloc(sizeof(char) * UUID_STR_LEN);
    char* uuid_dir_path = (char*) malloc(sizeof(char) * _POSIX_PATH_MAX);

    sprintf(uuid_dir_path, "%s%s", \
            TDB_BASE_STATE_DIR, TDB_SETTINGS_DB_PREFIX);

    if(TDB_ensure_directory_exists(uuid_dir_path) != TDB_SUCCESS) {
        LOG(TDB_LOG_ERR, "Failed to create directory structure when preparing the process UUID file.");
        return TDB_ERROR;
    }

    fh = fopen(uuid_file_path, "w");

    if(fh == NULL) {
        LOG(TDB_LOG_ERR, "Could not open the process UUID file at `%s'.", \
            uuid_file_path);
        return TDB_ERROR;
    }

    if(result != TDB_SUCCESS)  {
        if(unlink(uuid_file_path) == 0) {
            LOG(TDB_LOG_ERR, "Removed incomplete process UUID file at `%s'.",
                uuid_file_path);
        }
        else {
            LOG(TDB_LOG_ERR, "Failed to remove incomplete process UUID file at `%s'.",
                uuid_file_path);
        }

        return TDB_ERROR;
    }

    uuid_unparse(ctx->process_uuid, uuid_string);
    fwrite(uuid_string, 1, sizeof(char) * UUID_STR_LEN, fh);

    if(ferror(fh) != 0) {
        LOG(TDB_LOG_ERR, "An error occurred while writing the process UUID file.");
        return TDB_ERROR;
    }

    LOG(TDB_LOG_INFO, "Generated new process UUID of `%s'.", uuid_string);

    fclose(fh);
    free(uuid_string);
    return TDB_SUCCESS;
}

int TDB_prepare_settings_db(TDB_ctx_t* ctx)
{
    char* settings_db_path = (char*) malloc(sizeof(char) * _POSIX_PATH_MAX);
    char* uuid_string = (char*) malloc(sizeof(char) * UUID_STR_LEN);
    int offset, result;

    offset = sprintf(settings_db_path, "%s%s", \
                     TDB_BASE_STATE_DIR, TDB_SETTINGS_DB_PREFIX);

    if(TDB_ensure_directory_exists(settings_db_path) != TDB_SUCCESS) {
        LOG(TDB_LOG_ERR, "Failed to create directory structure when preparing the settings DB.");
        return TDB_ERROR;
    }

    uuid_unparse(ctx->process_uuid, uuid_string);
    sprintf(settings_db_path + offset, "/%s", uuid_string);
    result = TDB_db_init(&ctx->settings_db, settings_db_path);

    free(settings_db_path);
    free(uuid_string);

    return result;
}

/* EOF */
