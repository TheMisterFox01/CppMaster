#include <Windows.h>
#include <string>
#include <vector>
#include <map>


using unary_func = double(*)(double);


using binary_func = double(*)(double, double);


using unary_table = std::map<std::string, unary_func>;

using binary_table = std::map<std::string, binary_func>;


using unary_loader = unary_table & (*)(void);

using binary_loader = binary_table & (*)(void);


class plugin_loader
{
    std::vector<HMODULE> to_free; 
  public:
    unary_table dll_unary_table; 
    binary_table dll_binary_table; 


    plugin_loader(std::string plugins_path = "plugins/");


     void load_unary(HMODULE lib);
    

    void load_binary(HMODULE lib);

    ~plugin_loader();
};
