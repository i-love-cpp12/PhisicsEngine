#pragma once

#include<iostream>

class Printable
{
    protected:
        virtual std::ostream& print(std::ostream& stream) const = 0;
        friend std::ostream& operator<<(std::ostream& stream, const Printable& printable);
};

std::ostream& operator<<(std::ostream& stream, const Printable& printable);