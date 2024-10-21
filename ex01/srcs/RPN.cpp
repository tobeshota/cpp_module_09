#include "RPN.hpp"

// 文字列がすべて数字で構成されているかを確認する
static bool isAllDigits(const std::string& str) {
  if (str.empty()) return false;
  for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
    if (!std::isdigit(*it))
      return false;  // 1つでも数字でない文字があればfalseを返す
  }
  return true;  // 全て数字ならtrueを返す
}

static void calaculateSafely(std::stack<int>& stack, int operation) {
  // 引数チェック
  if (stack.size() < 2)
    throw std::length_error("Error: Stack size is less than 2");
  // 値を2つ取り出す
  const int v1 = stack.top();
  stack.pop();
  const int v2 = stack.top();
  stack.pop();
  switch (operation) {
    case ADD:
      stack.push(add(v1, v2));
      break;
    case SUB:
      stack.push(sub(v1, v2));
      break;
    case MUL:
      stack.push(mul(v1, v2));
      break;
    case DIV:
      stack.push(divSafely(v1, v2));
      break;
  }
}

static int getOperatorSafely(const std::string& str) {
  std::string operation[] = {"+", "-", "*", "/"};
  for (size_t i = 0; i < sizeof(operation) / sizeof(operation[0]); i++) {
    if (str == operation[i]) return i;
  }
  throw std::invalid_argument("Error: " + str + ": invalid argument");
  return 0;
}

void rpn(const std::string& input) {
  try {
    if (input.empty())
      throw std::invalid_argument("Error: arguments are empty");
    std::istringstream ss(input);
    std::string elem;
    std::stack<int> stack;
    while (std::getline(ss, elem, ARGV_DELIMITER)) {
      // 1桁の数字の場合，stackに安全に格納する
      if (isAllDigits(elem) && elem.length() == 1)
        stack.push(str2TSafely(elem, static_cast<int>(42)));
      else  // 演算子の場合，安全に演算する
        calaculateSafely(stack, getOperatorSafely(elem));
    }
    // 計算結果を出力する
    std::cout << stack.top() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}