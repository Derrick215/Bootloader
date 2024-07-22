#ifndef __SYS_H
#define __SYS_H

void sys_nvic_set_vector_table(uint32_t baseaddr, uint32_t offset);
void sys_msr_msp(uint32_t addr);

#endif

