/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:47:56 by benpicar          #+#    #+#             */
/*   Updated: 2025/07/02 18:41:04 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <map>
# include <stdexcept>
# include <ctime>

# define FILE_EXCHANGE "data.csv"

/**
 * @brief	Class to manage Bitcoin exchange rates.
 * 			This class provides functionality to load exchange rates from a file,
 * 			validate the format of the rates, and retrieve the exchange rate for a
 * 			specific date. It also processes a file containing dates and rates,
 * 			calculating the value of Bitcoin for each date based on the exchange
 */
class BitcoinExchange
{
	private:
		std::map<std::string, double> _exchangeRates;

		static bool		isValidFormInit(const std::string &line);
		static bool		isValidForm(const std::string &line, bool &firstLine);
		static bool		isValidDate(const std::string &date);
		static bool		isValidRateInit(const std::string &rateStr);
		static bool		isValidRate(const std::string &rateStr);

		void			addExchangeRate(const std::string &date, double rate);

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &origin);
		BitcoinExchange	&operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		void			loadExchangeRates(const char *filename);
		double			getExchangeRate(const std::string &date) const;
		
		void			processingFile(const char *filename) const;
};

#endif
