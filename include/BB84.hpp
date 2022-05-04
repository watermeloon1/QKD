#ifndef BB84_HPP
#define BB84_HPP
 
class BB84 : public QProtocol{
    public:
        BB84(); // constructor
        ~BB84(); // destructor
        std::string get_protocol_name();

};

#endif