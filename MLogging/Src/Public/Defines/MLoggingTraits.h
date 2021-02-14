#pragma once

namespace MLog {

	template <class Ty, class TFirst, class... Args>
	struct is_in_stream_friendly {
	public:
		constexpr static bool value = is_in_stream_friendly<Ty, TFirst>::value &
										is_in_stream_friendly<Ty, Args...>::value;
	};

	/// <summary>
	/// Type trait to test whether a class can accept input stream
	/// </summary>
	template <class Ty, class Tx>
	struct is_in_stream_friendly <Ty, Tx> {
	private:
		template <class Target, class Test>
		constexpr static auto is_friendly(int) -> decltype(std::declval<Target&>() >> std::declval<Test>(), std::true_type());

		template <class, class>
		constexpr static auto is_friendly(...)->std::false_type;
	public:
		constexpr static bool value = decltype(is_friendly<Ty, Tx>(0))::value;
	};

	template <class Ty, class TFirst, class... Args>
	struct is_out_stream_friendly {
	public:
		static constexpr bool value = is_out_stream_friendly<Ty, TFirst>::value &
										is_out_stream_friendly<Ty, Args...>::value;
	};

	/// <summary>
	/// Type trait to test whether a class can be streamed
	/// </summary>
	template <class Ty, class Tx>
	struct is_out_stream_friendly<Ty, Tx> {
	private:
		template <class Target, class Test>
		static auto is_friendly(int) -> decltype(std::declval<Target&>() << std::declval<Test>(), std::true_type());

		template <class, class>
		static auto is_friendly(...)->std::false_type;
	public:
		static constexpr bool value = decltype(is_friendly<Ty, Tx>(0))::value;
	};

}