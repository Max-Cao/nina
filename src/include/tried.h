#pragma once

#include "./panic.h"
#include "./typedef.h"
#include "option.h"

#define tried(...)                                                                                                                                                                 \
	{                                                                                                                                                                              \
		auto &&res = __VA_ARGS__;                                                                                                                                                  \
		if (!nina::try_traits<std::decay_t<decltype(res)>>::is_expected(res)) {                                                                                                    \
			return nina::try_traits<std::decay_t<decltype(res)>>::get_unexpected(res);                                                                                             \
		}                                                                                                                                                                          \
		nina::try_traits<std::decay_t<decltype(res)>>::get_expected(res);                                                                                                          \
	}

namespace nina {
	template <typename>
	struct try_traits {
		static_assert(false, "Unspecialization type for try_traits");
	};

	template <typename T>
	struct try_traits<option<T>> {
		using expected_t   = some_t<T>;
		using unexpected_t = none_t;

		auto is_expected(option<T> const &opt) const -> bool {
			return opt.has_value();
		}

		auto get_expected(option<T> const &opt) const -> expected_t {
			if (!is_expected(opt)) {
				panic::unreachable();
			}
			return expected_t{opt.value()};
		}

		auto get_unexpected(option<T> const &opt) const -> unexpected_t {
			if (is_expected(opt)) {
				panic::unreachable();
			}
			return none;
		}
	};


} // namespace nina
