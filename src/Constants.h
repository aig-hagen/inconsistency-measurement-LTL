#include <string>

// Author: Isabelle Kuhlmann

#ifndef INCONSISTENCY_MEASURE_ALGORITHMS_constants_h
#define INCONSISTENCY_MEASURE_ALGORITHMS_constants_h
namespace constants {
    static const std::string TRUTH_VALUE_T = "tv_t";
    static const std::string TRUTH_VALUE_B = "tv_b";
    static const std::string TRUTH_VALUE_F = "tv_f";

    static const std::string TRUTH_VALUE_PREDICATE = "truthValue";

    static const std::string ATOM = "atom";
    static const std::string KB_MEMBER = "kbMember";
    static const std::string FORMULA_PREFIX = "phi_";

    static const std::string CONJUNCTION = "conjunction";
    static const std::string CONJUNCT_OF = "conjunctOf";
    static const std::string NUM_CONJUNCTS = "numConjuncts";

    static const std::string DISJUNCTION = "disjunction";
    static const std::string DISJUNCT_OF = "disjunctOf";
    static const std::string NUM_DISJUNCTS = "numDisjuncts";

    static const std::string NEGATION = "negation";

    static const std::string FORMULA_IS_ATOM = "formulaIsAtom";

    static const std::string IS_NEXT = "next";
    static const std::string IS_UNTIL = "until";
    static const std::string IS_GLOBALLY = "globally";
    static const std::string IS_FINALLY = "finally";
    static const std::string IS_STATE = "state";
    static const std::string FINAL_STATE = "finalState";
    static const std::string NUM_B_IN_STATE = "numBInState";
    static const std::string SUM_B = "sumB";
    static const std::string AFFECTED_STATE = "as";

    // new constants unique to "mv-mis", "mv-mcs", "p-mis", "p-mcs", "r", "mi"

    static const std::string ATOM_IN_FORMULA = "aInF";

    static const std::string INTERPRETATION = "interp";
    static const std::string IN_CS = "inCS";
    static const std::string ATOM_IN_CS = "atomInCS";
    static const std::string NUM_ELEMENTS_IN_CS = "numElsInCS";
    static const std::string NUM_ELEMENTS_IN_SUBSET = "numElsInSub";
    static const std::string IS_SUBSET = "isSubset";
    static const std::string IN_SUBSET = "inSubset";
    static const std::string SUBSET_EQ = "subsetEq";
    static const std::string SUBSET_IS_SAT = "subsetIsSat";
    static const std::string IS_UNSAT = "isUnsat";

    static const std::string QUERY_FORMULA = "qf";
    static const std::string NUM_KB_ELEMENTS = "numKBEls";
    static const std::string TRUTH_VALUE_PREDICATE_CS = "tvCS";
    static const std::string TRUTH_VALUE_PREDICATE_SET = "tvSet";
    static const std::string IS_SUPERSET = "isSuperset";
    static const std::string NOT_IN_CS = "notInCS";
    static const std::string CS_IS_SAT = "csIsSAT";
    static const std::string NUM_SUPERSETS = "numSupers";
    static const std::string ADDITIONAL_ELEMENT = "addEl";
    static const std::string SUPERSET_EQ = "superEq";
    static const std::string IN_SUPERSET = "inSuperset";
    static const std::string ATOM_IN_SUPERSET = "atomInSuper";

    static const std::string NUM_ELEMENTS_IN_COMPLEMENT = "numElsInComp";

}
#endif