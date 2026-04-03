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
	std::deque<int>		deque;
	try{
		addNumbersToVec(vector, argv);
		addNumbersToDeq(deque, argv);
	} catch(std::exception &e){
		std::cerr << e.what() << std::endl;
		return 1;
	}
	std::cout << BLUE"Before:\t";
	printVector(vector);

	auto time_start = std::chrono::high_resolution_clock::now();
	fordJohnsonVec(vector);
	auto time_end = std::chrono::high_resolution_clock::now();
	std::cout << GREEN"After:\t";
	printVector(vector);
	std::chrono::duration<double, std::milli> duration = time_end - time_start;
	std::cout << MAGENTA"Sorted vector in\t" << duration.count() << " ms" RESET << std::endl;

	time_start = std::chrono::high_resolution_clock::now();
	fordJohnsonDeq(deque);
	time_end = std::chrono::high_resolution_clock::now();
	duration = time_end - time_start;
	std::cout << MAGENTA"Sorted deque in\t\t" << duration.count() << " ms" RESET << std::endl;
	std::cout << "Moves: " << comparison_count(true) << std::endl;
	return 0;
}
