#include <boost/bind.hpp>
#include <boost/bind/bind.hpp>
#include <boost/version.hpp>
#include <iostream>

using namespace std;
using namespace boost;

int fun(int x, int y) { return x + y; }

int main() {
  cout << "Boost version: " << BOOST_VERSION << endl;
  cout << "Boost lib version: " << BOOST_LIB_VERSION << endl;

  cout << boost::bind(fun, _1, _2)(1, 2) << endl;
  return 0;
}