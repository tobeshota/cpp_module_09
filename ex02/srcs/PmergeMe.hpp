#pragma once

#include <algorithm>
#include <vector>
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>  //  for std::stringstream


void pmergeMe(char **argv);

// ---------- template function ---------- //

// 文字列を指定された型に安全に変換する。変換が失敗した場合は例外を投げる。
template <typename Container>
Container str2TSafely(const std::string &s, Container type) {
  (void)type;
  std::stringstream ss(s);
  Container value;
  ss >> value;
  if (ss.fail() || !ss.eof())
    throw std::invalid_argument("Error:" + s + "type failed to convert");
  return value;
}

template <typename Container>
Container storeValueSafely(char **srcs,
                           void (Container::*insertMethod)(const int &)) {
  Container dest;
  for (int i = 1; srcs[i];
       i++) {  //	int i = 1である理由は，srcs[1]=="./PmergeMe"のため
    // char*をint型に安全に変換する
    int num = str2TSafely(std::string(srcs[i]), static_cast<int>(42));
    // 変換した値が負の数なら例外を投げる
    if (num < 0) throw std::invalid_argument("Error");
    // 値をコンテナに代入する
    (dest.*insertMethod)(num);
  }
  return dest;
}

template <typename Container>
Container storeValueSafely(const char **srcs,
                           void (Container::*insertMethod)(const int &)) {
  Container dest;
  for (int i = 1; srcs[i];
       i++) {  //	int i = 1である理由は，srcs[1]=="./PmergeMe"のため
    // char*をint型に安全に変換する
    int num = str2TSafely(std::string(srcs[i]), static_cast<int>(42));
    // 変換した値が負の数なら例外を投げる
    if (num < 0) throw std::invalid_argument("Error");
    // 値をコンテナに代入する
    (dest.*insertMethod)(num);
  }
  return dest;
}

template <typename Container>
void putDataforDebug(Container stl) {
  std::cout << "- (putDataforDebug) ---------" << std::endl;
  for (typename Container::iterator it = stl.begin(); it != stl.end(); it++)
    std::cout << "test: " << *it << std::endl;
}
