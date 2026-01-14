#include "RPN.hpp"

int RPN::calculate(std::string &line)
{
	std::stack<int> stack;
	int	a, b;

	for (size_t i = 0; i < line.length(); i++)
	{
		if (line[i] == ' ')
			continue;

		if (std::isdigit(line[i]))
		{
			stack.push(line[i] - '0');
			continue;
		}

		if (stack.size() < 2)
			throw::std::runtime_error(RED"Error: incorrect input" RESET);

		b = stack.top();
		stack.pop();
		a = stack.top();
		stack.pop();

		switch (line[i])
		{
			case '+':
				stack.push(a + b);
				break;
			case '-':
				stack.push(a - b);
				break;
			case '*':
				stack.push(a * b);
				break;
			case '/':
				if (b == 0)
					throw::std::runtime_error(RED"Error: incorrect input" RESET);
				stack.push(a / b);
				break;
			default:
				throw::std::runtime_error(RED"Error: incorrect input" RESET);
		}
	}

	if (stack.size() != 1)
		throw::std::runtime_error(RED"Error: incorrect input" RESET);
	return stack.top();
}
