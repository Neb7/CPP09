/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:21:57 by benpicar          #+#    #+#             */
/*   Updated: 2025/06/24 17:30:54 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <list>
# include <algorithm>
# include <stdexcept>
# include <cctype>
# include <ctime>

# define UINT_MAX 4294967295

# define GREEN	"\033[0;92m"
# define RED	"\033[0;91m"
# define BLUE	"\033[0;94m"
# define NC		"\033[0m"

/**
 * @brief	Class to manage and sort a collection of unsigned integers.
 * 			This class provides functionality to fill containers with numbers,
 * 			sort them using a merge-insertion sort algorithm, and print the
 * 			contents of the containers.
 */
class PmergeMe
{
	private:
		std::vector<unsigned int>	_vector;
		std::list<unsigned int>		_list;

		void		nextInfo(std::string &str, size_t &index) const;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &origin);
		PmergeMe	&operator=(const PmergeMe &other);
		~PmergeMe();

		std::vector<unsigned int> const	&getVector() const;
		std::list<unsigned int> const	&getList() const;

		void		fillContainer(char **numbers, int length);
		void		sortContainers();
};

/**
 * @brief	Checks if a container is sorted in ascending order.
 * 
 * @param	container The container to check, which can be a vector or a list.
 */
template <typename Co>
bool	isSorted(const Co &container)
{
	typename Co::const_iterator prev, it;

	if (container.size() < 2)
	{
		return (true);
	}

	prev = container.begin();
	it = ++container.begin();

	while (it != container.end())
	{
		if (*it < *prev)
			return (false);
		++prev;
		++it;
	}
	return (true);
}

/**
 * @brief	Sorts a container using a merge-insertion sort algorithm.
 * 			This function takes a container (vector or list) and sorts it in place.
 * 			Using a recursive approach, it separates the container into pairs
 * 			(Ford Johnson algorithm), sorts the larger elements, and then
 * 			inserts the smaller elements back into the sorted order.
 * 
 * @param	container The container to sort, which can be a vector or a list.
 * @tparam	Co The type of the container, which must support iterators and value_type.
 */
template <typename Co>
void	sortCo(Co &container)
{
	if (container.size() <= 1 || isSorted(container))
		return ;

	// Séparer en paires
	std::vector<typename Co::value_type> pairs;
	typename Co::iterator it = container.begin();
	while (it != container.end())
	{
		typename Co::iterator first = it++;
		if (it != container.end())
		{
			// Mettre le plus grand devant
			if (*first < *it)
				std::iter_swap(first, it);
			pairs.push_back(*first);
			++it;
		}
		else
		{
			pairs.push_back(*first);
		}
	}

	// Tri récursif des plus grands de chaque paire
	Co mainChain(pairs.begin(), pairs.end());
	sortCo(mainChain);

	// Insertion des plus petits de chaque paire
	it = container.begin();
	typename Co::iterator mainIt = mainChain.begin();
	std::advance(mainIt, 1); // On saute le premier élément (déjà en place)
	while (it != container.end())
	{
		typename Co::iterator first = it++;
		if (it != container.end())
		{
			// Insérer le plus petit de la paire à la bonne position
			typename Co::value_type	insertVal = (*first < *it) ? *first : *it;
			typename Co::iterator 	pos;
			for (pos = mainChain.begin(); pos != mainChain.end(); ++pos)
			{
				if (insertVal < *pos)
					break;
			}
			mainChain.insert(pos, insertVal); 
			++it;
		}
	}

	// Copier le résultat dans le container d'origine
	typename Co::iterator src = mainChain.begin(), dest;
	for (dest = container.begin(); dest != container.end() && src != mainChain.end(); ++dest, ++src)
	{
		*dest = *src;
	}
}

/**
 * @brief	Prints the contents of a container to the standard output.
 * 
 * @tparam	Co The type of the container, which must support iterators.
 */
template <typename Co>
void	printContainers(const Co &container)
{
	typename Co::const_iterator it;

	for (it = container.begin(); it != container.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}


#endif
