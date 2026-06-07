#pragma once
#include <optional>
#include "class.h"

namespace nina {

	/*
		just a simple wrapper of std::optional
		TODO: will be re-implemented in the future
	*/
	template <typename val_t>
	struct option: public nina_alias<std::optional<val_t>> {};

	template <typename val_t>
	struct some_t {
		val_t val;

		operator option<val_t>() {
			return option{val};
		}
	};

	struct none_t {
		template <typename cast_to>
		operator option<cast_to>() {
			return option<cast_to>{std::nullopt};
		}
	};

	template <typename val_t>
	inline static auto some(val_t&& val) {
		return some_t{std::forward<std::decay_t<val_t>>(val)};
	}

	inline static auto none = none_t{};
} // namespace nina
