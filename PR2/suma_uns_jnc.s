.section .data
#ifndef TEST
#define TEST 6
#endif
	.macro linea
	#if TEST==1
		.int 1, 1, 1, 1
	#elif TEST==2
		.int 0x04000000, 0x04000000, 0x04000000, 0x04000000
	#elif TEST==3
		.int 0x08000000, 0x08000000, 0x08000000, 0x08000000
	#elif TEST==4
		.int 0x10000000, 0x10000000, 0x10000000, 0x10000000
	#elif TEST==5
		.int 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff
	#else
		.error "Definir TEST entre 1..5"
	#endif
		.endm

lista: .irpc i,1234
			linea
		.endr

longlista:	.int   (.-lista)/4
resultado:	.int   0,0
  formato: 	.string	"long unsigned:\t%lu\nhexadecimal:\t0x%016lx\nhex32:\t\t0x%08x %08x\n"

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
	mov  %eax, resultado
	mov  %edx, resultado+4
	ret

suma:
	mov  $0, %esi  #contador bucle
	mov  $0, %eax  #acumulador de suma
	mov  $0, %edx  #acumulador acarreos
bucle:
	add  (%rbx,%rsi,4), %eax
	jnc continuarbucle 	#condicional de acarreo
	inc %edx			#incrementamos registro de acarreo
continuarbucle:
	inc   %rsi
	cmp   %rsi,%rcx
	jne    bucle
	ret



imprim_C:			# requiere libC
	mov   $formato, %rdi
	mov   resultado, %rsi
	mov	  resultado, %rdx
	mov   resultado+4,%ecx
	mov   resultado, %r8d
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
