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
//std::set<std::string> getFormulasInMCS(std::string& program);
//int compute_optimum(std::string& program);

double p_measure_LTL_MCS(Kb& kb, int m);

double mv_measure_LTL_MCS(Kb& kb, int m);

int r_measure_LTL(Kb& kb, int m);
