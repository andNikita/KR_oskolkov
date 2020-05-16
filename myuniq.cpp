#include <iostream>
#include <string>
#include <set>

using namespace std;

int main(){

	string str;
	set<string> box;

	while(std::cin) {
		getline(cin, str);
		box.emplace(str);
	}

	for (auto i : box) {
		cout << i << std::endl;
	}
}