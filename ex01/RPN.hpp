/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:56:12 by benpicar          #+#    #+#             */
/*   Updated: 2025/06/24 17:05:01 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <sstream>
# include <stdexcept>
# include <cctype>

/**
 * @brief	Class to evaluate Reverse Polish Notation (RPN) expressions.
 *			This class provides functionality to evaluate RPN expressions using
 * 			a stack.
 */
class RPN
{
	private:
		std::stack<long long>	_stack;

		void		nextInfo(std::string &expression, size_t &idx);
		void		performOperation(char *expression);

	public:
		RPN();
		RPN(const RPN &origin);
		RPN			&operator=(const RPN &other);
		~RPN();

		void		evaluateExpression(char **expressions, int length);

		class TooManyOperands : public std::exception
		{
			public:
				const char*	what() const throw();
		};
		class NotEnoughOperands : public std::exception
		{
			public:
				const char*	what() const throw();
		};

};

#endif

