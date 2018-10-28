#include "guesser.hpp"

using namespace std;

Question Guesser::question;
Properties Guesser::num_properties;
vector<int> Guesser::wrong_numbers;
bool Guesser::can_be_assembled;

void Guesser::add_wrong_number(int number)
{
	wrong_numbers.push_back(number);
}

question_type Guesser::get_random_question_type()
{
	vector<question_type> types = { digit_existence,
									number_comparison,
									divisibility_rule,
									sorted_flag };

	if (num_properties.divisible != 0)
		types.erase(types.begin() + 2);

	if (num_properties.order.length() != 0 ||
		num_properties.not_order.size() == 2)
		types.erase(types.end() - 1);

	if (num_properties.contains.size() != 0)
		types.erase(types.begin());

	if (num_properties.greater_than == num_properties.less_than ||
		num_properties.greater_than == num_properties.less_than + 1 ||
		num_properties.greater_than == num_properties.less_than - 1)
		return question_type::enough;

	return types[rand() % types.size()];
}

void Guesser::process_num_comparison_answer(const bool &answer)
{
	char sign = num_properties.pending[0];
	string number = num_properties.pending;
	number = number.substr(1, 3);
	
	if (sign == '>')
		answer ? 
		num_properties.greater_than = stoi(number) : 
		num_properties.less_than = stoi(number);
	else if (sign == '<')
		answer ?
		num_properties.less_than = stoi(number) :
		num_properties.greater_than = stoi(number);
	else
		return;
}

void Guesser::number_assemblance_check()
{
	if (num_properties.contains.size() == 3)
	{
		can_be_assembled = true;
		return;
	}

	if (num_properties.greater_than == num_properties.less_than ||
		num_properties.greater_than == num_properties.less_than + 1 ||
		num_properties.greater_than == num_properties.less_than - 1)
	{
		can_be_assembled = true;
		return;
	}

	//if (num_properties["contains"].size() == 2)
	//{
	//	if (num_properties["divisible"].size() > 0 ||
	//		num_properties["more_than"].size() > 0 ||
	//		num_properties["greater_than"].size() > 0 ||
	//		num_properties["order"].size() > 0)
	//	{
	//		can_be_assembled = true;
	//		return;
	//	}
	//}
}

std::vector<int> Guesser::assemble_number()
{
	vector<int> number;
	auto vec_to_num = [](vector<int> vec) -> int { 
		return vec[0] * 100 + vec[1] * 10 + vec[2]; 
	};
	

	if (num_properties.contains.size() == 3)
	{
		number = num_properties.contains;
		
		if (num_properties.divisible != 0)
		{
			while (vec_to_num(number) % num_properties.divisible != 0 ||
				   (find(wrong_numbers.begin(), 
					    wrong_numbers.end(), 
					    vec_to_num(number)) != wrong_numbers.end()))
			{
				shuffle(number.begin(),
						number.end(),
						default_random_engine((unsigned)time(NULL)));
			}
		}

		if (num_properties.greater_than > 0 ||
			num_properties.less_than > 0)
		{
			while ((vec_to_num(number) >= num_properties.less_than ||
				   vec_to_num(number) <= num_properties.greater_than) || 
				   (find(wrong_numbers.begin(),
						wrong_numbers.end(),
						vec_to_num(number)) != wrong_numbers.end()))
			{
				shuffle(number.begin(),
						number.end(),
						default_random_engine((unsigned)time(NULL)));
			}
		}
	}

	if (num_properties.greater_than == num_properties.less_than ||
		num_properties.greater_than == num_properties.less_than + 1 ||
		num_properties.greater_than == num_properties.less_than - 1)
	{
		if (find(wrong_numbers.begin(),
			wrong_numbers.end(),
			num_properties.greater_than) != wrong_numbers.end())
		{
			return { num_properties.greater_than / 100,
					(num_properties.greater_than % 100) / 10,
					num_properties.greater_than % 10 };
		}
		else
		{
			return { num_properties.less_than / 100,
				(num_properties.less_than % 100) / 10,
				num_properties.less_than % 10 };
		}			
	}

	return number;
}

std::string Guesser::get_question(const question_type &type)
{
	vector<int> exceptions;

	switch (type)
	{
	case digit_existence:
	{
		exceptions.insert(exceptions.begin(),
			num_properties.contains.begin(),
			num_properties.contains.end());
		exceptions.insert(exceptions.begin(),
			num_properties.not_contains.begin(),
			num_properties.not_contains.end());

		question.content = QuestionComposer::compose_digit_question(exceptions);
		question.type = "contains";
		return question.content;
	}
	case number_comparison:
	{
		question.content = QuestionComposer::compose_number_question(
			num_properties.greater_than,
			num_properties.less_than);
		question.type = "num_comparison";
		return question.content;
	}
	case divisibility_rule:
	{
		exceptions.insert(exceptions.begin(), num_properties.divisible);
		exceptions.insert(exceptions.begin() + 1,
			num_properties.not_divisible.begin(),
			num_properties.not_divisible.end());
		question.content = QuestionComposer::compose_divisibility_question(exceptions);
		question.type = "divisible";
		return question.content;
	}
	case sorted_flag:
	{
		question.content = QuestionComposer::compose_sorted_question(num_properties.not_order);
		question.type = "order";
		return question.content;
	}
	default:
		return string();
		break;
	}
}

void Guesser::process_answer(const bool &answer)
{
	if (question.type == "num_comparison")
	{
		process_num_comparison_answer(answer);
		num_properties.pending.clear();
		return;
	}

	if (answer)
	{
		num_properties.process_pending(question.type);
	}
	else if (!answer)
	{
		num_properties.process_pending("!" + question.type);
	}

	num_properties.pending.clear();
	number_assemblance_check();
}

int Guesser::get_potential_number()
{
	vector<int> unparsed_number = num_properties.contains;

	if (num_properties.order == "ascending")
		sort(unparsed_number.begin(), unparsed_number.end());
	else if (num_properties.order == "descending")
		sort(unparsed_number.begin(), unparsed_number.end(), greater<>());
	else
		unparsed_number = assemble_number();

	return unparsed_number[0] * 100 +
		   unparsed_number[1] * 10 +
		   unparsed_number[2];
}

void Guesser::init()
{
	Guesser::question;
	Guesser::question.set_defaults();
	Guesser::num_properties.set_defaults();
	Guesser::wrong_numbers.clear();
	Guesser::can_be_assembled = false;
}

void Properties::set_defaults()
{
	contains.clear();
	not_contains.clear();
	divisible = 0;
	not_divisible.clear();
	greater_than = 100;
	less_than = 999;
	order.clear();
	not_order.clear();
	pending.clear();
}

void Properties::process_pending(string property)
{
	if (property == "contains")
		contains.push_back(stoi(pending));
	else if (property == "!contains")
		not_contains.push_back(stoi(pending));
	else if (property == "divisible")
		divisible = stoi(pending);
	else if (property == "!divisible")
		not_divisible.push_back(stoi(pending));
	else if (property == "order")
		order = pending;
	else if (property == "!order")
		not_order.push_back(pending);
}

void Question::set_defaults()
{
	content.clear();
	type.clear();
}
