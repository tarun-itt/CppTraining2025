#include <iostream>
#include <iomanip>
#include <sstream>

#include "../inc/XmlParser.h"

void XmlParser::dumpXmlElement(const XMLElement* element, std::ostringstream& oss, std::string indentString) const {
    if (element){
        std::string elementName = element->Name();
        
        const std::string text = element->GetText();
        bool hasText = !text.empty();
        
        const XMLAttribute* attr = element->FirstAttribute();
        bool hasAttributes = (attr != nullptr);
        
        const XMLElement* child = element->FirstChildElement();
        bool hasChildren = (child != nullptr);
        
        if (hasAttributes) {
            oss << indentString << elementName << ":" << std::endl;
            
            while (attr) {
                oss << indentString << "  " << std::setw(10) << std::left << attr->Name() 
                    << " : " << attr->Value() << std::endl;
                attr = attr->Next();
            }
        } else if (hasText && !hasChildren) {
            oss << indentString << std::setw(10) << std::left << elementName 
                << " : " << text << std::endl;
        } else if (hasChildren) {
            oss << indentString << elementName << ":" << std::endl;
        } else {
            oss << indentString << elementName << ":" << std::endl;
        }
        
        if (hasText && hasChildren) {
            oss << indentString << std::setw(10) << std::left << "text" 
                << " : " << text << std::endl;
        }
        
        while (child) {
            dumpXmlElement(child, oss, indentString + "  ");
            child = child->NextSiblingElement();
        }
    }
}

ParserResult XmlParser::parse() {
    XMLError result = doc.LoadFile(filename.c_str());
    
    if (result != XML_SUCCESS) {
        std::string errorMessage = doc.ErrorStr();
        if (result == XML_ERROR_FILE_NOT_FOUND) errorMessage = "File not found";
        return ParserResult(ParserStatus::PARSE_ERROR, errorMessage);
    }
    
    XMLElement* root = doc.RootElement();
    if (!root) {
        return ParserResult(ParserStatus::INVALID_DATA, "No root element found");
    }
    
    return ParserResult();
}

std::string XmlParser::dump() {
    std::ostringstream oss;
    const XMLElement* root = doc.RootElement();
    if (root) {
        dumpXmlElement(root, oss, "  ");
    } else {
        oss << "No XML data to display" << std::endl;
    }
    return oss.str();
} 