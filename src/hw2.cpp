#include "../include/hw2.h"
#include <fstream>
#include <algorithm>
#include <memory>

//Parametrized Constructor : 1st Question
User::User(std::string name, std::string pass, std::string mail) : username{ name }, password{ pass }, email{ mail }
{
}

//Default Destructor : 1st Question
User::~User() {



}

//Default Constructor : 1st Question
Login::Login() {}

//Default Destructor : 1st Question
Login::~Login() {
	for (auto it = users.begin(); it != users.end(); it++) {
		delete *it;
	}
	for (auto it = LoginedUsers.begin(); it != LoginedUsers.end(); it++) {
		delete* it;
	}
}



void Login::registerUser(std::string username, std::string password, std::string email) {
	if (checkUsername(username) == true && checkEmail(email) == true) {
		User* user = new User(username, password, email);
		users.push_back(user);
	}
	else {
		std::cout << "Sorry The User's Credentials Already Exist" << std::endl;
	}
}

void Login::readFile(std::string path) {
	std::string test;
	std::string username;
	std::string password;
	std::string email;
	std::string logstatus;
	std::ifstream of{ path };
	while (of >> test) {
		of >> username >> password >> email >> logstatus;
		registerUser(username, password, email);
		if (logstatus == "Yes")
			loginUser(username, password);
	}
	of.close();
}

bool Login::checkEmail(std::string& new_email) {
	for (std::vector<User*> ::iterator i = users.begin(); i != users.end(); i++) {
		if ((*i)->email == new_email)
			return false;
	}
	return true;
}


bool Login::checkUsername(std::string& new_username) {
	for (std::vector<User*> ::iterator i = users.begin(); i != users.end(); i++) {
		if ((*i)->username == new_username)
			return false;
	}
	return true;
}

void Login::loginUser(std::string username, std::string password) {
	int p{ 1 };
	//check if the user Name already exits:
	for (std::vector<User*> ::iterator i = LoginedUsers.begin(); i != LoginedUsers.end(); i++){
		if ((*i)->username == username) {
			p = 0;
			break;
		}
	}
	//Now To pushback in vector:
	if (p == 1) {
		User* userlog = new User(username, password, "No email");
		LoginedUsers.push_back(userlog);
	}
	else {
		std::cout << "The user name cannot be logged in twice , Since it has been already logged in" << std::endl;
	}
}

User* Login::getUser(std::string username) {
	for (std::vector<User*> ::iterator i = users.begin(); i != users.end(); i++) {
		if ((*i)->username == username)
			return *i;
	}
	std::cout << "The User does not exist" << std::endl;
	return nullptr;
}

void Login::changeUsername(std::string username, std::string newUsername) {
	int p{};
	for (std::vector<User*> ::iterator j = LoginedUsers.begin(); j != LoginedUsers.end(); j++) {
		if ((*j)->username == username) {
			(*j)->username = newUsername;
			break;
		}
	}
	for (std::vector<User*> ::iterator i = users.begin(); i != users.end(); i++) {
		if ((*i)->username == username) {
			(*i)->username = newUsername;
			p = 0;
			break;
		}
		else
			p = 1;
	}
	if (p == 1)
		std::cout << "Sorry , The Username Entered has not been Found" << std::endl;
}

void Login::changePassword(std::string username, std::string newPassword) {
	int p{};
	for (std::vector<User*> ::iterator i = users.begin(); i != users.end(); i++) {
		if ((*i)->username == username) {
			(*i)->password = newPassword;
			p = 0;
			break;
		}
		else
			p = 1;
	}
	if (p == 1)
		std::cout << "Sorry, the username entered has not been found" << std::endl;
}

void Login::changeMail(std::string username, std::string newMail) {
	int p{};
	for (std::vector<User*> ::iterator i = users.begin(); i != users.end(); i++) {
		if ((*i)->username == username) {
			(*i)->email = newMail;
			p = 0;
			break;
		}
		else
			p = 1;
	}
	if (p == 1)
		std::cout << "Sorry , The Username Entered has not been Found" << std::endl;

}

void Login::removeUser(std::string username) {
	for (std::vector<User*> ::iterator j = LoginedUsers.begin(); j != LoginedUsers.end(); j++) {
		if ((*j)->username == username) {
			LoginedUsers.erase(j);
			std::cout << "User Successfully Removed From LogginedUsers" << std::endl;
			break;
		}
	}
	for (std::vector<User*> ::iterator i = users.begin(); i != users.end(); i++) {
		if ((*i)->username == username) {
			users.erase(i);
			std::cout << "User Successfully Removed From Users" << std::endl;
			return;
		}
	}

	std::cout << "User Not Found" << std::endl;
}



