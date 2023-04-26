#pragma once
#include <iostream>
#include <mysql.h>

class Database
{
public:
	void Connect();
	void Disconnect();
	void CreateTables();
	void addUser(const std::string& login, const std::string& password, const std::string& name);
private:
	MYSQL _mysql{ nullptr };
};

