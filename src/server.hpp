#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED

namespace shortener {

class Server
{
public:
    virtual ~Server() = default;

    virtual void setup() = 0;
    virtual void run() = 0;
};

}

#endif
