// #include "LTLMeasuresASP.h"
#include "ComputeMIS.h"
#include <iostream>
using namespace constants;

// Author: Isabelle Kuhlmann

std::string add_truth_values_LTL(){
    std::string all_truth_values = "tv(" + TRUTH_VALUE_T + ").";
    all_truth_values += "tv(" + TRUTH_VALUE_F + ").";
    return all_truth_values;
}

std::string handle_formulas_in_kb_LTL(Kb& kb){
    std::vector<Formula> formulas = kb.GetFormulas();
    std::string formula_rules = "";
    for (int i = 0; i < formulas.size(); i++){
        std::string formula_name = FORMULA_PREFIX + std::to_string(i);
        for(std::string at : formulas.at(i).GetSignature()){
            std::transform(at.begin(), at.end(), at.begin(),
                [](unsigned char c){ return std::tolower(c); });
            std::string atom_in_formula_rule = ATOM_IN_FORMULA + "(" + at + "," + formula_name + ").";
            formula_rules += atom_in_formula_rule;
        }

        std::string curr_formula_rules = "";
        ltl_to_asp(formulas.at(i), formula_name, curr_formula_rules);
        formula_rules += curr_formula_rules;
    }

    return formula_rules;
}


std::string add_conjunction_rules_LTL(){
    std::string conjunction_rules = "";
    // T:
    conjunction_rules += TRUTH_VALUE_PREDICATE + "(F,S,I," + TRUTH_VALUE_T + "):-" + CONJUNCTION + "(F)," + INTERPRETATION + "(I)," + IS_STATE + "(S),N{" + TRUTH_VALUE_PREDICATE + "(C,S,I," + TRUTH_VALUE_T + "):" + CONJUNCT_OF + "(C,F)}N," + NUM_CONJUNCTS + "(F,N).";
    // F:
    conjunction_rules += TRUTH_VALUE_PREDICATE + "(F,S,I," + TRUTH_VALUE_F + "):-" + CONJUNCTION + "(F)," + INTERPRETATION + "(I)," + IS_STATE + "(S),1{" + TRUTH_VALUE_PREDICATE + "(C,S,I," + TRUTH_VALUE_F + ")}," + CONJUNCT_OF + "(C,F).";

    return conjunction_rules;
}

std::string add_disjunction_rules_LTL(){
    std::string disjunction_rules = "";
    // T:
    disjunction_rules += TRUTH_VALUE_PREDICATE + "(F,S,I," + TRUTH_VALUE_T + "):-" + DISJUNCTION + "(F)," + INTERPRETATION + "(I)," + IS_STATE + "(S),1{" + TRUTH_VALUE_PREDICATE + "(C,S,I," + TRUTH_VALUE_T + ")}," + DISJUNCT_OF + "(C,F).";
    // F:
    disjunction_rules += TRUTH_VALUE_PREDICATE + "(F,S,I," + TRUTH_VALUE_F + "):-" + DISJUNCTION + "(F)," + INTERPRETATION + "(I)," + IS_STATE + "(S),N{" + TRUTH_VALUE_PREDICATE + "(C,S,I," + TRUTH_VALUE_F + "):" + DISJUNCT_OF + "(C,F)}N," + NUM_DISJUNCTS + "(F,N).";

    return disjunction_rules;
}

std::string add_negation_rules_LTL(){
    std::string negation_rules = "";
    // T:
    negation_rules += TRUTH_VALUE_PREDICATE + "(F,S,I," + TRUTH_VALUE_T + "):-" + NEGATION + "(F,G)," + IS_STATE + "(S)," + INTERPRETATION + "(I)," + TRUTH_VALUE_PREDICATE + "(G,S,I," + TRUTH_VALUE_F + ").";
    // F:
    negation_rules += TRUTH_VALUE_PREDICATE + "(F,S,I," + TRUTH_VALUE_F + "):-" + NEGATION + "(F,G)," + IS_STATE + "(S)," + INTERPRETATION + "(I)," + TRUTH_VALUE_PREDICATE + "(G,S,I," + TRUTH_VALUE_T + ").";

    return negation_rules;
}

std::string add_next_rules(){
    std::string next_rules = "";
    // i < m:
    next_rules += TRUTH_VALUE_PREDICATE + "(F,S1,I,T):-" + IS_NEXT + "(F,G)," + INTERPRETATION + "(I)," + IS_STATE + "(S1),tv(T),S2=S1+1,S1<M," + FINAL_STATE + "(M)," + TRUTH_VALUE_PREDICATE + "(G,S2,I,T).";
    // i >= m:
    next_rules += TRUTH_VALUE_PREDICATE + "(F,S,I," + TRUTH_VALUE_F + "):-" + IS_NEXT + "(F,_)," + INTERPRETATION + "(I)," + IS_STATE + "(S),S>=M," + FINAL_STATE + "(M).";
    return next_rules;
}

std::string add_until_rules(){
    std::string until_rules = "";
    // T:
    until_rules += TRUTH_VALUE_PREDICATE + "(F,S1,I," + TRUTH_VALUE_T + "):-" + IS_UNTIL + "(F,G,H)," + IS_STATE + "(S1)," + TRUTH_VALUE_PREDICATE + "(G,S1,I," + TRUTH_VALUE_T + ")," + TRUTH_VALUE_PREDICATE + "(H,S1,I," + TRUTH_VALUE_T + ")," + INTERPRETATION + "(I).";

    until_rules += TRUTH_VALUE_PREDICATE + "(F,S1,I," + TRUTH_VALUE_T + "):-" + IS_UNTIL + "(F,G,H)," + IS_STATE + "(S1)," + IS_STATE + "(S2),S2>S1,S2<=M," + FINAL_STATE + "(M),X{"
        + TRUTH_VALUE_PREDICATE + "(G,S,I," + TRUTH_VALUE_T + "):" + IS_STATE + "(S),S>=S1,S<S2}X,X=S2-S1," + TRUTH_VALUE_PREDICATE + "(H,S2,I," + TRUTH_VALUE_T + ")," + INTERPRETATION + "(I).";

    // F:
    until_rules += TRUTH_VALUE_PREDICATE + "(F,S1,I," + TRUTH_VALUE_F + "):-" + IS_UNTIL + "(F,G,H)," + IS_STATE  + "(S1),X{" + TRUTH_VALUE_PREDICATE + "(H,S,I," + TRUTH_VALUE_F + "):" + IS_STATE + "(S),S>=S1}X," + FINAL_STATE + "(M),X=M-S1+1," + INTERPRETATION + "(I).";

    until_rules += TRUTH_VALUE_PREDICATE + "(F,S1,I," + TRUTH_VALUE_F + "):-" + IS_UNTIL + "(F,G,H)," + IS_STATE  + "(S1)," + IS_STATE  + "(S2)," + TRUTH_VALUE_PREDICATE + "(H,S2,I," + TRUTH_VALUE_T + "),S2>S1,S2<=M," + FINAL_STATE + "(M),1{"
        + TRUTH_VALUE_PREDICATE + "(G,S,I," + TRUTH_VALUE_F + "):" + IS_STATE + "(S),S>=S1,S<S2}," + INTERPRETATION + "(I).";

    return until_rules;
}

std::string add_globally_rules(){
    std::string gobally_rules = "";
    // T:
    gobally_rules += TRUTH_VALUE_PREDICATE + "(F,S1,I," + TRUTH_VALUE_T + "):-" + IS_GLOBALLY + "(F,G)," + IS_STATE + "(S1),X{" + TRUTH_VALUE_PREDICATE + "(G,S,I," + TRUTH_VALUE_T + "):" + IS_STATE + "(S),S>=S1}X," + FINAL_STATE + "(M),X=M-S1+1," + INTERPRETATION + "(I).";
    // F:
    gobally_rules += TRUTH_VALUE_PREDICATE + "(F,S1,I," + TRUTH_VALUE_F + "):-" + IS_GLOBALLY + "(F,G)," + IS_STATE + "(S1),1{" + TRUTH_VALUE_PREDICATE + "(G,S,I," + TRUTH_VALUE_F + "):" + IS_STATE + "(S),S>=S1}," + INTERPRETATION + "(I).";

    return gobally_rules;
}

std::string add_finally_rules(){
    std::string finally_rules = "";
    // T:
    finally_rules += TRUTH_VALUE_PREDICATE + "(F,S1,I," + TRUTH_VALUE_T + "):-" + IS_FINALLY + "(F,G)," + IS_STATE + "(S1)," + IS_STATE + "(S2)," + TRUTH_VALUE_PREDICATE + "(G,S2,I," + TRUTH_VALUE_T + "),S2>=S1," + INTERPRETATION + "(I).";
    // F:
    finally_rules += TRUTH_VALUE_PREDICATE + "(F,S1,I," + TRUTH_VALUE_F + "):-" + IS_FINALLY + "(F,G)," + IS_STATE + "(S1),X{" + TRUTH_VALUE_PREDICATE + "(G,S,I," + TRUTH_VALUE_F + "):" + IS_STATE + "(S),S>=S1}X," + FINAL_STATE + "(M),X=M-S1+1," + INTERPRETATION + "(I).";

    return finally_rules;
}


std::string add_guess_candidate_set_rules(){

    std::string guess_cs = "1{" + IN_CS + "(X):" + KB_MEMBER + "(X)}.";

    guess_cs += ATOM_IN_CS + "(A):-" + ATOM_IN_FORMULA + "(A,F)," + IN_CS + "(F).";

    guess_cs += NUM_ELEMENTS_IN_CS + "(X):-X=#count{F:" + IN_CS + "(F)}.";
    guess_cs += NUM_ELEMENTS_IN_SUBSET + "(X):-" + NUM_ELEMENTS_IN_CS + "(Y),X=Y-1.";

    return guess_cs;
}


std::string add_SAT_check_rules(){
    // Define subsets:
    std::string sat_rules = IS_SUBSET + "(1..X):-" + NUM_ELEMENTS_IN_CS + "(X),X>1.";

    // Fill subsets with formulas from the candidate set
    sat_rules += "Y{" + IN_SUBSET + "(F,Ss):" + IN_CS + "(F)}Y:-" + IS_SUBSET + "(Ss)," + NUM_ELEMENTS_IN_SUBSET + "(Y).";

    // Define equality of two subsets:
    sat_rules += SUBSET_EQ + "(S1,S2):-" + IS_SUBSET + "(S1)," + IS_SUBSET + "(S2),S1!=S2,X=#count{F:" + IN_SUBSET + "(F,S1)," + IN_SUBSET + "(F,S2)}," + NUM_ELEMENTS_IN_SUBSET + "(Y),X==Y.";

    // Ensure that all subsets are different, i. e., no pair of subsets is allowed to be equal:
    sat_rules += ":-" + SUBSET_EQ + "(S1,S2).";

    // Define interpretations:
    sat_rules += INTERPRETATION + "(1..X):-" + NUM_ELEMENTS_IN_CS + "(X),X>1.";

    // Assign each atom exactly one truth value wrt. each interpretation:
    sat_rules += "1{" + TRUTH_VALUE_PREDICATE + "(A,S,I,T):tv(T)}1:-" + ATOM + "(A)," + IS_STATE + "(S)," + INTERPRETATION + "(I),I!=u.";

    // A subset is satisfiable if all of its formulas can be evaluated to true under the same interpretation:
    sat_rules += SUBSET_IS_SAT + "(Ss):-" + IS_SUBSET + "(Ss)," + NUM_ELEMENTS_IN_SUBSET + "(X),X{" + TRUTH_VALUE_PREDICATE + "(F,0,I," + TRUTH_VALUE_T + "):" + IN_SUBSET + "(F,Ss),"
        + KB_MEMBER + "(F)}X," + INTERPRETATION + "(I),I!=u.";

    // If a subset is not satisfiable, the candidate set cannot be an MIS:
    sat_rules += ":-not " + SUBSET_IS_SAT + "(Ss)," + IS_SUBSET + "(Ss).";

    return sat_rules;
}


std::string add_saturation_rules(){
    // Create additional interpretation:
    std::string saturation_rules = INTERPRETATION + "(u).";

    // Each atom in the candidate set can be true or false:
    saturation_rules += TRUTH_VALUE_PREDICATE + "(A,S,u," + TRUTH_VALUE_T + ")|" + TRUTH_VALUE_PREDICATE + "(A,S,u," + TRUTH_VALUE_F + "):-" + ATOM_IN_CS + "(A)," + IS_STATE + "(S).";

    // The candidate set must evaluate to false under all interpretations:
    saturation_rules += IS_UNSAT + ":-" + TRUTH_VALUE_PREDICATE + "(F,0,u," + TRUTH_VALUE_F + ")," + IN_CS + "(F)," + KB_MEMBER + "(F).";

    // If the candidate set is not unsatisfiable, we do not want to derive an answer set:
    saturation_rules += ":-not " + IS_UNSAT + ".";

    // If all interpretations are considered, and no satisfiable solution is found, both truthValue(A,u,t) and truthValue(A,u,f) are derived:
    saturation_rules += TRUTH_VALUE_PREDICATE + "(A,S,u," + TRUTH_VALUE_T + "):-" + IS_UNSAT + "," + ATOM_IN_CS + "(A)," + IS_STATE + "(S).";
    saturation_rules += TRUTH_VALUE_PREDICATE + "(A,S,u," + TRUTH_VALUE_F + "):-" + IS_UNSAT + "," + ATOM_IN_CS + "(A)," + IS_STATE + "(S).";

    return saturation_rules;
}


void ltl_to_asp(Formula& formula, std::string formula_name, std::string& rules){
    if(formula.IsAtom()){
        std::string new_formula_name = formula.GetName();
        std::transform(new_formula_name.begin(), new_formula_name.end(), new_formula_name.begin(),
    [](unsigned char c){ return std::tolower(c); });
        rules += FORMULA_IS_ATOM + "(" + formula_name + "," + new_formula_name + ")." ;
        return;
    }

    if(formula.IsNegation()){
        auto subformulas = formula.GetSubformulas();
        Formula formula_without_negation = Formula(*(subformulas.begin()));
        std::string new_formula_name = formula_name + "_n";
        rules += NEGATION + "(" + formula_name + "," + new_formula_name + ").";
        ltl_to_asp(formula_without_negation, new_formula_name, rules);
    }

    if(formula.IsConjunction()){
        rules += CONJUNCTION + "(" + formula_name + ").";
        std::vector<Formula> conjuncts = formula.GetSubformulas();
        rules += NUM_CONJUNCTS + "(" + formula_name + "," + std::to_string(conjuncts.size()) + ").";

        int conjunct_count = 0;
        for(auto conjunct : conjuncts){
            std::string new_formula_name = formula_name + "_" + std::to_string(conjunct_count);
            rules += CONJUNCT_OF + "(" + new_formula_name + "," + formula_name + ").";

            conjunct_count++;

            ltl_to_asp(conjunct, new_formula_name, rules);
        }
    }

    if(formula.IsDisjunction()){
        rules += DISJUNCTION + "(" + formula_name + ").";
        std::vector<Formula> disjuncts = formula.GetSubformulas();
        rules += NUM_DISJUNCTS + "(" + formula_name + "," + std::to_string(disjuncts.size()) + ").";

        int disjunct_count = 0;
        for(auto disjunct : disjuncts){
            std::string new_formula_name = formula_name + "_" + std::to_string(disjunct_count);
            rules += DISJUNCT_OF + "(" + new_formula_name + "," + formula_name + ").";

            disjunct_count++;

            ltl_to_asp(disjunct, new_formula_name, rules);
        }
    }

    if(formula.IsImplication()){
        auto subformulas = formula.GetSubformulas();
        auto i = subformulas.begin();
        Formula left = *(i++);
        Formula right = *(i);
        Formula disj = Formula(Type::OR, Formula(Type::NOT, left), right);
        ltl_to_asp(disj, formula_name, rules);
    }

    if(formula.IsEquivalence()){
        auto subformulas = formula.GetSubformulas();
        auto i = subformulas.begin();
        Formula left = *(i++);
        Formula right = *(i);
        Formula disj_left = Formula(Type::OR, Formula(Type::NOT, left), right);
        Formula disj_right = Formula(Type::OR, Formula(Type::NOT, right), left);
        Formula conj = Formula(Type::AND, disj_left, disj_right);
        ltl_to_asp(conj, formula_name, rules);
    }

    if(formula.IsNext()){
        auto subformulas = formula.GetSubformulas();
        Formula base_formula = Formula(*(subformulas.begin()));
        std::string new_formula_name = formula_name + "_x";
        rules += IS_NEXT + "(" + formula_name + "," + new_formula_name + ").";
        ltl_to_asp(base_formula, new_formula_name, rules);
    }

    if(formula.IsUntil()){
        auto subformulas = formula.GetSubformulas();
        auto i = subformulas.begin();
        Formula left = *(i++);
        Formula right = *(i);

        std::string new_formula_name_left = formula_name + "_l";
        std::string new_formula_name_right = formula_name + "_r";
        rules += IS_UNTIL + "(" + formula_name + "," + new_formula_name_left + "," + new_formula_name_right + ").";
        ltl_to_asp(left, new_formula_name_left, rules);
        ltl_to_asp(right, new_formula_name_right, rules);
    }

    if(formula.IsGlobally()){
        auto subformulas = formula.GetSubformulas();
        Formula base_formula = Formula(*(subformulas.begin()));
        std::string new_formula_name = formula_name + "_g";
        rules += IS_GLOBALLY + "(" + formula_name + "," + new_formula_name + ").";
        ltl_to_asp(base_formula, new_formula_name, rules);
    }

    if(formula.IsFinally()){
        auto subformulas = formula.GetSubformulas();
        Formula base_formula = Formula(*(subformulas.begin()));
        std::string new_formula_name = formula_name + "_f";
        rules += IS_FINALLY + "(" + formula_name + "," + new_formula_name + ").";
        ltl_to_asp(base_formula, new_formula_name, rules);
    }
}

std::string get_base_program_LTL(Kb& kb){

    std::string program = "";

    program += IS_STATE + "(0..X):-" + FINAL_STATE + "(X).";

    // add truth value rules:
    program += add_truth_values_LTL();

    // add rules for each formula:
    program += handle_formulas_in_kb_LTL(kb);

    // atom(A) :- atomInFormula(A,_).
    program += ATOM + "(A):-" + ATOM_IN_FORMULA + "(A,_).";
    // kbMember(F) :- atomInFormula(_,F).
    program += KB_MEMBER + "(F):-" + ATOM_IN_FORMULA + "(_,F).";

    // add universal rules for connectors and formulas consisting of single atoms:
    program += TRUTH_VALUE_PREDICATE + "(F,S,I,T):-tv(T)," + FORMULA_IS_ATOM + "(F,A)," + IS_STATE + "(S)," + INTERPRETATION + "(I)," + TRUTH_VALUE_PREDICATE + "(A,S,I,T).";

    if(program.find(CONJUNCTION) != std::string::npos)
        program += add_conjunction_rules_LTL();
    if(program.find(DISJUNCTION) != std::string::npos)
        program += add_disjunction_rules_LTL();
    if(program.find(NEGATION) != std::string::npos)
        program += add_negation_rules_LTL();
    if(program.find(IS_NEXT) != std::string::npos)
        program += add_next_rules();
    if(program.find(IS_UNTIL) != std::string::npos)
        program += add_until_rules();
    if(program.find(IS_GLOBALLY) != std::string::npos)
        program += add_globally_rules();
    if(program.find(IS_FINALLY) != std::string::npos)
        program += add_finally_rules();

    // guess candidate set and add auxiliary rules:
    program += add_guess_candidate_set_rules();

    // add SAT check of subsets of candidate set:
    program += add_SAT_check_rules();

    // add saturation part:
    program += add_saturation_rules();

    program += "#show " + IN_CS + "/1.";

    return program;
}


bool answerSetExists(std::string& program){
    Clingo::Logger logger = [](Clingo::WarningCode, char const *message) {
            std::cerr << message << std::endl;
        };
    Clingo::StringSpan string_span{"--opt-mode=opt"};
    Clingo::Control control{string_span, logger, 20};
    const char * program_char_array = program.c_str();

    control.add("base", {}, program_char_array);
    control.ground({{"base", {}}});

    // compute models:
    Clingo::SolveHandle sh = control.solve();
    Clingo::Model m = sh.model();

    if(m){
        std::cout << "answer set found" << std::endl;
        std::cout << m << std::endl;
        return true;
    }
    else{
        std::cout << "No MUS found." << std::endl;
        return false;
    }
}
