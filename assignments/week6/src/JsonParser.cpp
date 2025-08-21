#include <iostream>
#include <fstream>
#include <sstream>

#include "../inc/JsonParser.h"


using json = nlohmann::json;

ParserResult JsonParser::parse() {
    try {
        ParserResult result;
        std::ifstream file(filename);
        if (!file) {
            result.status = ParserStatus::FILE_NOT_FOUND;
            result.message = "Could not open file: " + filename;
        }
        
        data = json::parse(file);

        return result;
    } catch (const json::parse_error& e) {
        return ParserResult(ParserStatus::PARSE_ERROR,  e.what());
    } catch (const std::exception& e) {
        return ParserResult(ParserStatus::UNKNOWN_ERROR, e.what());
    }
}

void JsonParser::dumpJsonValue(const nlohmann::json& value, const std::string& key, std::ostringstream& oss, std::string indentString) const {
    if (value.is_object()) {
        if (!key.empty()) {
            oss << indentString << key << ":" << std::endl;
        }

        for (auto it = value.begin(); it != value.end(); ++it) {
            dumpJsonValue(it.value(), it.key(), oss, indentString + "  ");
        }
    } else if (value.is_array()) {
        if (!key.empty()) {
            oss << indentString << key << ":" << std::endl;
        }
        
        for (const auto& item : value) {
            if (item.is_primitive()) {
                oss << indentString << "  - " << item.dump() << std::endl;
            } else {
                dumpJsonValue(item, "", oss, indentString + "  ");
            }
        }
    } else {
        oss << indentString << key << " : " << value.dump() << std::endl;
    }
}

std::string JsonParser::dump() {
    std::ostringstream oss;

    try {
        dumpJsonValue(data, "", oss, "  ");
    } catch (const std::exception& e) {
        oss << "Error displaying JSON data.";
    }
    return oss.str();
} 