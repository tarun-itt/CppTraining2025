#include "../inc/Parser.h"

ParserResult::ParserResult(ParserStatus status, const std::string& msg): status(status), message(msg) {}

void Parser::print(std::ostream& out) {
    out << dump();
} 