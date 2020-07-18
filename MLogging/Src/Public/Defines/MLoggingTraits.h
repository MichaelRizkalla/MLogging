#pragma once

namespace MLog {

	template <class _Ty, class TFirst, class... Args>
	struct is_in_stream_friendly {
	public:
		constexpr static bool value = is_in_stream_friendly<_Ty, TFirst>::value &
										is_in_stream_friendly<_Ty, Args...>::value;
	};

	/// <summary>
	/// Type trait to test whether a class can accept input stream
	/// </summary>
	template <class _Ty, class _Tx>
	struct is_in_stream_friendly <_Ty, _Tx> {
	private:
		template <class _Target, class _Test>
		constexpr static auto is_friendly(int) -> decltype(std::declval<_Target&>() >> std::declval<_Test>(), std::true_type());

		template <class, class>
		constexpr static auto is_friendly(...)->std::false_type;
	public:
		constexpr static bool value = decltype(is_friendly<_Ty, _Tx>(0))::value;
	};

	template <class _Ty, class TFirst, class... Args>
	struct is_out_stream_friendly {
	public:
		static constexpr bool value = is_out_stream_friendly<_Ty, TFirst>::value &
										is_out_stream_friendly<_Ty, Args...>::value;
	};

	/// <summary>
	/// Type trait to test whether a class can be streamed
	/// </summary>
	template <class _Ty, class _Tx>
	struct is_out_stream_friendly<_Ty, _Tx> {
	private:
		template <class _Target, class _Test>
		static auto is_friendly(int) -> decltype(std::declval<_Target&>() << std::declval<_Test>(), std::true_type());

		template <class, class>
		static auto is_friendly(...)->std::false_type;
	public:
		static constexpr bool value = decltype(is_friendly<_Ty, _Tx>(0))::value;
	};

}