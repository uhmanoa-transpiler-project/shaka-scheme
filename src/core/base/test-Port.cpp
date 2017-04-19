#include <gtest/gtest.h>

#include "core/base/DataNode.h"
#include "core/base/Port.h"

#include <sstream>

using namespace shaka;

//Text, input, filesteam -
TEST(Port, initialization_text_input_filestream) {
	std::string str = "sample";
	shaka::Port p1(str, shaka::Port::Mode::TEXT, shaka::Port::Type::INPUT, shaka::Port::Source::FILESTREAM);
		
	//Check if mode and type is the sample
	ASSERT_EQ(p1.get_mode(), shaka::Port::Mode::TEXT);
	ASSERT_EQ(p1.get_type(), shaka::Port::Type::INPUT);
	ASSERT_EQ(p1.get_source_type(), shaka::Port::Source::FILESTREAM);
}

//Text, input, string -
TEST(Port, initialization_text_input_string) {
	std::string str = "sample";
	
	//Port(std::string str, Mode mode, Type type, Source source)
	shaka::Port p0(str, shaka::Port::Mode::TEXT, shaka::Port::Type::INPUT, shaka::Port::Source::STRING);

	//Check if mode and type is the sample
	ASSERT_EQ(p0.get_mode(), shaka::Port::Mode::TEXT);
	ASSERT_EQ(p0.get_type(), shaka::Port::Type::INPUT);
	ASSERT_EQ(p0.get_source_type(), shaka::Port::Source::STRING);
}

//Text, output, filestream -
TEST(Port, initialization_text_output_filestream) {
	std::string str = "sample";

	shaka::Port p3(str, shaka::Port::Mode::TEXT, shaka::Port::Type::OUTPUT, shaka::Port::Source::FILESTREAM);
	
	ASSERT_EQ(p3.get_mode(), shaka::Port::Mode::TEXT);
	ASSERT_EQ(p3.get_type(), shaka::Port::Type::OUTPUT);
	ASSERT_EQ(p3.get_source_type(), shaka::Port::Source::FILESTREAM);
}

//Text, output, string -
TEST(Port, initialization_text_output_string) {
	std::string str = "sample";

	shaka::Port p3(str, shaka::Port::Mode::TEXT, shaka::Port::Type::OUTPUT, shaka::Port::Source::STRING);
	
	ASSERT_EQ(p3.get_mode(), shaka::Port::Mode::TEXT);
	ASSERT_EQ(p3.get_type(), shaka::Port::Type::OUTPUT);
	ASSERT_EQ(p3.get_source_type(), shaka::Port::Source::STRING);
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

//Binary, input, filesteam -
TEST(Port, initialization_binary_input_filestream) {
	std::string str = "sample";
	shaka::Port p1(str, shaka::Port::Mode::BINARY, shaka::Port::Type::INPUT, shaka::Port::Source::FILESTREAM);
		
	//Check if mode and type is the sample
	ASSERT_EQ(p1.get_mode(), shaka::Port::Mode::BINARY);
	ASSERT_EQ(p1.get_type(), shaka::Port::Type::INPUT);
	ASSERT_EQ(p1.get_source_type(), shaka::Port::Source::FILESTREAM);
}

//Binary, input, string -
TEST(Port, initialization_binary_input_string) {
	std::string str = "sample";
	
	//Port(std::string str, Mode mode, Type type, Source source)
	shaka::Port p0(str, shaka::Port::Mode::BINARY, shaka::Port::Type::INPUT, shaka::Port::Source::STRING);

	//Check if mode and type is the sample
	ASSERT_EQ(p0.get_mode(), shaka::Port::Mode::BINARY);
	ASSERT_EQ(p0.get_type(), shaka::Port::Type::INPUT);
	ASSERT_EQ(p0.get_source_type(), shaka::Port::Source::STRING);
}

//Binary, output, filestream -
TEST(Port, initialization_binary_output_filestream) {
	std::string str = "sample";

	shaka::Port p3(str, shaka::Port::Mode::BINARY, shaka::Port::Type::OUTPUT, shaka::Port::Source::FILESTREAM);
	
	ASSERT_EQ(p3.get_mode(), shaka::Port::Mode::BINARY);
	ASSERT_EQ(p3.get_type(), shaka::Port::Type::OUTPUT);
	ASSERT_EQ(p3.get_source_type(), shaka::Port::Source::FILESTREAM);
}

//Binary, output, string -
TEST(Port, initialization_binary_output_string) {
	std::string str = "sample";

	shaka::Port p3(str, shaka::Port::Mode::BINARY, shaka::Port::Type::OUTPUT, shaka::Port::Source::STRING);
	
	ASSERT_EQ(p3.get_mode(), shaka::Port::Mode::BINARY);
	ASSERT_EQ(p3.get_type(), shaka::Port::Type::OUTPUT);
	ASSERT_EQ(p3.get_source_type(), shaka::Port::Source::STRING);
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
