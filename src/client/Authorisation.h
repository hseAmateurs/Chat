#ifndef AUTHORISATION_H
#define AUTHORISATION_H
#include <iostream>
#include <string>

class Authorisation
{
private:
    std::string login;
    std::string pass;
public:
    Authorisation(std::string name, std::string key);
    std::string GetLogin() const;
    std::string GetPass() const;
    bool IsEmptyLogin() const;
    bool IsEmptyPass() const;
    bool IsCorrectPass() const;
    bool IsCorrectData(std::string name, std::string key) const; // a function for getting an answer from server
};

#endif // AUTHORISATION_H
