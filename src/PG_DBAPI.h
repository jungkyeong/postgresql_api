/**
  ******************************************************************************
  * @file           : PG_DBAPI
  * @brief          : Class PG_DBAPI define use Postgresql DB API function 
  ******************************************************************************
  * Made in GreenOasis  
  * https://github.com/jungkyeong/linux_server_cms_v1
  * CopyRigth MIT License
  ******************************************************************************
  * Release History
  * branch name, working description, time
  * version_001: define add version  2025-02-19
  ******************************************************************************
  */

#ifndef PG_DBAPI_H
#define PG_DBAPI_H

#include <libpq-fe.h>
#include <vector>
#include <string>
#include <cstring>
#include "../lib/json/json.h"
#include "Util.h"
#include "Define.h"
#include "PG_SQLAPI.h"

// Debug print
#ifdef DEBUG
#define DBG_PRINT(fmt, ...) printf("[DEBUG] " fmt, ##__VA_ARGS__)
#else
#define DBG_PRINT(fmt, ...)
#endif

class PgDBAPI {
public:

    /**
     * @brief DB Class Open
     * @param host DB Server IP
     * @param port DB port
     * @param dbname Database name
     * @param user Database user id
     * @param password Database user password
     * @return
     */
    bool connect(const std::string host, const std::string port, const std::string dbname,
                 const std::string user, const std::string password);

    /**
     * @brief DB disConnect
     * @param
     * @return
     */
    void disconnect();

    /**
     * @brief DB row insert
     * @param table_name DB insert target table name
     * @param columns add label name
     * @param values add value
     * @return Success 0, Fail else
     */  
    int db_row_insert(const std::string &table_name, const std::vector<std::string> &columns,
      const std::vector<std::string> &values);
    
    /**
     * @brief DB row remove
     * @param table_name DB remove target table name
     * @param columns remove label name
     * @param values remove value
     * @return Success 0, Fail else
     */  
    int db_row_remove(const std::string &table_name, const std::vector<std::string> &columns,
     const std::vector<std::string> &values);

    /**
     * @brief DB row modify
     * @param table_name table name
     * @param switch_target_column switch target columns
     * @param switch_target_value switch target value
     * @param columns modify target columns
     * @param values modify columns value
     * @return Success 0, Fail else
     */
    int db_row_modify(const std::string &table_name, 
      const std::string &switch_target_column, const std::string &switch_target_value,
      const std::vector<std::string> &columns, 
      const std::vector<std::string> &values);

    /**
     * @brief DB row query
     * @param table_name DB query target table name
     * @param columns query label name
     * @param values query value
     * @param type_arr whild card search type, use: 1, unused: 0
     * @param recv_buffer query output buffer
     * @param max_buf_size max_buffer_size
     * @param count number of rows to fetch, if not search: 0
     * @param offset starting row number, if not search: 0
     * @param date_label date check label, "" not query
     * @param start_date start date, "" not query
     * @param end_date end date,  "" not query
     * @return Success buffer size, Fail -1
     */  
    int db_row_query(const std::string &table_name, const std::vector<std::string> &columns,
      const std::vector<std::string> &values, const std::vector<int> &type_arr, char* recv_buf, size_t max_buf_size, int count, int offset,
      const std::string &date_label, const std::string &start_date, const std::string &end_date);

    /**
     * @brief read json file insert db data
     * @param Jsonfile input file root
     * @return Success 0, Fail else
     */
    int db_json_insert_rows(std::string Jsonfile);

    /**
     * @brief read json file modify db data
     * @param Jsonfile input file root
     * @return Success 0, Fail else
     */
    int db_json_modify_rows(std::string Jsonfile);

    /**
     * @brief read json file remove db data
     * @param Jsonfile input file root
     * @return Success 0, Fail else
     */
    int db_json_remove_rows(std::string Jsonfile);

    /**
     * @brief read json file search db data
     * @param Jsonfile input file root
     * @param recv_buf response message
     * @param max_buf_size buffer max length
     * @return Success Data len, Fail else
     */
    int db_json_search_rows(std::string Jsonfile, char* recv_buf, size_t max_buf_size);

private:
    PgSQLAPI pgsql;
    PGconn *conn;
    bool connected;
    std::string errorMessage;
};

#endif // PG_DBAPI_H