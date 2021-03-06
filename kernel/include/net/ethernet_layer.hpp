//=======================================================================
// Copyright Baptiste Wicht 2013-2016.
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://www.opensource.org/licenses/MIT)
//=======================================================================

#ifndef NET_ETHERNET_LAYER_H
#define NET_ETHERNET_LAYER_H

#include <types.hpp>
#include <expected.hpp>

#include "net/network.hpp"
#include "net/ethernet_packet.hpp"

namespace network {

namespace ethernet {

static_assert(sizeof(address) == 6, "The size of a MAC address is 6 bytes");
static_assert(sizeof(header) == 14, "The size of the Ethernet header is 14 bytes");

uint64_t mac6_to_mac64(const char* mac);
void mac64_to_mac6(uint64_t input, char* mac);

/*!
 * \brief Decode a network packet.
 *
 * This must only be called from the network interface.
 *
 * \param interface The interface on which the packet was received
 * \param packet The packet to decode
 */
void decode(network::interface_descriptor& interface, packet& packet);

/*!
 * \brief Prepare a packet for the kernel
 * \param interface The interface on which to prepare the packet for
 * \param descriptor The packet descriptor
 * \return the prepared packet or an error
 */
std::expected<packet> kernel_prepare_packet(network::interface_descriptor& interface, const packet_descriptor& descriptor);

/*!
 * \brief Prepare a packet for the user
 * \param buffer The buffer to write the packet to
 * \param interface The interface on which to prepare the packet for
 * \param descriptor The packet descriptor
 * \return the prepared packet or an error
 */
std::expected<packet> user_prepare_packet(char* buffer, network::interface_descriptor& interface, const packet_descriptor* descriptor);

/*!
 * \brief Finalize a prepared packet
 * \param interface The interface on which to finalize the packet
 * \param p The packet to finalize
 * \return nothing or an error
 */
std::expected<void> finalize_packet(network::interface_descriptor& interface, packet& p);

} // end of ethernet namespace

} // end of network namespace

#endif
