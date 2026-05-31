// 以下代码来自 suslib, 感谢 Google LLC
// 调整部分代码，版权使用Apache-2.0 License

#pragma once

#include <string_view>

#include "fmt/base.h"
#include "fmt/core.h"

namespace nina {
	namespace panic {
		// TODO: 添加更多致命错误相关函数，比如更多系统接口

		/// Location of a panic
		// TODO: 使用了一些宏，后面要支持更多编译器
		struct panic_location {
			const char *file_name;
			const unsigned line;
			const unsigned column;

			constexpr static panic_location
			current(const char *file_name = __builtin_FILE(),
					unsigned line		  = __builtin_LINE(),
#if __has_builtin(__builtin_COLUMN)
					unsigned column = __builtin_COLUMN()
#else
					unsigned column = 0u
#endif
							) noexcept {
				return panic_location{
						.file_name = file_name,
						.line	   = line,
						.column	   = column,
				};
			}
		};

		[[noreturn]] inline static void abort() noexcept {
#if __has_builtin(__builtin_trap)
			__builtin_trap();
#elif __has_builtin(__fastfail)
			__fastfail(1);
#else
			std::abort();
#endif
		}

		[[noreturn]] inline static void panic(std::string_view message = "", panic_location loc = panic_location::current()) noexcept {
			fmt::print(stderr, "PANIC! at {}:{}:{}\n", loc.file_name, loc.line, loc.column);
			for (char c: message) {
				fmt::print(stderr, "%c", c);
			}
			abort();
		}

		[[noreturn]] inline static void unreachable(panic_location loc = panic_location::current()) noexcept {
			panic("Entered unreachable code", loc);
		}
	} // namespace panic
	using panic::abort;
	using panic::panic;
	using panic::unreachable;
} // namespace nina
