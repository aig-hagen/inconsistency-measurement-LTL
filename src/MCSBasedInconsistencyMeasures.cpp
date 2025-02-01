// #include "LTLMeasuresASP.h"
#include "ComputeMCS.h"
#include "MCSBasedInconsistencyMeasures.h"
#include <iostream>
using namespace constants;

// Author: Isabelle Kuhlmann

std::set<std::string> getFormulasInMCS(std::string& program){
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

    std::set<std::string> atom_list;

    if(m){
        // std::cout << m << std::endl;
        for (auto atom : m.symbols()){
            if (atom.match("notInCS",1)){
                for(auto arg : atom.arguments()){
                    atom_list.insert(arg.name());
                }
            }
        }
        return atom_list;
    }
    else{
        return atom_list;
    }

}

// needed for r measure
int compute_optimum(std::string& program){
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

    Clingo::SolveResult sr = sh.get();
    if(!sr.is_satisfiable()){
        return 0;
    }
    else{
        Clingo::Model m = sh.model();

        // get minimum value:
        int min_val = m.cost().at(0);
        while(sh.next()){
            Clingo::Model next_m = sh.model();
            if(next_m.cost().at(0) < min_val)
                min_val = m.cost().at(0);
        }

        return min_val;
    }
}

double p_measure_LTL_MCS(Kb& kb, int m){

    // Check if KB is empty:
    if(kb.size() == 0){
        std::cout << "Knowledge base is empty." << std::endl;
        return 0;
    }

    else{

        std::vector<Formula> formulas = kb.GetFormulas();

        std::set<std::string> formulas_in_MCS;
        std::set<std::string> remaining_formulas;

        for (int i = 0; i < kb.size(); i++){
            std::string formula_name = FORMULA_PREFIX + std::to_string(i);
            remaining_formulas.insert(formula_name);
            // std::cout << formula_name << std::endl;
        }

        std::string program = create_MCS_base_program(kb,m);

        program += "validCS:-1{" + NOT_IN_CS + "(F):" + QUERY_FORMULA + "(F)}.";
        program += ":-not validCS.";

        // std::cout << program << std::endl << std::endl;

        while(!remaining_formulas.empty()){

            // add query formulas:
            std::string all_query_formulas = "";

            for(auto f: remaining_formulas){
                std::string query_formula = QUERY_FORMULA + "(" + f + ").";
                all_query_formulas += query_formula;
                // std::cout << query_formula << std::endl;
            }
            // std::cout << std::endl;

            std::string curr_program = program + all_query_formulas;
            // std::cout << curr_program << std::endl << std::endl;

            // check if an answer set exists (via Clingo)
            // and check which formulas are included in the MCS found
            std::set<std::string> formulas_in_curr_MCS = getFormulasInMCS(curr_program);

            if (formulas_in_curr_MCS.empty()){
                // std::cout << "I'm empty :(" << std::endl << std::endl;
                break;
            }

            for(auto a: formulas_in_curr_MCS){
                formulas_in_MCS.insert(a);
                remaining_formulas.erase(a);
            }
        }
        return (double)formulas_in_MCS.size();
    }
}

double mv_measure_LTL_MCS(Kb& kb, int m){

    // Check if KB is empty:
    if(kb.size() == 0){
        std::cout << "Knowledge base is empty." << std::endl;
        return 0;
    }

    else{

        std::set<std::string> signature = kb.GetSignature();

        std::string program = create_MCS_base_program(kb,m);

        program += "validCS:-1{" + NOT_IN_CS + "(F):" + QUERY_FORMULA + "(F)}.";
        program += ":-not validCS.";

        std::set<std::string> formulas_in_MCS;
        std::set<std::string> atoms_in_MCS;

        // Create mapping between formula names and formulas
        std::map<std::string, Formula> formula_dict;
        std::vector<Formula> formulas = kb.GetFormulas();
        for (int i = 0; i < formulas.size(); i++){
            std::string formula_name = FORMULA_PREFIX + std::to_string(i);
            formula_dict.insert(std::pair<std::string, Formula>(formula_name, formulas.at(i)));
        }

        std::set<std::string> remaining_formulas;
        for(std::map<std::string,Formula>::iterator it = formula_dict.begin(); it != formula_dict.end(); ++it) {
            remaining_formulas.insert(it->first);
        }

        while(!remaining_formulas.empty()){
            // add query formulas:
            std::string all_query_formulas = "";

            for(auto f: remaining_formulas){
                std::string query_formula = QUERY_FORMULA + "(" + f + ").";
                all_query_formulas += query_formula;
            }

            std::string curr_program = program + all_query_formulas;

            // let Clingo solve the problem; check if an answer set exists:
            // also check which atoms are included in the MCS found
            std::set<std::string> formulas_in_curr_MCS = getFormulasInMCS(curr_program);

            if (formulas_in_curr_MCS.empty()){
                break;
            }

            for(auto f: formulas_in_curr_MCS){
                // get actual formula from dict
                Formula curr_formula = formula_dict.at(f);
                // get signature of formula
                std::set<std::string> curr_formula_signature = curr_formula.GetSignature();
                // add signature to atoms_in_MCS
                for (auto a: curr_formula_signature){
                    atoms_in_MCS.insert(a);
                }
                // remove formula from remaining_formulas
                remaining_formulas.erase(f);
            }

            // iterate over remaining_formulas:
            auto remaining_formulas_copy = remaining_formulas;
            for(auto f: remaining_formulas_copy){
                // - get signature of formula
                Formula curr_formula = formula_dict.at(f);
                std::set<std::string> curr_formula_signature = curr_formula.GetSignature();

                if(std::includes(atoms_in_MCS.begin(), atoms_in_MCS.end(), curr_formula_signature.begin(), curr_formula_signature.end())){
                    remaining_formulas.erase(f);
                }
            }
        }
        return (double)atoms_in_MCS.size() / (double)signature.size();
    }
}

int r_measure_LTL(Kb& kb, int m){

    // Check if KB is empty:
    if(kb.size() == 0){
        std::cout << "Knowledge base is empty." << std::endl;
        return 0;
    }

    else{
        std::string program = create_MCS_base_program(kb,m);
        // ensure that MCS is not empty:
        program += ":-not 1{" + NOT_IN_CS + "(X):" + KB_MEMBER + "(X)}.";

        program += "#minimize{1,F:" + NOT_IN_CS + "(F)}.";

        int result = compute_optimum(program);

        return result;

    }

}
