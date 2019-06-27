#include  <stdio.h>
#include  <stdint.h>
#include  <stdlib.h>
#include  <stdarg.h>
#include  <string.h>

const char *reg[32] = {
  "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
  "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
  "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
  "t8", "t9", "k0", "k1", "gp", "sp", "s8", "ra"
};

const char *c0reg[32] = {
  "inx", "rand", "tlblo", "bpc", "ctxt", "bda", "pidmask",
  "dcic", "badvaddr", "bdam", "tlbhi", "bpcm", "sr", "cause",
  "epc", "prid", "erreg", "r17", "r18", "r19", "r20", "r21",
  "r22", "r23", "r24", "r25", "r26", "r27", "r28", "r29", "r30",
  "r31"
};

const char *c2dreg[32] = {
  "vxy0", "vz0", "vxy1", "vz1", "vxy2", "vz2", "rgb", "otz",
  "ir0", "ir1", "ir2", "ir3", "sxy0", "sxy1", "sxy2", "sxyp",
  "sz0", "sz1", "sz2", "sz3", "rgb0", "rgb1", "rgb2", "r23",
  "mac0", "mac1", "mac2", "mac3", "irgb", "orgb", "lzcs", "lzcr"
};

const char *c2creg[32] = {
  "r11r12", "r13r21", "r22r23", "r31r32", "r33", "trx", "try",
  "trz", "l11l12", "l13l21", "l22l23", "l31l32", "l33", "rbk",
  "gbk", "bbk", "lr1lr2", "lr3lg1", "lg2lg3", "lb1lb2", "lb3",
  "rfc", "gfc", "bfc", "ofx","ofy", "h", "dqa", "dqb", "zsf3",
  "zsf4", "flag"
};

static void dis_r(unsigned long data)
{
  unsigned long code3 = (data >> 3) & 0x7;
  unsigned long code4 = (data >> 0) & 0x7;

  switch(code3){
  case 0:
    switch(code4){
    case 0:
      if(data == 0){
        printf("nop\n");
      }
      else{
        printf("sll %s, %s, %d\n", reg[(data >> 11) & 0x1f], reg[(data >> 16) & 0x1f], (data >> 6) & 0x1f);
      }
      break;
    case 2:
      printf("srl %s, %s, %d\n", reg[(data >> 11) & 0x1f], reg[(data >> 16) & 0x1f], (data >> 6) & 0x1f);
      break;
    case 3:
      printf("sra %s, %s, %d\n", reg[(data >> 11) & 0x1f], reg[(data >> 16) & 0x1f], (data >> 6) & 0x1f);
      break;
    case 4:
      printf("sllv %s, %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 16) & 0x1f], reg[(data >> 21) & 0x1f]);
      break;
    case 6:
      printf("srlv %s, %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 16) & 0x1f], reg[(data >> 21) & 0x1f]);
      break;
    case 7:
      printf("srav %s, %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 16) & 0x1f], reg[(data >> 21) & 0x1f]);
      break;
    default:
      printf("0x%x\n", data);
      break;
    }
    break;
  case 1:
    switch(code4){
    case 0:
      printf("jr %s\n", reg[(data >> 21) & 0x1f]);
      break;
    case 1:
      printf("jalr %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 21) & 0x1f]);
      break;
    case 4:
      printf("syscall $%x\n", (data >> 6) & 0xfffff);
      break;
    case 5:
      printf("break $%x\n", (data >> 6) & 0xfffff);
      break;
    case 7:
      printf("sync\n");
      break;
    default:
      printf("0x%x\n", data);
      break;
    }
    break;
  case 2:
    switch(code4){
    case 0:
      printf("mfhi %s\n", reg[(data >> 11) & 0x1f]);
      break;
    case 1:
      printf("mthi %s\n", reg[(data >> 11) & 0x1f]);
      break;
    case 2:
      printf("mflo %s\n", reg[(data >> 11) & 0x1f]);
      break;
    case 3:
      printf("mtlo %s\n", reg[(data >> 11) & 0x1f]);
      break;
    case 4:
      printf("dsllv %s, %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 16) & 0x1f], reg[(data >> 21) & 0x1f]);
      break;
    case 6:
      printf("dsrlv %s, %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 16) & 0x1f], reg[(data >> 21) & 0x1f]);
      break;
    case 7:
      printf("dsrav %s, %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 16) & 0x1f], reg[(data >> 21) & 0x1f]);
      break;
    default:
      printf("0x%x\n", data);
      break;
    }
    break;
  case 3:
    switch(code4){
    case 0:
      printf("mult %s, %s\n", reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f]);
      break;
    case 1:
      printf("multu %s, %s\n", reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f]);
      break;
    case 2:
      printf("div %s, %s\n", reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f]);
      break;
    case 3:
      printf("divu %s, %s\n", reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f]);
      break;
    case 4:
      printf("dmult %s, %s\n", reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f]);
      break;
    case 7:
      printf("ddivu %s, %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 16) & 0x1f], reg[(data >> 21) & 0x1f]);
      break;
    default:
      printf("0x%x\n", data);
      break;
    }
    break;
  case 4:
    switch(code4){
    case 0:
      printf("add %s, %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f]);
      break;
    case 1:
      if(((data >> 16) & 0x1f) == 0){
        printf("move %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 21) & 0x1f]);
      }
      else{
        printf("addu %s, %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f]);
      }
      break;
    case 2:
      printf("sub %s, %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f]);
      break;
    case 3:
      printf("subu %s, %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f]);
      break;
    case 4:
      printf("and %s, %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f]);
      break;
    case 5:
      printf("or %s, %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f]);
      break;
    case 6:
      printf("xor %s, %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f]);
      break;
    case 7:
      printf("nor %s, %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f]);
      break;
    }
    break;
  case 5:
    switch(code4){
    case 2:
      printf("slt %s, %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f]);
      break;
    case 3:
      printf("sltu %s, %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f]);
      break;
    case 4:
      printf("dadd %s, %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f]);
      break;
    case 5:
      printf("daddu %s, %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f]);
      break;
    case 6:
      printf("dneg %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 16) & 0x1f]);
      break;
    case 7:
      printf("dnegu %s, %s\n", reg[(data >> 11) & 0x1f], reg[(data >> 16) & 0x1f]);
      break;
    default:
      printf("0x%x\n", data);
      break;
    }
    break;
  case 6:
    switch(code4){
    case 0:
      printf("tge %s, %s\n", reg[(data >> 21) & 0x1f], 
        reg[(data >> 16) & 0x1f]);
      break;
    case 1:
      printf("tgeu %s, %s\n", reg[(data >> 21) & 0x1f], 
        reg[(data >> 16) & 0x1f]);
      break;
    case 2:
      printf("tlt %s, %s\n", reg[(data >> 21) & 0x1f], 
        reg[(data >> 16) & 0x1f]);
      break;
    case 3:
      printf("tltu %s, %s\n", reg[(data >> 21) & 0x1f], 
        reg[(data >> 16) & 0x1f]);
      break;
    case 4:
      printf("teq %s, %s\n", reg[(data >> 21) & 0x1f], 
        reg[(data >> 16) & 0x1f]);
      break;
    case 6:
      printf("tne %s, %s\n", reg[(data >> 21) & 0x1f], 
        reg[(data >> 16) & 0x1f]);
      break;
    default:
      printf("0x%x\n", data);
      break;
    }
    break;
  default:
    printf("0x%x\n", data);
    break;
  }
}

static void dis_ri(unsigned long data)
{
  unsigned long code3 = (data >> 19) & 0x3;
  unsigned long code4 = (data >> 16) & 0x7;

  switch(code3){
  case 0:
    switch(code4){
    case 0:
      printf("bltz %s, %d\n", reg[(data >> 21) & 0x1f], ((short)data) << 2);
      break;
    case 1:
      printf("bgez %s, %d\n", reg[(data >> 21) & 0x1f], ((short)data) << 2);
      break;
    case 2:
      printf("bltzl %s, %d\n", reg[(data >> 21) & 0x1f], ((short)data) << 2);
      break;
    case 3:
      printf("bgezl %s, %d\n", reg[(data >> 21) & 0x1f], ((short)data) << 2);
      break;
    default:
      printf("0x%x\n", data);
      break;
    }
    break;
  case 1:
    switch(code4){
    case 0:
      printf("tgei %s, %d\n", reg[(data >> 21) & 0x1f], (short)data);
      break;
    case 1:
      printf("tgeiu %s, %d\n", reg[(data >> 21) & 0x1f], (short)data);
      break;
    case 3:
      printf("tltiu %s, %d\n", reg[(data >> 21) & 0x1f], (short)data);
      break;
    case 4:
      printf("teqi %s, %d\n", reg[(data >> 21) & 0x1f], (short)data);
      break;
    case 6:
      printf("tnei %s, %d\n", reg[(data >> 21) & 0x1f], (short)data);
      break;
    default:
      printf("0x%x\n", data);
      break;
    }
    break;
  default:
    printf("0x%x\n", data);
    break;
  }
}

static void disasm(unsigned long data)
{
  static unsigned long addr=0;
  unsigned long code1, code2, code3, code4;

  code1 = (data >> 29) & 0x7;
  code2 = (data >> 26) & 0x7;

  printf("%x: %08x ", addr, data);
  addr+= 4;
  switch(code1){
  case 0:
    switch(code2){
    case 0:
      dis_r(data);
      break;
    case 1:
      dis_ri(data);
      break;
    case 2:
      printf("j 0x%x\n", ((data & 0x03ffffff) << 2));
      break;
    case 3:
      printf("jal 0x%x\n", ((data & 0x03ffffff) << 2));
      break;
    case 4:
      if(((data >> 16) & 0x1f) == 0){
        printf("beqz %s, %d\n", reg[(data >> 21) & 0x1f], ((short)data) << 2);
      }
      else{
        printf("beq %s, %s, %d\n", reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f], ((short)data) << 2);
      }
      break;
    case 5:
      if(((data >> 16) & 0x1f) == 0){
        printf("bnez %s, %d\n", reg[(data >> 21) & 0x1f], ((short)data) << 2);
      }
      else{
        printf("bne %s, %s, %d\n", reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f], ((short)data) << 2);
      }
      break;
    case 6:
      printf("blez %s, %d\n", reg[(data >> 21) & 0x1f], ((short)data) << 2);
      break;
    case 7:
      printf("bgtz %s, %d\n", reg[(data >> 21) & 0x1f], ((short)data) << 2);
      break;
    }
    break;
  case 1:
    switch(code2){
    case 0:
      printf("addi %s, %s, %d\n", reg[(data >> 16) & 0x1f], reg[(data >> 21) & 0x1f], (short)data);
      break;
    case 1:
      if( ((data >> 21) & 0x1f)==0 ){
        printf("li %s, %d\n", reg[(data >> 16) & 0x1f], (short)data);
      }
      else{
        printf("addiu %s, %s, %d\n", reg[(data >> 16) & 0x1f], reg[(data >> 21) & 0x1f], (short)data);
      }
      break;
    case 2:
      printf("slti %s, %s, %d\n", reg[(data >> 16) & 0x1f], reg[(data >> 21) & 0x1f], (short)data);
      break;
    case 3:
      printf("sltiu %s, %s, %d\n", reg[(data >> 16) & 0x1f], reg[(data >> 21) & 0x1f], (short)data);
      break;
    case 4:
      printf("andi %s, %s, %d\n", reg[(data >> 16) & 0x1f], reg[(data >> 21) & 0x1f], (short)data);
      break;
    case 5:
      if((short)data < 0){
        printf("addiu %s, %s, %d\n", reg[(data >> 16) & 0x1f], reg[(data >> 21) & 0x1f], (short)data);
      }
      else{
        printf("ori %s, %s, %d\n", reg[(data >> 16) & 0x1f], reg[(data >> 21) & 0x1f], (short)data);
      }
      break;
    case 6:
      printf("xori %s, %s, %d\n", reg[(data >> 16) & 0x1f], reg[(data >> 21) & 0x1f], (short)data);
      break;
    case 7:
      printf("lui %s, %d\n", reg[(data >> 16) & 0x1f], (short)data);
      break;
    }
    break;
  case 2:
    switch(code2){
    case 0:
      code3 = (data >> 21) & 0x1f;
      switch(code3){
      case 0:
        printf("mfc0 %s, $%d\n", reg[(data >> 16) & 0x1f], (data >> 11) & 0x1f);
        break;
      case 1:
        printf("dmfc0 %s, $%d\n", reg[(data >> 16) & 0x1f], (data >> 11) & 0x1f);
        break;
      case 4:
        printf("mtc0 %s, %s\n", reg[(data >> 16) & 0x1f], c0reg[(data >> 11) & 0x1f]);
        break;
      case 16:
        if((data & 0x1f) == 16){
          printf ("rfe\n");
        }
        else{
          printf("0x%x\n", data);
        }
        break;
      default:
        printf("0x%x\n", data);
        break;
      }
      break;
    case 2:
      code3 = (data >> 25) & 0x1;
      if(code3 == 1){
        data&= 0x1ffffff;
        if((data & 0x1f003ff) == 0x0400012){
          printf("mvmva %d, %d, %d, %d, %d\n", (data >> 19) & 1, (data >> 17) & 3, 
            (data >> 15) & 3, (data >> 13) & 3, (data >> 10) & 1);
        }
        else if((data & 0x1f003ff) == 0x0a00428){
          printf("sqr %d\n", (data >> 19) & 1);
        }
        else if((data & 0x1f003ff) == 0x170000c){
          printf("op %d\n", (data >> 19) & 1);
        }
        else if((data & 0x1f003ff) == 0x190003d){
          printf("gpf %d\n", (data >> 19) & 1);
        }
        else if((data & 0x1f003ff) == 0x1a0003e){
          printf("gpl %d\n", (data >> 19) & 1);
        }
        else if(data == 0x0180001){
          printf("rtps\n");
        }
        else if(data == 0x0280030){
          printf("rtpt\n");
        }
        else if(data == 0x0680029){
          printf("dcpl\n");
        }
        else if(data == 0x0780010){
          printf("dcps\n");
        }
        else if(data == 0x0980011){
          printf("intpl\n");
        }
        else if(data == 0x0c8041e){
          printf("ncs\n");
        }
        else if(data == 0x0d80420){
          printf("nct\n");
        }
        else if(data == 0x0e80413){
          printf("ncds\n");
        }
        else if(data == 0x0f80416){
          printf("ncdt\n");
        }
        else if(data == 0x0f8002a){
          printf("dpct\n");
        }
        else if(data == 0x108041b){
          printf("nccs\n");
        }
        else if(data == 0x118043f){
          printf("ncct\n");
        }
        else if(data == 0x1280414){
          printf("cdp\n");
        }
        else if(data == 0x138041c){
          printf("cc\n");
        }
        else if(data == 0x1400006){
          printf("nclip\n");
        }
        else if(data == 0x158002d){
          printf("avsz3\n");
        }
        else if(data == 0x168002e){
          printf("avsz4\n");
        }
        else{
          printf("cop2 $%x\n", data & 0x1ffffff);
        }
      }
      else{
        code3 = (data >> 21) & 0x1f;
        switch(code3){
        case 0:
          printf( "mfc2 %s, %s\n", reg[(data >> 16) & 0x1f], c2dreg[(data >> 11) & 0x1f]);
          break;
        case 2:
          printf( "cfc2 %s, %s\n", reg[(data >> 16) & 0x1f], c2creg[(data >> 11) & 0x1f]);
          break;
        case 4:
          printf( "mtc2 %s, %s\n", reg[(data >> 16) & 0x1f], c2dreg[(data >> 11) & 0x1f]);
          break;
        case 6:
          printf( "ctc2 %s, %s\n", reg[(data >> 16) & 0x1f], c2creg[(data >> 11) & 0x1f]);
          break;
        default:
          printf("0x%x\n", data);
          break;
        }
      }
      break;
    case 4:
      printf("beql %s, %s, %d\n", reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f], ((short)data) << 2);
      break;
    case 5:
      printf("bnel %s, %s, %d\n", reg[(data >> 21) & 0x1f], reg[(data >> 16) & 0x1f], ((short)data) << 2);
      break;
    case 6:
      printf("blezl %s, %d\n", reg[(data >> 21) & 0x1f], ((short)data) << 2);
      break;
    case 7:
      printf("bgtzl %s, %d\n", reg[(data >> 21) & 0x1f], ((short)data) << 2);
      break;
    default:
      printf("0x%x\n", data);
      break;
    }
    break;
  case 3:
    switch(code2){
    case 0:
      printf("daddi %s, %s, %d\n", reg[(data >> 16) & 0x1f], reg[(data >> 21) & 0x1f], (short)data);
      break;
    case 1:
      printf("daddiu %s, %s, %d\n", reg[(data >> 16) & 0x1f], reg[(data >> 21) & 0x1f], (short)data);
      break;
    case 2:
      printf("ldl %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 3:
      printf("ldr %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    default:
      printf("0x%x\n", data);
      break;
    }
    break;
  case 4:
    switch(code2){
    case 0:
      printf("lb %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 1:
      printf("lh %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 2:
      printf("lwl %s,%d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 3:
      printf("lw %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 4:
      printf("lbu %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 5:
      printf("lhu %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 6:
      printf("lwr %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 7:
      printf("lwu %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    default:
      printf("0x%x\n", data);
      break;
    }
    break;
  case 5:
    switch(code2){
    case 0:
      printf("sb %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 1:
      printf("sh %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 2:
      printf("swl %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 3:
      printf("sw %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 4:
      printf("sdl %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 5:
      printf("sdr %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 6:
      printf("swr %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    default:
      printf("0x%x\n", data);
      break;
    }
    break;
  case 6:
    switch(code2){
    case 0:
      printf("ll %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 1:
      printf("lwc1 $f%d, %d(%s)\n", (data >> 16) & 0x1f, (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 2:
      printf("lwc2 %s, %d(%s)\n", c2dreg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 3:
      printf("lwc3 $%d, %d(%s)\n", (data >> 16) & 0x1f, (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 4:
      printf("lld %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 5:
      printf("ldc1 $f%d, %d(%s)\n", (data >> 16) & 0x1f, (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 6:
      printf("ldc2 $%d, %d(%s)\n", (data >> 16) & 0x1f, (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 7:
      printf("ldc %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    default:
      printf("0x%x\n", data);
      break;
    }
    break;
  case 7:
    switch(code2){
    case 0:
      printf("sc %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 1:
      printf("swc1 $f%d, %d(%s)\n", (data >> 16) & 0x1f, (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 2:
      printf("swc2 %s, %d(%s)\n", c2dreg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 3:
      printf("swc3 $%d, %d(%s)\n", (data >> 16) & 0x1f, (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 4:
      printf("scd %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 5:
      printf("sdc1 $f%d, %d(%s)\n", (data >> 16) & 0x1f, (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 6:
      printf("sdc2 $%d, %d(%s)\n", (data >> 16) & 0x1f, (short)data, reg[(data >> 21) & 0x1f]);
      break;
    case 7:
      printf("sd %s, %d(%s)\n", reg[(data >> 16) & 0x1f], (short)data, reg[(data >> 21) & 0x1f]);
      break;
    default:
      printf("0x%x\n", data);
      break;
    }
    break;
  default:
    printf("0x%x\n", data);
    break;
  }
}

int main(int argc, char** argv)
{
  FILE *f;
  unsigned long chunk;

  if(argc == 1){
    printf("usage: disasm xxx\n");
    return -1;
  }
  
  f = fopen(argv[1], "rb");
  if(f == NULL){
    printf("invalid file path\n");
    return -1;
  }

  while((chunk = fgetc(f)) != EOF){
    chunk|= (fgetc(f) << 8);
    chunk|= (fgetc(f) << 16);
    chunk|= (fgetc(f) << 24);
    disasm(chunk);
  }
  fclose(f);
  return 0;
}

