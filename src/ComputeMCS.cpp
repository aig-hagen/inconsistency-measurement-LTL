#include "ComputeMCS.h"

using namespace constants;

// Author: Isabelle Kuhlmann

std::string add_conjunction_rules_LTL_MCS(){
    std::string conjunction_rules = "";
    // CS:
    // T:
    conjunction_rules += TRUTH_VALUE_PREDICATE_CS + "(F,S," + TRUTH_VALUE_T + "):-" + CONJUNCTION + "(F)," + IS_STATE + "(S),N{" + TRUTH_VALUE_PREDICATE_CS + "(C,S," + TRUTH_VALUE_T + "):" + CONJUNCT_OF + "(C,F)}N," + NUM_CONJUNCTS + "(F,N).";
    // F:
    conjunction_rules += TRUTH_VALUE_PREDICATE_CS + "(F,S," + TRUTH_VALUE_F + "):-" + CONJUNCTION + "(F)," + IS_STATE + "(S),1{" + TRUTH_VALUE_PREDICATE_CS + "(C,S," + TRUTH_VALUE_F + ")}," + CONJUNCT_OF + "(C,F).";

    // Superset:
    // T:
    conjunction_rules += TRUTH_VALUE_PREDICATE_SET + "(F,Su,S," + TRUTH_VALUE_T + "):-" + CONJUNCTION + "(F)," + IS_STATE + "(S),N{" + TRUTH_VALUE_PREDICATE_SET + "(C,Su,S," + TRUTH_VALUE_T + "):" + CONJUNCT_OF + "(C,F)}N," + NUM_CONJUNCTS + "(F,N)," + IS_SUPERSET + "(Su).";
    // F:
    conjunction_rules += TRUTH_VALUE_PREDICATE_SET + "(F,Su,S," + TRUTH_VALUE_F + "):-" + CONJUNCTION + "(F)," + IS_STATE + "(S),1{" + TRUTH_VALUE_PREDICATE_SET + "(C,Su,S," + TRUTH_VALUE_F + ")}," + CONJUNCT_OF + "(C,F)," + IS_SUPERSET + "(Su).";

    return conjunction_rules;
}

std::string add_disjunction_rules_LTL_MCS(){
    std::string disjunction_rules = "";
    // CS:
    // T:
    disjunction_rules += TRUTH_VALUE_PREDICATE_CS + "(F,S," + TRUTH_VALUE_T + "):-" + DISJUNCTION + "(F)," + IS_STATE + "(S),1{" + TRUTH_VALUE_PREDICATE_CS + "(C,S," + TRUTH_VALUE_T + ")}," + DISJUNCT_OF + "(C,F).";
    // F:
    disjunction_rules += TRUTH_VALUE_PREDICATE_CS + "(F,S," + TRUTH_VALUE_F + "):-" + DISJUNCTION + "(F)," + IS_STATE + "(S),N{" + TRUTH_VALUE_PREDICATE_CS + "(C,S," + TRUTH_VALUE_F + "):" + DISJUNCT_OF + "(C,F)}N," + NUM_DISJUNCTS + "(F,N).";

    // Superset:
    // T:
    disjunction_rules += TRUTH_VALUE_PREDICATE_SET + "(F,Su,S," + TRUTH_VALUE_T + "):-" + DISJUNCTION + "(F)," + IS_STATE + "(S),1{" + TRUTH_VALUE_PREDICATE_SET + "(C,Su,S," + TRUTH_VALUE_T + ")}," + DISJUNCT_OF + "(C,F)," + IS_SUPERSET + "(Su).";
    // F:
    disjunction_rules += TRUTH_VALUE_PREDICATE_SET + "(F,Su,S," + TRUTH_VALUE_F + "):-" + DISJUNCTION + "(F)," + IS_STATE + "(S),N{" + TRUTH_VALUE_PREDICATE_SET + "(C,Su,S," + TRUTH_VALUE_F + "):" + DISJUNCT_OF + "(C,F)}N," + NUM_DISJUNCTS + "(F,N)," + IS_SUPERSET + "(Su).";

    return disjunction_rules;
}

std::string add_negation_rules_LTL_MCS(){
    std::string negation_rules = "";
    // CS:
    // T:
    negation_rules += TRUTH_VALUE_PREDICATE_CS + "(F,S," + TRUTH_VALUE_T + "):-" + NEGATION + "(F,G)," + IS_STATE + "(S)," + TRUTH_VALUE_PREDICATE_CS + "(G,S," + TRUTH_VALUE_F + ").";
    // F:
    negation_rules += TRUTH_VALUE_PREDICATE_CS + "(F,S," + TRUTH_VALUE_F + "):-" + NEGATION + "(F,G)," + IS_STATE + "(S)," + TRUTH_VALUE_PREDICATE_CS + "(G,S," + TRUTH_VALUE_T + ").";

    // Superset:
    // T:
    negation_rules += TRUTH_VALUE_PREDICATE_SET + "(F,Su,S," + TRUTH_VALUE_T + "):-" + NEGATION + "(F,G)," + IS_STATE + "(S)," + TRUTH_VALUE_PREDICATE_SET + "(G,Su,S," + TRUTH_VALUE_F + ")," + IS_SUPERSET + "(Su).";
    // F:
    negation_rules += TRUTH_VALUE_PREDICATE_SET + "(F,Su,S," + TRUTH_VALUE_F + "):-" + NEGATION + "(F,G)," + IS_STATE + "(S)," + TRUTH_VALUE_PREDICATE_SET + "(G,Su,S," + TRUTH_VALUE_T + ")," + IS_SUPERSET + "(Su).";

    return negation_rules;
}

std::string add_next_rules_MCS(){
    std::string next_rules = "";
    // CS:
    // i < m:
    next_rules += TRUTH_VALUE_PREDICATE_CS + "(F,S1,T):-" + IS_NEXT + "(F,G)," + IS_STATE + "(S1),tv(T),S2=S1+1,S1<M," + FINAL_STATE + "(M)," + TRUTH_VALUE_PREDICATE_CS + "(G,S2,T).";
    // i >= m:
    next_rules += TRUTH_VALUE_PREDICATE_CS + "(F,S," + TRUTH_VALUE_F + "):-" + IS_NEXT + "(F,_)," + IS_STATE + "(S),S>=M," + FINAL_STATE + "(M).";

    // Superset:
    // i < m:
    next_rules += TRUTH_VALUE_PREDICATE_SET + "(F,Su,S1,T):-" + IS_NEXT + "(F,G)," + IS_STATE + "(S1),tv(T),S2=S1+1,S1<M," + FINAL_STATE + "(M)," + TRUTH_VALUE_PREDICATE_SET + "(G,Su,S2,T)," + IS_SUPERSET + "(Su).";
    // i >= m:
    next_rules += TRUTH_VALUE_PREDICATE_SET + "(F,Su,S," + TRUTH_VALUE_F + "):-" + IS_NEXT + "(F,_)," + IS_STATE + "(S),S>=M," + FINAL_STATE + "(M)," + IS_SUPERSET + "(Su).";

    return next_rules;
}

std::string add_until_rules_MCS(){
    std::string until_rules = "";
    // CS:
    // T:
    until_rules += TRUTH_VALUE_PREDICATE_CS + "(F,S1," + TRUTH_VALUE_T + "):-" + IS_UNTIL + "(F,G,H)," + IS_STATE + "(S1)," + TRUTH_VALUE_PREDICATE_CS + "(G,S1," + TRUTH_VALUE_T + ")," + TRUTH_VALUE_PREDICATE_CS + "(H,S1," + TRUTH_VALUE_T + ").";

    until_rules += TRUTH_VALUE_PREDICATE_CS + "(F,S1," + TRUTH_VALUE_T + "):-" + IS_UNTIL + "(F,G,H)," + IS_STATE + "(S1)," + IS_STATE + "(S2),S2>S1,S2<=M," + FINAL_STATE + "(M),X{"
        + TRUTH_VALUE_PREDICATE_CS + "(G,S," + TRUTH_VALUE_T + "):" + IS_STATE + "(S),S>=S1,S<S2}X,X=S2-S1," + TRUTH_VALUE_PREDICATE_CS + "(H,S2," + TRUTH_VALUE_T + ").";

    // F:
    until_rules += TRUTH_VALUE_PREDICATE_CS + "(F,S1," + TRUTH_VALUE_F + "):-" + IS_UNTIL + "(F,G,H)," + IS_STATE  + "(S1),X{" + TRUTH_VALUE_PREDICATE_CS + "(H,S," + TRUTH_VALUE_F + "):" + IS_STATE + "(S),S>=S1}X," + FINAL_STATE + "(M),X=M-S1+1.";

    until_rules += TRUTH_VALUE_PREDICATE_CS + "(F,S1," + TRUTH_VALUE_F + "):-" + IS_UNTIL + "(F,G,H)," + IS_STATE  + "(S1)," + IS_STATE  + "(S2)," + TRUTH_VALUE_PREDICATE_CS + "(H,S2," + TRUTH_VALUE_T + "),S2>S1,S2<=M," + FINAL_STATE + "(M),1{"
        + TRUTH_VALUE_PREDICATE_CS + "(G,S," + TRUTH_VALUE_F + "):" + IS_STATE + "(S),S>=S1,S<S2}.";

    // Superset:
    // T:
    until_rules += TRUTH_VALUE_PREDICATE_SET + "(F,Su,S1," + TRUTH_VALUE_T + "):-" + IS_UNTIL + "(F,G,H)," + IS_STATE + "(S1)," + TRUTH_VALUE_PREDICATE_SET + "(G,Su,S1," + TRUTH_VALUE_T + ")," + TRUTH_VALUE_PREDICATE_SET + "(H,Su,S1," + TRUTH_VALUE_T + ")," + IS_SUPERSET + "(Su).";

    until_rules += TRUTH_VALUE_PREDICATE_SET + "(F,Su,S1," + TRUTH_VALUE_T + "):-" + IS_UNTIL + "(F,G,H)," + IS_STATE + "(S1)," + IS_STATE + "(S2),S2>S1,S2<=M," + FINAL_STATE + "(M),X{"
        + TRUTH_VALUE_PREDICATE_SET + "(G,Su,S," + TRUTH_VALUE_T + "):" + IS_STATE + "(S),S>=S1,S<S2}X,X=S2-S1," + TRUTH_VALUE_PREDICATE_SET + "(H,Su,S2," + TRUTH_VALUE_T + ")," + IS_SUPERSET + "(Su).";

    // F:
    until_rules += TRUTH_VALUE_PREDICATE_SET + "(F,Su,S1," + TRUTH_VALUE_F + "):-" + IS_UNTIL + "(F,G,H)," + IS_STATE  + "(S1),X{" + TRUTH_VALUE_PREDICATE_SET + "(H,Su,S," + TRUTH_VALUE_F + "):" + IS_STATE + "(S),S>=S1}X," + FINAL_STATE + "(M),X=M-S1+1," + IS_SUPERSET + "(Su).";

    until_rules += TRUTH_VALUE_PREDICATE_SET + "(F,Su,S1," + TRUTH_VALUE_F + "):-" + IS_UNTIL + "(F,G,H)," + IS_STATE  + "(S1)," + IS_STATE  + "(S2)," + TRUTH_VALUE_PREDICATE_SET + "(H,Su,S2," + TRUTH_VALUE_T + "),S2>S1,S2<=M," + FINAL_STATE + "(M),1{"
        + TRUTH_VALUE_PREDICATE_SET + "(G,Su,S," + TRUTH_VALUE_F + "):" + IS_STATE + "(S),S>=S1,S<S2}," + IS_SUPERSET + "(Su).";

    return until_rules;
}

std::string add_globally_rules_MCS(){
    std::string gobally_rules = "";
    // CS:
    // T:
    gobally_rules += TRUTH_VALUE_PREDICATE_CS + "(F,S1," + TRUTH_VALUE_T + "):-" + IS_GLOBALLY + "(F,G)," + IS_STATE + "(S1),X{" + TRUTH_VALUE_PREDICATE_CS + "(G,S," + TRUTH_VALUE_T + "):" + IS_STATE + "(S),S>=S1}X," + FINAL_STATE + "(M),X=M-S1+1.";
    // F:
    gobally_rules += TRUTH_VALUE_PREDICATE_CS + "(F,S1," + TRUTH_VALUE_F + "):-" + IS_GLOBALLY + "(F,G)," + IS_STATE + "(S1),1{" + TRUTH_VALUE_PREDICATE_CS + "(G,S," + TRUTH_VALUE_F + "):" + IS_STATE + "(S),S>S1}.";

    // Superset:
    // T:
    gobally_rules += TRUTH_VALUE_PREDICATE_SET + "(F,Su,S1," + TRUTH_VALUE_T + "):-" + IS_GLOBALLY + "(F,G)," + IS_STATE + "(S1),X{" + TRUTH_VALUE_PREDICATE_SET + "(G,Su,S," + TRUTH_VALUE_T + "):" + IS_STATE + "(S),S>=S1}X," + FINAL_STATE + "(M),X=M-S1+1," + IS_SUPERSET + "(Su).";
    // F:
    gobally_rules += TRUTH_VALUE_PREDICATE_SET + "(F,Su,S1," + TRUTH_VALUE_F + "):-" + IS_GLOBALLY + "(F,G)," + IS_STATE + "(S1),1{" + TRUTH_VALUE_PREDICATE_SET + "(G,Su,S," + TRUTH_VALUE_F + "):" + IS_STATE + "(S),S>S1}," + IS_SUPERSET + "(Su).";

    return gobally_rules;
}

std::string add_finally_rules_MCS(){
    std::string finally_rules = "";
    // CS:
    // T:
    finally_rules += TRUTH_VALUE_PREDICATE_CS + "(F,S1," + TRUTH_VALUE_T + "):-" + IS_FINALLY + "(F,G)," + IS_STATE + "(S1)," + IS_STATE + "(S2)," + TRUTH_VALUE_PREDICATE_CS + "(G,S2," + TRUTH_VALUE_T + "),S2>=S1.";
    // F:
    finally_rules += TRUTH_VALUE_PREDICATE_CS + "(F,S1," + TRUTH_VALUE_F + "):-" + IS_FINALLY + "(F,G)," + IS_STATE + "(S1),X{" + TRUTH_VALUE_PREDICATE_CS + "(G,S," + TRUTH_VALUE_F + "):" + IS_STATE + "(S),S>=S1}X," + FINAL_STATE + "(M),X=M-S1+1.";

    // Superset:
    // T:
    finally_rules += TRUTH_VALUE_PREDICATE_SET + "(F,Su,S1," + TRUTH_VALUE_T + "):-" + IS_FINALLY + "(F,G)," + IS_STATE + "(S1)," + IS_STATE + "(S2)," + TRUTH_VALUE_PREDICATE_SET + "(G,Su,S2," + TRUTH_VALUE_T + "),S2>=S1," + IS_SUPERSET + "(Su).";
    // F:
    finally_rules += TRUTH_VALUE_PREDICATE_SET + "(F,Su,S1," + TRUTH_VALUE_F + "):-" + IS_FINALLY + "(F,G)," + IS_STATE + "(S1),X{" + TRUTH_VALUE_PREDICATE_SET + "(G,Su,S," + TRUTH_VALUE_F + "):" + IS_STATE + "(S),S>=S1}X," + FINAL_STATE + "(M),X=M-S1+1," + IS_SUPERSET + "(Su).";

    return finally_rules;
}

std::string add_guess_candidate_set_rules_MCS(){

    std::string guess_cs = "1{" + IN_CS + "(X):" + KB_MEMBER + "(X)}.";

    // Auxiliary predicate that tells whether a formula is NOT in the candidate set:
    guess_cs += NOT_IN_CS + "(F):-" + KB_MEMBER + "(F),not " + IN_CS + "(F).";

    // Auxiliary predicate that determines whether an atom is contained in the candidate set:
    guess_cs += ATOM_IN_CS + "(A):-" + ATOM_IN_FORMULA + "(A,F)," + IN_CS + "(F).";

    // numElementsInCs(X) :- X = #count{F: inCs(F)}.
    guess_cs += NUM_ELEMENTS_IN_CS + "(X):-X=#count{F:" + IN_CS + "(F)}.";

    return guess_cs;
}

std::string add_SAT_check_of_CS_rules(){
    // Assign each atom in the candidate set exactly one truth value:
    std::string sat_rules = "1{" + TRUTH_VALUE_PREDICATE_CS + "(A,S,T):tv(T)}1:-" + ATOM + "(A)," + IS_STATE + "(S).";

    // The candidate set is satisfiable if all of its formulas can be evaluated to true:
    sat_rules += CS_IS_SAT + ":-" + NUM_ELEMENTS_IN_CS + "(X),X{" + TRUTH_VALUE_PREDICATE_CS + "(F,0," + TRUTH_VALUE_T + "):" + IN_CS + "(F)," + KB_MEMBER + "(F)}X.";

    // The candidate set must be satisfiable:
    sat_rules += ":-not " + CS_IS_SAT + ".";

    return sat_rules;
}

std::string add_superset_rules(){
    // Number of supersets required (i.e., |KB|-|CS|):
    std::string superset_rules = NUM_SUPERSETS + "(X):-" + NUM_ELEMENTS_IN_CS + "(Y)," + NUM_KB_ELEMENTS + "(Z),X=Z-Y.";

    // Define supersets:
    superset_rules += IS_SUPERSET + "(1..X):-" + NUM_SUPERSETS + "(X),X>0.";

    // Every formula that is not in the CS must be added to the CS once to form a superset:
    superset_rules += "1{" + ADDITIONAL_ELEMENT + "(F,Su):" + NOT_IN_CS + "(F)}1:-" + IS_SUPERSET + "(Su).";

    // No two supersets are allowed to be the same:
    superset_rules += SUPERSET_EQ + "(Su1,Su2):-" + IS_SUPERSET + "(Su1)," + IS_SUPERSET + "(Su2),Su1!=Su2," + ADDITIONAL_ELEMENT + "(F1,Su1)," + ADDITIONAL_ELEMENT + "(F2,Su2),F1==F2.";
    superset_rules += ":-" + SUPERSET_EQ + "(Su1,Su2).";

    // Define which formulas and atoms are included in each superset:
    superset_rules += IN_SUPERSET + "(F,Su):-" + IN_CS + "(F)," + IS_SUPERSET + "(Su).";
    superset_rules += IN_SUPERSET + "(F,Su):-" + ADDITIONAL_ELEMENT + "(F,Su)," + IS_SUPERSET + "(Su).";
    superset_rules += ATOM_IN_SUPERSET + "(A,Su):-" + ATOM_IN_CS + "(A)," + IS_SUPERSET + "(Su).";
    superset_rules += ATOM_IN_SUPERSET + "(A,Su):-" + ADDITIONAL_ELEMENT + "(F,Su)," + ATOM_IN_FORMULA + "(A,F).";

    return superset_rules;
}

std::string add_saturation_rules_MCS(){
    // Each atom in the superset can be true or false:
    std::string saturation_rules = TRUTH_VALUE_PREDICATE_SET + "(A,Su,S," + TRUTH_VALUE_T + ")|" + TRUTH_VALUE_PREDICATE_SET + "(A,Su,S," + TRUTH_VALUE_F + "):-" + ATOM_IN_SUPERSET + "(A,Su)," + IS_SUPERSET + "(Su)," + IS_STATE + "(S).";

    // A superset must evaluate to false under all interpretations:
    saturation_rules += IS_UNSAT + "(Su):-" + TRUTH_VALUE_PREDICATE_SET + "(F,Su,0," + TRUTH_VALUE_F + ")," + IN_SUPERSET + "(F,Su)," + KB_MEMBER + "(F).";
    // If a superset is not unsatisfiable, we do not want to derive an answer set:
    saturation_rules += ":-not " + IS_UNSAT + "(Su)," + IS_SUPERSET + "(Su).";

    // If all interpretations are considered, and no satisfiable solution is found, both truthValueInt(A,S,t) and truthValueInt(A,S,f) are derived wrt. a superset S:
    saturation_rules += TRUTH_VALUE_PREDICATE_SET + "(A,Su,S," + TRUTH_VALUE_T + "):-" + IS_UNSAT + "(Su)," + ATOM_IN_SUPERSET + "(A,Su)," + IS_SUPERSET + "(Su)," + IS_STATE + "(S).";
    saturation_rules += TRUTH_VALUE_PREDICATE_SET + "(A,Su,S," + TRUTH_VALUE_F + "):-" + IS_UNSAT + "(Su)," + ATOM_IN_SUPERSET + "(A,Su)," + IS_SUPERSET + "(Su)," + IS_STATE + "(S).";

    return saturation_rules;
}

std::string create_MCS_base_program(Kb& kb, int m){
    // initialize program string:
    std::string program = "";

    // set number of states:
    program += FINAL_STATE + "(" + std::to_string(m) + ").";
    program += IS_STATE + "(0..X):-" + FINAL_STATE + "(X).";

    program += add_truth_values_LTL();

    // number of KB elements:
    int numFormulas = kb.size();
    program += NUM_KB_ELEMENTS + "(" + std::to_string(numFormulas) + ").";

    program += handle_formulas_in_kb_LTL(kb);

    program += ATOM + "(A):-" + ATOM_IN_FORMULA + "(A,_).";
    program += KB_MEMBER + "(F):-" + ATOM_IN_FORMULA + "(_,F).";

    // handle formulas consisting of individual atoms
    program += TRUTH_VALUE_PREDICATE_CS + "(F,S,T):-tv(T)," + FORMULA_IS_ATOM + "(F,A)," + TRUTH_VALUE_PREDICATE_CS + "(A,S,T)," + IS_STATE + "(S).";
    
    program += TRUTH_VALUE_PREDICATE_SET + "(F,Su,S,T):-tv(T),"+ FORMULA_IS_ATOM + "(F,A)," + TRUTH_VALUE_PREDICATE_SET + "(A,Su,S,T)," + IS_STATE + "(S)," + IS_SUPERSET + "(Su).";

    // add connector rules:
    if(program.find(CONJUNCTION) != std::string::npos)
        program += add_conjunction_rules_LTL_MCS();
    if(program.find(DISJUNCTION) != std::string::npos)
        program += add_disjunction_rules_LTL_MCS();
    if(program.find(NEGATION) != std::string::npos)
        program += add_negation_rules_LTL_MCS();
    if(program.find(IS_NEXT) != std::string::npos)
        program += add_next_rules_MCS();
    if(program.find(IS_UNTIL) != std::string::npos)
        program += add_until_rules_MCS();
    if(program.find(IS_GLOBALLY) != std::string::npos)
        program += add_globally_rules_MCS();
    if(program.find(IS_FINALLY) != std::string::npos)
        program += add_finally_rules_MCS();

    // guess candidate set:
    program += add_guess_candidate_set_rules_MCS();

    // Check for satisfiability of candidate set:
    program += add_SAT_check_of_CS_rules();

    // Define supersets of the candidate set:
    program += add_superset_rules();

    // Check whether the supersets are unsatisfiable (using saturation):
    program += add_saturation_rules_MCS();

    return program;
}
