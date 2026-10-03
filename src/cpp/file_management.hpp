#include <utils/platform.hpp>
#include <utils/json.hpp>
#include <filesystem>
#include <fstream>
#include <utils/log.hpp>

#include "settings.hpp"

inline Log logs;
inline const std::string FILE_NAME = "file_management.hpp";

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace file
{
    inline void saveData(json data = DEFAULT_DATA) {
        platform::setAppName(APPNAME);
        Log::SignatureScope scope(logs, FILE_NAME + "/saveData()");
        logs.write("Saving data...\n");
        fs::path absPath = platform::appDataPath() / SAVEFILE_NAME;
        if (!fs::exists(absPath)) 
            logs.write("Save file doesn't exist yet. Creating new one\n");

        std::ofstream file(absPath, std::ios::trunc);
        if (!file.is_open()) {
            logs.write("Couldn't open file for unkon reason!\n", MessageType::Error);
            return;
        }
        file << std::setw(JSON_INDENTATION_SPACES) << data << '\n';
        file.close();
        logs.write("Successfully wrote and closed file.\n");
    }
    inline json loadData() {
        platform::setAppName(APPNAME);
        Log::SignatureScope scope(logs, FILE_NAME + "/loadData()");
        logs.write("Loading data...\n");
        fs::path absPath = platform::appDataPath() / SAVEFILE_NAME;
        if (!fs::exists(absPath)) {
            fs::create_directories(absPath.parent_path());
            logs.write("File doesnt exist. Creating it...\n");
            logs.write("Calling saveData with default value\n");
            saveData();
            logs.write("Returning default data since we just saved that anyway, no need to load it.\n");
            return DEFAULT_DATA;
        }
        // else
        std::ifstream file(absPath);
        if (!file.is_open()) {
            logs.write("Couldn't open file for unknow reason!\n", MessageType::Error);
            return FAILED_FILE_ERRCODE;
        } else
        return json::parse(file);
    }

    inline std::ofstream makeLog() {
        platform::setAppName(APPNAME);
        fs::path absPath = platform::appDataPath() / LOGS_NAME;
        if (!fs::exists(absPath.parent_path())) {
            fs::create_directories(absPath.parent_path());
        }
        return std::ofstream(absPath, CLEAR_LOGS ? std::ios::trunc : std::ios::app);
    }
}