#include <gtest/gtest.h>

#include "core/base/DataNode.h"
#include "core/base/Port.h"

#include <sstream>

using namespace shaka;

TEST(Port, initialization) {
	std::string str = "sample";
	//Port(std::string str, Mode mode, Type type, Source source)
//	shaka::Port p0(str, shaka::Port::Mode::TEXT, shaka::Port::Type::INPUT, shaka::Port::Source::STRING);
	shaka::Port p1(str, shaka::Port::Mode::TEXT, shaka::Port::Type::INPUT, shaka::Port::Source::FILESTREAM);
		
//	shaka::Port p2(str, shaka::Port::Mode::TEXT, shaka::Port::Type::OUTPUT, shaka::Port::Source::STRING);
//	shaka::Port p3(str, shaka::Port::Mode::TEXT, shaka::Port::Type::OUTPUT, shaka::Port::Source::FILESTREAM);
	
//	shaka::Port p3(shaka::Port::Mode::BINARY, shaka::Port::Type::INPUT);
//	shaka::Port p4(str, shaka::Port::Mode::BINARY, shaka::Port::Type::OUTPUT, shaka::Port::Source::STRING);

	//Check if mode and type is the sample
	ASSERT_EQ(p1.get_mode(), shaka::Port::Mode::TEXT);
	ASSERT_EQ(p1.get_type(), shaka::Port::Type::INPUT);
	ASSERT_EQ(p1.get_source_type(), shaka::Port::Source::FILESTREAM);
	
//	ASSERT_EQ(p4.get_mode(), shaka::Port::Mode::BINARY);
//	ASSERT_EQ(p4.get_type(), shaka::Port::Type::OUTPUT);
//	ASSERT_EQ(p4.get_source_type(), shaka::Port::Source::STRING);
}

TEST(Port, file) {

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
