#pragma once
#include <string>
#include <fstream>

class Message
{
private:
	std::string _from;
	std::string _to;
	std::string _text;
public:
	Message() = default;
	~Message() = default;
	Message(const std::string &from, const std::string& to, const std::string& text);
	const std::string& getFrom() const;
	const std::string& getTo() const;
	const std::string& getText() const;
	friend std::ifstream& operator >>(std::ifstream& is, Message& obj);
	friend std::ostream& operator <<(std::ostream& os, const Message& obj);
};

