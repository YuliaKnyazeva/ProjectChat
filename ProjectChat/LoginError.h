#pragma once
#include <exception>
#include <iostream>

class LoginError :
    public std::exception
{
public:
    virtual const char* what() const noexcept override { return "Данный логин уже используется"; }
};


