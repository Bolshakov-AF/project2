#include <iostream>
#include <string>

template <typename T>
concept ComplexConcept = !std::has_virtual_destructor<T>::value && requires(const T v)
{
    {v.hash()} -> std::convertible_to<long>;
    {v.toString()} -> std::same_as<std::string>;
};

class ATest
{
public:
    ATest(const int v) :_v(v)
    {}
    virtual ~ATest()
    {}
    int hash() const
    {
        return _v;
    }
    std::string toString() const
    {
        return std::to_string(_v);
    }
private:
    int _v;
};

class BTest
{
    int _v;
public:
    BTest(const int v) :_v(v)
    {}
    int hash() const
    {
        return _v;
    }
    std::string toString() const
    {
        return std::to_string(_v);
    }
};

template <ComplexConcept T>
void concept_method(T val)
{
    std::cout << "Hash: " << val.hash() << std::endl;
    std::cout << "String: " << val.toString() << std::endl;
}

int main()
{
    //ATest a(2);
    //concept_method<A>(a);

    BTest b(4);
    concept_method<BTest>(b);
    return 0;
}