#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

#include "../inc/CsvParser.h"

void calculateColumnWidths(const Table& data, int* columnWidths, int columnCount);
void printBorder(std::ostringstream& oss, int totalWidth);
void printRow(std::ostringstream& oss, const Row& row, int* columnWidths, int columnCount);


Row CsvParser::splitLine(const std::string& line, char delimiter) {
    Row result(10);
    std::string rowItem;
    
    for (char currentChar : line) {
        if (currentChar == delimiter) {
            result.add(rowItem);
            rowItem.clear();
        } else {
            rowItem += currentChar;
        }
    }
    result.add(rowItem);
    
    return result;
}

ParserResult CsvParser::parse() {
    ParserResult result;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                data.add(splitLine(line));
            }
        }
        
        file.close();
        
        if (data.getSize() == 0) {
            result.status = ParserStatus::INVALID_DATA;
            result.message = "No valid CSV data found";
        }
    } else {
        result.status = ParserStatus::FILE_NOT_FOUND;
        result.message = "Could not open file: " + filename;
    }
    return result;
}

bool CsvParser::hasNextRow() {
    return currentRow < data.getSize();
}

Row CsvParser::nextRow() {
    if (hasNextRow()) {
        return data[currentRow++];
    }
    return Row();
}

int CsvParser::getRowCount() {
    return data.getSize();
}

Row CsvParser::getRowAt(int index) {
    if (index >= 0 && index < data.getSize()) {
        return data[index];
    }

    return Row();
}

Row CsvParser::getRowHeader() {
    if (data.getSize() > 0) {
        return data[0];
    }
    return Row();
}


std::string CsvParser::dump() {
    std::ostringstream oss;
    
    if (data.getSize() > 0) { 
        int columnCount = data[0].getSize();
        int* columnWidths = new int[columnCount];
        
        calculateColumnWidths(data, columnWidths, columnCount);
        
        int totalWidth = 0;
        for (int col = 0; col < columnCount; col++) {
            totalWidth += columnWidths[col] + PADDING_SIZE;
        }
        
        printBorder(oss, totalWidth);
        
        printRow(oss, getRowHeader(), columnWidths, columnCount);
        
        printBorder(oss, totalWidth);
        
        for (int i = 1; i < getRowCount(); i++) {
            printRow(oss, getRowAt(i), columnWidths, columnCount);
        }
        
        printBorder(oss, totalWidth);
        
        oss << "Total Records: " << getRowCount()-1 << std::endl;
        
        delete[] columnWidths;
    } else {
        oss << "No CSV data to display" << std::endl;
    }
    return oss.str();
} 


//helper functions
void calculateColumnWidths(const Table& data, int* columnWidths, int columnCount) {
    for (int col = 0; col < columnCount; col++) {
        columnWidths[col] = 0;
    }
    
    for (int row = 1; row < data.getSize(); row++) {
        for (int col = 0; col < data[row].getSize() && col < columnCount; col++) {
            int cellWidth = data[row][col].length();
            if (cellWidth > columnWidths[col]) {
                columnWidths[col] = cellWidth;
            }
        }
    }
    
    for (int col = 0; col < columnCount; col++) {
        columnWidths[col] += PADDING_SIZE;
    }
}

void printBorder(std::ostringstream& oss, int totalWidth) {
    for (int i = 0; i < totalWidth; i++) {
        oss << "-";
    }
    oss << std::endl;
}

void printRow(std::ostringstream& oss, const Row& row, int* columnWidths, int columnCount) {
    oss << "|";
    
    for (int col = 0; col < row.getSize() && col < columnCount; col++) {
        oss << " " << std::setw(columnWidths[col]) << std::left << row[col] << "|";
    }

    oss << std::endl;
}