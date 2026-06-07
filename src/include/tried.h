#pragma once

#include "expected.h"
#include "panic.h"
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
				unreachable();
			}
			return expected_t{opt.value()};
		}

		auto get_unexpected(option<T> const &opt) const -> unexpected_t {
			if (is_expected(opt)) {
				unreachable();
			}
			return none;
		}
	};

	template <typename val_t, typename err_t>
	struct try_traits<expected<val_t, err_t>> {
		using expected_t   = val_t;
		using unexpected_t = err_t;

		auto is_expected(expected<val_t, err_t> const &res) const -> bool {
			return res.has_value();
		}

		auto get_expected(expected<val_t, err_t> const &res) const -> expected_t {
			if (!is_expected(res)) {
				unreachable();
			}
			return res.value();
		}

		auto get_unexpected(expected<val_t, err_t> const &res) const -> unexpected_t {
			if (is_expected(res)) {
				unreachable();
			}
			return res.error();
		}
	};
} // namespace nina
