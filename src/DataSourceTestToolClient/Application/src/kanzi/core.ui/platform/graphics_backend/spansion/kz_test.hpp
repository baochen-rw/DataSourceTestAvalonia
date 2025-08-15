// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TEST_HPP
#define KZ_TEST_HPP

#include <stdio.h>

#include <mm_types.h>
#include <mm_defines.h>
#include <mml_gdc_driver_api.h>
#include <sm_util.h>
#include <ut_compatibility.h>
#include <pdl.h>
#include <timer/timer.h>
#include <display/display.h>
#include <ut_memman.h>
#include <ut_printf.h>
#include <pe_matrix.h>


#define KZ_TEST(ret, execute) if ((ret = execute) != MML_OK) kanzi::fail(ret);


namespace kanzi
{

void fail(MM_ERROR err);

void logHeap();

void logVram();

}



#endif
