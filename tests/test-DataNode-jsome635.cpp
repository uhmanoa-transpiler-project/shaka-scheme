#include "gtest/gtest.h"
#include "DataNode.h"

#include <boost/variant.hpp>

#include <functional>
#include <algorithm>
#include <numeric>
#include <string>


enum class MetaTag {
	DEFINE,
	PROC_CALL
};

using Data = boost::variant<
	MetaTag,
	int,
	std::string
>;



using DataTree = shaka::DataNode<Data>;

TEST(DataNode, constructor_defualt) {
	// Define 3 shaka::DataNode<Data>
	DataTree root1(MetaTag::PROC_CALL);
	DataTree root2(1);
	DataTree root3("a");

	// Try to retrieve the types inside
	auto data1 = boost::get<MetaTag>(*root1.get_data());
	auto data2 = boost::get<int>(*root2.get_data());
	auto data3 = boost::get<std::string>(*root3.get_data());

	// Here is how we check if it's one of the inside types:
	if (MetaTag* ptr =
		boost::get<MetaTag>(root1.get_data().get())) {
		std::cout << "root1 is a MetaTag" << std::endl;
	} else if (int* ptr =
		boost::get<int>(root1.get_data().get())) {
		std::cout << "root1 is an int" << std::endl;
	} else if (std::string* ptr =
		boost::get<std::string>(root1.get_data().get())) {
		std::cout << "root1 is a std::string" << std::endl;
	} else {
		std::cout << "root1 doesn't appear to be holding "
		"one of its variant types" << std::endl;
	}

	std::shared_ptr<DataTree> root = std::make_shared<DataTree>(
		MetaTag::DEFINE
	);

}

/*
/// @brief Basic default constructor test
TEST(DataNode, constructor_default) {
    DataTree root(shaka::MetaTag::NULL_LIST);

    ASSERT_TRUE(true);
}

TEST(DataNode, creaete_list) {
	auto root = std::make_shared<DataTree>(shaka::MetaTag::LIST);

	// Push children to the root node
	root->push_child(1);
	root->push_child(2);
	root->push_child(3);

	// Get pointer to the data of the first child
	auto first_child_ptr = root->get_child(0);

	// Get an 'int' from the data pointer inside the DataNode.
	auto first_child_data = shaka::get<int>( *first_child_ptr->get_data() );

	// Is 1 == first_child_data?
	ASSERT_EQ(1, first_child_data);

	// Get the parent of the first child
	auto first_childs_parent = first_child_ptr->get_parent();

	// Is the first child's parent root?
	ASSERT_EQ(first_childs_parent,root);

}

TEST(DataNode, create_and_verify_list){
	// Create a LIST root node, and then
	// push three ints that should up to 10.
	//
	// Then, only using the root node,
	// get the three children,
	// get the ints from them
	// add them together
	// and assert that their sum is equal to 10.

	auto root = std::make_shared<DataTree>(shaka::MetaTag::LIST);

	root->push_child(-1);
	root->push_child(11);
	root->push_child(0);

	auto child_data_1 = shaka::get<int>( *root->get_child(0)->get_data() );
	auto child_data_2 = shaka::get<int>( *root->get_child(1)->getdata() );
	auto child_data_2 = shaka::get<int>( *root->get_child(2)->getdata() );

	ASSERT_EQ(10,child_data_1+child_data_2+child_data_3 )
}
*/


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
