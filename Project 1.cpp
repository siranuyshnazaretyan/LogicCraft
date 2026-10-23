

#include <iostream>
#include <string>
#include <vector>
#include "Header.h"
using namespace std;
bool test_logic(const string& exp)
{

    for (int i = 0;i < exp.length();)
    {
        while ((i < exp.length()) && (exp[i] == '!' || exp[i] == '('))// (  and ! //
        {
            if (i == exp.length() - 1)
                return false;
            i++;
        }
        if (exp[i] > 64 && exp[i] < 91)//letteres//
        {
            if (i == exp.length() - 1)
                return true;
            i++;
            if (exp[i] == '&' || exp[i] == '^' || exp[i] == '|')//operationes///
            {
                if (i == exp.length() - 1)
                    return false;
                i++;
                if (!(exp[i] == '!' || exp[i] == '(')&&(exp[i] < 64 || exp[i] > 91 ))
                    return false;
            }
            else if (exp[i] == ')')// ) //
            {
                
                while (i < exp.length() && exp[i] == ')')
                {
                    if (i == exp.length() - 1)
                        return true;
                    i++;
                }
                if (!(exp[i] == '&' || exp[i] == '^' || exp[i] == '|' || exp[i] == ')'))
                    return false;
                else
                    if (i < exp.length()-1)
                        i++;
                    else
                        return false;

            }
            else
                return false;

        }
        else
            return false;
    }
    return false;
}
bool test_lexic(const string& exp)
{
    int test = 0;
    for (int i = 0;i < exp.length();i++)
    {
        if ((exp[i] > 64 && exp[i] < 91))//A-Z)
            test++;
       
        if(exp[i]=='('|| exp[i] == ')' || exp[i] == '&' ||
           exp[i] == '|' || exp[i] == '!' || exp[i] == '^')//synbols
            test++;

        if (test != i+1)
            return false;
    }
        return true;
    
}
bool test_brackets(const string& exp)
{
    int balance = 0;
    for (int i = 0;i < exp.length();i++)
    {
        if (exp[i] == '(')
            balance++;
        if (exp[i] == ')')
            balance--;
        if (balance < 0)
            return false;
    }
    if (!balance)
        return true;
    
    else
        return false;

}
bool AND(bool a,bool b)
{
    return a && b;
}
bool OR(bool a,bool b)
{
    return a||b;
}
bool XOR(bool a,bool b)
{
    return a^b;
}
bool NOT(bool a)
{
    return !a ;
}
void printTree(Node*root,int depth)
{
    if (root == nullptr)
        return;
    for (int i = 0;i < depth;i++)
    {
        cout << "  ";
    }
    cout << root->symbol_getter() << endl;
    printTree(root->left_child(), depth+1);
    printTree(root->right_child(), depth+1);
}
bool evaluate(Node* root, const vector<char>& var, const vector<bool>& val)
{
    if (root == nullptr)
        return 0;
    if (root->symbol_getter() > 64 && root->symbol_getter() < 91)
    {
        for (int i = 0;i < var.size();i++)
        {
            if (var[i] == root->symbol_getter())
                return val[i];

        }
    }
    if (root->symbol_getter() == '!')
    {
       return NOT( evaluate(root->left_child(), var, val));
    }
    if (root->symbol_getter() == '&')
    {
       return AND( evaluate(root->left_child(), var, val), evaluate(root->right_child(), var, val));
    }
    if (root->symbol_getter() == '^')
    {
       return XOR( evaluate(root->left_child(), var, val), evaluate(root->right_child(), var, val));
    }
    if (root->symbol_getter() == '|')
    {
       return OR( evaluate(root->left_child(), var, val), evaluate(root->right_child(), var, val));
    }
}

int main()
{
    string expression, exp;
    vector <char> variables;
    do
    {
        cout << "Enter the expression:";
        if (!getline(cin, expression))
            return 0;
        exp.clear();
        for (int i = 0;i < expression.length();i++)
        {
            if (expression[i] != ' ')
                exp.push_back(expression[i]);
        }

    } while (!(test_lexic(exp) && test_brackets(exp) && test_logic(exp)));

    int letteres[26] = { 0 };
    int n = 0;
    cout << "The vairables are: ";
    for (int i = 0;i < exp.size();i++)
    {

        if (exp[i] > 64 && exp[i] < 91)//A-Z
        {
            letteres[exp[i] - 65]++;
            if (letteres[exp[i] - 65] == 1)
            {
                variables.push_back(exp[i]);
                cout << exp[i] << " ";
            }
        }
    }
    cout << "the num of variables is: " << variables.size() << endl;

    Parser* test = new Parser(exp);
    Node* root = test->General();
    printTree(root, 0);
    n = variables.size();
    vector <bool>values(n);
    //sort of variablees
    for (int i = 0,j=0;i < 26;i++)
    {
        if (letteres[i])
        {
            variables[j] = char(i + 65);
            j++;
        }
    }
    for (int j = 0;j <n;j++)
    {
        cout << variables[j] << " ";
    }
    cout << " | " << "Rresult" << endl;
   for (unsigned long long i = 0;i <pow(2, variables.size());i++)
   {
       for (int j = 0;j <n;j++)
       {
           values[j] = ((i >> n-1-j) & 1);
           cout << values[j] << " ";
       }
       cout<<" | " << evaluate(root, variables, values) << endl;
   }
   delete root;
   delete test;
    return 0;
}
