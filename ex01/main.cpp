/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:57:53 by benpicar          #+#    #+#             */
/*   Updated: 2025/06/20 16:15:48 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int ac, char **av)
{
	RPN	rpn;

	if (ac < 2)
	{
		std::cerr << "Usage: " << av[0] << " <expression>" << std::endl;
		return (1);
	}
	try
	{
		rpn.evaluateExpression(&av[1], ac - 1);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
