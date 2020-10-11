#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <string>
#include <vector>
#include <iostream>

namespace kxz
{
    using CSVRow = std::vector<std::string>;
    using CSVTable = std::vector<CSVRow>;

    class CSVParser
    {
        CSVTable table;

    public:
        CSVParser() = default;

        bool loadFromString(std::string str);
        bool loadFromFile(std::string path);
        bool saveToFile(std::string path);
        std::string toString();

        void clear();

        void addRow(CSVRow row);

        void setTable(CSVTable table);
        void setRow(CSVRow row, size_t position);

        CSVTable getTable();
        CSVRow getRow(size_t position);
        size_t getSize();
        size_t getLength();

        // getting values
        std::string getField(size_t row, size_t column);
        int getInt(size_t row, size_t column);
        float getFloat(size_t row, size_t column);
        bool getBool(size_t row, size_t column);
    };
}

#endif // CSVPARSER_H
