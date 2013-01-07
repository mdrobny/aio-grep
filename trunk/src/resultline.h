#ifndef RESULTLINE_H
#define RESULTLINE_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

typedef std::pair<int, int> int_pair_t;

class ResultLine
{

private:
    std::string line;
    std::string filename;
    std::vector<int_pair_t > occurences;
    int lineNum;
    char * begin;
    char * end;

public:
    char * getBeginLine();
    char * getEndLine();
    ResultLine();
    void setLine(const std::string& str);
    void setLine(char * b, char * e);
    const std::string& getLine() const;
    void addOccurence(int_pair_t occ);
    const std::pair<int, int>& getOccurence(int which) const;
    void setLineNum(int n);
    int getLineNum() const;
    const std::string& getFilename() const;
    void setFilename(const std::string &filename);
    int getNumberOfOccurences();
    void clear();
};

#endif
