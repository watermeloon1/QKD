#ifndef BB84_HPP
#define BB84_HPP

#include <vector>
 
class BB84 : public QProtocol{
    public:
        BB84();
        std::string get_protocol_name();

};

#endif