#include "../include/command/CommandTree.h"
#include "../include/command/Command.h"

#include <unistd.h>

inline bool CinIsTerminal() { return isatty(fileno(stdin)); }
inline bool CoutIsTerminal() { return isatty(fileno(stdout)); }
inline bool CerrIsTerminal() { return isatty(fileno(stderr)); }

inline void ShowSPrompt()
{
    if (CoutIsTerminal())
    {
        std::cout << "\033[36m" << "cattail" << "\033[0m" << "$ ";
    }
}

inline void Rephrase(std::string _str)
{
    if (!CoutIsTerminal())
    {
        static int cmdCount = 0;
        std::cout << "---- Command " << ++cmdCount << " ---- { " << _str << " }" << std::endl;
    }
}

int main()
{
    // STATE::SetVerbose(VLevel::Detailed);
    
    // Construct command tree for the program
    CTree cattail("cattail", CMD::Help, "display cattail help message");
    CTree ct_help("help", CMD::Help, "display cattail help message"); cattail.Grow(&ct_help);
    CTree ct_set("set", CMD::SET::Help, "display set help message"); cattail.Grow(&ct_set);
    CTree ct_set_help("help", CMD::SET::Help, "display set help message"); cattail.Grow(&ct_set_help);
    CTree ct_set_verbose("verbose", CMD::SET::Verbose, "set verbose level"); ct_set.Grow(&ct_set_verbose);
    CTree ct_set_color("color", CMD::SET::Color, "set output color"); ct_set.Grow(&ct_set_color);
    CTree ct_new("new", CMD::NEW::Help, "display new help message"); cattail.Grow(&ct_new);
    CTree ct_new_help("help", CMD::NEW::Help, "display new help message"); cattail.Grow(&ct_new_help);
    CTree ct_new_circ("circ", CMD::NEW::Circ, "instantiate a circle object");  ct_new.Grow(&ct_new_circ);
    CTree ct_new_rect("rect", CMD::NEW::Rect, "instantiate a rectangle object");  ct_new.Grow(&ct_new_rect);
    CTree ct_new_tria("tria", CMD::NEW::Tria, "instantiate a triandle object");  ct_new.Grow(&ct_new_tria);
    CTree ct_tmp("tmp", CMD::Tmp, "view temporary memory object"); cattail.Grow(&ct_tmp);
    CTree ct_stk("stk", CMD::STK::Help, "display stk help message"); cattail.Grow(&ct_stk);
    CTree ct_stk_help("help", CMD::STK::Help, "display stk help message"); cattail.Grow(&ct_stk_help);
    CTree ct_stk_push("push", CMD::STK::Push, "push the temporary object into stack"); ct_stk.Grow(&ct_stk_push);
    CTree ct_stk_pop("pop", CMD::STK::Pop, "pop the stack top"); ct_stk.Grow(&ct_stk_pop);
    CTree ct_stk_top("top", CMD::STK::Top, "retrieve the stack top"); ct_stk.Grow(&ct_stk_top);
    CTree ct_stk_state("state", CMD::STK::State, "display stack status"); ct_stk.Grow(&ct_stk_state);
    CTree ct_exit("exit", CMD::Exit, "exit the program"); cattail.Grow(&ct_exit);
    
    // Call info function in advance
    if (CoutIsTerminal()) { CMD::Info(); }
    
    // Disable colored output for file IO
    if (!CerrIsTerminal()) { STATE::SetColor(false); }
    
    // handle user command
    int pos;
    std::string input;
    std::vector<std::string> cmd;
    std::function<void()> func;
    while (!std::cin.eof())
    {
        ShowSPrompt();
        
        // Fetch command & Interpret
        std::getline(std::cin, input);
        CTree::CommandSlice(input, cmd);
        Rephrase(input);
        if (VS::IsWhiteString(input)) { continue; }
        func = cattail.Retrieve(cmd, pos);
        
        // Passing remaining args into `lync`
        CMD::lync = std::stringstream();
        for (int i = pos; i < cmd.size(); i++)
        {
            STATE::LOG(VLevel::Detailed, "Passing \"" + cmd[i] + "\" into `lync`.");
            CMD::lync << cmd[i] << " ";
        }
        
        // Execute command & handle exception
        try { func(); }
        catch (const std::invalid_argument& excep)
        {
            CMD::tmpType = CMD::ptrType::none;
            std::cout << "Invalid argument received: " << excep.what() << std::endl;
        }
        catch (const std::exception& excep)
        {
            std::cout << "An exception occurred: " << excep.what() << std::endl;
        }
    }
    
    return 0;
}