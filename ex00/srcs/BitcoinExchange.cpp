/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:30:38 by omizin            #+#    #+#             */
/*   Updated: 2026/01/15 13:27:49 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"


double	getRateForDate(std::string &date, std::map<std::string, double> &db){
	std::map<std::string, double>::iterator it;

	it = db.find(date);
	if (it != db.end())
		return it->second;

	it = db.lower_bound(date);
	if (it == db.begin())
		throw std::runtime_error(RED"Error: no earlier date in db" RESET);

	if (it == db.end() || it->first != date)
		--it;

	return it->second;
}

void	processingInputFile(std::string filename, std::map<std::string, double> &db){
	std::ifstream file(filename);
	if (!file.is_open())
		throw::std::runtime_error(RED"Error: could not open file." RESET);

	std::string line;
	if (!std::getline(file, line))
		throw::std::runtime_error(RED"Error: file is empty." RESET);

	if (line.compare("date | value") != 0)
		throw::std::runtime_error(RED"Error: missing valid header." RESET);

	while(std::getline(file, line)){
		std::stringstream ss(line);

		std::string date;
		std::string amountSTR;
		if (!std::getline(ss, date, '|') || !std::getline(ss, amountSTR) || date.empty() || amountSTR.empty()){
			std::cerr << RED << "Error: bad input => " << date << " " << amountSTR << RESET << std::endl;
			continue;
		}
		skipSpaces(date);
		skipSpaces(amountSTR);
		double amount;

		try{
			size_t pos;
			amount = std::stod(amountSTR, &pos);
			if (pos != amountSTR.length()){
				std::cerr << RED << "Error: bad input => " << date << " " << amountSTR << RESET << std::endl;
				continue;
			}

		} catch (...){
			std::cerr << RED << "Error: bad input => " << date << " " << amountSTR << RESET << std::endl;
			continue;
		}
		if (!isValidDate(date, false) || !isValidAmount(amount)){
			std::cerr << RED << "Error: bad input => " << date << " " << amountSTR << RESET << std::endl;
			continue;
		}

		try {
			double rate = getRateForDate(date, db);
			std::cout << date << " => " << amount << " = " << amount * rate << std::endl;
		} catch (std::exception &e){
			std::cout << e.what() << std::endl;
		}

	}
}

void loadDB(std::map<std::string, double> &db){
	std::ifstream file("data.csv");
	if (!file.is_open())
		throw::std::runtime_error(RED"Error: could not open database file." RESET);

	std::string line;
	int	line_count = 1;

	if (!std::getline(file, line))
		throw::std::runtime_error(RED"Error: file is empty." RESET);

	if (line.compare("date,exchange_rate") != 0)
		throw::std::runtime_error(RED"Error: missing valid header." RESET);

	while(std::getline(file, line)){
		line_count++;
		std::stringstream ss(line);
		std::string date;
		std::string rateStr;
		if (!std::getline(ss, date, ',') || !std::getline(ss, rateStr) || date.empty() || rateStr.empty()){
			std::cerr << RED << "Error: Corrupted data on line " << line_count << RESET << std::endl;
			continue;
		}
		if (!isValidDate(date, true)){
			std::cerr << RED << "Error: Incorrect date on line " << line_count << RESET << std::endl;
			continue;
		}
		try{
			size_t pos;
			double rate = std::stod(rateStr, &pos);
			if (rate < 0 || pos != rateStr.length()){
				std::cerr << RED << "Error: Incorrect date on line " << line_count << RESET << std::endl;
				continue;
			}
			db.insert(std::make_pair(date, rate));
		} catch (...){
			std::cerr << RED << "Error: Failed to insert data to map on line " << line_count << RESET << std::endl;
		}
	}
	file.close();
}
