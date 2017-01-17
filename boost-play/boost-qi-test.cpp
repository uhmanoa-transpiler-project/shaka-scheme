#include "precomp-boost.h"


int main(int argc, char** argv) {

    std::vector<double> vec_numbers;

    auto vec_writer = [&vec_numbers](double d) {
        vec_numbers.push_back(d);
    };

    auto parser = [&vec_writer](boost::spirit::istream_iterator begin,
                                boost::spirit::istream_iterator end) {

        using boost::spirit::qi::double_;

        bool r = boost::spirit::qi::phrase_parse(
            begin,
            end,
            double_[vec_writer] >> *(',' >> double_[vec_writer]),
            boost::spirit::qi::ascii::space
        );

        if (begin != end) {
            return false;
        } else {
            return r;
        }
    };
        

    if (argc == 2) {
        std::ifstream filein(argv[1]);
        filein.unsetf(std::ios::skipws);

        boost::spirit::istream_iterator begin(filein);
        boost::spirit::istream_iterator end;

        std::cout << parser(
            begin,
            end
        ) << std::endl;

        for (auto it : vec_numbers) {
            std::cout << it << ' ';
        }   std::cout << std::endl;

    }
}