/**
  ******************************************************************************
  * @file           : PG_SQLAPI
  * @brief          : Class PG_SQLAPI define use Postgresql DB API function 
  ******************************************************************************
  * Made in GreenOasis  
  * https://github.com/jungkyeong/linux_server_cms_v1
  * CopyRigth MIT License
  ******************************************************************************
  * Release History
  * branch name, working description, time
  * version_002: define add version  2025-02-19
  ******************************************************************************
  */

  #include "PG_SQLAPI.h"

/**
* @brief sql maker create
* @param table_name table name
* @param columns insert target columns
* @param values insert columns value
* @return SQL command ex) INSERT INTO test_table (test_string, test_time, test_time) VALUES ($1, $2, $3);
*/  
std::string PgSQLAPI::sql_row_insert(const std::string &table_name, 
    const std::vector<std::string> &columns, 
    const std::vector<std::string> &values){
    
        // create SQL command
        std::string sql = "INSERT INTO " + table_name + " (";
        
        for (size_t i = 0; i < columns.size(); i++) {
            sql += columns[i]; // add label_name
            if (i < columns.size() - 1) sql += ", "; // if not end add ","
        }
        sql += ") VALUES (";
    
        for (size_t i = 0; i < values.size(); i++) {
            sql += "$" + std::to_string(i + 1); // add $x
            if (i < values.size() - 1) sql += ", "; // if not end add ","
        }
        sql += ");";

        return sql;
    }

/**
* @brief sql maker remove
* @param table_name table name
* @param columns remove target columns
* @param values remove columns value
* @return SQL command ex) DELETE FROM table_name WHERE test_string = $1 AND test_string = $2;
*/
    std::string PgSQLAPI::sql_row_remove(const std::string &table_name, 
        const std::vector<std::string> &columns, 
        const std::vector<std::string> &values){
        
        std::string sql = "DELETE FROM " + table_name + " WHERE ";

        for(size_t i = 0; i < columns.size(); i++){
            sql += columns[i] + " = $" + std::to_string(i + 1);
            if (i < columns.size() - 1) {
                sql += " AND "; // if not end add AND 
            }
        }
        sql += ";";
        return sql;
    }

/**
* @brief sql maker modify
* @param table_name table name
* @param switch_target_column switch target columns
* @param switch_target_value switch target value
* @param columns modify target columns
* @param values modify columns value
* @return SQL command ex) UPDATE table_name SET test_string = $1, test_string = $2 WHERE switch_target_column =$3;
*/
    std::string PgSQLAPI::sql_row_modify(const std::string &table_name, 
        const std::string &switch_target_column, const std::string &switch_target_value,
        const std::vector<std::string> &columns, 
        const std::vector<std::string> &values){

            std::string sql = "UPDATE " + table_name + " SET ";

            for (size_t i = 0; i < columns.size(); i++) {
                sql += columns[i] + " = $" + std::to_string(i + 1);
                if (i < columns.size() - 1) {
                    sql += ", ";
                }
            }
        
            sql += " WHERE " + switch_target_column + " = $" + std::to_string(columns.size() + 1) + ";";
        
            return sql;       
    }

 /**
* @brief sql maker query
* @param table_name table name
* @param columns remove target columns
* @param values remove columns value
* @param type_arr wild card handler string:1, int or timestamp: 0
* @param count number of rows to fetch, if not search: 0
* @param offset starting row number, if not search: 0
* @return SQL command ex) SELECT * FROM test_table WHERE test_string LIKE $1 AND test_int = $2 LIMIT $3 OFFSET $4;
*/
std::string PgSQLAPI::sql_row_query(const std::string &table_name, 
    const std::vector<std::string> &columns, 
    const std::vector<std::string> &values, const std::vector<int> &type_arr, int count, int offset){

    std::string sql = "SELECT * FROM " + table_name + " WHERE ";
    
    for (size_t i = 0; i < columns.size(); i++) {
        if(type_arr[i]==1){
            sql += columns[i] + " LIKE $" + std::to_string(i + 1); // string -> whild card search
        }
        else{
            sql += columns[i] + " = $" + std::to_string(i + 1); // not string(int, timestamp)
        }
        if (i < columns.size() - 1) {
            sql += " AND ";
        }
    }
    if(count > 0){ // add count
        sql += " LIMIT $" + std::to_string(columns.size() + 1);
    }
    if(offset > 0){ // add offset
        sql += " OFFSET $" + std::to_string(columns.size() + 2);
    }
    
    sql += ";";
    return sql;    
}