	.arch msp430g2553
	.p2align 1,0
	.text

	
	.global led_init
	.global toggle_green
	.global toggle_red
	.equ LEDS, 0x41 	; 0x41 represents bit 0 and bit 6 (0x01 | 0x40)
	.equ LED_GREEN, 0x40 	; 0x40 represents bit 6
	.equ LED_RED, 0x01   	; 0x01 represents bit 0
	.extern P1OUT
	.extern P1DIR

	;;  Assuming LEDS, LED_GREEN, and LED_RED are defined appropriately

led_init:

	bis.b #LEDS, &P1DIR	; P1DIR |= LEDS
	bic.b #LED_GREEN, &P1OUT ; P1OUT &= ~LED_GREEN
	bic.b #LED_RED, &P1OUT ; P1OUT &= ~LED_RED
	pop r0


toggle_green:

	xor.b #LED_GREEN, &P1OUT ; P1OUT ^= LED_GREEN
	pop r0

toggle_red:

	xor.b #LED_RED, &P1OUT ; P1OUT ^= LED_RED
	pop r0

	

	
