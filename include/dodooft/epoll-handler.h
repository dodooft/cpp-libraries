/**
 * Copyright (C) 2020, Javier E. Soto
 *
 * All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice,
 *       this list of conditions and the following disclaimer in the documentation
 *       and/or other materials provided with the distribution.
 *     * Neither the name of {{ project }} nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef EPOLL_HANDLER_H_
#define EPOLL_HANDLER_H_

#include <iostream>
#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/epoll.h>
#include "fd-handler.h"

class epoll_handler
{
private:
	std::unordered_map <int, std::weak_ptr<fd_handler> > data;
	int efd;
	int max_events;
	int event_check;
	std::vector<std::shared_ptr<struct epoll_event> > event_list;
	struct epoll_event * events;

public:
	/**
	 * @brief Construct a new epoll handler object
	 *
	 * @param max_events: amount of events that can be handle the epoll
	 * @param event_check: timeout of epoll_wait
	 */
	epoll_handler (int max_events, int event_check = -1);
	/**
	 * @brief Destroy the epoll handler object
	 */
	~epoll_handler ();
	/**
	 * @brief Register a file descriptor on epoll
	 *
	 * @param fd: smart pointer to a file descriptor handler
	 * @param cb: callback
	 */
	std::shared_ptr<epoll_event> register_event (std::weak_ptr<fd_handler> fd,
	    std::function<void (std::weak_ptr<fd_handler>, uint32_t)> cb);
	/**
	 * @brief Blocking epoll loop
	 */
	void listen_loop ();
};

#endif /* EPOLL_HANDLER_H_ */
