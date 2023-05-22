#include <fstream>

#include "LTLConformanceChecking.h"
#include "LTLMeasuresASP.h"
#include "InconsistencyMeasureASP.h"

using namespace constants;

// Author: Isabelle Kuhlmann

std::string add_truth_values_LTL_2VL(){
    std::string all_truth_values = "tv(" + TRUTH_VALUE_T + ").";
    all_truth_values += "tv(" + TRUTH_VALUE_F + ").";
    return all_truth_values;
}

std::string add_conjunction_rules_LTL_2VL(){
    std::string conjunction_rules = "";
    // T:
    conjunction_rules += TRUTH_VALUE_PREDICATE + "(Y,S," + TRUTH_VALUE_T + "):-" + CONJUNCTION + "(Y)," + IS_STATE + "(S),N{" + TRUTH_VALUE_PREDICATE + "(X,S," + TRUTH_VALUE_T + "):" + CONJUNCT_OF + "(X,Y)}N," + NUM_CONJUNCTS + "(Y,N).";
    // F:
    // conjunction_rules += TRUTH_VALUE_PREDICATE + "(Y,S," + TRUTH_VALUE_F + "):-" + CONJUNCTION + "(Y)," + IS_STATE + "(S),1{" + TRUTH_VALUE_PREDICATE + "(X,S," + TRUTH_VALUE_F + ")}," + CONJUNCT_OF + "(X,Y).";
    conjunction_rules += TRUTH_VALUE_PREDICATE + "(Y,S," + TRUTH_VALUE_F + "):-" + CONJUNCTION + "(Y)," + IS_STATE + "(S),not " + TRUTH_VALUE_PREDICATE + "(Y,S," + TRUTH_VALUE_T + ")." ;

    return conjunction_rules;
}

std::string add_disjunction_rules_LTL_2VL(){
    std::string disjunction_rules = "";
    // T:
    // disjunction_rules += TRUTH_VALUE_PREDICATE + "(Y,S," + TRUTH_VALUE_T + "):-" + DISJUNCTION + "(Y)," + IS_STATE + "(S),1{" + TRUTH_VALUE_PREDICATE + "(X,S," + TRUTH_VALUE_T + ")}," + DISJUNCT_OF + "(X,Y).";
    disjunction_rules += TRUTH_VALUE_PREDICATE + "(Y,S," + TRUTH_VALUE_T + "):-" + DISJUNCTION + "(Y)," + IS_STATE + "(S),not " + TRUTH_VALUE_PREDICATE + "(Y,S," + TRUTH_VALUE_F + ")." ;
    // F:
    disjunction_rules += TRUTH_VALUE_PREDICATE + "(Y,S," + TRUTH_VALUE_F + "):-" + DISJUNCTION + "(Y)," + IS_STATE + "(S),N{" + TRUTH_VALUE_PREDICATE + "(X,S," + TRUTH_VALUE_F + "):" + DISJUNCT_OF + "(X,Y)}N," + NUM_DISJUNCTS + "(Y,N).";

    return disjunction_rules;
}

std::string add_negation_rules_LTL_2VL(){
    std::string negation_rules = "";
    // T:
    negation_rules += TRUTH_VALUE_PREDICATE + "(Y,S," + TRUTH_VALUE_T + "):-" + NEGATION + "(X,Y)," + IS_STATE + "(S)," + TRUTH_VALUE_PREDICATE + "(X,S," + TRUTH_VALUE_F + ").";
    // F:
    negation_rules += TRUTH_VALUE_PREDICATE + "(Y,S," + TRUTH_VALUE_F + "):-" + NEGATION + "(X,Y)," + IS_STATE + "(S)," + TRUTH_VALUE_PREDICATE + "(X,S," + TRUTH_VALUE_T + ").";

    return negation_rules;
}

std::string add_next_rules_2VL(){
    std::string next_rules = "";
    // i < m:
    next_rules += TRUTH_VALUE_PREDICATE + "(F,S1,T):-" + IS_NEXT + "(F,G)," + IS_STATE + "(S1),tv(T),S2=S1+1,S1<M," + FINAL_STATE + "(M)," + TRUTH_VALUE_PREDICATE + "(G,S2,T).";
    // i >= m:
    next_rules += TRUTH_VALUE_PREDICATE + "(F,S," + TRUTH_VALUE_F + "):-" + IS_NEXT + "(F,_)," + IS_STATE + "(S),S>=M," + FINAL_STATE + "(M).";
    return next_rules;
}

std::string add_until_rules_2VL(){
    std::string until_rules = "";
    // T: 
    until_rules += TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_T + "):-" + IS_UNTIL + "(F,G,H)," + IS_STATE + "(S1)," + IS_STATE + "(S2),S2>S1,S2<=M," + FINAL_STATE + "(M),X{"
        + TRUTH_VALUE_PREDICATE + "(G,S," + TRUTH_VALUE_T + "):" + IS_STATE + "(S),S>=S1,S<S2}X,X=S2-S1," + TRUTH_VALUE_PREDICATE + "(H,S2," + TRUTH_VALUE_T + ").";
    // B:
    // until_rules += TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_B + "):-" + IS_UNTIL + "(F,G,H)," + IS_STATE + "(S1)," + IS_STATE + "(S2),S2>S1,S2<=M," + FINAL_STATE + "(M),X{"
    //     + TRUTH_VALUE_PREDICATE + "(G,S," + TRUTH_VALUE_B + "):" + IS_STATE + "(S),S>=S1,S<S2;" + TRUTH_VALUE_PREDICATE + "(H,S2," + TRUTH_VALUE_B + ");" + TRUTH_VALUE_PREDICATE + "(G,S," + TRUTH_VALUE_T + "):"
    //     + IS_STATE + "(S),S>=S1,S<S2;" + TRUTH_VALUE_PREDICATE + "(H,S2," + TRUTH_VALUE_T + ")}X,not " + TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_T + "),X=S2-S1+1.";
    // F:
    // until_rules += TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_F + "):-" + IS_UNTIL + "(F,_,_)," + IS_STATE  + "(S1),not " + TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_T + "),not " + TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_B + ").";
    until_rules += TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_F + "):-" + IS_UNTIL + "(F,_,_)," + IS_STATE  + "(S1),not " + TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_T + ").";

    return until_rules;
}

std::string add_globally_rules_2VL(){
    std::string gobally_rules = "";
    // T:
    gobally_rules += TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_T + "):-" + IS_GLOBALLY + "(F,G)," + IS_STATE + "(S1),X{" + TRUTH_VALUE_PREDICATE + "(G,S," + TRUTH_VALUE_T + "):" + IS_STATE + "(S),S>S1}X," + FINAL_STATE + "(M),X=M-S1.";
    // F:
    // gobally_rules += TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_F + "):-" + IS_GLOBALLY + "(F,G)," + IS_STATE + "(S1),1{" + TRUTH_VALUE_PREDICATE + "(G,S," + TRUTH_VALUE_F + "):" + IS_STATE + "(S),S>S1}.";
    gobally_rules += TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_F + "):-" + IS_GLOBALLY + "(F,_)," + IS_STATE + "(S1),not " + TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_T + ").";
    // B:
    // gobally_rules += TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_B + "):-" + IS_GLOBALLY + "(F,_)," + IS_STATE + "(S1),not " + TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_T + "),not " + TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_F + ").";

    return gobally_rules;
}

std::string add_finally_rules_2VL(){
    std::string finally_rules = "";
    // T:
    finally_rules += TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_T + "):-" + IS_FINALLY + "(F,G)," + IS_STATE + "(S1)," + TRUTH_VALUE_PREDICATE + "(G,S2," + TRUTH_VALUE_T + ")," + IS_STATE + "(S2),S2>S1.";
    // F:
    // finally_rules += TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_F + "):-" + IS_FINALLY + "(F,G)," + IS_STATE + "(S1),X{" + TRUTH_VALUE_PREDICATE + "(G,S," + TRUTH_VALUE_F + "):" + IS_STATE + "(S),S>S1}X," + FINAL_STATE + "(M),X=M-S1.";
    finally_rules += TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_F + "):-" + IS_FINALLY + "(F,_)," + IS_STATE + "(S1),not " + TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_T + ").";
    // B:
    // finally_rules += TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_B + "):-" + IS_FINALLY + "(F,_)," + IS_STATE + "(S1),not " + TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_T + "),not " + TRUTH_VALUE_PREDICATE + "(F,S1," + TRUTH_VALUE_F + ").";

    return finally_rules;
}

std::string get_base_program_LTL_conformance_checking(Kb& kb){

    std::string program = "";

    program += IS_STATE + "(0..X):-" + FINAL_STATE + "(X).";

    // add truth value rules:
    program += add_truth_values_LTL_2VL();

    // add integrity constraint:
    program += ":-" + TRUTH_VALUE_PREDICATE + "(X,0," + TRUTH_VALUE_F + ")," + KB_MEMBER + "(X)," + IS_STATE + "(0).";

    // Unique atom evaluation:
    // program += "1{" + TRUTH_VALUE_PREDICATE + "(A,S,T):tv(T)}1:-" + ATOM + "(A)," + IS_STATE + "(S).";

    // add rule for each atom in the signature:
    program += add_atom_rules(kb);

    // add rules for each formula:
    program += handle_formulas_in_kb_LTL(kb);

    // add universal rules for connectors and formulas consisting of single atoms:
    program += TRUTH_VALUE_PREDICATE + "(F,S,T):-tv(T)," + FORMULA_IS_ATOM + "(F,A)," + IS_STATE + "(S)," + TRUTH_VALUE_PREDICATE + "(A,S,T).";

    if(program.find(CONJUNCTION) != std::string::npos)
        program += add_conjunction_rules_LTL_2VL();
    if(program.find(DISJUNCTION) != std::string::npos)
        program += add_disjunction_rules_LTL_2VL();
    if(program.find(NEGATION) != std::string::npos)
        program += add_negation_rules_LTL_2VL();
    if(program.find(IS_NEXT) != std::string::npos)
        program += add_next_rules_2VL();
    if(program.find(IS_UNTIL) != std::string::npos)
        program += add_until_rules_2VL();
    if(program.find(IS_GLOBALLY) != std::string::npos)
        program += add_globally_rules_2VL();
    if(program.find(IS_FINALLY) != std::string::npos)
        program += add_finally_rules_2VL();

    return program;
}

void conformance_checking(Kb& kb, std::string path_to_traces){

    // initialize program string:
    std::string program = "";
    
    program += get_base_program_LTL_conformance_checking(kb);
    program += TRUTH_VALUE_PREDICATE + "(A,S," + TRUTH_VALUE_F + "):-" + ATOM + "(A)," + IS_STATE + "(S),not " + TRUTH_VALUE_PREDICATE + "(A,S," + TRUTH_VALUE_T + ").";
    program += TRUTH_VALUE_PREDICATE + "(A,S," + TRUTH_VALUE_T + "):-" + ATOM + "(A)," + IS_STATE + "(S),not " + TRUTH_VALUE_PREDICATE + "(A,S," + TRUTH_VALUE_F + ").";

    // iterate over traces:
    // std::vector<std::string> curr_trace;
    int count = 0;
    std::ifstream file(path_to_traces);
    if (file.is_open()) {
        std::string line;
        int count = 1;
        while (std::getline(file, line)) {

            std::vector<std::string> curr_trace = split_by_comma(line);

            // get trace length
            int trace_length = curr_trace.size();

            std::string curr_program = program;
            // set number of states:
            curr_program += FINAL_STATE + "(" + std::to_string(trace_length-1) + ").";

            for (int i = 0; i < curr_trace.size(); i++){
                curr_program += TRUTH_VALUE_PREDICATE + "(" + curr_trace.at(i) + "," + std::to_string(i) + "," + TRUTH_VALUE_T + ").";
            }

            bool is_sat = answerSetExists(curr_program);         
            std::cout << count << ") ";
            if (is_sat){
                std::cout << "sat" << std::endl;
            }
            else{
                std::cout << "unsat" << std::endl;
            }
            // std::cout << "m = " << std::to_string(trace_length-1) << std::endl;

            count++;

            // TODO: print nicer output

        }
    file.close();
    }
}

std::vector<std::string> split_by_comma(std::string& input){
    std::stringstream sstr(input);
    std::vector<std::string> result;
    while(sstr.good())
    {
        std::string substr;
        getline(sstr, substr, ',');

        if (std::islower(substr[0])){
            result.push_back(substr);
        }
    }

    return result;
}
