#include "presenter.hpp"

using namespace std;

Presenter::Presenter()
{
	_view = new CLI();
}

void Presenter::main_loop()
{
	do
	{
		Guesser::init();
		start_inquiry();
		_view->ask_question("Another one?");
	} while (_view->get_answer());
}

void Presenter::start_inquiry()
{
	int potential_number;
	question_type type;
	int threshold = 0;

	while (true)
	{
		type = Guesser::get_random_question_type();
		type == question_type::digit_existence ? threshold = 0 : threshold++;
		if (threshold == 3)
		{
			type = question_type::digit_existence;
			threshold = 0;
		}

		if (type != enough)
		{
			_view->ask_question(Guesser::get_question(type));
			Guesser::process_answer(_view->get_answer());
		}

		if (Guesser::can_be_assembled)
		{
			potential_number = Guesser::get_potential_number();
			_view->ask_question("Is your number " +
								to_string(potential_number) + " ?");
			if (_view->get_answer())
				break;
			Guesser::add_wrong_number(potential_number);
			continue;
		}

	}
}
