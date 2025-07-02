/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:18:54 by benpicar          #+#    #+#             */
/*   Updated: 2025/06/24 17:31:13 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	PmergeMe	pmerge;

	if (ac < 2)
	{
		std::cerr << "Usage: " << av[0] << " <numbers>" << std::endl;
		return (1);
	}
	try
	{
		pmerge.fillContainer(av + 1, ac - 1);
		pmerge.sortContainers();
		if (!(isSorted<std::vector<unsigned int> >(pmerge.getVector()))
			&& !(isSorted<std::list<unsigned int> >(pmerge.getList())))
		{
			std::cerr << RED << "Error: Containers are not sorted." << NC << std::endl;
			return (1);
		}
		else
		{
			std::cout << BLUE << "Containers are sorted successfully." << NC << std::endl;
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error : " << e.what() << std::endl;
	}
	
	return (0);
}