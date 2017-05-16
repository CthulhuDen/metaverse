/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 * Copyright (c) 2016-2017 metaverse core developers (see MVS-AUTHORS)
 *
 * This file is part of metaverse-explorer.
 *
 * metaverse-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <metaverse/explorer/commands/ek-public-to-ec.hpp>

#include <cstdint>
#include <iostream>
#include <metaverse/bitcoin.hpp>
#include <metaverse/explorer/define.hpp>


namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc::wallet;

console_result ek_public_to_ec::invoke(std::ostream& output,
    std::ostream& error)
{
#ifdef WITH_ICU
    const auto& passphrase = get_passphrase_argument();
    const auto& key = get_ek_public_key_argument();

    bool compressed;
    uint8_t version;
    ec_compressed point;
    if (!decrypt(point, version, compressed, key, passphrase))
    {
        error << BX_EK_PUBLIC_TO_EC_INVALID_PASSPHRASE << std::flush;
        return console_result::failure;
    }

    output << ec_public(point, compressed) << std::flush;
    return console_result::okay;
#else
    error << BX_EK_PUBLIC_TO_EC_REQUIRES_ICU << std::flush;
    return console_result::failure;
#endif
}

} //namespace commands 
} //namespace explorer 
} //namespace libbitcoin 