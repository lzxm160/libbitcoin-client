/*
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-client.
 *
 * libbitcoin-client is free software: you can redistribute it and/or
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
#include "connection.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <bitcoin/client.hpp>

using namespace bc;
using namespace bc::chain;
using namespace bc::client;
using namespace bc::protocol;
using namespace bc::wallet;

/// Unknown message callback handler.
static void on_unknown(const std::string& command)
{
    std::cout << "unknown message:" << command << std::endl;
}

/// Update message callback handler.
static void on_update(const payment_address& address, size_t,
    const hash_digest&, const transaction&)
{
    std::cout << "update:" << address.encoded() << std::endl;
}

connection::connection(zmq::socket& socket, uint32_t timeout_ms)
  : stream(socket),
    proxy(stream, on_unknown, timeout_ms, 0)
{
    proxy.set_on_update(on_update);
}
