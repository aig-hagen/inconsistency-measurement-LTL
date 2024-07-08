#include <sstream>
#include <set>
#include <vector>
#include <iostream>

#include "Utils.h"
#include "Parser.h"
#include "Constants.h"

#include <clingo.hh>

#include "ComputeMIS.h"

// Author: Isabelle Kuhlmann

std::string add_conjunction_rules_LTL_MCS();
std::string add_disjunction_rules_LTL_MCS();
std::string add_negation_rules_LTL_MCS();
std::string add_next_rules_MCS();
std::string add_until_rules_MCS();
std::string add_globally_rules_MCS();
std::string add_finally_rules_MCS();

std::string add_guess_candidate_set_rules_MCS();
std::string add_SAT_check_of_CS_rules();
std::string add_superset_rules();
std::string add_saturation_rules_MCS();

std::string create_MCS_base_program(Kb& kb, int m);
