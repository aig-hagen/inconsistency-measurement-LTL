#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cctype>

#include "src/InconsistencyMeasureASP.h"
#include "src/Parser.h"
#include "src/Utils.h"

// Authors: Anna Gessler, Isabelle Kuhlmann 

static void PrintCmdHelp()
{
    std::cerr << "Call im-app with 3 arguments: ./im-app <file> <im> <m>" << std::endl
              << "'file' is a path to a  knowledge base file" << std::endl
              << "'im' is the name of an inconsistency measure" << std::endl
              << "'m' is the number of the final state (or type 'auto' for automatic detection of the knowledge base's maximal depth)" << std::endl
              << "possible 'im' values: contension-ltl, drastic-ltl, mv-mis, mv-mcs, p-mis, p-mcs, r, mi" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        PrintCmdHelp();
        return -1;
    }
    std::string measure = argv[2];
    std::transform(measure.begin(), measure.end(), measure.begin(), ::tolower);
    std::set<std::string> measures = {"contension-ltl", "drastic-ltl", "mv-mis", "mv-mcs", "p-mis", "p-mcs", "r", "mi"};
    if (measures.find(measure) == measures.end())
    {
        std::cerr << "Error: " << measure << " is not a valid inconsistency measure" << std::endl;
        return -1;
    }

    std::string m_str = argv[3];

    std::string file = argv[1];
    Parser p = Parser();
    Kb k = p.ParseKbFromFile(file);

    ImSettings config;
    config.measure_name = measure;

    double result {};

    // Parsing parameter m
    // Check if m is in 'auto' mode
    if (m_str.compare("auto") == 0){
        //if (measure.compare("contension-ltl") == 0){
        //    std::cerr << "Error: 'auto' mode not available for contension-ltl" << std::endl;
        //    return -1;
        //}
        //else{
            config.m = get_kb_depth(k);
        //}
    }
    // if m is specified manually, it needs to be a number (integer)
    else{
        if (!is_number(m_str))
        {
            std::cerr << "Error: " << m_str << " is not a digit" << std::endl;
            return -1;
        }
        else{
            int m = stoi(m_str);
            config.m = m;
        }
    }

    result = get_inconsistency_value(k, config);

    std::string result_string = std::to_string(result);
    if (result == -1)
    {
      result_string = "INF";
    }

    else if(result == -2)
    {
        result_string = "m";
    }

    
    std::cout << result_string << std::endl;

    return 0;
}
