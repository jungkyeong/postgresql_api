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
#include "PG_DBAPI.h"
#include <iostream>

/**
 * @brief DB Class Open
 * @param host DB Server IP
 * @param port DB port
 * @param dbname Database name
 * @param user Database user id
 * @param password Database user password
 * @return
 */
bool PgDBAPI::connect(const std::string host, const std::string port, const std::string dbname,
                 const std::string user, const std::string password) {

    std::string conninfo = "host=" + host + " port=" + port + " dbname=" + dbname + " user=" + user + " password=" + password;
    conn = PQconnectdb(conninfo.c_str());

    if (PQstatus(conn) != CONNECTION_OK) {
        errorMessage = PQerrorMessage(conn);

        DBG_PRINT("PostgreSQL Connected Fail %s \n", errorMessage.c_str());
        connected = false;
        return false;
    }
    DBG_PRINT("PostgreSQL Connected! \n");
    connected = true;
    return true;
}

/**
 * @brief DB disConnect
 * @param
 * @return
 */
void PgDBAPI::disconnect() {
    if (connected) {
        PQfinish(conn);
        connected = false;
        DBG_PRINT("PostgreSQL Disconnect! \n");
    }
}

/**
 * @brief DB row insert
 * @param table_name DB insert target table name
 * @param columns add label name
 * @param values add value
 * @return Success 0, Fail else
*/  
int PgDBAPI::db_row_insert(const std::string &table_name, const std::vector<std::string> &columns,
    const std::vector<std::string> &values){

    // make sql command
    std::string sql = pgsql.sql_row_insert(table_name, columns, values);

    // vector array casting change const char*
    std::vector<const char*> paramValues;
    for (const auto &val : values) {
        paramValues.push_back(val.c_str());
    }

    // not binary mode only use text
    PGresult *res = PQexecParams(conn, sql.c_str(), paramValues.size(), nullptr, paramValues.data(), nullptr, nullptr, 0);

    // status check
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Query failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        return -1;
    }
    std::cout << "Create Insert Rows" << std::endl;

    PQclear(res);
    return 0;
}

/**
 * @brief DB row remove
 * @param table_name DB remove target table name
 * @param columns remove label name
 * @param values remove value
 * @return Success 0, Fail else
*/
int PgDBAPI::db_row_remove(const std::string &table_name, const std::vector<std::string> &columns,
    const std::vector<std::string> &values){

    // make sql command
    std::string sql = pgsql.sql_row_remove(table_name, columns, values);

    // vector array casting change const char*
    std::vector<const char*> paramValues;
    for (const auto &val : values) {
        paramValues.push_back(val.c_str());
    }

    // not binary mode only use text
    PGresult *res = PQexecParams(conn, sql.c_str(), paramValues.size(), nullptr, paramValues.data(), nullptr, nullptr, 0);

    // status check
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Query failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        return -1;
    }
    std::cout << "Delete Rows" << std::endl;

    PQclear(res);
    return 0;
}

/**
 * @brief DB row modify
 * @param table_name table name
 * @param switch_target_column switch target columns
 * @param switch_target_value switch target value
 * @param columns modify target columns
 * @param values modify columns value
 * @return Success 0, Fail else
 */
int PgDBAPI::db_row_modify(const std::string &table_name, 
    const std::string &switch_target_column, const std::string &switch_target_value,
    const std::vector<std::string> &columns, 
    const std::vector<std::string> &values){

    // make sql command
    std::string sql = pgsql.sql_row_modify(table_name, switch_target_column, switch_target_value, columns, values);

    // vector array casting change const char*
    std::vector<const char*> paramValues;
    for (const auto &val : values) {
        paramValues.push_back(val.c_str());
    }

    // add switch target
    paramValues.push_back(switch_target_value.c_str());

    // not binary mode only use text
    PGresult *res = PQexecParams(conn, sql.c_str(), paramValues.size(), nullptr, paramValues.data(), nullptr, nullptr, 0);

    // status check
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Query failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        return -1;
    }
    std::cout << "Modify Rows" << std::endl;
    
    PQclear(res);
    return 0;
}

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
 * @param end_date end date, "" not query
 * @return Success buffer size, Fail -1
 */  
int PgDBAPI::db_row_query(const std::string &table_name, const std::vector<std::string> &columns,
    const std::vector<std::string> &values, const std::vector<int> &type_arr, char* recv_buf, size_t max_buf_size, int count, int offset,
    const std::string &date_label, const std::string &start_date, const std::string &end_date){

    // make sql command
    std::string sql = pgsql.sql_row_query(table_name, columns, values, type_arr, count, offset, date_label, start_date, end_date);

    // vector array casting change const char*
    std::vector<const char*> paramValues;
    for (const auto &val : values) {
        paramValues.push_back(val.c_str());
    }
    if(start_date != "" && end_date != ""){
        paramValues.push_back(start_date.c_str());
        paramValues.push_back(end_date.c_str());
    }
    if(count > 0){
        paramValues.push_back(std::to_string(count).c_str());
    }
    if(offset > 0){
        paramValues.push_back(std::to_string(offset).c_str());
    }

    // not binary mode only use text
    PGresult *res = PQexecParams(conn, sql.c_str(), paramValues.size(), nullptr, paramValues.data(), nullptr, nullptr, 0);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "Query failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        return -1;
    }

    // res get
    int rows = PQntuples(res);
    int cols = PQnfields(res);

    // make json string format
    std::string output = "[";
    
    for (int i = 0; i < rows; i++) {
        output += "{";
        for (int j = 0; j < cols; j++) {
            output += "\"" + std::string(PQfname(res, j)) + "\": ";
            output += "\"" + std::string(PQgetvalue(res, i, j)) + "\"";
            if (j < cols - 1) output += ", ";
        }
        output += "}";
        if (i < rows - 1) output += ", ";
    }

    output += "]";

    strncpy(recv_buf, output.c_str(), max_buf_size - 1); // copy buffer
    recv_buf[max_buf_size - 1] = '\0';  // add null

    PQclear(res);
    return output.size();
}

/**
 * @brief read json file insert db data
 * @param Jsonfile input file root
 * @return Success 0, Fail else
 */
int PgDBAPI::db_json_insert_rows(std::string Jsonfile){

    // Parsed Json
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(Jsonfile, root)) {
        DBG_PRINT("JWT Payload Parse fail \n");
        return FAIL;
    }

    std::string table_name = root["tablename"].asString();

    std::vector<std::string> columns;
    std::vector<std::string> values;

    // Check info Key and this key Object?
    if(root.isMember("info") && root["info"].isObject()){
        Json::Value info = root["info"];
        Json::Value::Members members = info.getMemberNames();

        // key and value push back to vector
        for (const auto& member : members) {
            columns.push_back(member);
            Json::Value value = info[member];
            values.push_back(value.asString());
        }
    } 
    else {
        DBG_PRINT("info object not found or invalid \n");
        return FAIL;
    }
    if(!columns.empty() && !values.empty()){
        int status = db_row_insert(table_name, columns, values);
        if(status != SUCCESS){
            DBG_PRINT("Insert DB Fail \n");
            return FAIL;
        } else {
            DBG_PRINT("Insert DB Success \n");
            return SUCCESS;
        }
    }
    DBG_PRINT("Insert Rows Empty \n");
    return FAIL;
}

/**
 * @brief read json file modify db data
 * @param Jsonfile input file root
 * @return Success 0, Fail else
 */
int PgDBAPI::db_json_modify_rows(std::string Jsonfile){

    // Parsed Json
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(Jsonfile, root)) {
        DBG_PRINT("JWT Payload Parse fail \n");
        return FAIL;
    }

    std::string table_name = root["tablename"].asString();
    std::string switch_key = root["switch_target_key"].asString();
    std::string switch_value = root["switch_target_value"].asString();

    std::vector<std::string> columns;
    std::vector<std::string> values;

    // Check info Key and this key Object?
    if(root.isMember("info") && root["info"].isObject()){
        Json::Value info = root["info"];
        Json::Value::Members members = info.getMemberNames();

        // key and value push back to vector
        for (const auto& member : members) {
            columns.push_back(member);
            Json::Value value = info[member];
            values.push_back(value.asString());
        }
    } 
    else {
        DBG_PRINT("info object not found or invalid \n");
        return FAIL;
    }
    if(!columns.empty() && !values.empty()){
        int status = db_row_modify(table_name, switch_key, switch_value, columns, values);
        if(status != SUCCESS){
            DBG_PRINT("Modify DB Fail \n");
            return FAIL;
        } else {
            DBG_PRINT("Modify DB Success \n");
            return SUCCESS;
        }
    }
    DBG_PRINT("Modify Rows Empty \n");
    return FAIL;
}

/**
 * @brief read json file remove db data
 * @param Jsonfile input file root
 * @return Success 0, Fail else
 */
int PgDBAPI::db_json_remove_rows(std::string Jsonfile){

    // Parsed Json
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(Jsonfile, root)) {
        DBG_PRINT("JWT Payload Parse fail \n");
        return FAIL;
    }

    std::string table_name = root["tablename"].asString();

    std::vector<std::string> columns;
    std::vector<std::string> values;

    // Check info Key and this key Object?
    if(root.isMember("info") && root["info"].isObject()){
        Json::Value info = root["info"];
        Json::Value::Members members = info.getMemberNames();

        // key and value push back to vector
        for (const auto& member : members) {
            columns.push_back(member);
            Json::Value value = info[member];
            values.push_back(value.asString());
        }
    } 
    else {
        DBG_PRINT("info object not found or invalid \n");
        return FAIL;
    }
    if(!columns.empty() && !values.empty()){
        int status = db_row_remove(table_name, columns, values);
        if(status != SUCCESS){
            DBG_PRINT("Remove DB Fail \n");
            return FAIL;
        } else {
            DBG_PRINT("Remove DB Success \n");
            return SUCCESS;
        }
    }
    DBG_PRINT("Remove Rows Empty \n");
    return FAIL;
}

/**
 * @brief read json file search db data
 * @param Jsonfile input file root
 * @param recv_buf response message
 * @param max_buf_size buffer max length
 * @return Success Data len, Fail else
 */
int PgDBAPI::db_json_search_rows(std::string Jsonfile, char* recv_buf, size_t max_buf_size){

    // Parsed Json
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(Jsonfile, root)) {
        DBG_PRINT("JWT Payload Parse fail \n");
        return FAIL;
    }

    std::string table_name = root["tablename"].asString();
    std::string wild_card = root["wild_card"].asString();
    int offset = std::atoi(root["offset"].asString().c_str());
    int count = std::atoi(root["count"].asString().c_str());

    // date string
    std::string date_label = root["date_label"].asString();
    std::string start_date = root["start_date"].asString();
    std::string end_date = root["end_date"].asString();

    std::vector<std::string> columns;
    std::vector<std::string> values;
    std::vector<int> type_arr;
    int type_arr_status =0;

    if(wild_card =="true"){
        type_arr_status =1;
    }

    // Check info Key and this key Object?
    if(root.isMember("info") && root["info"].isObject()){
        Json::Value info = root["info"];
        Json::Value::Members members = info.getMemberNames();

        // key and value push back to vector
        for (const auto& member : members) {
            columns.push_back(member);
            Json::Value value = info[member];
            // need wild card add string front and end '%'
            if(wild_card =="true"){
                values.push_back("%"+value.asString()+"%");
            } else {
               values.push_back(value.asString()); 
            }
            type_arr.push_back(type_arr_status);
        }
    } 
    else {
        DBG_PRINT("info object not found or invalid \n");
        return FAIL;
    }

    if(!columns.empty() && !values.empty()){
        int data_len = db_row_query(table_name, columns, values, type_arr, recv_buf, max_buf_size, count, offset, date_label, start_date, end_date);
        if(data_len == FAIL){
            DBG_PRINT("Search DB Fail \n");
            return FAIL;
        } else {
            DBG_PRINT("Search DB Success \n");
            return data_len;
        }
    }

    DBG_PRINT("Search Rows Empty \n");
    return FAIL;
}