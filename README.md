# do-cpp

Do-cpp is a simple library to handle file descriptors in non-blocking fashion in c++.

## Fifo example


```cpp
#include "dodooft/epoll-handler.h"
#include "dodooft/fd-handler.h"

// ...

auto epoll = std::make_shared<epoll_handler> (20); // max number of events

int fifo = open ("/tmp/fifo", O_RDONLY);
auto fifo_h = std::make_shared<fd_handler> (fifo);

epoll->register_event (fifo_h, [&] (std::weak_ptr<fd_handler> fd)
{
	int data;
	auto fd_s = fd.lock ();

	ssize_t count = read (fd_s->get_fd (), &data, sizeof (int));
	if (0 == count || cout != sizeof (int)) return;

	// Process data
	// ...
});

epoll->listen_loop ();

```
