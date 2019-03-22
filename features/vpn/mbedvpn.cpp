/*
 * Copyright (c) 2019 ARM Limited. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbedvpn.h"
#include "mbedvpn_certificate.h"
#include "EMACInterface.h"
#include "EMAC.h"

#define TRACE_GROUP "VPN"
#include "mbed-trace/mbed_trace.h"

/*
mbedvpn::mbedvpn(const char *host, uint16_t port) :
		_buffer(new char[256]),_host(host), _port(port)
{
    _net = NetworkInterface::get_default_instance();
}*/

mbedvpn::mbedvpn()
{
    _net = NetworkInterface::get_default_instance();
}

mbedvpn::~mbedvpn()
{
    // Close the socket to return its memory
    _socket->close();
    delete _socket;

    // Bring down the network interface
    _net->disconnect();
}


mbedvpn &mbedvpn::get_instance() {
    static mbedvpn vpn;
    return vpn;
}


void mbedvpn::start(void)
{
	if (_backhaul_driver_status_cb) {
		_net->attach(_backhaul_driver_status_cb);
	}

    _net->connect();

    printf("mbedvpn start\n");
    _socket = new TLSSocket;

    nsapi_size_or_error_t result = _socket->set_root_ca_cert(certificate);
    if (result != 0) {
        printf("Error: socket->set_root_ca_cert() returned %d\n", result);
    }

	result = _socket->open(_net);
    if (result != 0) {
        printf("Error! socket->open() returned: %d\n", result);
    }

	result = _socket->connect(MBED_CONF_APP_VPN_SERVER, MBED_CONF_APP_VPN_SERVER_PORT);
    if (result != 0) {
        printf("Error! socket->connect() returned: %d\n", result);
    }

}

void mbedvpn::stop(void)
{
	_socket->close();
	delete _socket;
}

TLSSocket *mbedvpn::get_socket(void)
{
	return _socket;
}

void mbedvpn::set_link_status_cb(void (*backhaul_ws_driver_status_cb)(nsapi_event_t status, intptr_t param))
{
	_backhaul_driver_status_cb = backhaul_ws_driver_status_cb;
}


extern "C"
{
nsapi_error_t tun_sending(uint8_t *ptr, uint16_t len)
{
    mbedvpn &vpn = mbedvpn::get_instance();
    nsapi_size_or_error_t result = vpn.get_socket()->send(ptr, len);
    if (result != len) {
        printf("Error! socket->send() returned: %d\n", result);
    }
    return result;
}

int16_t tun_receiving(uint8_t *ptr, uint16_t len)
{
/*
	char *buffer = new char[256];
	nsapi_size_or_error_t result;
	mbedvpn &vpn = mbedvpn::get_instance();
    while ((result = vpn.get_socket()->recv(buffer, 255)) > 0) {
        buffer[result] = 0;
        printf("%s", buffer);
    }*/
	mbedvpn &vpn = mbedvpn::get_instance();
    return vpn.get_socket()->recv(ptr, len);

}
} // extern "C"

