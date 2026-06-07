#pragma once

#include <expected>
#include "class.h"
namespace nina {
	namespace result {
		/*
			like option
			just a simple wrapper of std::expected
			TODO: will be re-implemented in the future
		*/
		template <typename val_t, typename err_t>
		struct expected: public nina_alias<std::expected<val_t, err_t>> {};

		template <typename val_t>
		struct ok_t {
			val_t val;

			template <typename err_t>
			operator expected<val_t, err_t>() {
				return expected<val_t, err_t>{val};
			}
		};

		template <typename err_t>
		struct error_t {
			err_t err;

			template <typename val_t>
			operator expected<val_t, err_t>() {
				return expected<val_t, err_t>{std::unexpected{err}};
			}
		};

		auto ok(auto &&val) {
			return ok_t<std::decay_t<decltype(val)>>{val};
		}

		auto error(auto &&err) {
			return error_t<std::decay_t<decltype(err)>>{err};
		}
	} // namespace result
	using result::error_t;
	using result::ok_t;

	using result::expected;
} // namespace nina
