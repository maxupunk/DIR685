#include <linux/linkage.h>
#include <asm/assembler.h>
#include <asm/arch/spec.h>
#include <asm/arch/intc.h>
#include "tve-config.h"
#include "tve200-fiq.h"

	.global	end_fiq_handler
	.global	end_fiq_handler_E

#ifdef CONFIG_CT656_VBI
	.macro ct656_put_vbi_asm, base, line, pdata
		str  \line, [\base, #0x14]
		ldr  \line, [\pdata]
		str  \line, [\base, #0x18]
		ldr  \line, [\pdata, #4]
		str  \line, [\base, #0x1C]
	.endm
#endif

	.text	
		
ENTRY(fiq_handler)
	ldr   r8, [sp, #ADDR_OFFSET(TVE_CTRL_BASE)]
	ldr   ip, [r8, #0x14]	@ //INTSts
CheckVstatus:		
	tst   ip, #0x40
	beq   end
	ldr   r10, [r8, #0x18]  @ //Ctrl1
	tst   r10, #0x30
	bne   Active_Image
	orr   r10, r10, #0x20
	str   r10, [r8, #0x18]
	ldr   r9, [sp, #ADDR_OFFSET(MACH_DATA_BASE)]	
	ldr   r10, [r9]		@ //mach_data->ctrl1
	tst   r10, #0x30
	bne   end
	b     Process_Frame
Active_Image:
	bic   r10, r10, #0x30
	str   r10, [r8, #0x18]
	ldr   r9, [sp, #ADDR_OFFSET(MACH_DATA_BASE)]	
	ldr   r10, [r9]		@ //mach_data->ctrl1
	tst   r10, #0x30
	beq   end
Process_Frame:
	ldr   r9, [sp, #ADDR_OFFSET(FFB_FBI_BASE)]
	ldr   r10, [r9, #804]
	cmp   r10, #0
	ldr   fp, [sp, #ADDR_OFFSET(FFB_DO_UPDATING)]
	ldr   fp, [fp]
	bne   Update_Base
	add   fp, fp, #1
	and   fp, fp, #1
	ldr   r9, [sp, #ADDR_OFFSET(FFB_MISS)]
	mov   r10, #0
	str   r10, [r9]
	b     end_str_update
Update_Base:
	cmp   fp, #0
	moveq fp, #1
	beq   end_str_update
	ldr   fp, [sp, #ADDR_OFFSET(FFB_OLD_FB)]
	ldr   fp, [fp]
	cmp   fp, r10
	ldreq r10, [sp, #ADDR_OFFSET(FFB_MISS)]
	ldreq fp, [r10]
	addeq fp, fp, #1
	streq fp, [r10]
	beq   end_update0
	ldr   fp, [sp, #ADDR_OFFSET(FFB_OLD_FB)]
	str   r10, [fp]
	add   r10, r9, r10, lsl #2
	ldr   fp, [r10, #764]
	str   fp, [r8]
	ldr   r9, [sp, #ADDR_OFFSET(MACH_DATA_BASE)]
	ldr   r10, [r9, #12]
	add   r10, fp, r10
	str   r10, [r8, #4]
	ldr   r10, [r9, #16]
	add   r10, fp, r10
	str   r10, [r8, #8]
	
end_update0:
	mov   fp, #0
	
end_str_update:
	ldr   r9, [sp, #ADDR_OFFSET(FFB_DO_UPDATING)]
	str   fp, [r9]	
#ifdef CONFIG_CT656_VBI
	cmp   fp, #1
	ldr   fp, [sp, #ADDR_OFFSET(G_VBI_LINE)]
	ldr   fp, [fp]
	addeq fp, fp, #1
	ldr   r10, [sp, #ADDR_OFFSET(ACT_VBI_INFO)]
	ldr   r9, [sp, #ADDR_OFFSET(FFB_OLD_FB)]
	ldr   r9, [r9]
	add   r10, r10, r9, lsl #4	
	addeq r10, r10, #8
	ldr   r9, [sp, #ADDR_OFFSET(CT656_CTRL_BASE)]
	ct656_put_vbi_asm r9, fp, r10
#endif

end:
	str ip, [r8, #0x10]
	ldr r10,[sp, #ADDR_OFFSET(INT_CTRL_BASE)]
	ldr ip, [sp, #ADDR_OFFSET(TVE_FIQ_NUM)]
	mov fp, #1
	mov fp, fp, lsl ip
	str fp, [r10, #FIQ_CLEAR_REG]
	subs	pc, lr, #4
	.ltorg
end_fiq_handler:


ENTRY(fiq_handler_E)
	ldr   r8, [sp, #ADDR_OFFSET(TVE_CTRL_BASE)]
	ldr   ip, [r8, #0x14]	@ //INTSts
CheckVstatus_E:		
	tst   ip, #0x40
	beq   end_E
Process_Frame_E:
	ldr   r9, [sp, #ADDR_OFFSET(FFB_FBI_BASE)]
	ldr   r10, [r9, #804]
	cmp   r10, #0
	ldr   fp, [sp, #ADDR_OFFSET(FFB_DO_UPDATING)]
	ldr   fp, [fp]
	bne   Update_Base_E
	add   fp, fp, #1
	and   fp, fp, #1
	ldr   r9, [sp, #ADDR_OFFSET(FFB_MISS)]
	mov   r10, #0
	str   r10, [r9]
	b     end_str_update_E
Update_Base_E:
	cmp   fp, #0
	moveq fp, #1
	beq   end_str_update_E
	ldr   fp, [sp, #ADDR_OFFSET(FFB_OLD_FB)]
	ldr   fp, [fp]
	cmp   fp, r10
	ldreq r10, [sp, #ADDR_OFFSET(FFB_MISS)]
	ldreq fp, [r10]
	addeq fp, fp, #1
	streq fp, [r10]
	beq   end_update0_E
	ldr   fp, [sp, #ADDR_OFFSET(FFB_OLD_FB)]
	str   r10, [fp]
	add   r10, r9, r10, lsl #2
	ldr   fp, [r10, #764]
	str   fp, [r8]
	ldr   r9, [sp, #ADDR_OFFSET(MACH_DATA_BASE)]
	ldr   r10, [r9, #12]
	add   r10, fp, r10
	str   r10, [r8, #4]
	ldr   r10, [r9, #16]
	add   r10, fp, r10
	str   r10, [r8, #8]
	
end_update0_E:
	mov   fp, #0
	
end_str_update_E:
	ldr   r9, [sp, #ADDR_OFFSET(FFB_DO_UPDATING)]
	str   fp, [r9]	
#ifdef CONFIG_CT656_VBI
	cmp   fp, #1
	ldr   fp, [sp, #ADDR_OFFSET(G_VBI_LINE)]
	ldr   fp, [fp]
	addeq fp, fp, #1
	ldr   r10, [sp, #ADDR_OFFSET(ACT_VBI_INFO)]
	ldr   r9, [sp, #ADDR_OFFSET(FFB_OLD_FB)]
	ldr   r9, [r9]
	add   r10, r10, r9, lsl #4	
	addeq r10, r10, #8
	ldr   r9, [sp, #ADDR_OFFSET(CT656_CTRL_BASE)]
	ct656_put_vbi_asm r9, fp, r10
#endif

end_E:
	str ip, [r8, #0x10]
	ldr r10,[sp, #ADDR_OFFSET(INT_CTRL_BASE)]
	ldr ip, [sp, #ADDR_OFFSET(TVE_FIQ_NUM)]
	mov fp, #1
	mov fp, fp, lsl ip
	str fp, [r10, #FIQ_CLEAR_REG]
	subs	pc, lr, #4
	.ltorg
end_fiq_handler_E:
