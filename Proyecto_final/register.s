      AREA |.text|, CODE, READONLY, ALIGN=2
        THUMB
        REQUIRE8
        PRESERVE8

		EXPORT RD_display
		EXPORT RM
			
		extern resgister ;arreglo para display
		extern memo
;Register display 
RD_display	
	push{r0}
	ldr r0, =resgister
	str r1, [r0, #4]	
	str r2, [r0, #8]	
	str r3, [r0, #12]	
	str r4, [r0, #16]	
	str r5, [r0, #20]	
	str r6, [r0, #24]	
	str r7, [r0, #28]	
	str r8, [r0, #32]	
	str r9, [r0, #36]	
	str r10, [r0, #40]	
	str r11, [r0, #44]	
	str r12, [r0, #48]	
	str sp, [r0, #52]	
	str lr, [r0, #56]	
	pop{r0}           
	push{r5}
	ldr r5, =resgister 
	str r0, [r5]	
	pop{r5}
	bx lr

;register modify
RM
	push{lr}
	cmp r0, #0
	beq r_0
	cmp r0, #1
	beq r_1
	cmp r0, #2
	beq r_2
	cmp r0, #3
	beq r_3
	cmp r0, #4
	beq r_4
	cmp r0, #5
	beq r_5
	cmp r0, #6
	beq r_6
	cmp r0, #7
	beq r_7
	cmp r0, #8
	beq r_8
	cmp r0, #9
	beq r_9
	cmp r0, #10
	beq r_10
	cmp r0, #11
	beq r_11
	cmp r0, #12
	beq r_13
	cmp r0, #14
	beq r_14
	pop{pc}
r_0
	push{lr}
	movs r0, r1
	pop{pc}
r_1 
	push{lr}
	movs r1, r1
	pop{pc}
r_2
	push{lr}
	movs r2, r1
	pop{pc}
r_3
	push{lr}
	movs r3, r1
	pop{pc}
r_4
	push{lr}
	movs r4, r1
	pop{pc}
r_5
	push{lr}
	movs r5, r1
	pop{pc}
r_6
	push{lr}
	movs r6, r1
	pop{pc}
r_7
	push{lr}
	movs r7, r1
	pop{pc}
r_8
	push{lr}
	movs r8, r1
	pop{pc}
r_9
	push{lr}
	movs r9, r1
	pop{pc}
r_10
	push{lr}
	movs r10, r1
	pop{pc}
r_11
	push{lr}
	movs r11, r1
	pop{pc}
r_12
	push{lr}
	movs r12, r1
	pop{pc}
r_13
	push{lr}
;	movs r13, r1
	pop{pc}
r_14
	push{lr}
	movs r14, r1
	pop{pc}

;Memory Display
MD
	cmp r0, r1
	bgt end_loop
	ldrb r5, [r0]
	add r0, r0, #1
	push{r0}
	ldr r0, =memo 
	str r5, [r0]
	pop{r0}
	b MD
end_loop
	bx lr
	
	
;Memory Modify
MM_BYTE
	push{lr}
	strb r1, [r0]
	pop{pc}
	
MM_HALF
	push{lr}
	strh r1, [r0]
	pop{pc}
	
MM_WORD
	push{lr}
	str r1, [r0]
	pop{pc}


	nop
	END

	
	