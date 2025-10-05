#include "printable.hpp"

std::ostream &operator<<(std::ostream &stream, const Printable &printable)
{
    return printable.print(stream);
}