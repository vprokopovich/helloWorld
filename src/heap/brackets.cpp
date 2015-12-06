#include <iostream>
#include "brackets.h"
#include "helpers.h"

bool Brackets::CheckBrackets(const std::string& in)
{
    _balance.empty();

    for(std::size_t i = 0; i < in.size(); i++)
    {
        auto parseResult = ParseBracket(in[i]);

        if (Unsupported == parseResult)
        {
            continue;
        }
        else if (Open == parseResult)
        {
            _balance.push_back(in[i]);
        }
        else
        {
            if (_balance.size() == 0)
            {
                return false;
            }
            if (in[i] == GetClosingPair(_balance.back()))
            {
                _balance.pop_back();
            }
            else
            {
                return false;
            }
        }
    }

    return (_balance.size() == 0);
}

Brackets::Status Brackets::ParseBracket(const char& br) const
{
    for (auto& it : _supported)
    {
        if (it._open == br)
        {
            return Open;
        }
        else if (it._close == br)
        {
            return Close;
        }
    }    
    return Unsupported;
}

char Brackets::GetClosingPair(const char& br) const
{
    for (auto& it : _supported)
    {
        if (it._open == br)
        {
            return it._close;
        }
    }
    std::string err = "Unsupported bracket: ";
    err += br;
    throw std::invalid_argument(err);

    return 0; // to avoid warning
}