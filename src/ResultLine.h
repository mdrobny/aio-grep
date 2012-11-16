#ifndef RESULTLINE_H
#define RESULTLINE_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

class ResultLine
{

private:
    std::string line;
    std::vector<std::pair<int, int> > occrurences;
    int lineNum;

public:
    ResultLine();
    void setLine(std::string& str);
    void appendToLine(std::string& str);
    std::string getLine() const;
    void addOccurence(std::pair<int, int> occ);
    std::pair<int, int> getOccurence(int which) const;
    void setLineNum(int n);
    int getLineNum() const;
};

#endif
