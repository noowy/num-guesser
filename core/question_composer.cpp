#include "question_composer.hpp"

using namespace std;

std::string QuestionComposer::compose_digit_question(const std::vector<int>& exceptions)
{
	string question;
	int digit;

	while ((digit = rand() % 10) + 1) // +1 to pass through in case of a 0
	{
		auto result = find(exceptions.begin(), exceptions.end(), digit);
		if (result == exceptions.end())
			break;
	}

	question = "Does your number contain digit " + to_string(digit) + " ?";
	
	Guesser::num_properties.pending.clear();
	Guesser::num_properties.pending = to_string(digit);

	return question;
}

std::string QuestionComposer::compose_number_question(const int &bot_boundary, 
													  const int &top_boundary)
{
	string question;
	int number;
	
	while (number = 100 + rand() % 900)
	{
		if (number > bot_boundary && number < top_boundary)
			break;
	}
	
	string random_sign = rand() % 2 == 0 ? ">" : "<"; 
	question = "Is your number " + random_sign + "=" + to_string(number);
	
	Guesser::num_properties.pending.clear();
	Guesser::num_properties.pending = random_sign + to_string(number);

	return question;
}

std::string QuestionComposer::compose_divisibility_question(const std::vector<int> &exceptions)
{
	string question;
	vector<int> divisors = { 2, 3, 4, 5, 9, 10 };
	int potential_divisor;

	while (potential_divisor = divisors[rand() % 6]) // +1 to pass through in case of a 0
	{
		auto result = find(exceptions.begin(), exceptions.end(), potential_divisor);
		if (result == exceptions.end())
			break;
	}

	question = "Is your number divisible by " + to_string(potential_divisor) + "?";
	
	Guesser::num_properties.pending.clear();
	Guesser::num_properties.pending = to_string(potential_divisor);

	return question;
}

std::string QuestionComposer::compose_sorted_question(const std::list<string> &exceptions)
{
	string question;
	string random_order;
	while (true)
	{
		random_order = rand() % 2 == 0 ? "ascending" : "descending";
		auto result = find(exceptions.begin(), exceptions.end(), random_order);
		if (result == exceptions.end())
			break;
	}

	question = "Are digits in your number in " + random_order + " order";

	Guesser::num_properties.pending.clear();
	Guesser::num_properties.pending = random_order;

	return question;
}
