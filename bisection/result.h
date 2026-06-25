#pragma once

#include <variant>
#include <stdexcept>


struct OkTag {};
struct ErrTag {};

inline constexpr OkTag Ok;
inline constexpr ErrTag Err;


template <typename R, typename E>
class [[nodiscard]] Result{
public:
	template <typename T>
	Result(OkTag, T&& result) : m_Result(std::in_place_type<R>, std::forward<T>(result)) {}

	template <typename T>
	Result(ErrTag, T&& error) : m_Result(std::in_place_type<E>, std::forward<T>(error)) {}

	bool ok() const {
		return std::holds_alternative<R>(m_Result);
	}

	const E& err() const {
		if (auto* val = std::get_if<E>(&m_Result)) 
			return *val;
			
		throw std::runtime_error("Called err() on an Ok value");
	}

	const R& get() const {
		if (auto* val = std::get_if<R>(&m_Result)) 
			return *val;

		throw std::runtime_error("Called get() on an Err value");
	}

	const R* get_if() const noexcept{
		return std::get_if<R>(&m_Result);
	}


private:
	std::variant<R, E> m_Result;
};