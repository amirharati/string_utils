#include "Poco/RegularExpression.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdint.h>
using Poco::RegularExpression;
int main(int argc, char** argv)
{
  RegularExpression re1("[0-9]+");
  bool match = re1.match("123"); // true
  match = re1.match("abc"); // false
  match = re1.match("abc123", 3); // true
  RegularExpression::Match pos;
  re1.match("123", 0, pos); // pos.offset == 0, pos.length == 3
  re1.match("ab12de", 0, pos); // pos.offset == 2, pos.length == 2
  re1.match("abcd", 0, pos); // pos.offset == std::string::npos
  RegularExpression re2("([0-9]+) ([0-9]+)");
  RegularExpression::MatchVec posVec;
  re2.match("123 456", 0, posVec);
  // posVec[0].offset == 0, posVec[0].length == 7
  // posVec[1].offset == 0, posVec[1].length == 3
  // posVec[2].offset == 4, posVec[2].length == 3
  std::string s;
  int n = re1.extract("123", s); // n == 1, s == "123"
  n = re1.extract("ab12de", 0, s); // n == 1, s == "12"
  n = re1.extract("abcd", 0, s); // n == 0, s == ""
  std::vector<std::string> vec;
  re2.split("123 456", 0, vec);
  // vec[0] == "123"
  // vec[1] == "456"
  s = "123";
  re1.subst(s, "ABC"); // s == "ABC"
  s = "123 456";
  re2.subst(s, "$2 $1"); // s == "456 123"
  RegularExpression re3("ABC");
  RegularExpression re4("ABC", RegularExpression::RE_CASELESS);
  match = re3.match("abc", 0); // false
  std::cout << match << std::endl;
  match = re4.match("abc", 0); // true
  std::cout << match << std::endl;
  s = "Who’s amir is 20 abc Who's ";
  RegularExpression re5("\xE2\x80\x99s");
  std::cout<<s<<std::endl;
  
  //char *c = "’";
  wchar_t c = s[3];
  
  std::cout << "Your character was " << c << " (unicode "
	     << std::hex << std::setw(2) << static_cast<uint16_t>(s[3]) << ")\n";
  re5.subst(s, "'s");
  std::cout<<s<<std::endl;
  return 0;
}
