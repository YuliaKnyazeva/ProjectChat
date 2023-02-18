#pragma once
#include <exception>

class LoginError :
    public std::exception
{
public:
    virtual const char* what() const noexcept override { return "Данный логин уже используется"; }
};


