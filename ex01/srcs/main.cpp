/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:04:33 by omizin            #+#    #+#             */
/*   Updated: 2026/01/15 13:04:34 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int argc, char **argv){
	if (argc != 2){
		std::cerr << "Error: Usage ./RPN \"argv\" " << std::endl;
		return 1;
	}
	try{
		std::string input(argv[1]);
		std::cout << RPN::calculate(input) << std::endl;
	} catch (std::exception &e){
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
