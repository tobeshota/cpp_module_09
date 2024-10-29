#pragma once

#include <iostream>
#include <sstream>
#include <stack>

#define ARGV_DELIMITER ' '

typedef enum { ADD, SUB, MUL, DIV } OPERATION;
typedef enum { DIGIT_STATE, OPERATOR_STATE, INVALID_STATE } STATE;

void rpn(const std::string &input);

// 文字列を指定された型に安全に変換する。変換が失敗した場合は例外を投げる。
template <typename Container>
static Container str2TSafely(const std::string &s, Container type) {
  (void)type;  // 型推論のために使わない引数
  std::stringstream ss(s);
  Container value;
  ss >> value;
  // 変換が失敗した場合、または残った文字列がある場合は例外を投げる
  if (ss.fail() || !ss.eof())
    throw std::invalid_argument("Error:" + s + "type failed to convert");
  return value;
}

template <typename Container>
Container add(Container v1, Container v2) {
  return v2 + v1;
}

template <typename Container>
Container sub(Container v1, Container v2) {
  return v2 - v1;
}

template <typename Container>
Container mul(Container v1, Container v2) {
  return v2 * v1;
}

template <typename Container>
Container divSafely(Container v1, Container v2) {
  if (v1 == 0) throw std::range_error("NaN");
  return v2 / v1;
}
