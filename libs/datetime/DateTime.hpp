#pragma once

#include <chrono>
#include <string>

namespace onion
{

	/// Represents a date and time in Coordinated Universal Time (UTC) with millisecond precision.
	///
	/// Instances are always valid and represent a precise point in time.
	/// The supported year range is [1, 9999].
	class DateTime
	{

	  public:
		/// Creates a DateTime object representing the current UTC date and time.
		DateTime();

		/// Constructs a DateTime object with the specified UTC date and time components.
		/// @param year Year component in range [1, 9999].
		/// @param month Month component in range [1, 12].
		/// @param day Day component in valid range for the specified month and year.
		/// @param hours Hour component in range [0, 23].
		/// @param minutes Minute component in range [0, 59].
		/// @param seconds Second component in range [0, 59].
		/// @param milliseconds Millisecond component in range [0, 999].
		/// @throws std::out_of_range If any component is outside its valid range.
		/// @throws std::invalid_argument If the calendar date is invalid.
		DateTime(int year, int month, int day, int hours, int minutes, int seconds, double milliseconds = 0);

		/// Returns the current UTC date and time.
		/// @return A DateTime representing the current UTC time.
		static DateTime UtcNow();

	  public:
		/// Returns the year component of the UTC date.
		/// @return Year in range [1, 9999].
		int getYear() const;

		/// Returns the month component of the UTC date.
		/// @return Month in range [1, 12].
		int getMonth() const;

		/// Returns the day component of the UTC date.
		/// @return Day value valid for the current month and year.
		int getDay() const;

		/// Returns the hour component of the UTC time.
		/// @return Hour in range [0, 23].
		int getHours() const;

		/// Returns the minute component of the UTC time.
		/// @return Minute in range [0, 59].
		int getMinutes() const;

		/// Returns the second component of the UTC time.
		/// @return Second in range [0, 59].
		int getSeconds() const;

		/// Returns the millisecond component of the UTC time.
		/// @return Millisecond in range [0, 999].
		double getMilliseconds() const;

	  public:
		bool operator==(const DateTime& other) const;
		bool operator!=(const DateTime& other) const;
		bool operator<(const DateTime& other) const;
		bool operator<=(const DateTime& other) const;
		bool operator>(const DateTime& other) const;
		bool operator>=(const DateTime& other) const;

	  public:
		/// @brief Returns a string representation of the DateTime in ISO 8601 format (e.g., "2024-06-15T12:30:45.500Z").
		/// @return A string representing the DateTime in ISO 8601 format.
		std::string toString() const;

		/// Returns a string representation of the DateTime formatted according to the provided chrono format string.
		///
		/// The format string follows the C++20 `std::chrono` formatting rules
		/// (same syntax as `std::format` for date/time types).
		///
		/// Common format specifiers:
		///
		/// Date components:
		///   %Y  Year as a four-digit number (e.g., 2026)
		///   %y  Year as last two digits (00–99)
		///   %m  Month as a zero-padded number (01–12)
		///   %b  Abbreviated month name (e.g., Feb)
		///   %B  Full month name (e.g., February)
		///   %d  Day of month, zero-padded (01–31)
		///   %e  Day of month, space-padded ( 1–31)
		///
		/// Time components:
		///   %H  Hour in 24-hour format (00–23)
		///   %I  Hour in 12-hour format (01–12)
		///   %M  Minute (00–59)
		///   %S  Seconds (00–59). Includes fractional seconds (milliseconds)   (e.g., 12.345).
		///   %p  AM/PM designator
		///
		/// Composite specifiers:
		///   %F  Equivalent to %Y-%m-%d (ISO 8601 date)
		///   %T  Equivalent to %H:%M:%S (ISO 8601 time)
		///   %R  Equivalent to %H:%M
		///
		/// Time zone:
		///   %z  UTC offset (e.g., +0000)
		///   %Z  Time zone abbreviation (UTC in this class)
		///
		/// Literal characters can be included directly. Use %% to output a percent sign.
		///
		/// Example:
		///   dt.toString("%Y-%m-%d %H:%M:%S");
		///   dt.toString("%F %T");
		///   dt.toString("%Y/%m/%d %H:%M");
		///
		/// @param format A C++20 chrono format string.
		/// @return A formatted string representing the UTC DateTime.
		/// @throws std::invalid_argument If the format string is invalid.
		std::string toString(const std::string& format) const;

		/// @brief Converts the DateTime to a Unix timestamp (number of seconds since January 1, 1970, UTC).
		/// @return The Unix timestamp representing the DateTime.
		long long toUnixTimestamp() const;

	  private:
		using TimePoint = std::chrono::sys_time<std::chrono::milliseconds>;
		TimePoint m_timePoint;

	  private:
		const TimePoint& timePoint() const noexcept { return m_timePoint; }
		friend struct std::formatter<DateTime>;
	};

} // namespace onion

/// @brief Provides a custom formatter for `onion::DateTime` to enable formatting with `std::format` and `std::vformat`.
template <> struct std::formatter<onion::DateTime>
{
	std::string chronoFormat = "%d-%m-%Y %H:%M:%S";

	constexpr auto parse(std::format_parse_context& ctx)
	{
		auto it = ctx.begin();
		auto end = ctx.end();

		if (it != end && *it != '}')
		{
			auto start = it;
			while (it != end && *it != '}')
				++it;

			chronoFormat = std::string(start, it);
		}

		return it;
	}

	template <typename FormatContext> auto format(const onion::DateTime& dt, FormatContext& ctx) const
	{
		return std::vformat_to(
			ctx.out(), "{:" + chronoFormat + "}", std::make_format_args(dt.timePoint()) // requires friend access
		);
	}
};
