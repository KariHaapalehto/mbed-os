
/** \addtogroup netsocket */
/** @{*/
/* VpnInterface
 * Copyright (c) 2019 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef VPN_INTERFACE_H
#define VPN_INTERFACE_H

#include "nsapi.h"
#include "EMACInterface.h"


/** Common interface
 */
class VpnInterface : public EMACInterface, public EthInterface {

public:
    /** Get the default VPN interface.
     *
     * This is provided as a weak method so applications can override.
     * Default behavior is to get the target's default interface, if
     * any.
     *
     * @return Pointer to interface.
     */
	VpnInterface(EMAC &emac = EMAC::get_default_instance(),
                      OnboardNetworkStack &stack = OnboardNetworkStack::get_default_lwip_instance()) : EMACInterface(emac, stack) { }

    static VpnInterface *get_default_instance();

#if !defined(DOXYGEN_ONLY)
protected:

    /** Get the target's default VPN interface.
     *
     * This is provided as a weak method so targets can override. The
     * default implementation will invoke LoWPANNDInterface or ThreadInterface
     * with the default NanostackRfPhy.
     *
     * @return pointer to interface, if any.
     */
    static VpnInterface *get_target_default_instance();
#endif //!defined(DOXYGEN_ONLY)

};


#endif

/** @}*/
