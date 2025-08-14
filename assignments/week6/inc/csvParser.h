#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include "parser.h"
#include "table.h"

class CsvParser : public Parser {
private:
    Table data;
    Row splitLine(const std::string& line, char delimiter = ',');

public:
    CsvParser(const std::string& filename) : Parser(filename), data(10) {}
    
    ParseResult parse() override;
    std::string dump() const override;
};

#endif