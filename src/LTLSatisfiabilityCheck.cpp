#include "LTLSatisfiabilityCheck.h"

using namespace constants;

// Author: Isabelle Kuhlmann

void check_satisfiability_LTL(Kb& kb, int m){

    // initialize program string:
    std::string program = "";

    // guessing part:
    // program += "1{" + IS_TRUE + "(A,S):" + IS_STATE + "(S)}1:-" + ATOM + "(A).";
    program += "1{" + IS_TRUE + "(A,S):" + ATOM + "(A)}1:-" + IS_STATE + "(S).";

    // program += "1{" + TRUTH_VALUE_PREDICATE + "(A,S,T):tv(T)}1:-" + ATOM + "(A)," + IS_STATE + "(S).";
    
    program += get_base_program_LTL_conformance_checking_new(kb);

    // set number of states:
    program += FINAL_STATE + "(" + std::to_string(m) + ").";

    auto start = std::chrono::high_resolution_clock::now();
    bool is_sat = answerSetExists(program);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double total_solving_time = (double)duration.count();

    if (is_sat){
        std::cout << "sat" << std::endl;
    }
    else{
        std::cout << "unsat" << std::endl;
    }

    // TODO: print nicer output

    std::cout << "\nTotal solving time: " << total_solving_time << "microseconds" << std::endl;
    std::cout << "Total solving time: " << total_solving_time/1000 << " milliseconds" << std::endl;
    std::cout << "Total solving time: " << total_solving_time/1000000 << " seconds" << std::endl;
    // }
}