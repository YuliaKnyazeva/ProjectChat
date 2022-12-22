#pragma once
#include <string>

class Message
{
private:
	std::string _from;
	std::string _to;
	std::string _text;
public:
	Message() = default;
	virtual ~Message() = default;
	Message(const std::string from, const std::string& to, const std::string& text);
	const std::string& getFrom();
	const std::string& getTo();
	const std::string& getText();
};

