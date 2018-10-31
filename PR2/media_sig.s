.section .data
#ifndef TEST
#define TEST 8
#endif
	.macro linea
	#if TEST==1
		.int 1, 2, 1, 2
	#elif TEST==2
		.int -1, -2, -1, -2
	#elif TEST==3
		.int 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff
	#elif TEST==4
		.int 0x80000000, 0x80000000, 0x80000000, 0x80000000
	#elif TEST==5
		.int 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff		
	#elif TEST==6
		.int 2000000000, 2000000000, 2000000000, 2000000000
	#elif TEST==7
		.int -2000000000, -2000000000, -2000000000, -2000000000
	#else
		.error "Definir TEST entre 1..7"
	#endif
		.endm

lista: .irpc i,1234
			linea
		.endr

longlista:	.int   (.-lista)/4
resultado:	.int   0,0
division:	.int   0,0
  formato: 	.string	"long signed:\t%ld\nmedia truncada:\t%d\nresto:\t\t%d\n"

# opción: 1) no usar printf, 2)3) usar printf/fmt/exit, 4) usar tb main
# 1) as  suma.s -o suma.o
#    ld  suma.o -o suma					1232 B
# 2) as  suma.s -o suma.o				6520 B
#    ld  suma.o -o suma -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2
# 3) gcc suma.s -o suma -no-pie –nostartfiles		6544 B
# 4) gcc suma.s -o suma	-no-pie				8664 B

.section .text
_start: .global _start
# main: .global  main

	call trabajar	# subrutina de usuario
	call imprim_C	# printf()  de libC
#	call acabar_L	# exit()   del kernel Linux
	call acabar_C	# exit()    de libC
	ret

trabajar:
	mov     $lista, %rbx
	mov  longlista, %ecx
	call suma		# == suma(&lista, longlista);
	mov  %esi, resultado
	mov  %ebp, resultado+4
	mov  %eax, division
	mov  %edx, division+4
	ret

suma:
	mov  $0, %esi  #contador bucle
	mov  $0, %eax  #acumulador de suma
	mov  $0, %edx  #acumulador acarreos
bucle:
	mov  (%rbx,%rsi,4), %ebp
	or	 %ebp, %ebp
	jns nosigno
	add  (%rbx,%rsi,4), %eax
	adc $0xffffffff, %edx
	jmp continuarbucle
nosigno:
	add  (%rbx,%rsi,4), %eax
	adc  $0, %edx
continuarbucle:
	inc   %rsi
	cmp   %rsi,%rcx
	jne    bucle

	mov %eax, %esi	#libero eax y edx para la division
	mov %edx, %ebp
	xor %edx, %edx	#si edx no era 0, damage floating point exception
	idiv %rcx		#divido entre el tamaño de lista
	ret



imprim_C:			# requiere libC
	mov   $formato, %rdi
	mov   resultado, %rsi
	mov	  division, %edx
	mov   division+4,%ecx
	mov   division, %r8d
	mov   $0,%eax	# varargin sin xmm
	call  printf		# == printf(formato, res, res);
	ret

#acabar_L:
#	mov        $60, %rax
#	mov  resultado, %edi
#	syscall			# == _exit(resultado)
#	ret

acabar_C:			# requiere libC
	mov  resultado, %edi
	call _exit		# ==  exit(resultado)
	ret
