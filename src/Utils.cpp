#include "Utils.h"

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

// needed for get_kb_depth
void get_formula_depth(Formula& formula, int& formula_depth){
    if(formula.IsAtom()){
        return;
    }

    if(formula.IsNegation()){
        auto subformulas = formula.GetSubformulas();
        Formula formula_without_negation = Formula(*(subformulas.begin()));
        get_formula_depth(formula_without_negation, formula_depth);
    }

    if(formula.IsConjunction()){
        std::vector<Formula> conjuncts = formula.GetSubformulas();

        int curr_formula_depth = formula_depth;
        for(auto conjunct : conjuncts){
            int tmp_formula_depth = curr_formula_depth;
            get_formula_depth(conjunct, tmp_formula_depth);
            if (tmp_formula_depth > curr_formula_depth){
                formula_depth = tmp_formula_depth;
            }

        }
    }

    if(formula.IsDisjunction()){
        std::vector<Formula> disjuncts = formula.GetSubformulas();

        int curr_formula_depth = formula_depth;
        for(auto disjunct : disjuncts){
            int tmp_formula_depth = curr_formula_depth;
            get_formula_depth(disjunct, tmp_formula_depth);
            if (tmp_formula_depth > curr_formula_depth){
                formula_depth = tmp_formula_depth;
            }

        }
    }

    if(formula.IsImplication()){
        auto subformulas = formula.GetSubformulas();
        auto i = subformulas.begin();
        Formula left = *(i++);
        Formula right = *(i);
        Formula disj = Formula(Type::OR, Formula(Type::NOT, left), right);
        get_formula_depth(disj, formula_depth);
    }

    if(formula.IsEquivalence()){
        auto subformulas = formula.GetSubformulas();
        auto i = subformulas.begin();
        Formula left = *(i++);
        Formula right = *(i);
        Formula disj_left = Formula(Type::OR, Formula(Type::NOT, left), right);
        Formula disj_right = Formula(Type::OR, Formula(Type::NOT, right), left);
        Formula conj = Formula(Type::AND, disj_left, disj_right);
        get_formula_depth(conj, formula_depth);
    }

    if(formula.IsNext()){
        auto subformulas = formula.GetSubformulas();
        Formula base_formula = Formula(*(subformulas.begin()));

        formula_depth += 1;
        get_formula_depth(base_formula, formula_depth);
    }

    if(formula.IsWeaknext()){
        auto subformulas = formula.GetSubformulas();
        Formula base_formula = Formula(*(subformulas.begin()));

        formula_depth += 1;
        get_formula_depth(base_formula, formula_depth);
    }

    if(formula.IsUntil()){
        auto subformulas = formula.GetSubformulas();
        auto i = subformulas.begin();
        Formula left = *(i++);
        Formula right = *(i);

        int tmp_formula_depth_left = formula_depth;
        int tmp_formula_depth_right = formula_depth;
        get_formula_depth(left, tmp_formula_depth_left);
        get_formula_depth(right, tmp_formula_depth_right);

        if (tmp_formula_depth_left >= tmp_formula_depth_right){
            formula_depth = 1 + tmp_formula_depth_left;
        }
        else{
            formula_depth = 1 + tmp_formula_depth_right;
        }

    }

    if(formula.IsRelease()){
        auto subformulas = formula.GetSubformulas();
        auto i = subformulas.begin();
        Formula left = *(i++);
        Formula right = *(i);

        int tmp_formula_depth_left = formula_depth;
        int tmp_formula_depth_right = formula_depth;
        get_formula_depth(left, tmp_formula_depth_left);
        get_formula_depth(right, tmp_formula_depth_right);

        if (tmp_formula_depth_left >= tmp_formula_depth_right){
            formula_depth = 1 + tmp_formula_depth_left;
        }
        else{
            formula_depth = 1 + tmp_formula_depth_right;
        }

    }

    if(formula.IsGlobally()){
        auto subformulas = formula.GetSubformulas();
        Formula base_formula = Formula(*(subformulas.begin()));

        formula_depth += 1;
        get_formula_depth(base_formula, formula_depth);
    }

    if(formula.IsFinally()){
        auto subformulas = formula.GetSubformulas();
        Formula base_formula = Formula(*(subformulas.begin()));

        formula_depth += 1;
        get_formula_depth(base_formula, formula_depth);
    }
}

// needed for auto mode is selected for value m
int get_kb_depth(Kb& kb){
    std::vector<Formula> formulas = kb.GetFormulas();

    int max_depth = 0;
    int initial_depth = 0;

    for (int i = 0; i < formulas.size(); i++){
        int formula_depth = initial_depth;
        get_formula_depth(formulas.at(i), formula_depth);

        if (formula_depth > max_depth){
            max_depth = formula_depth;
        }
    }
    return max_depth;
}
