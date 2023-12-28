#ifndef INC_4_PRINT_TUPLE_H
#define INC_4_PRINT_TUPLE_H

#include <iostream>

template<int I, int N, typename Ch, typename Tr, typename... Args> struct output {
    static void out(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...>const& t) {
        os << std::get<I>(t) << "\t";
        output<I+1, N, Ch, Tr, Args...>::out(os, t);
    }
};

template<int N, typename Ch, typename Tr, typename... Args> struct output<N, N, Ch, Tr, Args...> {
    static void out(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...>const& t) {}
};

template<typename Ch, typename Tr, typename... Args>
auto operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t) {
    output<0, sizeof...(Args), Ch, Tr, Args...>::out(os, t);
}

#endif //INC_4_PRINT_TUPLE_H
