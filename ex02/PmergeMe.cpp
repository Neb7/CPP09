/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:49 by benpicar          #+#    #+#             */
/*   Updated: 2025/06/24 17:21:16 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/**
 * @brief	Default constructor for PmergeMe.
 */
PmergeMe::PmergeMe()
{}

/**
 * @brief	Copy constructor for PmergeMe.
 * 
 * @param	origin The PmergeMe object to copy from.
 */
PmergeMe::PmergeMe(const PmergeMe &origin) : _vector(origin._vector), _list(origin._list)
{}

/**
 * @brief	Assignment operator for PmergeMe.
 * 
 * @param	other The PmergeMe object to assign from.
 * @return	A reference to the current PmergeMe object.
 */
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_vector = other._vector;
		_list = other._list;
	}
	return (*this);
}

/**
 * @brief	Destructor for PmergeMe.
 */
PmergeMe::~PmergeMe()
{}

/**
 * @brief	Get the vector of unsigned integers.
 * 
 * @return	A constant reference to the vector of unsigned integers.
 */
std::vector<unsigned int> const	&PmergeMe::getVector() const
{
	return (const_cast<std::vector<unsigned int> &>(_vector));
}

/**
 * @brief	Get the list of unsigned integers.
 * 
 * @return	A constant reference to the list of unsigned integers.
 */
std::list<unsigned int> const	&PmergeMe::getList() const
{
	return (const_cast<std::list<unsigned int> &>(_list));
}

/**
 * @brief	Advances the index past any whitespace characters in the string.
 * 
 * @param	str The string to process.
 * @param	index The current index in the string.
 */
void	PmergeMe::nextInfo(std::string &str, size_t &index) const
{
	while (index < str.length() && isspace(str[index]))
	{
		index++;
	}
}

/**
 * @brief	Fills the vector and list containers with unsigned integers from the input strings.
 * 
 * @param	numbers An array of strings containing numbers to be processed.
 * @param	length The number of strings in the array.
 * @throws	std::invalid_argument if the input contains invalid characters or formats.
 * @throws	std::out_of_range if a number exceeds the maximum value for unsigned int.
 */
void PmergeMe::fillContainer(char **numbers, int length)
{
	std::string	str;
	size_t		index;

	for (int i = 0; i < length; ++i)
	{
		str = numbers[i];
		index = 0;

		nextInfo(str, index);
		while (index < str.length())
		{
			if (!isdigit(str[index]))
			{
				if (str[index] != '+' || !isdigit(str[index + 1]))
				{
					throw std::invalid_argument("Invalid input : " + str);
				}
				index++;
			}
			unsigned long num = std::strtoul(str.substr(index).c_str(), NULL, 10);
			if (num > UINT_MAX)
			{
				throw std::out_of_range("Number out of range : " + str);
			}
			_vector.push_back(static_cast<unsigned int>(num));
			_list.push_back(static_cast<unsigned int>(num));

			while (index < str.length() && isdigit(str[index]))
			{
				index++;
			}
			nextInfo(str, index);
		}
	}
}

/**
 * @brief	Sorts the vector and list containers.
 * 			This function uses a merge-insertion sort algorithm to sort the elements
 * 			in both containers.
 */
void PmergeMe::sortContainers()
{
	clock_t	start, end;
	
	std::cout << "Before: ";
	printContainers(_vector);
	start = clock();
	sortCo(_vector);
	end = clock();
	std::cout << "After: ";
	printContainers(_vector);
	double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
	std::cout << GREEN << "Time to process a range of " << _vector.size()
			  << " elements with std::vector : " << time << " microseconds" << NC << std::endl;
	
	std::cout << "Before: ";
	printContainers(_list);
	start = clock();
	sortCo(_list);
	end = clock();
	std::cout << "After: ";
	printContainers(_list);
	time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
	std::cout << GREEN << "Time to process a range of " << _list.size()
			  << " elements with std::list : " << time << " microseconds" << NC << std::endl; 
}

