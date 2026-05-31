#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace nina {
	using int8	   = std::int8_t;
	using int16	   = std::int16_t;
	using int32	   = std::int32_t;
	using int64	   = std::int64_t;
	using int_size = std::ptrdiff_t;

	using uint8		= std::uint8_t;
	using uint16	= std::uint16_t;
	using uint32	= std::uint32_t;
	using uint64	= std::uint64_t;
	using uint_size = std::size_t;

	// llvm你去死吧
	// 不用stdfloat的内容，是因为llvm的libc++没有更新
	// TODO: 使用stdfloat或者准确的定位浮点数
	using float16 = float;
	using float32 = double;
	using float64 = long double;

	template <typename val_t>
	using global_alloc = std::allocator<val_t>;

	template <template <typename> typename alloc_t>
	using string = std::basic_string<char, std::char_traits<char>, alloc_t<char>>;

	template <typename... types>
	using sum = std::variant<types...>;

	template <typename... types>
	using product = std::tuple<types...>;

	template <typename val_t, template <typename> typename alloc_t>
	using vector = std::vector<val_t, alloc_t<val_t>>;
} // namespace nina
