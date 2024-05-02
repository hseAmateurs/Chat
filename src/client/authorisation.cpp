#include "Authorisation.h"

Authorisation::Authorisation(std::string name, std::string key)
{
    this->login = name;
    this->pass = key;
}

std::string Authorisation::GetLogin() const
{
    std::string name = this->login;
    return name;
}

std::string Authorisation::GetPass() const
{
    std::string key = this->pass;
    return pass;
}

bool Authorisation::IsEmptyLogin() const
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

bool Authorisation::IsEmptyPass() const
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

bool Authorisation::IsCorrectData(std::string name, std::string key) const
{
    // the server checks login and password, which it gets from GetLogin() and GetPass()
    // the server sends an answer about the user's registration
    return true; // correct data - this user exists
    //return false; // wrong data - this user does not exist
}

