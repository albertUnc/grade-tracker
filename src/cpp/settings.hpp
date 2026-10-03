#include <string>
#include <utils/json.hpp>
using json = nlohmann::json;

const std::string SAVEFILE_NAME = "grades.json";
const std::string LOGS_NAME = "log.txt";
const bool CLEAR_LOGS = false;
const std::string APPNAME = "grade-tracker";

const std::string NO_DATA_ERRCODE = "no_data";
const std::string FAILED_FILE_ERRCODE = "failed_top_open";

const int JSON_INDENTATION_SPACES = 4;
const json DEFAULT_DATA {
    {"chemestry", {10}},
};