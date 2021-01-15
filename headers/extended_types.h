#pragma once

#include <cstdint>
#include <tuple>
#include <iostream>

namespace impl {


    /**
    * Helper completion of recursion
    */
    constexpr auto params(std::index_sequence<0>) {
        return std::tuple<size_t>{};
    }

    /**
    * Helper tuple typename fix-size with elements type size_t
    */
    template<std::size_t I, std::size_t... O>
    constexpr auto params(std::index_sequence<I, O...>) {
        auto tup = std::tuple{ size_t{} };
        auto seq = std::make_index_sequence<sizeof...(O)>{};
        return std::tuple_cat(tup, params(seq));
    }

    /**
    * Generator tuple typename fix-size with elements type size_t
    */
    template<std::size_t N>
    constexpr auto gen(std::integral_constant<std::size_t, N>) {
        return params(std::make_index_sequence<N>{});
    }

    /**
    * Defining tuple typename fix-size with elements type size_t
    */
    template<size_t SZ>
    using TupleNArgs = decltype(gen(std::integral_constant<size_t, SZ>{}));

    /**
    * Helper from once argument for counting hash-sum
    */
    template <typename T>
    T sum_args(T& arg) { return arg; }

    /**
    * Helper from many argument for counting hash-sum
    */
    template <typename T, typename T1, typename ... Ts>
    size_t sum_args(T& first_arg, T1& second_arg, Ts&... tail_args) {

        T hash_pairing = ((first_arg + second_arg) * (first_arg + second_arg + 1))/2 + second_arg;

        if constexpr(sizeof...(Ts) > 0){
            return sum_args(hash_pairing, tail_args...);
        }
        else
            return hash_pairing;
    }

    /**
    * Helper for outputting a tuple to the stream
    */
    template <typename T, typename ... Ts>
    void print_args(std::ostream &cur_stream, const T& first_arg, const Ts& ...tail_args) {

        cur_stream << first_arg;
        (void)std::initializer_list<int>{((cur_stream << tail_args), 0)...};

    }

    /**
    * Function for outputting a tuple to the stream
    */
    template <typename ... Ts>
    std::ostream& operator<<(std::ostream &cur_stream, const std::tuple<Ts...>& in_parameter) {

        auto print_to_stream = [&cur_stream](const auto &...lyambda_args) {
            print_args(cur_stream, lyambda_args...);
        };

        std::apply(print_to_stream, in_parameter);

        return cur_stream;
    }


    /**
    * Key class creates key from gotten N arguments or std::tuple.
    */
    template <size_t SZ>
    class Key {
      public:
        Key() = delete;

        template <typename... Ts, typename = std::enable_if_t<SZ == sizeof...(Ts)>>
        Key(Ts... args) : indexes(std::make_tuple(args...)) {}

        template<typename...  Ts, typename = std::enable_if_t<SZ == sizeof...(Ts)>>
        Key(const std::tuple<Ts...>& arg_tuple) : indexes(arg_tuple) {}

        bool operator==(const Key& param) const {
            return indexes == param.indexes;
        }

        auto getTuple() const { return indexes; }

        TupleNArgs<SZ> indexes;
    };

    /**
    * Hash class returns hashsumm of Key
    */
    template <template<size_t> class Key>
    class Hash {
    public:
        template <size_t SZ>
        size_t operator()(const Key<SZ>& in_parameter) const {

            auto hash_sum_tuple = [](const auto&... lyambda_args) { return impl::sum_args(lyambda_args...); };

            return std::apply(hash_sum_tuple, in_parameter.getTuple());
        }
    };

}//namespace impl
