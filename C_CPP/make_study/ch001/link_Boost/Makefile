# 自行编译的 Boost 库
# BOOST_DIR = $${HOME}/boost
# BOOST_LIB_DIR = ${BOOST_DIR}/stage/lib

# CXXFLAGS 和 LDFLAGS 分别代表公共的编译和链接参数
# CXXFLAGS = -l $(BOOST_DIR)
# LDFLAGS = -L $(BOOST_LIB_DIR) -Wl,-R
# $(BOOST_LIB_DIR)

all: static_boost shared_boost

static_boost: main.cpp
	g++ main.cpp $(CXXFLAGS) $(LDFLAGS) -l:libboost_regex.a -o static_boost

shared_boost: main.cpp
	g++ main.cpp $(CXXFLAGS) $(LDFLAGS) -lboost_regex -o shared_boost

clean:
	rm *_boost