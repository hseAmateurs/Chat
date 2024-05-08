#include "Authorisation.h"

Authorisation::Authorisation(std::string name, std::string key)
{
    this->login = name;
    this->pass = key;
}

std::string Authorisation::getLogin() const
{
    std::string name = this->login;
    return name;
}

std::string Authorisation::getPass() const
{
    std::string key = this->pass;
    return pass;
}

bool Authorisation::isEmptyLogin() const
{
    if (this->login.empty())
    {
        return true; // empty
    }
    else
    {
        return false;
    }
}

bool Authorisation::isEmptyPass() const
{
    if (this->pass.empty())
    {
        return true; // empty
    }
    else
    {
        return false;
    }
}

bool Authorisation::isCorrectPass() const
{
    int countCapital = 0, countLowercase = 0, countDigit = 0;
    if (this->pass.length() >= 5)
    {
        for (int i = 0; i < this->pass.length(); ++i)
        {
            if (this->pass[i] >= 65 && this->pass[i] <= 90)
            {
                countCapital += 1;
            }
            else if (this->pass[i] >= 97 && this->pass[i] <= 122)
            {
                countLowercase += 1;
            }
            else if (this->pass[i] >= 48 && this->pass[i] <= 57)
            {
                countDigit += 1;
            }
            if (countCapital >= 1 && countLowercase >= 1 && countDigit >= 1)
            {
                return true;
            }
        }
        return false;
    }
    return false;
}

bool Authorisation::isCorrectData(std::string name, std::string key) const
{
    // the server checks login and password, which it gets from GetLogin() and GetPass()
    // the server sends an answer about the user's registration
    return true; // correct data - this user exists
    //return false; // wrong data - this user does not exist
}

