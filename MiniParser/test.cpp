#include <string>
using namespace std;
bool num(string input, int &position, int &ret)
{
    bool _success = false;
    int _pos0 = position;
    if(position + 1>=input.length())
        return false;
    if(input.substr(position, 1) == "1")
    {
        _success = true;
        position += 1;
    }
    else
    {
        _success =  false;
    }
    if(!_success)
    {
        return false;
    }
    int _dummy0;
    _success = num(input, position, _dummy0);
    if(_success)
    {
        return true;
    }
    position = _pos0;
    if(position + 0>=input.length())
        return false;
    if(input.substr(position, 0) == "")
    {
        _success = true;
        position += 0;
    }
    else
    {
        _success =  false;
    }
}
