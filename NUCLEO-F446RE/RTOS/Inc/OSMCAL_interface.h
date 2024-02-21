#ifndef OSMCAL_INTERFACE_H_
#define OSMCAL_INTERFACE_H_

void STK_voidInit(uint32_t Copy_u32TickHz);

__attribute__ ((naked)) void Stack_voidSchedulerStackInit(uint32_t Copy_u32SchedTOS);
#endif
