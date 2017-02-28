// TryList17.cpp: определяет точку входа для консольного приложения.
//17. Заменить все положительные числа максимальным из чисел.
// C. List

#include "stdafx.h"
#include "Functions.h"

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
	std::cout << " 9)Output" << std::endl;
	std::cout << "10)Exit" << std::endl;
	std::cout << "Enter the command: ";
}

std::string input_file_name()
{
	std::string name;
	std::cout << "Enter file name: ";
	std::getline(std::cin, name);
	std::getline(std::cin, name);
	if (name == "") name = "default_file_name";
	return name + ".txt";
}

int main()
{
	std::list<int> list;
	std::string file_name;
	char c;

	while (true)
	{
		print_menu();
		std::cin >> c;
		switch (c)
		{
		case '1':
			int N, M;
			file_name = input_file_name();
			std::cout << "Enter count: ";
			std::cin >> N;
			std::cout << "Enter range: ";
			std::cin >> M;
			random_fill_file_cicle(file_name, N, M);
			random_fill_file_generate("generate_"+file_name, N, M);
			break;
		case '2':
			file_name = input_file_name();
			list = get_list_from_file(file_name);
			output_list_console(list);
			break;
		case '3':
			if (!list.empty()) list = modify(list);
			else
			{
				std::cout << "List is empty(" << std::endl;
			}
			break;
		case '4':
			if (!list.empty()) list = modify(list.begin(), list.end());
			else
			{
				std::cout << "List is empty(" << std::endl;
			}
			break;
		case '5':
			if (!list.empty()) list = modify_transform(list);
			else
			{
				std::cout << "List is empty(" << std::endl;
			}
			break;
		case '6':
			if (!list.empty()) list = modify_foreach(list);
			else
			{
				std::cout << "List is empty(" << std::endl;
			}
			break;
		case '7':
			std::cout << "Sum of list = " << list_sum(list) << std::endl;
			break;
		case '8':
			std::cout << "Average of list = " << list_average(list) << std::endl;
			break;
		case '9':
			if (!list.empty())
			{
				file_name = input_file_name();
				output_list_file(list, file_name);
				output_list_file(list);
			}
			else
			{
				std::cout << "List is empty(" << std::endl;
			}
			break;
		case '10':
			return 0;
			break;
		default:
			std::cout << "!!!Wrong command!!!" << std::endl;
			break;
		}

	}
	setlocale(LC_ALL, "rus");
	random_fill_file_cicle("Test1.txt", 10, 25);
	random_fill_file_generate("Test2.txt", 10, 25);
	std::list<int> List = get_list_from_file("Test1.txt");
	output_list_console(List);
	output_list_console(modify(List));
	output_list_console(modify(List.begin(),List.end()));
	output_list_console(modify_transform(List));
	output_list_console(modify_foreach(List));

	system("pause");
	return 0;
}

