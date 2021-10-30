template<class derived>
2
struct compare {};
3
struct value : public compare<value> 
4
{
5
    value(const int x): m_x(x) {}
6
    bool operator<(const value &rhs) const { return m_x < rhs.m_x; }
7
private:
8
    int m_x;
9
};
10
11
template <class derived>
12
bool operator>(const compare<derived> &lhs, const compare<derived> &rhs) {
13
    // static_assert(std::is_base_of_v<compare<derived>, derived>); // Compile time safety measures
14
    return (static_cast<const derived&>(rhs) < static_cast<const derived&>(lhs));
15
}
16
17
/*  Same goes with other operators
18
 == :: returns !(lhs < rhs) and !(rhs < lhs)
19
 != :: returns !(lhs == rhs)
20
 >= :: returns (rhs < lhs) or (rhs == lhs)
21
 <= :: returns (lhs < rhs) or (rhs == lhs) 
22
*/
23
24
int main()
25
{   
26
    value v1{5}, v2{10};
27
    cout <<boolalpha<< "v1 == v2: " << (v1 > v2) << '\n';
28
    return 0;
29
}
30
// Now no need to write comparator operators for all the classes, 
31
// Write only type dependent `operator <` &  use CRTP
