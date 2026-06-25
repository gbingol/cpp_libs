# Bisection method

A generic, type-safe bisection method (uses interval-halving approach).

&nbsp;

```cpp
int main() {

	auto f = [](auto x)
	{ 
		using T = decltype(x);
		return std::pow(x, T{10}) - T{1.0};
	};

	auto res = bisect<double>(f, 0.0, 3.0, 1E-6, 100);
	if(auto p = res.get_if())
		std::cout<<p->Root <<std::endl;

	return 0;
}
```

&nbsp;

## Requirements
 Requires C++20 or higher.