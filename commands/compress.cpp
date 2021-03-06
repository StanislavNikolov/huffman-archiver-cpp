#include "compress.hpp"
#include "../huffman/compress.hpp"

#include<fstream>
#include<sstream>

void compress(const char* in_file, const char* out_file) {
	std::ofstream out(out_file);
	compress(in_file, out);
}

void compress(const char* in_file, std::ostream& out_stream) {
	std::ifstream in(in_file);
	auto freq_table = readTable(in);
	in.close();
	in.open(in_file);
	BinaryWrite bin_out(out_stream);
	compress(freq_table, in, bin_out);
}

void compress(std::istream& in_stream, std::ostream& out) {
	const std::string in_data((std::istreambuf_iterator<char>(in_stream)),
			std::istreambuf_iterator<char>());

	std::array<uint64_t, BYTES_COUNT> freq_table;
	{
		std::istringstream in_stream(in_data);
		freq_table = readTable(in_stream);
	}
	{
		std::istringstream in_stream(in_data);
		BinaryWrite bin_out(out);
		compress(freq_table, in_stream, bin_out);
	}
}
