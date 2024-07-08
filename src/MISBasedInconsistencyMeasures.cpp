// #include "LTLMeasuresASP.h"
#include "ComputeMIS.h"
#include "MISBasedInconsistencyMeasures.h"
#include <iostream>
using namespace constants;

// Author: Isabelle Kuhlmann

std::set<std::string> getFormulasInMUS(std::string& program){
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
        for (auto atom : m.symbols()){
            if (atom.match("inCS",1)){
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
// needed for mi measure
int enumerate_all_solutions_with_projection(std::string& program){
    Clingo::Logger logger = [](Clingo::WarningCode, char const *message) {
            std::cerr << message << std::endl;
        };
    // use projection and get all solutions ("0")
    Clingo::StringSpan string_span{"--project", "0"};
    Clingo::Control control{string_span, logger, 20};
    const char * program_char_array = program.c_str();

    control.add("base", {}, program_char_array);
    control.ground({{"base", {}}});

    // compute models:
    Clingo::SolveHandle sh = control.solve();

    int num_solutions = 0;

    Clingo::SolveResult sr = sh.get();
    if(!sr.is_satisfiable()){
        return num_solutions;
    }
    else{
        Clingo::Model m = sh.model();
        num_solutions++;
        while(sh.next()){
            Clingo::Model next_m = sh.model();
            num_solutions++;
        }

    }

    return num_solutions;
}

double p_measure_LTL(Kb& kb, int m){

    // Check if KB is empty:
    if(kb.size() == 0){
        std::cout << "Knowledge base is empty." << std::endl;
        return 0;
    }

    else{

        std::vector<Formula> formulas = kb.GetFormulas();

        // initialize program string:
        std::string program = "";

        // set number of states:
        program += FINAL_STATE + "(" + std::to_string(m) + ").";

        std::set<std::string> formulas_in_MUS;
        std::set<std::string> remaining_formulas;

        for (int i = 0; i < kb.size(); i++){
            std::string formula_name = FORMULA_PREFIX + std::to_string(i);
            remaining_formulas.insert(formula_name);
        }

        program += get_base_program_LTL(kb);

        program += "validCS:-1{" + IN_CS + "(F):" + QUERY_FORMULA + "(F)}.";
        program += ":-not validCS.";

        while(!remaining_formulas.empty()){

            // add query formulas:
            std::string all_query_formulas = "";

            for(auto f: remaining_formulas){
                std::string query_formula = QUERY_FORMULA + "(" + f + ").";
                all_query_formulas += query_formula;
            }

            std::string curr_program = program + all_query_formulas;

            // check if an answer set exists (via Clingo)
            // and check which formulas are included in the MCS found
            std::set<std::string> formulas_in_curr_MUS = getFormulasInMUS(curr_program);

            if (formulas_in_curr_MUS.empty()){
                break;
            }

            for(auto a: formulas_in_curr_MUS){
                formulas_in_MUS.insert(a);
                remaining_formulas.erase(a);
            }
        }

        return (double)formulas_in_MUS.size();
    }
}

double mv_measure_LTL(Kb& kb, int m){

    // Check if KB is empty:
    if(kb.size() == 0){
        std::cout << "Knowledge base is empty." << std::endl;
        return 0;
    }

    else{

        std::set<std::string> signature = kb.GetSignature();

        // initialize program string:
        std::string program = "";

        // set number of states:
        program += FINAL_STATE + "(" + std::to_string(m) + ").";

        program += get_base_program_LTL(kb);

        program += "validCS:-1{" + IN_CS + "(F):" + QUERY_FORMULA + "(F)}.";
        program += ":-not validCS.";

        std::set<std::string> formulas_in_MUS;
        std::set<std::string> atoms_in_MUS;

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

            std::set<std::string> formulas_in_curr_MUS = getFormulasInMUS(curr_program);

            if (formulas_in_curr_MUS.empty()){
                break;
            }

            for(auto f: formulas_in_curr_MUS){
                // get actual formula from dict
                Formula curr_formula = formula_dict.at(f);
                // get signature of formula
                std::set<std::string> curr_formula_signature = curr_formula.GetSignature();
                // add signature to atoms_in_MUS
                for (auto a: curr_formula_signature){
                    atoms_in_MUS.insert(a);
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

                if(std::includes(atoms_in_MUS.begin(), atoms_in_MUS.end(), curr_formula_signature.begin(), curr_formula_signature.end())){
                    remaining_formulas.erase(f);
                }
            }
        }
        return (double)atoms_in_MUS.size() / (double)signature.size();
    }
}

int mi_measure_LTL(Kb& kb, int m){

    // Check if KB is empty:
    if(kb.size() == 0){
        std::cout << "Knowledge base is empty." << std::endl;
        return 0;
    }

    else{
        std::string program = get_base_program_LTL(kb);
        program += FINAL_STATE + "(" + std::to_string(m) + ").";

        program += "#show " + IN_CS + "/1.";
        program += "#project " + IN_CS + "/1.";

        int result = enumerate_all_solutions_with_projection(program);

        return result;

    }

}
