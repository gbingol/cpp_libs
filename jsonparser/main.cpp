#include <iostream>
#include <filesystem>
#include "json.h"

int main()
{
	//exe is in outdir directory
	JSON::JSON json(std::filesystem::path("../jsonparser/testfiles/widgets.json"));
	JSON::Error err;
	auto v = json.Parse(err);

	if(!err.failed)
		std::cout << v;
}