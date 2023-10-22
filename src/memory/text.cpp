#include <string>
#include <cstdint>


// TODO: maybe don't?
class Instruction {
/*
LUISP-DA instruction definition
*/
    public:
        Instruction(std::string inst, std::uint32_t addr) {
            _inst = inst;
            _addr = addr;
        }

        const std::string & get_instuction() {
            return _inst;
        }

        // overload << operator
        friend std::ostream & operator << (std::ostream & out, Instruction const & ins) {

            out << "0x" << std::setfill('0') << std::setw(8) << std::right << std::hex << ins._addr;
            out << ins._inst;
            out << '\n';

            return out;
        }
    
    private:
        std::string _inst;  // instruction
        std::uint32_t _addr;  // address
};


// TODO: text segment (instructions)