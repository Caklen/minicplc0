#include "catch2/catch.hpp"
#include "tokenizer/tokenizer.h"
#include "fmt/core.h"
#include <sstream>
#include <vector>
#include <iostream>

// 下面是示例如何书写测试用例
TEST_CASE("Test tokenizer") {
	std::string input = 
		"begin\n"
		"	var a = 1;\n"
		"	const b = 1\n"
		"	print(a+b);\n"
		"end\n";
	std::stringstream ss;
	ss.str(input);
	miniplc0::Tokenizer tkz(ss);
	std::vector<miniplc0::Token> output = {};
	auto result = tkz.AllTokens();
	if (result.second.has_value()) {
		FAIL();
	}
	else {
		std::vector<miniplc0::Token>::iterator it;
		for (it = result.first.begin(); it != result.first.end(); it++)
		{
			auto p = it->GetStartPos();

			std::cout << p.first << " " << p.second << " "  << 
				it->GetType() << " " << it->GetValueString() << "\n";
		}
	}
	// REQUIRE( (result.first == output) );
}