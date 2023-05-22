#include <sstream>
#include <set>
#include <vector>
#include <iostream>

#include "Utils.h"
#include "Parser.h"
#include "Constants.h"
#include "InconsistencyMeasureASP.h"
#include <clingo.hh>

// Author: Isabelle Kuhlmann

std::string add_truth_values_LTL_2VL();

std::string add_conjunction_rules_LTL_2VL();
std::string add_disjunction_rules_LTL_2VL();
std::string add_negation_rules_LTL_2VL();
std::string add_next_rules_2VL();
std::string add_until_rules_2VL();
std::string add_globally_rules_2VL();
std::string add_finally_rules_2VL();
std::string get_base_program_LTL_conformance_checking(Kb& kb);

void conformance_checking(Kb& kb, std::string path_to_traces);
std::vector<std::string> split_by_comma(std::string& input);