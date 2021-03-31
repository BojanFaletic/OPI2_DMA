#ifndef REGISTER_HPP__
#define REGISTER_HPP__

#include "memory.hpp"
#include <map>

class Register
{
private:
    u32 base_hash;
    u32 offset;


public:
    Register(u32 base, u32 offset);

    ~Register();

    void write();

    void read();
};

#endif