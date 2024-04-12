#include <iostream>
#include <vector>

using namespace std;


class binarytree {
private:
	struct leaf {
		string name;
		vector <string> numbers;
		leaf* left;
		leaf* right;
	};
public:
	leaf* root = nullptr;
	string addPerson(string new_name, string new_num) {
		return addPerson(new_name, new_num, root);
	}
	string addPerson(string new_name, string new_num, leaf*& lf) {
		if (lf == nullptr) {
			lf = new leaf;
			lf->name = new_name;
			lf->numbers.push_back(new_num);
			lf->left = nullptr;
			lf->right = nullptr;
			return "Человек успешно добавлен\n";
		}
		if (new_name > lf->name) {
			return addPerson(new_name, new_num, lf->right);
		}
		else {
			return addPerson(new_name, new_num, lf->left);
		}
	}
	string addNumber(string find_name, string new_num) {
		if (findPerson(find_name).first == nullptr) {
			return "Человек не найден\n";
		}
		else {
			findPerson(find_name).first->numbers.push_back(new_num);
			return "Номер успешно добавлен\n";
		}
	}
	pair <leaf*, leaf**> findPerson(string find_name) {
		return findPerson(find_name, root);
	}
	pair <leaf*, leaf**> findPerson(string find_name, leaf*& lf) {
		if (lf == nullptr) {
			return make_pair(nullptr, nullptr);
		}
		if (find_name == lf->name) {
			return make_pair(lf, nullptr);
		}
		if (lf->left != nullptr) {
			if (find_name == lf->left->name) {
				return make_pair(lf->left, &(lf->left));
			}
		}
		if (lf->right != nullptr) {
			if (find_name == lf->right->name) {
				return make_pair(lf->right, &(lf->right));
			}
		}
		if (find_name > lf->name) {
			return findPerson(find_name, lf->right);
		}
		else {
			return findPerson(find_name, lf->left);
		}
	}
	void findNumbers(string find_name) {
		if (findPerson(find_name).first == nullptr) {
			cout << "Человек не найден\n";
			return;
		}
		else {
			cout << "Найденные номера телефона: ";
			for (auto now : findPerson(find_name).first->numbers) {
				cout << now << " ";
			}
			cout << endl;
			return;
		}
	}
	string delPerson(string find_name) {
		if (findPerson(find_name).first == nullptr) {
			return "Контакт не найден\n";
		}
		leaf* now = findPerson(find_name).first;
		leaf** prev = findPerson(find_name).second;
		if (findPerson(find_name).second == nullptr) {
			prev = &root;
		}
		if (now->left == nullptr && now->right == nullptr) {
			delete now;
			*prev = nullptr;
			return "Контакт успешно удален\n";
		}
		if (now->left == nullptr && now->right != nullptr) {
			*prev = now->right;
			delete now;
			return "Контакт успешно удален\n";
		}
		if (now->left != nullptr && now->right == nullptr) {
			*prev = now->left;
			delete now;
			return "Контакт успешно удален\n";
		}
		if (now->left->right != nullptr) {
			leaf* mx = now->left;
			while (mx->right->right != nullptr) {
				mx = mx->right;
			}
			mx->right->left = now->left;
			mx->right->right = now->right;
			delete now;
			*prev = mx->right;
			mx->right = nullptr;
			return "Контакт успешно удален\n";
		}
		else {
			now->left->right = now->right;
			*prev = now->left;
			delete now;
			return "Контакт успешно удален\n";
		}
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	binarytree bookNumbers;
	cout << "Добро пожаловать в телефонную книгу" << endl << endl <<
		"Доступные опции: " << endl <<
		"1) Добавить новый контакт в телефонную книгу" << endl <<
		"2) Добавить новый номер к контакту" << endl <<
		"3) Вывести номера человека" << endl <<
		"4) Удалить контакт" << endl <<
		"5) Выйти из книги" << endl << endl;
	int option = 0;
	string name, number;
	while (option != 5) {
		cout << endl << "Выберите опцию: ";
		cin >> option;
		cout << endl;
		if (option == 1) {
			cout << "Введите имя: ";
			cin >> name;
			cout << "Введите номер: ";
			cin >> number;
			cout << bookNumbers.addPerson(name, number);
			continue;
		}
		if (option == 2) {
			cout << "Введите имя: ";
			cin >> name;
			cout << "Введите номер: ";
			cin >> number;
			cout << bookNumbers.addNumber(name, number);
			continue;
		}
		if (option == 3) {
			cout << "Введите имя: ";
			cin >> name;
			bookNumbers.findNumbers(name);
			continue;
		}
		if (option == 4) {
			cout << "Введите имя: ";
			cin >> name;
			cout << bookNumbers.delPerson(name);
			continue;
		}
		if (option != 5) {
			cout << "Неверная опция! " << endl;
			continue;
		}
	}
	cout << "Спасибо, что воспользовались библиотекой!";
}
