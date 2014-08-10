#pragma once

#include <sstream>
#include <map>
#include <set>
template<typename T, typename U>
struct bimap : public std::map<T, std::set<U>>, public std::map<U, std::set<T>> {
	using map_tu = std::map<T, std::set<U>>;
	using map_ut = std::map<U, std::set<T>>;
	bimap() : map_tu(), map_ut()
	{}

	void insert( const T &t, const U &u ) {
		map_tu &tu = *this;
		map_ut &ut = *this;
		tu[ t ].insert( u );
		ut[ u ].insert( t );
	}
	void insert( const U &u, const T &t ) {
		insert( t, u );
	}

	template<typename T>
	struct proxy {
		bimap *ptr;
		T t;
		template<typename U>
		proxy &operator=( const U &u ) { 
			ptr->insert( t, u );
			return *this;
		}
	};

	proxy<U> operator[]( const U &u ) {
		return proxy<U>{ this, u }; 
	}
	proxy<T> operator[]( const T &t ) {
		return proxy<T>{ this, t }; 
	}

	std::string str() const {
		std::stringstream ss;
		for( auto &t : (const map_tu&)*this ) {
			ss << t.first << '=';
			for( auto &u : t.second ) {
				ss << u << ',';
			}
			ss << std::endl;
		}
		for( auto &u : (const map_ut&)*this ) {
			ss << u.first << '=';
			for( auto &t : u.second ) {
				ss << t << ',';
			}
			ss << std::endl;
		}
		return ss.str();
	}
};

