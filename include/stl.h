#ifndef WOW_STL
#define WOW_STL 1
//----------------------------
// 自定义SLT
//----------------------------
#include <exception>
#include <format>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

using str = std::string;
template<typename T>
using list = std::vector<T>;
template<typename T>
using func = std::function<T>;
template<typename Key, typename Value>
using dict = std::unordered_map<Key, Value>;
using std::exception;
using std::format;
using std::cout;
using std::endl;

#endif
