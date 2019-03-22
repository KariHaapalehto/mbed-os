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

#ifndef MBEDVPN_H
#define MBEDVPN_H

#include "TLSSocket.h"
#include "UDPSocket.h"
#include "nsapi_types.h"

class mbedvpn {
public:
	//mbedvpn(const char *host, uint16_t port);
	mbedvpn();
	~mbedvpn();

	static mbedvpn &get_instance();
	void start(void);
	void stop(void);
	void set_link_status_cb(void (*backhaul_ws_driver_status_cb)(nsapi_event_t status, intptr_t param));
	TLSSocket *get_socket(void);

private:
	TLSSocket *_socket;
	NetworkInterface *_net;
	void (*_backhaul_driver_status_cb)(nsapi_event_t status, intptr_t param);
};


#ifdef __cplusplus
extern "C"
{
#endif

nsapi_error_t tun_sending(uint8_t *ptr, uint16_t len);
int16_t tun_receiving(uint8_t *ptr, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif
