/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2024 Maarten L. Hekkelman
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <date/date.h>
#include <mcfp.hpp>

#include <chrono>
#include <iostream>

// --------------------------------------------------------------------

static constexpr date::sys_days
iso_week_start(date::year y) noexcept
{
	using namespace date;
	return sys_days{ Thursday[1] / January / y } - (Thursday - Monday);
}

int week_nr(date::year_month_day ymd)
{
	using namespace date;

	auto y = ymd.year();
	auto first_day = date::day{ 1 } / January / y;
	auto first_thursday = Thursday[1] / January / y;

	auto d = sys_days{ first_thursday } - sys_days{ first_day };
	return d.count() == 4 ? 1 : 2;
}

int main(int argc, char *const argv[])
{
	// using namespace date;
	using namespace std::chrono_literals;

	auto &config = mcfp::config::instance();

	auto now = std::chrono::system_clock::now();
	auto ymd = date::year_month_day{ date::floor<date::days>(now) };

	config.init("Gebruik: givt-toekenning [option]\n\n",
		mcfp::make_option<int>("jaar", static_cast<int>(ymd.year()), "Het jaar voor de toekenning"),
		mcfp::make_option<int>("aantal-collectes", 3, "Het aantal collectes per weer"));

	config.parse(argc, argv);

	auto jaar = date::year{ config.get<int>("jaar") };
	int aantal_collectes = config.get<int>("aantal-collectes");

	auto zondag = date::year_month_day{ jaar / date::January / date::Sunday[1] };
	int weeknr = week_nr(zondag);

	std::cout << "Begindatum; Einddatum; Naam; CollecteId;  BELANGRIJK: Er moet een spatie voor de datum!\n";

	date::sys_days z{ zondag };

	do
	{
		for (int i = 0; i < aantal_collectes; ++i)
		{
			std::cout << date::format(" %Y-%m-%d %H:%M", z) << ';'
					<< date::format(" %Y-%m-%d %H:%M", z + date::weeks{ 1 } - 1min) << ';'
					<< "Collecte " << (i + 1) << " week " << weeknr << ';'
					<< (i + 1) << '\n';
		}

		z += date::weeks{ 1 };
		++weeknr;
	} while (date::year_month_day{ z }.year() == jaar);

	return 0;
}
