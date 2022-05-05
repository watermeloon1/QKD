#ifndef BB84_HPP
#define BB84_HPP

#include <string>
 
class BB84 : public QProtocol{
    public:
        BB84(); // constructor
        ~BB84(); // destructor
        
        std::string get_protocol_name();

        void set_qber();
        double get_qber();
        
};

#endif