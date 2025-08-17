#include "main.h"
#include "Util.h"
#include "Define.h"
#include "ConfigRead.h"
#include "PG_DBAPI.h"
#include "../lib/json/json.h"
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string>
#include <cstring>
#include <dlfcn.h> // library load

Util util;
ConfigRead configread;
PgDBAPI pgdbapi;

int main() {


    // Json lib (if use SO file) 
    /*
    void* LibHandle = NULL;
    LibHandle = dlopen(JSON_LIB, RTLD_NOW);
    if(!LibHandle){
        DBG_PRINT("Failed to load JSON library: %s\n", dlerror());
        return FAIL;
    }
    */

    // 1. DB Connect
    std::string pw = util.get_input("user password: ");
    pgdbapi.connect("127.0.0.1", "5432", "test_db", "postgres", pw);
    pw.clear();

    // make json file
    Json::Value resroot;
    resroot["tablename"] = "users";
    Json::Value info_obj;
    info_obj["username"] = "alice";
    info_obj["position"] = "ST";
    resroot["info"] = info_obj;
    Json::StreamWriterBuilder abuilder;
    std::string create_json_file = Json::writeString(abuilder, resroot);

    // 2. insert rows
    pgdbapi.db_json_insert_rows(create_json_file);

    // make json file
    Json::Value resroot_a;
    resroot_a["tablename"] = "users";
    resroot_a["switch_target_key"] = "username";
    resroot_a["switch_target_value"] = "alice";
    Json::Value info_obj_a;
    info_obj_a["username"] = "Bob";
    info_obj_a["position"] = "ST";
    resroot_a["info"] = info_obj_a;
    Json::StreamWriterBuilder abuilder_a;
    std::string modify_json_file = Json::writeString(abuilder_a, resroot_a);

    // 3. modify rows
    pgdbapi.db_json_modify_rows(modify_json_file);

    // make json file
    Json::Value resroot_c;
    resroot_c["tablename"] = "users";
    resroot_c["wild_card"] = "true"; // wild card search
    resroot_c["offset"] = "2";
    resroot_c["count"] = "2";
    resroot_c["date_label"] = "created_at";
    resroot_c["start_date"] = "2025-08-11 00:00:00";
    resroot_c["end_date"] = "2025-08-20 00:00:00";
    Json::Value info_obj_c;
    info_obj_c["position"] = "S";
    resroot_c["info"] = info_obj_c;
    Json::StreamWriterBuilder abuilder_c;
    std::string search_json_file = Json::writeString(abuilder_c, resroot_c);

    // 4. search rows
    char recv_buffer[4096];
    int data_len = pgdbapi.db_json_search_rows(search_json_file, recv_buffer, 4096);

    printf("Data len: %d \n", data_len);
    printf("Data : %s \n", recv_buffer);


    // make json file
    Json::Value resroot_d;
    resroot_d["tablename"] = "users";
    Json::Value info_obj_d;
    info_obj_d["position"] = "ST";
    resroot_d["info"] = info_obj_d;
    Json::StreamWriterBuilder abuilder_d;
    std::string remove_json_file = Json::writeString(abuilder_d, resroot_d);

    // 5. remove rows
    pgdbapi.db_json_remove_rows(remove_json_file);

    // x. Close Disconnect
    pgdbapi.disconnect();
    //dlclose(LibHandle);

    return 0;
}