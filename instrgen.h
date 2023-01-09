#ifndef VMACHINE_INSTR_GEN
#	define VMACHINE_INSTR_GEN

#include "vmachine.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline size_t vmachine_instr_gen(
	uint32_t     instrbuf[const restrict static 1],
	enum VMachineInstrSet op,
	...
) {
	if( op >= MaxOps || op < halt ) {
		return 0;
	}
	
	size_t cells = sizeof(InstrFunc*) / sizeof *instrbuf;
	if( instrbuf != NULL ) {
		union VMachineVal faddr = { .uintptr = ( uintptr_t )(opcode_func[op]) };
		instrbuf[0] = faddr.uint32a[0];
		instrbuf[1] = faddr.uint32a[1];
	}
	
	va_list ap; va_start(ap, op);
	switch( op ) {
		/// 0 operands:
		case halt: case nop: case ret: case callr:
		case leave: case zeroA: case zeroB: case pushlr: case poplr:
		case add: case sub: case mul: case divi: case mod: case neg:
		case _and: case _or: case _xor: case sll: case srl: case sra: case _not:
		case slt: case sltu: case cmp:
		case incA: case incB: case decA: case decB: case swap:
			break;

		/// single 4-byte operand.
		case enter:
		case jmp: case jnz: case jz: case call:
		case jeq: case jlt: case jltu: case jle: case jleu:
		{
			const uint32_t oper1 = va_arg(ap, uint32_t);
			if( instrbuf != NULL ) {
				instrbuf[2] = oper1;
			}
			cells += sizeof oper1 / sizeof *instrbuf;
			break;
		}
		
		/// single 8-byte operand
		case immA: case immB:
		{
			const union VMachineVal oper1 = va_arg(ap, union VMachineVal);
			if( instrbuf != NULL ) {
				instrbuf[2] = oper1.uint32a[0];
				instrbuf[3] = oper1.uint32a[1];
			}
			cells += sizeof oper1 / sizeof *instrbuf;
			break;
		}
	}
	return cells;
}

#ifdef __cplusplus
}
#endif

#endif /** VMACHINE_INSTR_GEN */
