#include "csvparser.h"
namespace kxz
{
    bool CSVParser::loadFromString(std::string str)
    {
        CSVRow row;
        std::string field;
        size_t counter = 0;
        char ch;

        while(1)
        {
            ch = str[counter];
            if(ch == ',')
            {
                if (!field.empty()) row.push_back(field);
                field.clear();
            }
            else if(ch == '\n' || ch == '\0')
            {
                if (!field.empty()) row.push_back(field);
                field.clear();
                if (!row.empty()) table.push_back(row);
                row.clear();

                if (ch == '\0') break;
            }
            else field += ch;
            counter++;
        }
    }

    bool CSVParser::loadFromFile(std::string path)
    {

    }

    bool CSVParser::saveToFile(std::string path)
    {

    }

    std::string CSVParser::toString()
    {
        //for(size_t column=0; )
        return "";
    }

    void CSVParser::clear()
    {
        table.clear();
    }

    void CSVParser::addRow(CSVRow row)
    {
        table.push_back(row);
    }

    void CSVParser::setTable(CSVTable table)
    {
        this->table = table;
    }

    void CSVParser::setRow(CSVRow row, size_t position)
    {
        size_t size = table.size();
        if(size > position) table[position] = row;
        else table[size] = row;
    }

    CSVTable CSVParser::getTable()
    {
        return table;
    }

    CSVRow CSVParser::getRow(size_t position)
    {
        if(table.size() > position) return table[position];
        return CSVRow();
    }

    size_t CSVParser::getSize()
    {
        size_t counter = 0;
        size_t size = table.size();

        for(size_t i=0; i<size; i++) counter += table[i].size();

        return counter;
    }

    size_t CSVParser::getLength()
    {
        return table.size();
    }

    std::string CSVParser::getField(size_t row, size_t column)
    {
        if(table.size() > column)
        {
           if(table[column].size() > row) return std::string();
        }
        std::cerr << "CSVParser Error! No such field index row: " + std::to_string(row) + ", column: " + std::to_string(column) << std::endl;
        return 0;
    }

    int CSVParser::getInt(size_t row, size_t column)
    {
        std::string value = this->getField(row, column);
        if(!value.empty()) return atoi(value.c_str());
        else return 0;
    }

    float CSVParser::getFloat(size_t row, size_t column)
    {
        std::string value = this->getField(row, column);
        if(!value.empty()) return atof(value.c_str());
        else return 0;
    }

    bool CSVParser::getBool(size_t row, size_t column)
    {
        std::string value = this->getField(row, column);
        if(!value.empty()) return value == "true";
        else return 0;
    }
}
