#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include "Parser.h"
#include "Table.h"

#define PADDING_SIZE 2

class CsvParser : public Parser {
private:
    Table data;
    int currentRow;
    
    Row splitLine(const std::string& line, char delimiter = ',');

public:
    CsvParser(const std::string& filename) : Parser(filename), data(10) {}
    
    ParserResult parse() override;
    int getRowCount();
    bool hasNextRow();
    Row nextRow();
    Row getRowAt(int index);
    Row getRowHeader();
    std::string dump() override;
};

#endif