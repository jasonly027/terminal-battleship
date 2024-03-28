#ifndef BATTLESHIP_GENERIC_NET_H
#define BATTLESHIP_GENERIC_NET_H
#pragma once

#ifdef _WIN32
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00
#endif
#endif

#ifndef ASIO_STANDALONE
#define ASIO_STANDALONE
#endif

#include "impl/message.h" // IWYU pragma: export
#include "impl/connection.h" // IWYU pragma: export
#include "impl/tsqueue.h" // IWYU pragma: export
#include "impl/client_interface.h" // IWYU pragma: export
#include "impl/server_interface.h" // IWYU pragma: export

#endif