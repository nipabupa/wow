#include <exception>
#include <format>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
// 重新定义STL
using str = std::string;

template<typename T> using list = std::vector<T>;

template<typename T> using func = std::function<T>;

template<typename Key, typename Value>
using dict = std::unordered_map<Key, Value>;

using std::exception;

using std::format;
