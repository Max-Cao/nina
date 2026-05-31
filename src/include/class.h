#pragma once

#define nina_ref const &
#define nina_ref_mut &
#define nina_moved &&

namespace nina {
	template <typename val_t>
	struct nina_new_type {
		val_t val;

		val_t operator*() {
			return val;
		}
		val_t operator()() {
			return val;
		}
		explicit operator val_t() {
			return val;
		}
	};

	template <typename val_t>
	struct nina_alias {
		val_t val;

		val_t operator*() {
			return val;
		}
		val_t operator()() {
			return val;
		}
		operator val_t() {
			return val;
		}
	};

} // namespace nina
