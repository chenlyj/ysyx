#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "verilated.h"
#include "Vtop.h"
#include "verilated_vcd_c.h"
#include "nvboard.h"

#define sim_time 200


int main(int argc,char** argv){
  VerilatedContext* contextp = new VerilatedContext;
  contextp->commandArgs(argc, argv);
  Verilated::traceEverOn(true);
  VerilatedVcdC *m_trace = new VerilatedVcdC;
  Vtop* top = new Vtop{contextp};
  top->trace(m_trace,5);
  m_trace->open("waveform.vcd");
  while (contextp->time() < sim_time && !contextp->gotFinish()) {
    contextp->timeInc(1);
    int a = rand() & 1;
    int b = rand() & 1;
    top->a = a;
    top->b = b;
    top->eval();
    printf("a = %d, b = %d, f = %d\n", a, b, top->f);
    m_trace->dump(contextp->time());
    assert(top->f == (a ^ b));
  }
  m_trace->close();
  delete top;
  return 0;
}