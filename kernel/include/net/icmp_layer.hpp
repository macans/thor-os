//=======================================================================
// Copyright Baptiste Wicht 2013-2016.
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://www.opensource.org/licenses/MIT)
//=======================================================================

#ifndef NET_ICMP_LAYER_H
#define NET_ICMP_LAYER_H

#include <types.hpp>
#include <expected.hpp>

#include "tlib/net_constants.hpp"

#include "net/network.hpp"
#include "net/ip_layer.hpp"

namespace network {

namespace icmp {

static_assert(sizeof(echo_request_header) == sizeof(header::rest), "Invalid size for echo request header");

/*!
 * \brief Decode a network packet.
 *
 * This must only be called from the ip layer.
 *
 * \param interface The interface on which the packet was received
 * \param packet The packet to decode
 */
void decode(network::interface_descriptor& interface, network::ethernet::packet& packet);

/*!
 * \brief Prepare a packet for the kernel
 * \param interface The interface on which to prepare the packet for
 * \param descriptor The packet descriptor
 * \return the prepared packet or an error
 */
std::expected<network::ethernet::packet> kernel_prepare_packet(network::interface_descriptor& interface, const packet_descriptor& descriptor);

/*!
 * \brief Prepare a packet for the user
 * \param buffer The buffer to write the packet to
 * \param interface The interface on which to prepare the packet for
 * \param descriptor The packet descriptor
 * \return the prepared packet or an error
 */
std::expected<network::ethernet::packet> user_prepare_packet(char* buffer, network::socket& sock, const packet_descriptor* descriptor);

/*!
 * \brief Finalize a prepared packet
 * \param interface The interface on which to finalize the packet
 * \param p The packet to finalize
 * \return nothing or an error
 */
std::expected<void> finalize_packet(network::interface_descriptor& interface, network::ethernet::packet& p);

} // end of icmp namespace

} // end of network namespace

#endif
