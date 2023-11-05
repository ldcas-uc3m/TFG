#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP


#include <exception>
#include <string>


class TFGException : public std::exception {

    public:
        TFGException(std::string msg) : _message(msg) {}
        std::string what() {
            return _message;
        }

        std::string type() {
            return _type;
        }


    private:
        std::string _message;
        const std::string _type = "TFGException";
};


class LUISPDAException : public TFGException {
    using TFGException::TFGException;
    using TFGException::what;
    using TFGException::type;

    private:
        const std::string _type = "LUISPDAException";
};


class RFException : public TFGException {
    using TFGException::TFGException;
    using TFGException::what;
    using TFGException::type;

    private:
        const std::string _type = "RFException";
};


#endif