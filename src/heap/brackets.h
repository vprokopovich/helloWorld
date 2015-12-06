#include <vector>

class Brackets
{
public:

    Brackets()
        : _supported({{'(', ')'}, {'[',']'},{'{','}'}})
    {}
    
    bool CheckBrackets(const std::string& in);
private:
    struct BracketPair
    {
        BracketPair(const char& open, const char& close)
            : _open(open)
            , _close(close)
        {}

        char _open;
        char _close;
    };

    enum Status
    {
        Unsupported,
        Open,
        Close
    };

    Status ParseBracket(const char& br) const;
    char GetClosingPair(const char& br) const;

    std::vector<BracketPair> _supported;
    std::vector<char>        _balance;
};