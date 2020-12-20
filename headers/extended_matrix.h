#pragma once

#include "../headers/extended_types.h"
#include <unordered_map>


/**
* Here is implementation of a endless(within reasonable limits of course) any rank sparse matrix using unordered_map
*/
template<typename T, T defaultValue, size_t Rank = 2, typename = std::enable_if_t<std::is_integral_v<T>>>
class SparseMatrix {
  private:

    template <size_t TI>
    using Tuple = impl::typeTuple<TI>;

    template <size_t TP>
    using Key = impl::Key<TP>;

    template <template<size_t> class TK>
    using Hash = impl::Hash<TK>;

    using KeeperType = std::unordered_map<Key<Rank>, T, Hash<Key>>;

    /**
    * Proxy class. Index key computation helper.
    */
    template<size_t R, size_t SZ>
    class Idexer {
      public:

        Idexer(KeeperType& inKeeper, const size_t& index)
            : refKeeper(inKeeper), currentTuple(std::tuple<size_t>(index)) {}

        template<typename...  Ts>
        Idexer(KeeperType& inKeeper, const size_t& index, const std::tuple<Ts...>& inTuple)
            : refKeeper(inKeeper), currentTuple(std::tuple_cat(inTuple, std::tuple<size_t>(index))) {}

        Idexer<R - 1, SZ> operator[] (const size_t& index) {
            return Idexer<R - 1, SZ>(refKeeper, index, currentTuple);
        }

      private:
        KeeperType& refKeeper;
        Tuple<SZ - R> currentTuple;
    };

    /**
    * Proxy class. Index key computation.
    */
    template<size_t SZ>
    class Idexer<0, SZ> {
      public:

        template<typename...  Ts>
        Idexer(KeeperType& inKeeper, const size_t& index, const std::tuple<Ts...>& inTuple)
            : refKeeper(inKeeper), resultTuple(std::tuple_cat(inTuple, std::tuple<size_t>(index))) {}

        auto& operator=(const T& inValue) {

            if (inValue != defaultValue)
                refKeeper[Key<Rank>(resultTuple)] = inValue;
            else
                refKeeper.erase(Key<Rank>(resultTuple));

            return *this;
        }

        bool operator== (const T& inValue) {

            auto search = refKeeper.find(Key<Rank>(resultTuple));
            T foundValue{search == refKeeper.end() ? defaultValue : search->second};

            if (foundValue == inValue)
                return true;
            else
                return false;
        }

        operator T() const {

            auto search = refKeeper.find(Key<Rank>(resultTuple));

            if (search != refKeeper.end())
                return search->second;
            else
                return defaultValue;
        }

      private:
        KeeperType& refKeeper;
        Tuple<Rank> resultTuple;
    };

    /**
    * Iterator class. Needed for matrix traversal.
    */
	class iterator {
	  public:

		iterator(typename KeeperType::const_iterator it) : iter(it) {}

		iterator operator++() {
			++iter;
			return *this;
		}

		bool operator!=(const iterator& other) const {
		    return iter != other.iter;
        }

		const auto operator*() const {
			return std::tuple_cat(iter->first.indexes, std::make_tuple(iter->second));
		}

	  private:
		typename KeeperType::const_iterator iter;
	};

  public:
     SparseMatrix() = default;
    ~SparseMatrix() = default;

    auto operator[](const size_t& index) {
        return Idexer<Rank - 1, Rank>(this->keeper, index);
	}

	size_t size() {
		return keeper.size();
	}

	iterator begin() const {
	    return iterator(keeper.cbegin());
    }

	iterator end() const {
	    return iterator(keeper.cend());
    }

private:
    KeeperType keeper;
};
