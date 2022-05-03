#include <iostream>
#include <stack>
#include <algorithm>
#include <string>
using namespace std;

struct Vertex {
	string value;
	struct Vertex* left;
	struct Vertex* right;
};

class Derivative {
public:
	string infix_to_postfix(const string& infix) {
		string postfix;
		string temp;
		stack<string> stack;
		for (size_t i = 0; i < infix.size(); i++) {
			if (infix[i] == ' ' && temp != "") {
				if (!process_symbol_for_postfix(temp, postfix, stack))
					return "Input error";
				temp = "";
			}
			else {
				temp += infix[i];
			}
		}
		if (temp != "") {
			if (!process_symbol_for_postfix(temp, postfix, stack))
				return "Input error";
		}
		while (!stack.empty()) {
			if (stack.top() == "(")
				return "Input error";
			postfix += stack.top() + ' ';
			stack.pop();
		}
		return postfix;
	}

	Vertex* postfix_to_tree(const string& postfix) {
		stack<Vertex*> stack;
		string temp = "";
		for (size_t i = 0; i < postfix.size(); i++) {
			if (postfix[i] == ' ' && temp != "") {
				if (!process_symbol_for_tree(temp, stack))
					return new Vertex{ "Input error" };
				temp = "";
			}
			else {
				temp += postfix[i];
			}
		}
		if (temp != "") {
			if (!process_symbol_for_tree(temp, stack))
				return new Vertex{ "Input error" };
		}
		if (stack.size() == 1) {
			return stack.top();
		}
		else {
			return new Vertex{ "Input error" };
		}
	}

	void derivace(Vertex* root) {
		if (root->value == "x")
			root->value = '1';

		else if (isDouble(root->value))
			root->value = '0';

		else if (isOperator(root->value)) {
			Vertex* a = root->left;
			Vertex* b = root->right;
			Vertex* der_a = newVertex(*root->left); derivace(der_a);
			Vertex* der_b = newVertex(*root->right); derivace(der_b);

			if (root->value == "+" || root->value == "-") {
				root->left = der_a;
				root->right = der_b;
			}

			else if (root->value == "*") {
				root->value = "+";
				root->left = new Vertex{ "*", der_a, b };
				root->right = new Vertex{ "*", a, der_b };
			}

			else if (root->value == "/") {
				root->value = "/";
				root->left = new Vertex{ "-", new Vertex{"*", der_a, b}, new Vertex{"*", a, der_b} };
				root->right = new Vertex{ "*", b, b };
			}
		}
	}

	void reduce_tree(Vertex* root) {
		if (isOperator(root->left->value))
			reduce_tree(root->left);
		if (isOperator(root->right->value))
			reduce_tree(root->right);

		if (root->value == "+") {
			if (isDouble(root->left->value) && isDouble(root->right->value)) {
				root->value = to_string(stod(root->left->value) + stod(root->right->value));
				root->left = NULL; root->right = NULL;
			}
			else if (isDouble(root->left->value) && stod(root->left->value) == 0) {
				replace_with_right(*root);
			}
			else if (isDouble(root->right->value) && stod(root->right->value) == 0) {
				replace_with_left(*root);
			}
		}

		else if (root->value == "-") {
			if (isDouble(root->left->value) && isDouble(root->right->value)) {
				root->value = to_string(stod(root->left->value) - stod(root->right->value));
				root->left = NULL; root->right = NULL;
			}
			else if (isDouble(root->right->value) && stod(root->right->value) == 0) {
				replace_with_left(*root);
			}

		}

		else if (root->value == "*") {
			if (isDouble(root->left->value) && isDouble(root->right->value)) {
				root->value = to_string(stod(root->left->value) * stod(root->right->value));
				root->left = NULL; root->right = NULL;
			}
			else if ((isDouble(root->left->value) && stod(root->left->value) == 0) || (isDouble(root->right->value) && stod(root->right->value) == 0)) {
				make_zero(*root);
			}
			else if (isDouble(root->left->value) && stod(root->left->value) == 1) {
				replace_with_right(*root);
			}
			else if (isDouble(root->right->value) && stod(root->right->value) == 1) {
				replace_with_left(*root);
			}
		}

		else if (root->value == "/") {
			if (isDouble(root->left->value) && isDouble(root->right->value)) {
				root->value = to_string(stod(root->left->value) / stod(root->right->value));
				root->left = NULL; root->right = NULL;
			}
			else if (isDouble(root->left->value) && stod(root->left->value) == 0) {
				make_zero(*root);
			}
			else if (isDouble(root->right->value) && stod(root->right->value) == 1) {
				replace_with_left(*root);
			}
		}
	}

	void output(Vertex* root) {
		if (root->left != NULL) {
			cout << "(";
			output(root->left);
		}

		if (isDouble(root->value))
			cout << stod(root->value);
		else if (root->value.size() > 1 && root->value[0] == '-')
			cout << stod(root->value);
		else if (root->value == "x")
			cout << root->value;
		else
			cout << " " << root->value << " ";

		if (root->right != NULL) {
			output(root->right);
			cout << ")";
		}
	}
private:
	Vertex* newVertex(Vertex v) {
		return new Vertex{ v.value, v.left, v.right };
	}

	bool isDouble(const string& c) {
		int dots = 0;
		for (size_t i = 0; i < c.length(); i++) {
			if (c[i] == '.')
				dots++;
			else if (!isdigit(c[i]))
				return false;
		}
		if (dots <= 1)
			return true;
		else
			return false;
	}

	bool isOperator(const string& c) {
		if (c == "+" || c == "-" || c == "*" || c == "/")
			return true;
		else
			return false; 
	}

	bool isOperand(const string& c) {
		if (c == "x")
			return true;
		else if (isDouble(c))
			return true;
		else 
			return false;
	}

	int precedence(const string& c) {
		if (c == "+" || c == "-")
			return 1;
		else if (c == "*" || c == "/")
			return 2;
		else return 0;
	}

	bool process_symbol_for_postfix(const string& c, string& postfix, stack<string>& stack)
	{

		if (isOperand(c)) {
			postfix += c + ' ';
			return true;
		}

		else if (isOperator(c)) {
			while (!stack.empty() && stack.top() != "(" && precedence(stack.top()) >= precedence(c)) {
				postfix += stack.top() + ' ';
				stack.pop();
			}
			stack.push(c);
			return true;
		}

		else if (c == "(") {
			stack.push(c);
			return true;
		}

		else if (c == ")") {
			if (stack.empty())
				return false;
			while (stack.top() != "(") {
				postfix += stack.top() + ' ';
				stack.pop();
				if (stack.empty())
					return false;
			}
			stack.pop();
			return true;
		}
		else
			return false;
	}

	bool process_symbol_for_tree(const string& c, stack<Vertex*>& stack) {
		Vertex* newvertex = new Vertex;
		if (isOperand(c)) {
			newvertex->value = c;
			newvertex->left = NULL;
			newvertex->right = NULL;
			stack.push(newvertex);
		}
		else if (isOperator(c)) {
			if (stack.size() >= 2) {
				newvertex->value = c;
				newvertex->right = stack.top(); stack.pop();
				newvertex->left = stack.top(); stack.pop();
				stack.push(newvertex);
			}
			else {
				return false;
			}
		}
		return true;
	}

	void replace_with_left(Vertex& v) {
		v.value = v.left->value;
		v.right = v.left->right;
		v.left = v.left->left;
	}

	void replace_with_right(Vertex& v) {
		v.value = v.right->value;
		v.left = v.right->left;
		v.right = v.right->right;
	}

	void make_zero(Vertex& v) {
		v.value = "0";
		v.left = NULL;
		v.right = NULL;
	}
};

int main() {
	Derivative a;
	string line;
	while (getline(cin, line)) {

		if (line.empty())
			continue;

		string p = a.infix_to_postfix(line);
		if (p == "Input error") {
			cout << p << endl;
			continue;
		}

		Vertex* v = a.postfix_to_tree(p);
		if (v->value == "Input error") {
			cout << v->value << endl;
			continue;
		}

		a.derivace(v);

		a.reduce_tree(v);

		a.output(v);
		cout << endl;
	}
}
