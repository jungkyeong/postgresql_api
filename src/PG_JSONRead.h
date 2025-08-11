/**
  ******************************************************************************
  * @file           : PG_JSONRead
  * @brief          : Class PgJsonRead define use Json file read DBAPI function 
  ******************************************************************************
  * Made in GreenOasis  
  * https://github.com/jungkyeong
  * CopyRigth MIT License
  ******************************************************************************
  * Release History
  * branch name, working description, time
  * version_001: define add version  2025-08-11
  ******************************************************************************
  */

#ifndef __PG_JSONREAD_HPP
#define __PG_JSONREAD_HPP

#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstring>
#include "../lib/json/json.h"
#include "Util.h"
#include "Define.h"
#include "PG_DBAPI.h"

// Debug print
#ifdef DEBUG
#define DBG_PRINT(fmt, ...) printf("[DEBUG] " fmt, ##__VA_ARGS__)
#else
#define DBG_PRINT(fmt, ...)
#endif

class PgJsonRead {
private:
    //PgDBAPI pgdbapi;  

public:

    /**
     * @brief read json file insert db data
     * @param Jsonfile input file root
     * @return Success 0, Fail else
     */
    int db_json_insert_rows(std::string Jsonfile); 


};

#endif /* __PG_JSONREAD_HPP */