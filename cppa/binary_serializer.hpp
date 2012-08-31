/******************************************************************************\
 *           ___        __                                                    *
 *          /\_ \    __/\ \                                                   *
 *          \//\ \  /\_\ \ \____    ___   _____   _____      __               *
 *            \ \ \ \/\ \ \ '__`\  /'___\/\ '__`\/\ '__`\  /'__`\             *
 *             \_\ \_\ \ \ \ \L\ \/\ \__/\ \ \L\ \ \ \L\ \/\ \L\.\_           *
 *             /\____\\ \_\ \_,__/\ \____\\ \ ,__/\ \ ,__/\ \__/.\_\          *
 *             \/____/ \/_/\/___/  \/____/ \ \ \/  \ \ \/  \/__/\/_/          *
 *                                          \ \_\   \ \_\                     *
 *                                           \/_/    \/_/                     *
 *                                                                            *
 * Copyright (C) 2011, 2012                                                   *
 * Dominik Charousset <dominik.charousset@haw-hamburg.de>                     *
 *                                                                            *
 * This file is part of libcppa.                                              *
 * libcppa is free software: you can redistribute it and/or modify it under   *
 * the terms of the GNU Lesser General Public License as published by the     *
 * Free Software Foundation, either version 3 of the License                  *
 * or (at your option) any later version.                                     *
 *                                                                            *
 * libcppa is distributed in the hope that it will be useful,                 *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                       *
 * See the GNU Lesser General Public License for more details.                *
 *                                                                            *
 * You should have received a copy of the GNU Lesser General Public License   *
 * along with libcppa. If not, see <http://www.gnu.org/licenses/>.            *
\******************************************************************************/


#ifndef CPPA_BINARY_SERIALIZER_HPP
#define CPPA_BINARY_SERIALIZER_HPP

#include <utility>

#include "cppa/serializer.hpp"
#include "cppa/util/buffer.hpp"

namespace cppa {

namespace detail { class binary_writer; }

/**
 * @brief Implements the serializer interface with
 *        a binary serialization protocol.
 */
class binary_serializer : public serializer {

 public:

    /**
     * @brief Creates a binary serializer writing to @p write_buffer.
     * @warning @p write_buffer must be guaranteed to outlive @p this
     */
    binary_serializer(util::buffer* write_buffer);

    void begin_object(const std::string& tname);

    void end_object();

    void begin_sequence(size_t list_size);

    void end_sequence();

    void write_value(const primitive_variant& value);

    void write_tuple(size_t size, const primitive_variant* values);

    void write_raw(size_t num_bytes, const void* data);

 private:

    util::buffer* m_sink;

};

} // namespace cppa

#endif // CPPA_BINARY_SERIALIZER_HPP
