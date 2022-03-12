#include<stdio.h>
#include<string>
#include<vector>
class debug{
public:
    debug(int val_,std::string t_):val(val_),t(t_) {}
    void push_int();
    std::string get_string();
private:
    int val;
    std::string t;
    std::vector<int> num;
};