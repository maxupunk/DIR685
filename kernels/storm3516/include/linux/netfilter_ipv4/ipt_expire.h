/* This module matches until it expires, at which point the entire
 * rule is deleted
 *
 * This module is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This module is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this module; if not, write to:
 *      The Free Software Foundation, Inc.
 *      59 Temple Place, Suite 330
 *      Boston, MA  02111-1307  USA
 *
 * Copyright © 2005 Bryan Cardillo <dillo@seas.upenn.edu>
 */

#ifndef __IPT_EXPIRE_H
#define __IPT_EXPIRE_H

#include <linux/types.h>

struct ipt_exp_info {
	time_t expiration;
};

#endif
