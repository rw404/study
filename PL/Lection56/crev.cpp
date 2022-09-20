#include <iostream>
#include <type_traits>
#include <vector>
#include <iterator>
#include <algorithm>

int
main() {
  std::vector<char> v;

  std::copy(std::istream_iterator<char>(std::cin),
      std::istream_iterator<char>(),
      std::back_inserter(v)
      );

  std::copy(v.rbegin(), v.rend(), std::ostream_iterator<char>(std::cout));
  return 0;
}
