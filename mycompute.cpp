/*
создаем 2 массива, один для хранения чисел, второй для хранения операций. 
просбегаем по всем возможным вариантам, сохраняем в строках те, которые подходят и выводим ектор строк.

пояснение за массив операторов "operators" | res = 16
data 	  1      2      4
operators OP_NO OP_PL
то есть после единицы не ставить никакой оператор, после 2 ставить +.

поянение за get_res()
мы создаем список, состоящий из элементов и операций в том порядке, в котором должны быть.
Сначала ищем умножения, умножаем два соседних числа и сам элемент с умножением заменяем на число. Два соседних удаляем.
Потом аналогчино проходимся за + и -.
*/
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cmath>
#include <bits/stdc++.h> 
#include <iostream>
#include <sstream>

using namespace std;
//____________________define operations

#define OP_NO -1 //nothing
#define OP_PL -2 // +
#define OP_MI -3 // -
#define OP_MU -4 // *
#define OP_STOP -777 // stop search
#define OP_GO -666

//____________________end define

int get_int(vector<int>& x) {
	int res = 0;
	int k = x.size() - 1;
	for (int i = 0; i < x.size(); i++){
		res += pow(10,k) * x[i];
		k--;
	}
	x.clear();
	return res;
};

void init_list(vector<int> data, vector<int> operators, list<int>& list_res) {
	int size = operators.size() - 1;
	vector<int> x;
	for(int i = 0; i <= size; i++) {
		x.push_back(data[i]);
		while(operators[i] == OP_NO) {
			x.push_back(data[++i]);
		}
		list_res.push_back(get_int(x));
		list_res.push_back(operators[i]);
	}
	list_res.pop_back();
};

int get_res(vector<int> data,vector<int> operators) {
	list<int> list_res;
	init_list(data, operators, list_res);

	int x = 0;
	for(auto it = list_res.begin(); it != list_res.end(); it++) {
		if (*it == OP_MU){
			auto it_l = --it;
			++it;
			auto it_r = ++it;
			--it;

			*it = (*it_l) * (*it_r);

			list_res.erase(it_l);
			list_res.erase(it_r);
		}
	}
	for(auto it = list_res.begin(); it != list_res.end(); it++) {
			if ((*it == OP_MI) || (*it == OP_PL)) {
			auto it_l = --it;
			++it;
			auto it_r = ++it;
			--it;

			if (*it == OP_MI)
				*it = (*it_l) - (*it_r);
			else
				*it = (*it_l) + (*it_r);

			list_res.erase(it_l);
			list_res.erase(it_r);
		}
	}
	if (list_res.size() == 1)
		return list_res.front();
	else {
		cout << "WTF NOT RES" << endl;
		return 0;
	}
};

void change_operators(vector<int>& operators) {
	int i = 0;
	int size = operators.size() - 1;
	while(i < size) {
		if (operators[i] == OP_MU) {
			operators[i] = OP_NO;
			i++;
			if (i == size) {
				operators[i] = OP_STOP;
			}
		} else {
			operators[i] -= 1;
			break;
		} 
	}

};

string to_string(int x) { return std::to_string(x); }

string get_string(vector<int> data,vector<int> operators) {
	string str;
	std::stringstream ss;

	int k = 0;
	for (int i = 0; i < data.size(); i++) {
			ss << data[i];
			str.append(ss.str());
			ss.str("");
			if (operators[k] == OP_NO) {
				k++;
				continue;
			}
			else if (operators[k] == OP_PL)
				str.append("+");
			else if (operators[k] == OP_MI)
				str.append("-");
			else if (operators[k] == OP_MU)
				str.append("*");
			k++;
	}
	return str;
}

void search(vector<int>& data, vector<int>& operators, int res, vector<string>& answer) {
	int i = 0;
	while(operators[operators.size() - 1] != OP_STOP) {
		if (res == get_res(data, operators)){
			answer.push_back(get_string(data, operators));
		}
		change_operators(operators);
	}
};

int main(int argc, char* argv[]) {
	string argv_str = string(argv[1]);

	int res = atoi(argv[1]);
	vector<int> data;
	vector<int> operators;
	vector<string> answer;

	for (int i = 2; i < argc; i++) {
		int element = atoi(argv[i]);
		data.push_back(element);
	}
	for (int i = 0; i < data.size() - 1; i++) {
		operators.push_back(OP_NO);
	}
	operators.push_back(OP_GO);

	search(data, operators, res, answer);

	for (auto i: answer) {
		cout << i << "=" << res << endl;
	}
}
