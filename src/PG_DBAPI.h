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
#include "PG_SQLAPI.h"

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
    PgDBAPI(const std::string &host, const std::string &port, const std::string &dbname,
                 const std::string &user, const std::string &password);
    /**
     * @brief DB Class Close
     * @param
     * @return
     */
    ~PgDBAPI();

    /**
     * @brief DB Connect
     * @param
     * @return boolean
     */
    bool connect();

    /**
     * @brief DB disConnect
     * @param
     * @return
     */
    void disconnect();

    /**
     * @brief DB Connect check
     * @param
     * @return boolean
     */
    bool isConnected() const;

    /**
     * @brief DB errormessage
     * @param
     * @return DB error message
     */  
    const std::string &getErrorMessage() const;

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
     * @return Success buffer size, Fail -1
     */  
    int db_row_query(const std::string &table_name, const std::vector<std::string> &columns,
      const std::vector<std::string> &values, const std::vector<int> &type_arr, char* recv_buf, size_t max_buf_size);

private:
    PgSQLAPI pgsql;  
    std::string conninfo;
    PGconn *conn;
    bool connected;
    std::string errorMessage;
};

#endif // PG_DBAPI_H