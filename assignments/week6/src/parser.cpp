#include "../inc/parser.h"

ParseResult::ParseResult(ParseError err, const std::string& msg): error(err), message(msg) {}

void Parser::print(std::ostream& out) {
    out << dump();
} 