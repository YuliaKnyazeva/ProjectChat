#include "Message.h"

Message::Message(const std::string &from, const std::string& to, const std::string& text):_from(from),_to(to),_text(text){}

const std::string& Message::getFrom()
{
	return _from;
}

const std::string& Message::getTo()
{
	return _to;
}

const std::string& Message::getText()
{
	return _text;
}

std::ifstream& operator >>(std::ifstream& is, Message& obj)
{
	is >> std::ws;
	std::getline(is, obj._text,'|');
	is >> obj._from;
	is >> obj._to;
	return is;
}

std::ostream& operator <<(std::ostream& os, const Message& obj)
{
	os << '\n';
	os << obj._text;
	os << '|';
	os << obj._from;
	os << ' ';
	os << obj._to;
	return os;
}