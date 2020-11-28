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

#ifndef FD_HANDLER_H_
#define FD_HANDLER_H_

#include <iostream>
#include <functional>
#include <memory>

class fd_handler
{
public:
	enum type {SOCKET, FILE};
	/**
	 * @brief Construct a new fd handler object
	 *
	 * @param fd: file descriptor
	 * @param tp: type of file descriptor
	 */
	fd_handler (int fd, type tp = FILE);
	/**
	 * @brief Destroy the fd handler::fd handler object
	 */
	~fd_handler ();
	/**
	 * @brief Compare two objects
	 *
	 * @param handler: reference to another object
	 * @return true: both elements are equals
	 * @return false: elements are not equals
	 */
	bool operator== (const fd_handler &handler) const;
	/**
	 * @brief Get file descriptor of object
	 *
	 * @return int: file descriptor
	 */
	int get_fd () const;
	/**
	 * @brief: Set a callback function to handler
	 *
	 * @param cb: callback
	 */
	void set_callback (std::function<void (std::weak_ptr<fd_handler>)> cb);
	std::function<void (std::weak_ptr<fd_handler>)> callback;
protected:
	int fd;
	type tp;
};

namespace std {
	template <>
	struct hash<fd_handler>
	{
		std::size_t operator() (const fd_handler &k) const
		{
			return std::hash<int>()(k.get_fd ());
		}
	};
}

#endif /* FD_HANDLER_H_ */
