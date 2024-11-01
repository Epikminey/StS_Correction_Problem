#ifndef CASE_H
#define CASE_H

class Case
{
private:
    //***Attributs***//
    char lettre_;
    bool signe_;

public:
    //***Constructeurs et destructeurs***//
    Case() = delete;

    Case(char lettre, bool signe);


};

#endif //CASE_H