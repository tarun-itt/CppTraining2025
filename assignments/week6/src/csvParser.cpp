#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

#include "../inc/csvParser.h"

Row CsvParser::splitLine(const std::string& line, char delimiter) {
    Row result(10);
    std::string current;
    
    for (char c : line) {
        if (c == delimiter) {
            result.add(current);
            current.clear();
        } else {
            current += c;
        }
    }
    result.add(current);
    
    return result;
}

ParseResult CsvParser::parse() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return ParseResult(ParseError::FILE_NOT_FOUND, "Could not open file: " + filename);
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            data.add(splitLine(line));
        }
    }
    
    file.close();
    
    ParseResult result;
    if (data.getSize() == 0) {
        result.error = ParseError::INVALID_DATA;
        result.message = "No valid CSV data found";
    }

    
    std::cout << "Rows: " << data.getSize() << std::endl;
    return result;
}

std::string CsvParser::dump() const {
    std::ostringstream oss;
    
    if (data.getSize() > 0) {
        int numColumns = data[0].getSize();
        int* columnWidths = new int[numColumns];

        for (int column = 0; column < numColumns; column++) {
            columnWidths[column] = 0;
        }
        
        for (int row = 0; row < data.getSize(); row++) {
            for (int column = 0; column < data[row].getSize() && column < numColumns; column++) {
                if (data[row][column].length() > columnWidths[column]) {
                    columnWidths[column] = data[row][column].length();
                }
            }
        }
        
        for (int column = 0; column < numColumns; column++) {
            if (columnWidths[column] < 8) {
                columnWidths[column] = 8;
            }
        }
        
        int totalWidth = 0;
        for (int column = 0; column < numColumns; column++) {
            totalWidth += columnWidths[column] + 3;
        }
        totalWidth += 1;
        
        for (int i = 0; i < totalWidth; i++) {
            oss << "-";
        }
        oss << std::endl;
        
        oss << "|";
        for (int column = 0; column < numColumns; column++) {
            oss << " " << std::setw(columnWidths[column]) << std::left << data[0][column] << " |";
        }
        oss << std::endl;
        
        for (int i = 0; i < totalWidth; i++) {
            oss << "-";
        }
        oss << std::endl;
        
        for (int currentRow = 1; currentRow < data.getSize(); currentRow++) {
            oss << "|";
            const Row& row = data[currentRow];

            for (int column = 0; column < row.getSize() && column < numColumns; column++) {
                oss << " " << std::setw(columnWidths[column]) << std::left << row[column] << " |";
            }

            for (int column = row.getSize(); column < numColumns; column++) {
                oss << " " << std::setw(columnWidths[column]) << std::left << "" << " |";
            }
            oss << std::endl;
        }
        
        for (int currentWidth = 0; currentWidth < totalWidth; currentWidth++) {
            oss << "-";
        }
        oss << std::endl;
        
        oss << "Total Records: " << (data.getSize() - 1) << std::endl;
        delete[] columnWidths;
    } else {
        oss << "No CSV data to display" << std::endl;
    }
    
    return oss.str();
} 