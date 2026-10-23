#pragma once
#include <iostream>
#include<string>
using namespace std;
class Node {
private:
	char symbol;
	Node* left=nullptr;
	Node* right=nullptr;
public:
	Node(char symbol) :symbol(symbol){}
	Node(char symbol,Node* left,Node* right):symbol(symbol),left(left),right(right){}
	Node(char symbol, Node* left) :symbol(symbol), left(left){}
	char symbol_getter()const { return symbol; }
	Node* left_child()const { return left; }
	Node* right_child()const { return right; }
	~Node() {
		delete left;
		delete right;
	}
	Node(const Node& node)  = delete;
	Node& operator =(const Node& node) = delete;
	
};

class Parser {
private:
	string exp;
	int index = 0;

	Node* parseOr()
	{
		if (index >= exp.length())
			return nullptr;
		Node* Or = parseXor();
		while (index < exp.length() && exp[index] == '|')
		{
			index++;
			Or = new Node('|', Or, parseXor());
		}
		return Or;
	}
	Node* parseXor()
	{
		if (index >= exp.length())
			return nullptr;
		Node* Xor = parseAnd();
		while (index < exp.length() && exp[index] == '^')
		{
			index++;
			Xor = new Node('^', Xor, parseAnd());
		}
		return Xor;
	}
	Node* parseAnd()
	{ 

		if (index >= exp.length())
			return nullptr;
		Node* And= parseNot();
		while (index <exp.length()&&exp[index] == '&')
		{
			index++;
			And = new Node('&',And, parseNot());
		}
		return And;
		
	}
	Node* parseNot() 
	{
		if (index >= exp.length())
			return nullptr;
		if (exp[index] == '!')
		{
			index++;
			Node* Not= new Node('!', parseNot());
			return Not;
    	}
		return parsePrimary();
	}
	Node* parsePrimary()
	{
		if (index>=exp.length())
			return nullptr;
		
		if (exp[index] > 64 && exp[index] < 91)
		{
			Node* sym = new Node(exp[index]);
			index++;
			return sym;
	    }
		if (exp[index] == '(')
		{
			index++;
			Node* current = nullptr;
				current=parseOr();
				if (index >= exp.length())
				{
					delete current;
					return nullptr;
				}
				if (exp[index] == ')')
				{
					index++;
					return current;
				}
		}
	}
public:
	Node* General()
	{
		Node*root=parseOr();
		return root;
	}
	Parser(const string exp) :exp(exp){}
};
