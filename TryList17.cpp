// TryList17.cpp: определяет точку входа для консольного приложения.
//17. Заменить все положительные числа максимальным из чисел.
// C. List

#include "stdafx.h"
#include "Functions.h"

enum menu_item
{
	FILL, IN, MOD, MOD_I, MOD_T, MOD_F, SUM, AVG, OUT, OUT_F, EXIT, WRONG
};

void print_menu()
{
	std::cout << "Command list" << std::endl;
	std::cout << " 1)Fill file with random numbers" << std::endl;
	std::cout << " 2)Input" << std::endl;
	std::cout << " 3)Modify" << std::endl;
	std::cout << " 4)Modify(iterators)" << std::endl;
	std::cout << " 5)Modify(transform)" << std::endl;
	std::cout << " 6)Modify(foreach)" << std::endl;
	std::cout << " 7)Sum of list" << std::endl;
	std::cout << " 8)Average of list" << std::endl;
	std::cout << " 9)Output console" << std::endl;
	std::cout << "10)Output file" << std::endl;
	std::cout << "11)Exit" << std::endl;
	std::cout << "Enter the command: " << std::endl;
}

std::string output_file_name()
{
	std::string name;
	std::cout << "Enter file name(empty string = 'defaulname'): " << std::endl;
	std::getline(std::cin, name);
	if (name == "") name = "defaultname";
	return name + ".txt";
}

std::string input_file_name()
{
	std::fstream f;
	std::string res;
	std::cout << "Enter text file name(empty string = 'defaultname'): ";
	std::getline(std::cin, res);
	f.open(res + ".txt");
	while (!f.is_open() && res != "")
	{
		std::cout << "There are no such file, repeat input(empty string = 'defaultname'): ";
		std::getline(std::cin, res);
		f.open(res + ".txt");
	};
	f.close();
	return (res == "") ? "defaultname.txt" : res + ".txt";
}


int main()
{
	std::list<int> list;
	std::string file_name;
	std::string str;
	menu_item mi;

	auto begin = list.begin();
	auto end = list.begin();

	while (true)
	{
		print_menu();
		std::getline(std::cin, str);
		try
		{
			mi = (menu_item)(std::stoi(str) - 1);
		}
		catch (std::invalid_argument e)
		{
			mi = WRONG;
		}
		catch (std::out_of_range e)
		{
			mi = WRONG;
		}
		switch (mi)
		{
		case FILL:
			int N, M;
			file_name = output_file_name();
			std::cout << "Enter count: ";
			std::cin >> N;
			std::cout << "Enter range: ";
			std::cin >> M;
			random_fill_file_cicle(file_name, N, M);
			random_fill_file_generate("generate_" + file_name, N, M);
			std::getline(std::cin, str);
			break;
		case IN:
			file_name = input_file_name();
			list = get_list_from_file(file_name);
			output_list_console(list);
			break;
		case MOD:
			if (!list.empty())
			{
				output_list_console(list);
				list = modify(list);
				output_list_console(list);
			}
			else
			{
				std::cout << "List is empty(" << std::endl;
			}
			break;
		case MOD_I:
			int a, b, o;
			a = b = o = 0;
			if (!list.empty()) {
				output_list_console(list);
				while ((o < 1) || (o > 3))
				{
					std::cout << " 1)[list.begin(), list.end())\n";
					std::cout << " 2)[a, b)\n";
					std::cout << " 3)Cancel\n";
					std::cout << " >> ";
					std::cin >> o;
				}
				switch (o)
				{
				case 1:
					modify_range(list.begin(), list.end());
					output_list_console(list);

					std::getline(std::cin, str);
					break;
				case 2:
					std::cout << "a: ";
					std::cin >> a;
					std::cout << "b: ";
					std::cin >> b;

					while (a < 0 || a > list.size() )
					{
						std::cout << "repeat input a: ";
						std::cin >> a;
					}

					while (b < 0 || b > list.size())
					{
						std::cout << "repeat input b: ";
						std::cin >> b;
					}

					if (b < a)
					{
						int tmp = a;
						a = b;
						b = tmp;
					}

					begin = list.begin();
					end = list.begin();

					std::advance(begin, a);
					std::advance(end, b);

					modify_range(begin, end);

					output_list_console(list);

					std::getline(std::cin, str);
					break;
				case 3:

					std::getline(std::cin, str);
					break;
				}
			}
			break;
		case MOD_T:
			if (!list.empty())
			{
				output_list_console(list);
				list = modify_transform(list);
				output_list_console(list);
			}
			else
			{
				std::cout << "List is empty(" << std::endl;
			}
			break;
		case MOD_F:
			if (!list.empty())
			{
				output_list_console(list);
				list = modify_foreach(list);
				output_list_console(list);
			}
			else
			{
				std::cout << "List is empty(" << std::endl;
			}
			break;
		case SUM:
			if (!list.empty())
			{
				std::cout << "Sum of list = " << list_sum(list) << std::endl;
			}
			else
			{
				std::cout << "List is empty(" << std::endl;
			}
			break;
		case AVG:
			if (!list.empty())
			{
				std::cout << "Average of list = " << list_average(list) << std::endl;
			}
			else
			{
				std::cout << "List is empty(" << std::endl;
			}
			break;
		case OUT:
			if (!list.empty())
			{
				output_list_console(list);
			}
			else
			{
				std::cout << "List is empty(" << std::endl;
			}
			break;
		case OUT_F:
			if (!list.empty())
			{
				file_name = output_file_name();
				output_list_file(list, file_name);
			}
			else
			{
				std::cout << "List is empty(" << std::endl;
			}
			break;
		case EXIT:
			return 0;
			break;
		case WRONG:
			std::cout << "!!!Wrong command!!!" << std::endl;
			break;
		}
	}
}
