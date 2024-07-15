#include<iostream>
template<typename T1, typename T2>
class KeyValuePair
{
    private:
        T1 key;
        T2 value;
    public:
        T1 getKey()
        {
            return key;
        }
        void setKey(T1 k)
        {
            key = k;
        }
        T2 getvalue()
        {
            return value;
        }
        void setvalue(T2 v)
        {
            value = v;
        }
        KeyValuePair(T1 k, T2 v)
        {
            key = k;
            value = v;
        }
};

int main()
{
    KeyValuePair<int,std::string> pair(3,"doaa");
    int key = pair.getKey();
    std::cout << pair.getKey() << ":" << pair.getvalue() << std::endl;
}
