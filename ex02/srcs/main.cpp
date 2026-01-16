/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:05:59 by omizin            #+#    #+#             */
/*   Updated: 2026/01/16 14:43:39 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int argc, char **argv){
	if (argc < 2){
		std::cerr << RED"Usage: ./PmergeMe numbers" RESET << std::endl;
		return 1;
	}
	std::vector<int>	vector;
	try{
		addNumbersToVec(vector, argv);
	} catch(std::exception &e){
		std::cerr << e.what() << std::endl;
		return 1;
	}
	std::cout << "Before:\t";
	printVector(vector);
	fordJohnson(vector);
	std::cout << "After:\t";
	printVector(vector);
	return 0;
}
