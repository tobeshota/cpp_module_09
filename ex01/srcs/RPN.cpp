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
  throw std::invalid_argument("Error: " + str + ": invalid token");
  return -1;
}

void printResultSafely(const std::stack<int>& stack) {
  if (stack.size() != 1)
    throw std::invalid_argument("Error: number of operators is Insufficient");
  std::cout << stack.top() << std::endl;
}

static bool isTokenDigit(const std::string& token) {
  return (isAllDigits(token) && token.length() == 1);
}

static bool isTokenOperator(const std::string& token) {
  return (token == "+" || token == "-" || token == "*" || token == "/");
}

static STATE getState(const std::string& token) {
  if (isTokenDigit(token)) return DIGIT_STATE;
  if (isTokenOperator(token)) return OPERATOR_STATE;
  return INVALID_STATE;
}

void rpn(const std::string& istr) {
  try {
    if (istr.empty())
      throw std::invalid_argument("Error: arguments are empty");

    std::istringstream iss(istr);
    std::string token;
    std::stack<int> stack;
    while (std::getline(iss, token, ARGV_DELIMITER)) {
      switch (getState(token)) {
        case DIGIT_STATE:
          stack.push(str2TSafely(token, static_cast<int>(42)));
          break;
        case OPERATOR_STATE:
          calaculateSafely(stack, getOperatorSafely(token));
          break;
        case INVALID_STATE:
        default:
          throw std::invalid_argument("Error: " + token + ": invalid token");
      }
    }
    printResultSafely(stack);
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}
