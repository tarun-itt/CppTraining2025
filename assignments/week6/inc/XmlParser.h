#ifndef XML_PARSER_H
#define XML_PARSER_H

#include "Parser.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XmlParser : public Parser {
private:
    XMLDocument doc;   
    void dumpXmlElement(const XMLElement* element, std::ostringstream& oss, std::string indentString) const;

public:
    XmlParser(const std::string& filename) : Parser(filename) {}
    
    ParserResult parse() override;
    std::string dump() override;
};

#endif