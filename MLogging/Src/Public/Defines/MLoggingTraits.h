#pragma once

namespace MLog {

	/// <summary>
	/// Type trait to test whether a class can accept input stream
	/// </summary>
	template <class _Ty, class _Tx>
	struct is_in_stream_friendly {
	private:
		template <class _Target, class _Test>
		constexpr static auto is_friendly() -> decltype(std::declval<_Target&>() >> std::declval<_Test>(), std::true_type) {}

		template <class, class>
		constexpr static auto is_friendly() -> std::false_type {}
	public:
		constexpr static bool value = decltype(is_friendly<_Ty, _Tx>())::value;
	};

	/// <summary>
	/// Type trait to test whether a class can be streamed
	/// </summary>
	template <class _Ty, class _Tx>
	struct is_out_stream_friendly {
	private:
		template <class _Target, class _Test>
		constexpr static auto is_friendly() -> decltype(std::declval<_Target&>() << std::declval<_Test>(), std::true_type) {}

		template <class, class>
		constexpr static auto is_friendly()->std::false_type {}
	public:
		constexpr static bool value = decltype(is_friendly<_Ty, _Tx>())::value;
	};

}