#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cctype>

#include "src/InconsistencyMeasureASP.h"
#include "src/LTLConformanceChecking.h"
#include "src/Parser.h"
#include "src/Utils.h"

// Authors: Anna Gessler, Isabelle Kuhlmann 

static void PrintCmdHelp()
{
    std::cerr << "Call im-app with the following arguments for inconsistency measurement: ./im-app im <kb_file> <im> <m>" << std::endl
              << "Call im-app with the following arguments for conformance checking: ./im-app cc <kb_file> <trace_file>" << std::endl
              << "'kb_file' is a path to a knowledge base file" << std::endl
              << "'trace_file' is a path to a file containing traces corresponding to the given knowledge base" << std::endl
              << "'im' is the name of an inconsistency measure" << std::endl
              << "'m' is the number of the final state" << std::endl
              << "possible 'im' options: contension-ltl, drastic-ltl" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        PrintCmdHelp();
        return -1;
    }
    std::string task = argv[1];
    std::transform(task.begin(), task.end(), task.begin(), ::tolower);
    std::set<std::string> tasks = {"im", "cc"};
    if (tasks.find(task) == tasks.end())
    {
        std::cerr << "Error: " << task << " is not a valid mode" << std::endl;
        return -1;
    }

    if (task == "im"){
        if (argc != 5)
        {
            PrintCmdHelp();
            return -1;
        }

        std::string measure = argv[3];
        std::transform(measure.begin(), measure.end(), measure.begin(), ::tolower);
        std::set<std::string> measures = {"contension-ltl", "drastic-ltl"};
        if (measures.find(measure) == measures.end())
        {
            std::cerr << "Error: " << measure << " is not a valid inconsistency measure" << std::endl;
            return -1;
        }

        std::string m_str = argv[4];
        if (!is_number(m_str))
        {
            std::cerr << "Error: " << m_str << " is not a digit" << std::endl;
            return -1;
        }

        std::string file = argv[2];
        Parser p = Parser();
        Kb k = p.ParseKbFromFile(file);

        ImSettings config;
        config.measure_name = measure;

        double result {};

        int m = stoi(m_str);
        config.m = m;

        result = get_inconsistency_value(k, config);

        std::string result_string = std::to_string(result);
        if (result == -1)
        {
            result_string = "INF";
        }

        
        std::cout << result_string << std::endl;
    }

    else if (task == "cc"){

        std::string kb_file = argv[2];
        Parser p = Parser();
        Kb k = p.ParseKbFromFile(kb_file);

        std::string trace_file = argv[3];

        // std::cout << "I'm conformance checking!" << std::endl;
        
        conformance_checking(k, trace_file);
    }
    

    return 0;
}
