#include "catch2/catch.hpp"


#include "instruction/instruction.h"
#include "tokenizer/tokenizer.h"
#include "analyser/analyser.h"
#include <sstream>
#include <iostream>
#include <climits>
/*
	不要忘记写测试用例喔。
*/

TEST_CASE("Test analizer") {
	std::vector<std::string> _instructions = { "ILL", "LIT", "LOD", "STO", "ADD",
	"SUB", "MUL", "DIV", "WRT" };
	std::string input =
		"begin\n"
		"const b = 1;\n"
		"var a;\n"
		"a = 4294967295;"
		"print(a+b*5);\n"
		"end\n";
	std::stringstream ss;
	ss.str(input);
	miniplc0::Tokenizer toekenizer(ss);
	auto result = toekenizer.AllTokens();
	std::vector<miniplc0::Token> tks = result.first;
	miniplc0::Analyser analizer(tks);
	auto result2 = analizer.Analyse();
	if (result2.second.has_value()) {
		auto error = result2.second.value();
		std::cout << error.GetCode() << " " <<
			error.GetPos().first << " " << error.GetPos().second << "\n";
		FAIL();
	}
	else {
		std::vector<miniplc0::Instruction> instructions = result2.first;
		std::vector<miniplc0::Instruction>::iterator it;
		for (it = instructions.begin(); it != instructions.end(); it++) {
			std::cout << _instructions.at(it->GetOperation()) << " " << it->GetX() << "\n";
		}
	}
}