# A generic Result class

### Inspired by Rust's Result data structure, it returns the result or the error.

&nbsp;

```cpp
struct BisectResult{
	std::size_t iter;
	double root;
};


Result<BisectResult, const char*> FindRoot(double f)
{
	if(std::abs(f) <= 1E-6)
		return {Ok, BisectResult{20, 1.44}};

	return {Err, "No root found"};
}

int main() {

	auto root = FindRoot(0.0);
	if(const auto r = root.get_if())
		std::cout<<"Root="<<r->root <<" iter="<<r->iter;
	else
		std::cout<<root.err();
}

```

&nbsp;

## Requirements
 Requires C++17 or higher.