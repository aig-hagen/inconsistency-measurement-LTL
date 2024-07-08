#include <sstream>
#include <set>
#include <vector>
#include <iostream>

#include "Utils.h"
#include "Parser.h"
#include "Constants.h"
#include <clingo.hh>

// Author: Isabelle Kuhlmann

std::string add_truth_values_LTL();
std::string handle_formulas_in_kb_LTL(Kb& kb);

std::string add_conjunction_rules_LTL();
std::string add_disjunction_rules_LTL();
std::string add_negation_rules_LTL();
std::string add_next_rules();
std::string add_until_rules();
std::string add_globally_rules();
std::string add_finally_rules();
std::string get_base_program_LTL(Kb& kb);

void ltl_to_asp(Formula& formula, std::string formula_name, std::string& rules);

std::string add_guess_candidate_set_rules();
std::string add_SAT_check_rules();
std::string add_saturation_rules();

bool answerSetExists(std::string& program);
