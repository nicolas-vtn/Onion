#include "DateTime.hpp"

#include <chrono>
#include <format>
#include <stdexcept>
#include <string>

using namespace std::chrono;

namespace onion
{

	DateTime::DateTime() : m_timePoint(std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now()))
	{
	}

	DateTime::DateTime(int year, int month, int day, int hours, int minutes, int seconds, double milliseconds)
	{
		// ---- Validate ranges ----
		if (year < 1 || year > 9999)
			throw std::out_of_range("year out of range");

		if (month < 1 || month > 12)
			throw std::out_of_range("month out of range");

		if (hours < 0 || hours > 23)
			throw std::out_of_range("hour out of range");

		if (minutes < 0 || minutes > 59)
			throw std::out_of_range("minute out of range");

		if (seconds < 0 || seconds > 59)
			throw std::out_of_range("second out of range");

		if (milliseconds < 0.0 || milliseconds >= 1000.0)
			throw std::out_of_range("millisecond out of range");

		// ---- Construct calendar date ----
		year_month_day ymd{std::chrono::year{year},
						   std::chrono::month{static_cast<unsigned>(month)},
						   std::chrono::day{static_cast<unsigned>(day)}};

		if (!ymd.ok())
			throw std::invalid_argument("invalid calendar date");

		// ---- Convert to sys_days (UTC midnight) ----
		sys_days dayPoint{ymd};

		// ---- Convert milliseconds safely ----
		auto ms = std::chrono::milliseconds{static_cast<long long>(milliseconds)};

		// ---- Build final sys_time<milliseconds> ----
		m_timePoint = sys_time<std::chrono::milliseconds>{dayPoint} + std::chrono::hours{hours} +
			std::chrono::minutes{minutes} + std::chrono::seconds{seconds} + ms;
	}

	DateTime DateTime::UtcNow()
	{
		return DateTime();
	}

	// ---- Date components ----

	int DateTime::getYear() const
	{
		auto days = floor<std::chrono::days>(m_timePoint);
		year_month_day ymd{days};
		return int(ymd.year());
	}

	int DateTime::getMonth() const
	{
		auto days = floor<std::chrono::days>(m_timePoint);
		year_month_day ymd{days};
		return unsigned(ymd.month());
	}

	int DateTime::getDay() const
	{
		auto days = floor<std::chrono::days>(m_timePoint);
		year_month_day ymd{days};
		return unsigned(ymd.day());
	}

	// ---- Time components ----

	int DateTime::getHours() const
	{
		auto dayPoint = floor<days>(m_timePoint);
		hh_mm_ss<milliseconds> tod{m_timePoint - dayPoint};
		return int(tod.hours().count());
	}

	int DateTime::getMinutes() const
	{
		auto dayPoint = floor<days>(m_timePoint);
		hh_mm_ss<milliseconds> tod{m_timePoint - dayPoint};
		return int(tod.minutes().count());
	}

	int DateTime::getSeconds() const
	{
		auto dayPoint = floor<days>(m_timePoint);
		hh_mm_ss<milliseconds> tod{m_timePoint - dayPoint};
		return int(tod.seconds().count());
	}

	double DateTime::getMilliseconds() const
	{
		auto dayPoint = floor<days>(m_timePoint);
		hh_mm_ss<milliseconds> tod{m_timePoint - dayPoint};
		return static_cast<double>(tod.subseconds().count());
	}

	// ---- Comparison operators ----
	bool DateTime::operator==(const DateTime& other) const
	{
		return m_timePoint == other.m_timePoint;
	}

	bool DateTime::operator!=(const DateTime& other) const
	{
		return m_timePoint != other.m_timePoint;
	}

	bool DateTime::operator<(const DateTime& other) const
	{
		return m_timePoint < other.m_timePoint;
	}

	bool DateTime::operator<=(const DateTime& other) const
	{
		return m_timePoint <= other.m_timePoint;
	}

	bool DateTime::operator>(const DateTime& other) const
	{
		return m_timePoint > other.m_timePoint;
	}

	bool DateTime::operator>=(const DateTime& other) const
	{
		return m_timePoint >= other.m_timePoint;
	}

	// ---- String representation ----
	std::string DateTime::toString() const
	{
		auto secondsPart = floor<seconds>(m_timePoint);
		auto msPart = duration_cast<milliseconds>(m_timePoint - secondsPart).count();

		return std::format("{:%Y-%m-%dT%H:%M:%S}.{:03}Z", secondsPart, msPart);
	}

	std::string DateTime::toString(const std::string& format) const
	{
		try
		{
			return std::vformat("{:" + format + "}", std::make_format_args(m_timePoint));
		}
		catch (const std::format_error&)
		{
			throw std::invalid_argument("Invalid DateTime format string: " + format);
		}
	}

	// ---- Converts the DateTime to a Unix timestamp (number of seconds since January 1, 1970, UTC) ----
	long long DateTime::toUnixTimestamp() const
	{
		auto epoch = sys_time<seconds>{};
		auto durationSinceEpoch = m_timePoint - epoch;
		return duration_cast<seconds>(durationSinceEpoch).count();
	}

} // namespace onion
