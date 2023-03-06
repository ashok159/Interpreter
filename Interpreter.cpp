//Name: Ashok Surujdeo
//Interpreter C++ File

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include "Interpreter.h"
using namespace std;

vector<string> Parser::operator()(const string &str)
{
    string newstr = str;
    vector<string> tokens; //vector to hold tokens of parsed lines
    for (int len = 0; len < newstr.length(); len++)
    {
        if ((newstr[len] == '=') || (newstr[len] == '+') || (newstr[len] == '-') || (newstr[len] == '*'))
        {
            newstr.insert(len++, " "); 
            newstr.insert(len+1, " ");
        }
    }

    string temp;
    char ch = '#';
    char ch2 = '\"';
    if (newstr[0] == '#')
    {
        tokens.clear();
        return tokens;
    }
    else 
    {
        if (newstr.find(ch) != string::npos)
        {
            newstr.erase(newstr.find(ch), newstr.length());
            if (newstr.find(ch2) != string::npos)
            { 
                int pos = newstr.find(ch2);
                string s1 = newstr.substr(pos, newstr.length());
                newstr.erase(newstr.find(ch2), newstr.length());
                s1.erase(remove(s1.begin(), s1.end(), ch2), s1.end());
                stringstream ss(newstr);
                while (ss >> temp)
                {
                    tokens.push_back(temp);
                }
                tokens.push_back(s1);
            }
            else
            {
                stringstream ss(newstr);
                while (ss >> temp)
                {
                    tokens.push_back(temp);
                }
            }
            
        }
        else
        {
            if (newstr.find(ch2) != string::npos)
            { 
                int pos = newstr.find(ch2);
                string s1 = newstr.substr(pos, newstr.length());
                newstr.erase(newstr.find(ch2), newstr.length());
                s1.erase(remove(s1.begin(), s1.end(), ch2), s1.end());
                stringstream ss(newstr);
                while (ss >> temp)
                {
                    tokens.push_back(temp);
                }
                tokens.push_back(s1);
            }
            else
            {
                stringstream ss(newstr);
                while (ss >> temp)
                {
                    tokens.push_back(temp);
                }
            }
        }
    }

    return tokens; //vector containing tokens of command
}

void Interpreter::Run(const string &filename)
{
    Parser pars;
    ifstream file(filename);
    string line;
    while (getline(file, line))
    {
        interpret(pars(line));
    }
}

void Interpreter::interpret(vector<string> tokens)
{
    count++;

    for (int len = 0; len < tokens.size(); len++)
    {
        if (tokens.empty())
        {
            continue;
        }

        else if (tokens[0] == "STRING")
        {
            if (tokens.size() == 2)
            {
                if (isdigit(tokens[1][0]))   
                {
                    cout << "Error on line " << count << endl;
                    std::exit(0);
                }
                else 
                {    
                    declareString(tokens[1]);
                    tokens.clear();
                }
            }   
            else 
            {
                cout << "Error on line " << count << endl;
                std::exit(0);
            }
        }   
        
        else if (tokens[0] == "NUMBER")
        {
            if (tokens.size() == 2)
            {
                if (isdigit(tokens[1][0]))   
                {
                    cout << "Error on line " << count << endl;
                    std::exit(0);
                }
                else 
                {    
                    declareNum(tokens[1]);
                    tokens.clear();
                }
            }   
            else 
            {
                cout << "Error on line " << count << endl;
                std::exit(0);
            }
        }

        else if (string_map.find(tokens[0]) != string_map.end())
        {
            if (tokens.size() == 3)
            {
                if (tokens[1] == "=")
                {
                    InitializeString(tokens[0], tokens[2]);
                    tokens.clear();
                }
            }
            else 
            {
                cout << "Error on line " << count << endl;
                std::exit(0);
            }
        }

        else if (number_map.find(tokens[0]) != number_map.end())
        {
            if ((tokens.size() == 3) && (tokens[1] == "="))
            {
                if (string_map.find(tokens[2]) != string_map.end())
                {
                    cout << "Error on line " << count << endl;
                    std::exit(0);
                }
                else 
                {
                    InitializeNum(tokens[0], tokens[2]);
                    tokens.clear();
                }
            }
            else if ((tokens.size() > 3) && (tokens[1] == "="))
            {
                for (int i = 0; i < tokens.size(); i++)
                {
                    if (string_map.find(tokens[i]) != string_map.end())
                    {
                        cout << "Error on line " << count << endl;
                        std::exit(0);
                    }
                    else if (tokens[i] == "/")
                    {
                        cout << "Error on line " << count << endl;
                        std::exit(0);
                    }
                    else if (tokens[i] == tokens[i+1])
                    {
                        cout << "Error on line " << count << endl;
                        std::exit(0);
                    }
                }
                InitializeNum(tokens[0], ExpressionSolver(tokens));
                tokens.clear();
            }
        }

        else if (tokens[0] == "PRINT")
        {
            if (string_map.find(tokens[1]) != string_map.end())
            {
                Print(string_map[tokens[1]]);
                tokens.clear();
            }
            else if (number_map.find(tokens[1]) != number_map.end())
            {
                string str = to_string(number_map[tokens[1]]);
                Print(str);
                tokens.clear();
            }

            else
            {
                Print(tokens[1]);
                tokens.clear();
            }
        }
        else 
        {
            cout << "Error on line " << count << endl;
            std::exit(0);
        }
    }
}

void Interpreter::declareString(const string &str)
{ 
    string_map[str] = "";
}

void Interpreter::declareNum(const string &num)
{
    number_map[num] = 0;
}

void Interpreter::Print(const string &str)
{
    string newstr = str;
    for (int len = 0; len < newstr.length(); len++)
    {
        if (newstr[len] == '\\' && newstr[len+1] == 'n')
        {
            newstr.erase(len, 2);        
        }
    }

    if (newstr.find('\\') != string::npos)
    {
        cout << "Error on line " << count << endl;
        std::exit(0);
    }

    cout << newstr << endl;
} 

void Interpreter::InitializeString(string str, string str2)
{
    string_map.erase(str);
    string_map[str] = str2;
}

void Interpreter::InitializeNum(string str, string num)
{
    if (isdigit(num[0]))
    {
        number_map.erase(str);
        number_map[str] = stoll(num);
    }
    else if (number_map.find(num) != number_map.end())
    {
        number_map.erase(str);
        number_map[str] = number_map[num];
    }
    else 
    {
        cout << "Error on line " << count << endl;
        std::exit(0);
    }
}
 
string Interpreter::ExpressionSolver(vector<string> tokens)
{
    long long total = 0;

    for (int len = 1; len < tokens.size(); len++)
    {
        if (number_map.find(tokens[len]) != number_map.end())
        {
            tokens[len] = to_string(number_map[tokens[len]]);
        }
    }

    for (int len = 2; len < tokens.size(); len++)
    {
        if (tokens[len] == "*")
        {
            total = stoll(tokens[len-1]) * stoll(tokens[len+1]);
            tokens[len] = to_string(total);
            tokens.erase(tokens.begin() + len + 1);
            tokens.erase(tokens.begin() + len - 1);
            total = 0;
        }
    }

    for (int len = 2; len < tokens.size(); len++)
    {
        if (tokens[len] == "+")
        {
            total = stoll(tokens[len-1]) + stoll(tokens[len+1]);
            tokens[len] = to_string(total);
            tokens.erase(tokens.begin() + len + 1);
            tokens.erase(tokens.begin() + len - 1);
            total = 0;
        }
        else if (tokens[len] == "-")
        {
            total = stoll(tokens[len-1]) - stoll(tokens[len+1]);
            tokens[len] = to_string(total);
            tokens.erase(tokens.begin() + len + 1);
            tokens.erase(tokens.begin() + len - 1);
            total = 0;
        }
    }
    
    return tokens[2];
}
