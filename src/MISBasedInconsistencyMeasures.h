#include <sstream>
#include <set>
#include <vector>
#include <iostream>

#include "Utils.h"
#include "Parser.h"
#include "Constants.h"
#include <clingo.hh>

// Author: Isabelle Kuhlmann



// This doesn't need to be in the header I think? Doesn't seem to be used anywhere else
//std::set<std::string> getFormulasInMUS(std::string& program);
//int enumerate_all_solutions_with_projection(std::string& program);
//void get_formula_depth(Formula& formula, int& formula_depth);
//int get_kb_depth(Kb& kb);

double p_measure_LTL(Kb& kb, int m);

double mv_measure_LTL(Kb& kb, int m);

int mi_measure_LTL(Kb& kb, int m);
