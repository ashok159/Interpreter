//Name: Ashok Surujdeo
//Header File

#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

class Parser
{
    public:
        std::vector<std::string> operator()(const std::string &str); 
};

class Interpreter
{
    protected:
        std::unordered_map<std::string, std::string> string_map;
        std::unordered_map<std::string, long long> number_map;
        int count = 0;
    public:
        void Run(const std::string &filename);
        void interpret(std::vector<std::string> tokens);
        void declareString(const std::string &str);
        void declareNum(const std::string &num);
        void Print(const std::string &str);
        void InitializeString(std::string str, std::string str2);
        void InitializeNum(std::string str, std::string num);
        std::string ExpressionSolver(std::vector<std::string> tokens);
};



