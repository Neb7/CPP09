/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:38:29 by benpicar          #+#    #+#             */
/*   Updated: 2025/06/24 18:01:51 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/**
 * @brief	Default constructor for RPN.
 */
RPN::RPN() : _stack()
{}

/**
 * @brief	Copy constructor for RPN.
 * 
 * @param	origin The RPN object to copy from.
 */
RPN::RPN(const RPN &origin) : _stack(origin._stack)
{}

/**
 * @brief	Assignment operator for RPN.
 * 
 * @param	other The RPN object to assign from.
 * @return	A reference to the current RPN object.
 */
RPN	&RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		_stack = other._stack;
	}
	return (*this);
}

/**
 * @brief	Destructor for RPN.
 */
RPN::~RPN()
{}

/**
 * @brief	Evaluate a Reverse Polish Notation (RPN) expression.
 * 
 * @param	expressions An array of strings representing the RPN expressions.
 * @param	length The number of expressions in the array.
 * @throws	std::invalid_argument if the expressions array is null or empty,
 * 			or if an expression is invalid.
 * @throws	TooManyOperands if there are more than one result left in the stack
 */
void	RPN::evaluateExpression(char **expressions, int length)
{
	if (!expressions || length <= 0)
	{
		throw std::invalid_argument("Invalid expressions input.");
	}
	for (int i = 0; i < length; ++i)
	{
		if (!expressions[i] || !*expressions[i])
		{
			continue ;
		}
		performOperation(expressions[i]);
	}
	if (this->_stack.size() != 1)
	{
		throw (TooManyOperands());
	}
	std::cout << this->_stack.top() << std::endl;
}

/**
 * @brief	Skip whitespace characters in the expression.
 * 
 * @param	expression The expression string to process.
 * @param	idx The current index in the expression string.
 */
void	RPN::nextInfo(std::string &expression, size_t &idx)
{
	while (idx < expression.length() && isspace(expression[idx]))
	{
		idx++;
	}
}

/**
 * @brief	Perform operations based on the RPN expression.
 * 
 * @param	expression The RPN expression string to evaluate.
 * @throws	std::invalid_argument if the expression is empty, contains invalid
 * 			characters, or if there are not enough operands for an operation.
 * @throws	NotEnoughOperands if there are not enough operands for an operation.
 */
void	RPN::performOperation(char *expression)
{
	size_t		idx = 0;
	char		token;
	long long	a, b;

	if (!expression || !*expression)
	{
		throw std::invalid_argument("Empty expression.");
	}
	std::string	expressionStr(expression);
	
	while (idx < expressionStr.length())
	{
		nextInfo(expressionStr, idx);
		if (idx >= expressionStr.length())
		{
			break;
		}
		
		token = expressionStr[idx];
		if (expressionStr[idx + 1] != '\0' && !isspace(expressionStr[idx + 1]))
		{
			throw std::invalid_argument("Invalid expression format.");
		}
		if (isdigit(token))
		{
			this->_stack.push(static_cast<long long>(token - '0'));
		}
		else if (token == '+' || token == '-' || token == '*' || token == '/')
		{
			if (this->_stack.size() < 2)
				throw (NotEnoughOperands());
			b = this->_stack.top();
			this->_stack.pop();
			a = this->_stack.top();
			this->_stack.pop();
			switch (token)
			{
				case ('+'):
					this->_stack.push(a + b);
					break ;
				case ('-'):
					this->_stack.push(a - b);
					break ;
				case ('*'):
					this->_stack.push(a * b);
					break ;
				case ('/'):
					if (b == 0)
						throw std::invalid_argument("Division by zero.");
					this->_stack.push(a / b);
					break ;
				default:
					throw std::invalid_argument("Unknown operator.");
			}
		}
		else
		{
			throw std::invalid_argument("Invalid character encountered in expression.");
		}
		idx++;
	}
}

/**
 * @brief	Exception message for too many operands in the expression.
 * 
 * @return	A constant character pointer to the error message.
 */
const char* RPN::TooManyOperands::what() const throw()
{
	return ("Too many operands in the expression.");
}

/**
 * @brief	Exception message for not enough operands in the expression.
 * 
 * @return	A constant character pointer to the error message.
 */
const char* RPN::NotEnoughOperands::what() const throw()
{
	return ("Not enough operands for the operation.");
}

