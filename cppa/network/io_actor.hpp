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
 * Copyright (C) 2011-2013                                                    *
 * Dominik Charousset <dominik.charousset@haw-hamburg.de>                     *
 *                                                                            *
 * This file is part of libcppa.                                              *
 * libcppa is free software: you can redistribute it and/or modify it under   *
 * the terms of the GNU Lesser General Public License as published by the     *
 * Free Software Foundation; either version 2.1 of the License,               *
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


#ifndef IO_ACTOR_HPP
#define IO_ACTOR_HPP

#include <functional>

#include "cppa/stackless.hpp"
#include "cppa/threadless.hpp"
#include "cppa/local_actor.hpp"
#include "cppa/mailbox_element.hpp"

#include "cppa/network/io_service.hpp"

#include "cppa/detail/fwd.hpp"

namespace cppa { namespace network {

class io_actor_backend;
class io_actor_continuation;

class io_actor : public extend<local_actor>::with<threadless, stackless> {

    typedef combined_type super;

    friend class io_actor_backend;
    friend class io_actor_continuation;

 public:

    void enqueue(const message_header& hdr, any_tuple msg);

    bool initialized() const;

    void quit(std::uint32_t reason);

    static intrusive_ptr<io_actor> from(std::function<void (io_service*)> fun);

    template<typename F, typename T0, typename... Ts>
    static intrusive_ptr<io_actor> from(F fun, T0&& arg0, Ts&&... args) {
        return from(std::bind(std::move(fun),
                              std::placeholders::_1,
                              detail::fwd<T0>(arg0),
                              detail::fwd<Ts>(args)...));
    }

 protected:

    io_service& io_handle();

 private:

    void invoke_message(mailbox_element* elem);

    void invoke_message(any_tuple msg);

    intrusive_ptr<io_actor_backend> m_parent;

};

typedef intrusive_ptr<io_actor> io_actor_ptr;

} } // namespace cppa::network

#endif // IO_ACTOR_HPP