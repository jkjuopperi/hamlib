/*
 *  Hamlib JRC backend - NRD-545 DSP description
 *  Copyright (c) 2001 by Stephane Fillod
 *
 *		$Id: nrd545.c,v 1.1 2001-12-17 22:40:34 fillods Exp $
 *
 *   This library is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Library General Public License for more details.
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <hamlib/rig.h>
#include "jrc.h"


#define NRD545_MODES (RIG_MODE_AM|RIG_MODE_CW|RIG_MODE_SSB|RIG_MODE_FM|RIG_MODE_RTTY)

#define NRD545_FUNC (RIG_FUNC_FAGC|RIG_FUNC_NB|RIG_FUNC_LOCK|RIG_FUNC_ABM|RIG_FUNC_BC|RIG_FUNC_NR)

#define NRD545_LEVEL (RIG_LEVEL_SQLSTAT|RIG_LEVEL_STRENGTH|RIG_LEVEL_RF|RIG_LEVEL_AF|RIG_LEVEL_AGC|RIG_LEVEL_IF|RIG_LEVEL_NR|RIG_LEVEL_NOTCHF|RIG_LEVEL_SQL)

#define NRD545_PARM (RIG_PARM_TIME|RIG_PARM_BACKLIGHT|RIG_PARM_BEEP)

#define NRD545_VFO (RIG_VFO_A)

/*
 * FIXME: measure S-meter levels
 */
#define NRD545_STR_CAL { 2, { \
		{   0, -60 }, \
		{ 255, 60 }, \
	} }

static const struct jrc_priv_caps nrd545_priv_caps = {
		NRD545_STR_CAL
};

/*
 * NRD-545 rig capabilities.
 *
 */
const struct rig_caps nrd545_caps = {
rig_model: RIG_MODEL_NRD545,
model_name:"NRD-545 DSP",
mfg_name: "JRC",
version: "0.1",
copyright: "LGPL",
status: RIG_STATUS_UNTESTED,
rig_type: RIG_TYPE_RECEIVER,
ptt_type: RIG_PTT_NONE,
dcd_type: RIG_DCD_NONE,
port_type: RIG_PORT_SERIAL,
serial_rate_min: 4800,
serial_rate_max: 4800,
serial_data_bits: 8,
serial_stop_bits: 1,
serial_parity: RIG_PARITY_NONE,
serial_handshake: RIG_HANDSHAKE_NONE,
write_delay: 0,
post_write_delay: 0,
timeout: 200,
retry: 3,

has_get_func: NRD545_FUNC,
has_set_func: NRD545_FUNC,
has_get_level: NRD545_LEVEL,
has_set_level: RIG_LEVEL_SET(NRD545_LEVEL),
has_get_parm: NRD545_PARM,
has_set_parm: RIG_PARM_SET(NRD545_PARM),
level_gran: {},                 /* FIXME: granularity */
parm_gran: {},
ctcss_list: NULL,
dcs_list: NULL,
preamp:  { RIG_DBLST_END },
attenuator:  { 20, RIG_DBLST_END },	/* To be confirmed */
max_rit: Hz(0),
max_xit: Hz(0),
max_ifshift: kHz(2.3),
targetable_vfo: 0,
transceive: RIG_TRN_RIG,
bank_qty:  0,
chan_desc_sz: 0,

chan_list: {
			{ 0, 999, RIG_MTYPE_MEM, 0 },
			RIG_CHAN_END,
		},

rx_range_list1: { RIG_FRNG_END, },    /* FIXME: enter region 1 setting */
tx_range_list1: { RIG_FRNG_END, },
rx_range_list2: {
	{kHz(100),MHz(30),NRD545_MODES,-1,-1,NRD545_VFO},
	RIG_FRNG_END,
  },
tx_range_list2: { RIG_FRNG_END, },

tuning_steps: {
	 {NRD545_MODES,1},
	 {NRD545_MODES,10},
	 {NRD545_MODES,100},
	 {NRD545_MODES,kHz(1)},
	 {NRD545_MODES,kHz(5)},
	 {NRD545_MODES,kHz(6.25)},
	 {NRD545_MODES,kHz(9)},
	 {NRD545_MODES,kHz(10)},
	 {NRD545_MODES,kHz(12.5)},
	 {NRD545_MODES,kHz(20)},
	 {NRD545_MODES,kHz(25)},
	 {NRD545_MODES,kHz(30)},
	 {NRD545_MODES,kHz(100)},
	 RIG_TS_END,
	},
        /* mode/filter list, remember: order matters! */
filters: {
		{RIG_MODE_AM|RIG_MODE_FM, kHz(10)},
		{NRD545_MODES, kHz(2.4)},
		{NRD545_MODES, kHz(1)},
		{NRD545_MODES, kHz(4.5)},
		RIG_FLT_END,
	},
priv: (void*)&nrd545_priv_caps,

rig_open: jrc_open,
rig_close: jrc_close,
set_freq: jrc_set_freq,
get_freq: jrc_get_freq,
set_mode: jrc_set_mode,
set_func: jrc_set_func,
get_func: jrc_get_func,
set_level: jrc_set_level,
get_level: jrc_get_level,
get_dcd: jrc_get_dcd,
set_trn: jrc_set_trn,
set_powerstat: jrc_set_powerstat,
reset: jrc_reset,
set_mem: jrc_set_mem,

};

/*
 * Function definitions below
 */
