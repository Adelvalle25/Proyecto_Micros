      AREA |.text|, CODE, READONLY, ALIGN=2
        THUMB
        REQUIRE8
        PRESERVE8

		EXPORT RD_display
			
			
RD_display
	ldrb r2, [R0]
	strb R0, [r1]
	bx lr



