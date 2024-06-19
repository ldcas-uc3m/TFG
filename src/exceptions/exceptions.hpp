#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP


#include <exception>
#include <string>


class TFGException : public std::exception {

    public:
        TFGException(std::string msg) : _message(msg) {}
        std::string what() { return _message; }

        const std::string type = "TFGException";
    private:
        std::string _message;
};


class LUISPDAException : public TFGException {
    using TFGException::TFGException;
    public:
        const std::string type = "LUISPDAException";

};


class RFException : public TFGException {
    using TFGException::TFGException;
    public:
        const std::string type = "RFException";
};


class MEMException : public TFGException {
    using TFGException::TFGException;
    public:
        const std::string type = "MEMException";
};

class CompilerException : public TFGException {
    using TFGException::TFGException;
    public:
        const std::string type = "CompilerException";
};


class StopExecution : public TFGException {
    using TFGException::TFGException;
    public:
        const std::string type = "StopExecution";

};


#endif