/*
Name: Vo Nguyen
Assignment 6
Date: 7 July 2020
bool tokenize(std::string s, std::vector<std::string>& tokens)

*/

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

bool is_op_paren(char c)
{
	return c == '*' or c == '+' or c == '-' or c == '/' or c == '(' or c == ')';
}

bool is_decimal_point(char c)
{
	return c == '.';
}

bool is_LT(char c)
{
	return c == '<';
}

bool is_GT(char c)
{
	return c == '>';
}

bool is_equal(char c)
{
	return c == '=';
}

bool tokenize(std::string s, std::vector<std::string>& tokens)
{
	enum{INTEGER, DECIMAL, FRAC, ALPHA, ALPHANUM, OP_PAREN, LT1, LT2, GT1,GT2, SPACE};

	std::string current_word;
	int state = SPACE;

	s.push_back(' ');

	for(char c : s)
	{
		if (state == INTEGER)
		{
			if (isdigit(c)) { current_word.push_back(c); }	
			else if (isspace(c))
			{
				tokens.push_back(current_word);
				current_word.clear();
				state = SPACE;
			}			
			else if (is_decimal_point(c))
			{
				state = DECIMAL;
				current_word.push_back(c);
			}
			else if (is_equal(c))
				return false;
			else
			{
				tokens.push_back(current_word);
				current_word.clear();
				current_word.push_back(c);

				if (isalpha(c)) state = ALPHA;
				else if (is_op_paren(c)) state = OP_PAREN;
				else if (is_LT(c)) state = LT1;
				else if (is_GT(c)) state = GT1;
				
			}
		}
		else if (state == DECIMAL)
		{
			if (isdigit(c))
			{
				current_word.push_back(c);
				state = FRAC;
			}
			else return false;
		}
		else if (state == FRAC)
		{
			if (isdigit(c)) current_word.push_back(c);
			else if (is_decimal_point(c) or is_equal(c))
				return false;
			else if (isspace(c))
			{
				tokens.push_back(current_word);
				current_word.clear();
				state = SPACE;
			}
			else 
			{
				tokens.push_back(current_word);
				current_word.clear();
				current_word.push_back(c);

				if (isalpha(c)) state = ALPHA;
				else if (is_op_paren(c)) state = OP_PAREN;
				else if (is_LT(c)) state = LT1;
				else if (is_GT(c)) state = GT1;
			}
		}
		else if (state == ALPHA)
		{
			if (isdigit(c) or isalpha(c))
			{
				current_word.push_back(c);
				state = ALPHANUM;
			}	
			else if (is_decimal_point(c) or is_equal(c))
				return false;
			else if (isspace(c))
			{
				tokens.push_back(current_word);
				current_word.clear();
				state = SPACE;
			}
			else 
			{
				tokens.push_back(current_word);
				current_word.clear();
				current_word.push_back(c);

				if (is_op_paren(c)) state = OP_PAREN;
				else if (is_LT(c)) state = LT1;
				else if (is_GT(c)) state = GT1;
			}	
		}
		else if (state == ALPHANUM)
		{
			if (isdigit(c) or isalpha(c)) current_word.push_back(c);
			else if (is_decimal_point(c) or is_equal(c)) return false;
			else if (isspace(c))
			{
				tokens.push_back(current_word);
				current_word.clear();
				state = SPACE;
			}
			else
			{
				tokens.push_back(current_word);
				current_word.clear();
				current_word.push_back(c);

				if (is_op_paren(c)) state = OP_PAREN;
				else if (is_LT(c)) state = LT1;
				else if (is_GT(c)) state = GT1;
			}
		}
		else if (state == OP_PAREN)
		{
			//if (is_op_paren(c)) current_word.push_back(c);
			if (is_decimal_point(c) or is_equal(c))
				return false;
			else if (isspace(c))
			{
				tokens.push_back(current_word);
				current_word.clear();
				state = SPACE;
			}
			else
			{
				tokens.push_back(current_word);
				current_word.clear();
				current_word.push_back(c);

				if (isdigit(c)) state = INTEGER;
				else if (isalpha(c)) state = ALPHA;
				else if (is_LT(c)) state = LT1;
				else if (is_GT(c)) state = GT1;
			}
		}
		else if (state == LT1)
		{
			if (isdigit(c) or is_decimal_point(c)) return false;
			else if (is_equal(c))
			{
				current_word.push_back(c);
				state = LT2;
			} 	
			else if (isspace(c))
			{
				tokens.push_back(current_word);
				current_word.clear();
				state = SPACE;
			}
			else 
			{
				tokens.push_back(current_word);
				current_word.clear();
				current_word.push_back(c);

				if (isalpha(c)) state = ALPHA;
				else if (is_op_paren(c)) state = OP_PAREN;
				else if (is_LT(c)) state = LT1;
				else if (is_GT(c)) state = GT1;
			}
		}
		else if (state == LT2)
		{
			if (is_equal(c) or isdigit(c) or is_decimal_point(c)) return false;
			else if (isspace(c))
			{
				tokens.push_back(current_word);
				current_word.clear();
				state = SPACE;
			}
			else
			{
				tokens.push_back(current_word);
				current_word.clear();
				current_word.push_back(c);

				if (isalpha(c)) state = ALPHA;
				else if (is_op_paren(c)) state = OP_PAREN;
				else if (is_LT(c)) state = LT1;
				else if (is_GT(c)) state = GT1;

			}
		}
		else if (state == GT1)
		{
			if (is_decimal_point(c)) return false;
			else if (isspace(c))
			{
				tokens.push_back(current_word);
				current_word.clear();
				state = SPACE;
			}
			else if (is_equal(c))
			{
				current_word.push_back(c);
				state = GT2;
			} 	
			else
			{
				tokens.push_back(current_word);
				current_word.clear();
				current_word.push_back(c);
				
				if (isalpha(c)) state = ALPHA;
				else if (is_op_paren(c)) state = OP_PAREN;
				else if (isdigit(c)) state = INTEGER;
				else if (is_LT(c)) state = LT1;
				else if (is_GT(c)) state = GT1;
			}
		}
		else if (state == GT2)
		{
			if (is_decimal_point(c) or is_equal(c)) return false;
			else if (isspace(c))
			{
				tokens.push_back(current_word);
				current_word.clear();
				state = SPACE;
			}
			else
			{
				tokens.push_back(current_word);
				current_word.clear();
				current_word.push_back(c);
				
				if (isalpha(c)) state = ALPHA;
				else if (is_op_paren(c)) state = OP_PAREN;
				else if (isdigit(c)) state = INTEGER;
				else if (is_LT(c)) state = LT1;
				else if (is_GT(c)) state = GT1;
			}
		}
		else if (state == SPACE)
		{
			if (is_equal(c) or is_decimal_point(c)) return false;
			else if (isspace(c)){}
			else
			{
				current_word.push_back(c);

				if (isalpha(c)) state = ALPHA;
				else if (is_op_paren(c)) state = OP_PAREN;
				else if (isdigit(c)) state = INTEGER;
				else if (is_LT(c)) state = LT1;
				else if (is_GT(c)) state = GT1;
			}
		}
	}

	return true;
}
