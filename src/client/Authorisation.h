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
    std::string getLogin() const;
    std::string getPass() const;
    bool isEmptyLogin() const;
    bool isEmptyPass() const;
    bool isCorrectPass() const;
    bool isCorrectData(std::string name, std::string key) const; // a function for getting an answer from server
};

#endif // AUTHORISATION_H
