/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:52:58 by benpicar          #+#    #+#             */
/*   Updated: 2025/07/02 18:41:14 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/**
 * @brief	Default constructor for BitcoinExchange.
 */
BitcoinExchange::BitcoinExchange()
{} 

/**
 * @brief	Copy constructor for BitcoinExchange.
 * 
 * @param	origin The BitcoinExchange object to copy from.
 */ 
BitcoinExchange::BitcoinExchange(const BitcoinExchange &origin)
{
	*this = origin;
}

/**
 * @brief	Assignment operator for BitcoinExchange.
 * 
 * @param	other The BitcoinExchange object to assign from.
 */
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		_exchangeRates = other._exchangeRates;
	}
	return (*this);
}

/**
 * @brief	Destructor for BitcoinExchange.
 */
BitcoinExchange::~BitcoinExchange()
{}

/**
 * @brief	Load exchange rates from a file.
 * 			This function reads a file containing exchange rates in the format:
 * 			YYYY-MM-DD,rate
 * 
 * @param	filename The name of the file containing exchange rates.
 * @throws	std::runtime_error if the file cannot be opened.
 */
void	BitcoinExchange::loadExchangeRates(const char *filename)
{
	std::string		filenameStr(filename);
	std::ifstream	file(filename);
	std::string		line, date;
	double			rate;
	char			*end;

	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file: " + filenameStr);
	}

	while (std::getline(file, line))
	{
		if (!isValidFormInit(line))
		{
			continue;
		}
		date = line.substr(0, 10);
		rate = std::strtod(line.substr(11).c_str(), &end);
		if (_exchangeRates.find(date) != _exchangeRates.end())
		{
			std::cerr << "Warning: Duplicate exchange rate for date " << date
					  << std::endl;
		}
		addExchangeRate(date, rate);
	}
}

/**
 * @brief	Validate the date format.
 * 			The date must be in the format YYYY-MM-DD and represent a valid date.
 * 
 * @param	date The date string to validate.
 * @return	true if the date is valid, false otherwise.
 */
bool	BitcoinExchange::isValidDate(const std::string &date)
{
	if (date.length() != 10)
	{
		return (false);
	}
	// Check format: YYYY-MM-DD
	for (size_t i = 0; i < date.length(); ++i)
	{
		if (i == 4 || i == 7)
		{
			if (date[i] != '-')
				return false;
		}
		else
		{
			if (!isdigit(date[i]))
				return false;
		}
	}
	// Extract year, month, day
	long int year = std::strtol(date.substr(0, 4).c_str(), NULL, 10);
	long int month = std::strtol(date.substr(5, 2).c_str(), NULL, 10);
	long int day = std::strtol(date.substr(8, 2).c_str(), NULL, 10);

	if (year < 0 || month < 1 || month > 12 || day < 1)
		return (false);

	// Days in month
	long int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	// Leap year check
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		daysInMonth[1] = 29;

	if (day > daysInMonth[month - 1])
		return (false);

	return (true);
}

/**
 * @brief	Validate the initial exchange rate format.
 * 			The rate must be a positive number, can contain a decimal point,
 * 			but cannot have more than one decimal point.
 * 
 * @param	rateStr The exchange rate string to validate.
 * @return	true if the rate is valid, false otherwise.
 * @throws	std::invalid_argument if the rate is negative
 */
bool	BitcoinExchange::isValidRateInit(const std::string &rateStr)
{
	bool hasDecimalPoint = false;

	if (rateStr.empty())
	{
		return (false);
	}
	size_t i = 0;
	if (rateStr[i] == '-')
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return (false);
	}
	if (i >= rateStr.length())
	{
		return (false);
	}

	for (i = 0; i < rateStr.length(); ++i)
	{
		if (rateStr[i] == '.')
		{
			if (hasDecimalPoint)
			{
				std::cerr << "Error: more than one decimal point in rate." << std::endl;
				return (false); // More than one decimal point
			}
			hasDecimalPoint = true;
			continue;
		}
		if (!isdigit(rateStr[i]))
		{
			std::cerr << "Error: non-digit character found in value." << std::endl;
			return (false); // Non-digit character found
		}
	}
	return (true);
}

/**
 * @brief	Validate the exchange rate format.
 * 			The rate must be a positive number, can contain a decimal point,
 * 			but cannot have more than one decimal point, and must not exceed 1000.
 * 
 * @param	rateStr The exchange rate string to validate.
 * @return	true if the rate is valid, false otherwise.
 * @throws	std::invalid_argument if the rate is negative or exceeds 1000
 */
bool	BitcoinExchange::isValidRate(const std::string &rateStr)
{
	bool hasDecimalPoint = false;

	if (rateStr.empty())
	{
		return (false);
	}
	size_t i = 0;
	if (rateStr[i] == '-')
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return (false);
	}
	if (i >= rateStr.length())
	{
		return (false);
	}

	for (i = 0; i < rateStr.length(); ++i)
	{
		if (rateStr[i] == '.')
		{
			if (hasDecimalPoint)
			{
				std::cerr << "Error: more than one decimal point in rate." << std::endl;
				return (false); // More than one decimal point
			}
			hasDecimalPoint = true;
			continue;
		}
		if (!isdigit(rateStr[i]))
		{
			std::cerr << "Error: non-digit character found in value." << std::endl;
			return (false); // Non-digit character found
		}
	}
	double	rate = std::strtod(rateStr.c_str(), NULL);
	if (rate > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return (false); // Rate exceeds maximum value
	}
	return (true);
}

/**
 * @brief	Validate the initial format of the exchange rate line.
 * 			The line must be in the format YYYY-MM-DD,rate and represent a
 * 			valid date and rate.
 * 
 * @param	line The line to validate.
 * @return	true if the line is valid, false otherwise.
 */
bool	BitcoinExchange::isValidFormInit(const std::string &line)
{
	size_t		pos = line.find(',');
	
	if (pos == std::string::npos || pos != 10)
	{
		return (false);
	}
	std::string	date = line.substr(0, pos);
	std::string	rateStr = line.substr(pos + 1);

	if (date[4] != '-' || date[7] != '-')
	{
		return (false);
	}
	if (!isValidDate(date))
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return (false);
	}
	if (!isValidRateInit(rateStr))
	{
		return (false);
	}
	return (true);
}

/**
 * @brief	Validate the format of the exchange rate line.
 * 			The line must be in the format "YYYY-MM-DD | rate" and represent a
 * 			valid date and rate.
 * 
 * @param	line The line to validate.
 * @return	true if the line is valid, false otherwise.
 */
bool	BitcoinExchange::isValidForm(const std::string &line, bool &firstLine)
{
	size_t	pos = line.find('|');

	if (pos == std::string::npos || pos < 10)
	{
		if (!firstLine)
			std::cerr << "Error: bad input => " << line << std::endl;
		else
			firstLine = false;
		return (false);
	}
	std::string date = line.substr(0, pos);
	std::string rateStr = line.substr(pos + 1);

	// Trim spaces around date and rateStr
	date.erase(date.find_last_not_of(" \t") + 1);
	date.erase(0, date.find_first_not_of(" \t"));
	rateStr.erase(rateStr.find_last_not_of(" \t") + 1);
	rateStr.erase(0, rateStr.find_first_not_of(" \t"));

	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
	{
		return (false);
	}
	if (!isValidDate(date))
	{
		if (!firstLine)
			std::cerr << "Error: bad input => " << date << std::endl;
		else
			firstLine = false;
		return (false);
	}
	if (!isValidRate(rateStr))
	{
		return (false);
	}
	return (true);
}

/**
 * @brief	Add an exchange rate for a specific date.
 * 			If the date already exists, the rate will be updated.
 * 
 * @param	date The date for which the exchange rate is being added.
 * @param	rate The exchange rate to be added.
 * @throws	std::invalid_argument if the rate is negative.
 */
void	BitcoinExchange::addExchangeRate(const std::string &date, double rate)
{
	if (rate < 0)
	{
		throw std::invalid_argument("Exchange rate cannot be negative.");
	}
	if (_exchangeRates.find(date) != _exchangeRates.end())
	{
		std::cerr << "Warning: Duplicate exchange rate for date " << date
				  << ", updating existing rate." << std::endl;
	}
	_exchangeRates[date] = rate;
}

/**
 * @brief	Get the exchange rate for a specific date.
 * 			If the date does not exist, it will return the closest preceding
 * 			date's rate.
 * 
 * @param	date The date for which the exchange rate is requested.
 * @return	The exchange rate for the specified date.
 * @throws	std::out_of_range if no exchange rate is found for the specified
 * 			date or any preceding date.
 */
double	BitcoinExchange::getExchangeRate(const std::string &date) const
{
	std::map<std::string, double>::const_iterator it = _exchangeRates.find(date);
	if (it != _exchangeRates.end())
	{
		return it->second;
	}
	else
	{
		it = _exchangeRates.lower_bound(date);
		if (it == _exchangeRates.begin())
		{
			throw std::out_of_range("Exchange rate for date " + date + " not found.");
		}
		--it; // Move to the previous date (the closest preceding date)
		return (it->second);
	}
}

/**
 * @brief	Process a file containing dates and rates.
 * 			This function reads a file where each line contains a date and a rate
 * 			in the format "YYYY-MM-DD | rate". It validates each line, retrieves
 * 			the exchange rate for the date, and prints the result in the format:
 * 			"YYYY-MM-DD => rate = exchangeRate".
 * 
 * @param	filename The name of the file to process.
 */
void	BitcoinExchange::processingFile(const char *filename) const
{
	std::ifstream	file(filename);
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file: " + std::string(filename));
	}
	std::string	line;
	bool		firstLine = true;

	while (std::getline(file, line))
	{
		if (!isValidForm(line, firstLine))
		{
			continue;
		}
		size_t		pos = line.find('|');
		std::string	date = line.substr(0, pos);
		std::string	rateStr = line.substr(pos + 1);

		// Trim spaces around date and rateStr
		date.erase(date.find_last_not_of(" \t") + 1);
		date.erase(0, date.find_first_not_of(" \t"));
		rateStr.erase(rateStr.find_last_not_of(" \t") + 1);
		rateStr.erase(0, rateStr.find_first_not_of(" \t"));

		double rate = std::strtod(rateStr.c_str(), NULL);
		try
		{
			double exchangeRate = getExchangeRate(date);
			std::cout << date << " => " << rate << " = " << (rate * exchangeRate) << std::endl;
		}
		catch (const std::out_of_range &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}
