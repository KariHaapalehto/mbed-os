/*
 * Copyright (c) 2018-2019, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*********** WARNING: This is an auto-generated file. Do not edit! ***********/

#ifndef __TFM_SERVICE_LIST_INC__
#define __TFM_SERVICE_LIST_INC__

{% for partition in partitions %}
#ifdef TFM_PSA_API
/******** {{partition.name|upper}} ********/
{% for rot_srv in partition.rot_services %}
{"{{rot_srv.name|upper}}", {{partition.name|upper}}_ID, {{rot_srv.signal|upper}}, {{rot_srv.id}}, {% if rot_srv.nspe_callable %}true{% else %}false{% endif %}, {{rot_srv.minor_version}}, TFM_VERSION_POLICY_{{rot_srv.minor_policy|upper}}},
{% endfor %}
#endif /* TFM_PSA_API */

{% endfor %}
#endif /* __TFM_SERVICE_LIST_INC__ */
