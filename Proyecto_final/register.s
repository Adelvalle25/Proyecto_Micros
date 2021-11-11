      AREA |.text|, CODE, READONLY, ALIGN=2
        THUMB
        REQUIRE8
        PRESERVE8

		EXPORT RD_display
			
			
RD_display
loop
	ldrb r2, [r0] 
	adds r0, #1 
	strb r2, [r1] 
	adds r1, #1
	cmp r2, #0 
	bne loop 
	