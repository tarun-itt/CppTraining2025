#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include <iostream>
#include <ostream>

enum class ParserStatus {
    SUCCESS = 0,
    FILE_NOT_FOUND,
    FILE_EMPTY,
    FILE_READ_ERROR,
    PARSE_ERROR,
    INVALID_DATA,
    UNKNOWN_ERROR
};

struct ParserResult {
    ParserStatus status;
    std::string message;
    
    ParserResult(ParserStatus status = ParserStatus::SUCCESS, const std::string& msg = ""); 
    
    bool success() const { return status == ParserStatus::SUCCESS; }
};

class Parser {
protected:
    std::string filename;

public:
    Parser(const std::string& fname) : filename(fname) {}
    virtual ~Parser(){}
    
    virtual ParserResult parse() = 0;
    virtual std::string dump() = 0;
    
    void print(std::ostream& out = std::cout);
};

#endif