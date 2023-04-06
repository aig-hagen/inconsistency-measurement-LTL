#include "Parser.h"

#include <stdio.h>

#include <fstream>
#include <sstream>
#include <stack>

#include <iostream>

// Authors: Anna Gessler, Isabelle Kuhlmann

Kb Parser::ParseKbFromFile(std::string path)
{
    Kb k = Kb();
    std::vector<std::string> chs = std::vector<std::string>();
    std::ifstream kb_file(path);
    if (kb_file.fail())
    {
        std::stringstream msg;
        msg << "Parser Error: File " << path << " does not exist";
        throw std::runtime_error(msg.str().c_str());
    }
    if (kb_file.is_open())
    {
        std::string line;
        while (getline(kb_file, line))
        {
            if (!line.empty())
            {
              Formula f = ParseFormula(line);
              k.Add(f);
            }
        }
        kb_file.close();
    }
    return k;
}

Formula Parser::ParseFormulaFromString(std::string s)
{
    return ParseFormula(s);
}

Kb Parser::ParseKbFromString(std::string s)
{
    Kb k = Kb();
    std::string line;
    for (char c : s)
    {
        if (c == '\n' || c == '\r')
        {
            if (!line.empty())
            {
                Formula f = ParseFormula(line);
                k.Add(f);
                line = "";
            }
        }
        else
        {
            line += c;
        }
    }
    return k;
}

// The method is partly based on this implementation of the
// Shunting Yard Algorithm:
// https://rosettacode.org/wiki/Parsing/Shunting-yard_algorithm#C.2B.2B
Formula Parser::ParseFormula(const std::string &tokens)
{
    std::vector<std::string> output_list;
    std::stack<std::string> parsing_stack;

    bool stack_top_is_operator = false;
    for (auto &ctoken : tokens)
    {
        std::string s = std::string(1, ctoken);
        if (IsIgnoreToken(s))
        {
            continue;
        }

        std::string token = std::string(1, ctoken);
        // Case: Token is part of an operator --> concatenate tokens that belong to
        // the same operator
        if (token == "|" || token == "&" || token == "!" || token == "=" || token == ">" || token == "<" || token == "X" || token == "U" || token == "G" || token == "F")
        {
            stack_top_is_operator = true;
            if (token == "&" || token == "|")
            {
                if (parsing_stack.size() > 0)
                {
                    std::string t = parsing_stack.top();
                    if (t == token)
                    {
                        parsing_stack.pop();
                        s = token + token;
                    }
                    else
                    {
                        parsing_stack.push(token);
                        continue;
                    }
                }
                else
                {
                    parsing_stack.push(token);
                    continue;
                }
            }
            else if (token == "=" || token == "<" || token == "X" || token == "U" || token == "G" || token == "F")
            {
                parsing_stack.push(token);
                continue;
            }
            else if (token == ">")
            {
                std::string t = parsing_stack.top();
                if ((t == "="))
                {
                    parsing_stack.pop();
                    if (parsing_stack.size() > 0)
                    {
                        std::string t2 = parsing_stack.top();
                        if (t2 == "<")
                        {
                            parsing_stack.pop();
                            s = "<=>";
                        }
                        else
                        {
                            s = "=>";
                        }
                    }
                    else
                    {
                        s = "=>";
                    }
                }
                else if ((t == "X"))
                {
                    parsing_stack.pop();
                    if (parsing_stack.size() > 0)
                    {
                        std::string t2 = parsing_stack.top();
                        if (t2 == "<")
                        {
                            parsing_stack.pop();
                            s = "<X>";
                        }
                    }
                }
                else if ((t == "U"))
                {
                    parsing_stack.pop();
                    if (parsing_stack.size() > 0)
                    {
                        std::string t2 = parsing_stack.top();
                        if (t2 == "<")
                        {
                            parsing_stack.pop();
                            s = "<U>";
                        }
                    }
                }
                else if ((t == "G"))
                {
                    parsing_stack.pop();
                    if (parsing_stack.size() > 0)
                    {
                        std::string t2 = parsing_stack.top();
                        if (t2 == "<")
                        {
                            parsing_stack.pop();
                            s = "<G>";
                        }
                    }
                }
                else if ((t == "F"))
                {
                    parsing_stack.pop();
                    if (parsing_stack.size() > 0)
                    {
                        std::string t2 = parsing_stack.top();
                        if (t2 == "<")
                        {
                            parsing_stack.pop();
                            s = "<F>";
                        }
                    }
                }
                else
                {
                    parsing_stack.push(token);
                    continue;
                }
            }
        }

        // Case: Token is an identifier (atom name)
        if (IsIdentifier(s))
        {
            if (output_list.size() > 0 && !stack_top_is_operator && IsIdentifier(output_list[output_list.size() - 1]))
            {
                std::string t2 = output_list[output_list.size() - 1];
                output_list[output_list.size() - 1] = t2 + s;
            }
            else
            {
                output_list.push_back(s);
            }
            stack_top_is_operator = false;
        }

        // Case: Token is an operator or parenthesis
        else if (IsOperator(s) || IsParenthesis(s))
        {
            stack_top_is_operator = true;
            if (!IsOpenParenthesis(s))
            {
                // pop and move element to output list:
                // - until '(' if token is ')'
                // - while precedence(token) > precedence(top)
                // - while precedence(token) == precedence(top) AND associativity(token)
                // is left-to-right
                while (!parsing_stack.empty() && ((IsCloseParenthesis(s) && !IsOpenParenthesis(parsing_stack.top())) ||
                                                  (precedence(parsing_stack.top()) > precedence(s)) ||
                                                  ((precedence(parsing_stack.top()) == precedence(s)) &&
                                                   (associativity(s) == Associates::left_to_right))))
                {
                    output_list.push_back(parsing_stack.top());
                    parsing_stack.pop();
                }
                if (IsCloseParenthesis(s))
                {
                    if (parsing_stack.empty())
                    {
                        throw std::runtime_error("Parser Error: Input contains mismatched parentheses");
                    }
                    parsing_stack.pop();
                }
            }
            if (!IsCloseParenthesis(s))
            {
                parsing_stack.push(s);
            }
        }
        else
        {
            throw std::runtime_error("Parser Error: Illegal token " + token);
        }
    }

    if (parsing_stack.empty() && output_list.empty())
    {
        throw std::runtime_error("Parser Error: Empty parentheses");
        return Formula(Type::TRUE);
    }

    while (!parsing_stack.empty())
    {
        output_list.push_back(parsing_stack.top());
        parsing_stack.pop();
    }
    return ParseOutput(output_list);
}

// Converts the parsing stack into Formula instances
Formula Parser::ParseOutput(const std::vector<std::string> &parser_output)
{
    std::stack<Formula> temp;
    for (auto t : parser_output)
    {
        if (IsOperator(t))
        {
            if (t == "!" || t == "<X>" || t == "<G>" || t == "<F>")
            {
                Formula left = temp.top();
                temp.pop();
                Formula res = EvaluateUnaryExpression(left, t);
                temp.push(res);
            }
            else
            {
                Formula left = temp.top();
                temp.pop();
                if (temp.size() == 0)
                {
                    Formula res = EvaluateUnaryExpression(left, t);
                    temp.push(res);
                }
                else
                {
                    Formula right = temp.top();
                    temp.pop();
                    Formula res = EvaluateBinaryExpression(left, right, t);
                    temp.push(res);
                }
            }
        }
        else
        {
            temp.push(EvaluateAtomaryExpression(t));
        }
    }

    if (temp.empty())
    {
        throw std::runtime_error("General Parser Error");
        return Formula(Type::TRUE);
    }
    return Formula(temp.top());
}

// Parses input to '!(left)'
Formula Parser::EvaluateUnaryExpression(const Formula &left, std::string op)
{
    if (op == "!")
    {
        return Formula(Type::NOT, left);
    }
    else if (op == "&&")
    {
        return Formula(Type::AND, left);
    }
    else if (op == "||")
    {
        return Formula(Type::OR, left);
    }
    else if (op == "<X>")
    {
        return Formula(Type::NEXT, left);
    }
    else if (op == "<G>")
    {
        return Formula(Type::GLOBALLY, left);
    }
    else if (op == "<F>")
    {
        return Formula(Type::FINALLY, left);
    }
    else
    {
        std::stringstream msg;
        msg << "Parser Error: Invalid unary expression " << op << "(" << left << ")";
        throw std::runtime_error(msg.str().c_str());
        return Formula(Type::FALSE);
    }
}

// Parses input to 'left op right'
Formula Parser::EvaluateBinaryExpression(Formula &left, Formula &right, std::string op)
{
    if (op == "&&")
    {
        if (right.IsConjunction())
        {
            right.AddSubformula(left);
            return right;
        }
        if (left.IsConjunction())
        {
            left.AddSubformula(right);
            return left;
        }
        return Formula(Type::AND, right, left);
    }
    else if (op == "||")
    {
        if (right.IsDisjunction())
        {
            right.AddSubformula(left);
            return right;
        }
        if (left.IsDisjunction())
        {
            left.AddSubformula(right);
            return left;
        }
        return Formula(Type::OR, right, left);
    }
    else if (op == "=>")
    {
        return Formula(Type::IMPLIES, right, left);
    }
    else if (op == "<=>")
    {
        return Formula(Type::IFF, right, left);
    }
    else if (op == "<U>")
    {
        return Formula(Type::UNTIL, right, left);
    }
    else
    {
        std::stringstream msg;
        msg << "Parser Error: Invalid binary expression " << op << "(" << left << "," << right << ")";
        throw std::runtime_error(msg.str().c_str());
        return Formula(Type::FALSE);
    }
}

// Parses input to tautology, contradiction or atom
Formula Parser::EvaluateAtomaryExpression(std::string atom)
{
    if (atom == "+")
    {
        return Formula(Type::TRUE);
    }
    else if (atom == "-")
    {
        return Formula(Type::FALSE);
    }
    else
    {
        return Formula(atom);
    }
}
