#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "Parser.h"
#include "nlohmann/json.hpp"

class JsonParser : public Parser {
private:
    nlohmann::json data;
    void dumpJsonValue(const nlohmann::json& value, const std::string& key, std::ostringstream& oss, std::string indentString) const;

public:
    JsonParser(const std::string& filename) : Parser(filename) {}
    
    ParserResult parse() override;
    std::string dump() override;
};

#endif