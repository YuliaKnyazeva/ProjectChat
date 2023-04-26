#include "Database.h"

void Database::Connect()
{
	mysql_init(&_mysql);
	if (&_mysql == nullptr) {
		// Если дескриптор не получен — выводим сообщение об ошибке
		std::cout << "Error: can't create MySQL-descriptor" << std::endl;
	}
	// Подключаемся к серверу
	if (!mysql_real_connect(&_mysql, "localhost", "root", "poison", "testdb", NULL, NULL, 0)) {
		// Если нет возможности установить соединение с БД выводим сообщение об ошибке
		std::cout << "Error: can't connect to database " << mysql_error(&_mysql) << std::endl;
	}
	else {
		// Если соединение успешно установлено выводим фразу — "Success!"
		std::cout << "Success!" << std::endl;
	}
}

void Database::Disconnect()
{
	mysql_close(&_mysql);
}

void Database::CreateTables()
{
	mysql_query(&_mysql, "CREATE TABLE IF NOT EXISTS users(id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), login VARCHAR(255), password VARCHAR(255))");
	mysql_query(&_mysql, "INSERT INTO users(id, name, login, password) values(default, 'Daria', 'Daria', '123')");
	mysql_query(&_mysql, "INSERT INTO users(id, name, login, password) values(default, 'Lida', 'Lida', '234')");
	mysql_query(&_mysql, "INSERT INTO users(id, name, login, password) values(default, 'Nastya', 'Nastya', '345')");
	mysql_query(&_mysql, "CREATE TABLE IF NOT EXISTS messages(id INT AUTO_INCREMENT PRIMARY KEY, from_id VARCHAR(255), to_id VARCHAR(255), text VARCHAR(255))");
	mysql_query(&_mysql, "INSERT INTO messages(id, from_id, to_id, text) values(default, 'Lida', 'Daria', 'Hi!')");
	mysql_query(&_mysql, "INSERT INTO messages(id, from_id, to_id, text) values(default, 'Daria', 'all', 'Hi all!')");
}

void Database::addUser(const std::string& login, const std::string& password, const std::string& name)
{
	std::string temp;
	temp = "INSERT INTO users (id, name, login, password) VALUES (default,' " + name + "','" + login + "','" + password + "')";
	mysql_query(&_mysql, temp.c_str());
}
