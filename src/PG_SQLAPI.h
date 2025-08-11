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

  #ifndef __PG_SQL_API_HPP
  #define __PG_SQL_API_HPP
  
  #include <iostream>
  #include <ctime>
  #include <iomanip>
  #include <sstream>
  #include <string>
  #include <vector>

  // Debug print
  #ifdef DEBUG
  #define DBG_PRINT(fmt, ...) printf("[DEBUG] " fmt, ##__VA_ARGS__)
  #else
  #define DBG_PRINT(fmt, ...)
  #endif
  
  class PgSQLAPI {
  private:
  
  public:

      /**
     * @brief sql maker create
     * @param table_name table name
     * @param columns insert target columns
     * @param values insert columns value
     * @return SQL command ex) INSERT INTO test_table (test_string, test_time, test_time) VALUES ($1, $2, $3);
     */
    std::string sql_row_insert(const std::string &table_name, 
        const std::vector<std::string> &columns, 
        const std::vector<std::string> &values);

      /**
     * @brief sql maker remove
     * @param table_name table name
     * @param columns remove target columns
     * @param values remove columns value
     * @return SQL command ex) DELETE FROM table_name WHERE test_string = $1;
     */
    std::string sql_row_remove(const std::string &table_name, 
      const std::vector<std::string> &columns, 
      const std::vector<std::string> &values);

      /**
     * @brief sql maker modify
     * @param table_name table name
     * @param switch_target_column switch target columns
     * @param switch_target_value switch target value
     * @param columns modify target columns
     * @param values modify columns value
     * @return SQL command ex) UPDATE table_name SET test_string = $1, test_string = $2 WHERE switch_target_column =$3;
     */
    std::string sql_row_modify(const std::string &table_name, 
      const std::string &switch_target_column, const std::string &switch_target_value,
      const std::vector<std::string> &columns, 
      const std::vector<std::string> &values);

      /**
     * @brief sql maker query
     * @param table_name table name
     * @param columns remove target columns
     * @param values remove columns value
     * @return SQL command ex) SELECT * FROM test_table WHERE test_string LIKE $1 AND test_int = $2;
     */
    std::string sql_row_query(const std::string &table_name, 
      const std::vector<std::string> &columns, 
      const std::vector<std::string> &values, const std::vector<int> &type_arr);
  
  };
  
  #endif /* __PG_SQL_API_HPP */