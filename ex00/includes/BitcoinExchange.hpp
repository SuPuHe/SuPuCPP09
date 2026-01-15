/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:30:51 by omizin            #+#    #+#             */
/*   Updated: 2026/01/15 13:27:44 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>

void	loadDB(std::map<std::string, double> &db);
void	processingInputFile(std::string filename, std::map<std::string, double> &db);
double	getRateForDate(std::string &date, std::map<std::string, double> &db);
bool	isValidAmount(double amount);
void	skipSpaces(std::string &line);
bool	isValidDate(const std::string &date, bool flag);
bool	isLeapYear(int year);
