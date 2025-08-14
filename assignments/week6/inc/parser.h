#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include <iostream>
#include <ostream>

enum class ParseError {
    SUCCESS = 0,
    FILE_NOT_FOUND,
    FILE_EMPTY,
    FILE_READ_ERROR,
    PARSE_ERROR,
    INVALID_DATA,
    UNKNOWN_ERROR
};

struct ParseResult {
    ParseError error;
    std::string message;
    
    ParseResult(ParseError err = ParseError::SUCCESS, const std::string& msg = ""); 
    
    bool success() const { return error == ParseError::SUCCESS; }
    operator bool() const { return error == ParseError::SUCCESS; }
};

class Parser {
protected:
    std::string filename;

public:
    Parser(const std::string& fname) : filename(fname) {}
    virtual ~Parser(){}
    
    virtual ParseResult parse() = 0;
    virtual std::string dump() const = 0;
    
    void print(std::ostream& out = std::cout);
    
    const std::string& getFilename() const { return filename; }
};

#endif