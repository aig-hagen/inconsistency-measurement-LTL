#include <clingo.hh>
#include <chrono>
#include <fstream>

#include "Constants.h"
#include "LTLConformanceChecking.h"

// Author: Isabelle Kuhlmann

void check_satisfiability_LTL(Kb& kb, int m);