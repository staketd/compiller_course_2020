#pragma once

#include <map>
#include <string>
#include <fstream>
#include <scanner.h>
#include <parser.hh>
#include <Program.h>

class Driver {
public:
    Driver();
    std::map<std::string, int> variables;
    int result;
    std::string file;
    bool trace_parsing;
    bool trace_scanning;
    Scanner scanner;
    yy::location location;
    yy::parser parser;
    Program* program;

    void InitiateScan();
    void FinishScan();
    void Evaluate() const;
    void Print() const;

    int Parse(const std::string& f);
    friend class Scanner;

private:
    std::ifstream stream;
};

#include "parser.hh"
