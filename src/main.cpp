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


    // Json lib
    void* LibHandle = NULL;
    LibHandle = dlopen(JSON_LIB, RTLD_NOW);
    if(!LibHandle){
        DBG_PRINT("Failed to load JSON library: %s\n", dlerror());
        return FAIL;
    }

    // 1. DB Connect
    std::string pw = util.get_input("user password: ");
    pgdbapi.connect("127.0.0.1", "5432", "test_db", "postgres", pw);
    pw.clear();

    // 2. make json file
    Json::Value resroot;
    resroot["tablename"] = "users";
    Json::Value info_obj;
    info_obj["username"] = "alice";
    info_obj["position"] = "ST";
    resroot["info"] = info_obj;
    Json::StreamWriterBuilder abuilder;
    std::string create_json_file = Json::writeString(abuilder, resroot);

    // 3. insert DB
    pgdbapi.db_json_insert_rows(create_json_file);

    // x. Close Disconnect
    pgdbapi.disconnect();
    dlclose(LibHandle);

    return 0;
}