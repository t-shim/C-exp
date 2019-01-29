/******************************************
* (C)Copyright by N.T.T 1993(unpublished) *
* All rights are reserved.                *
******************************************/
declare alu32 {
    input       a<32> ;
    input       b<32> ;
    output      out<32> ;
    output      ov ;
    output      z ;
    instrin     add ;
    instrin     sub ;
    instrin     and ;
    instrin     or ;
    instrin     xor ;
    instr_arg add(a,b) ;
    instr_arg sub(a,b) ;
    instr_arg and(a,b) ;
    instr_arg or(a,b) ;
    instr_arg xor(a,b) ;
}

circuit alu32 {
    input       a<32> ;
    input       b<32> ;
    output      out<32> ;
    output      ov ;
    output      z ;
    instrin     add ;
    instrin     sub ;
    instrin     and ;
    instrin     or ;
    instrin     xor ;
    instruct add par {
        out  = a + b ;
        ov   = ( (^a<31>) & (^b<31>) & ( out<31>) )
             | ( ( a<31>) & ( b<31>) & (^out<31>) ) ;
    }
    instruct sub par {
        out  = a + (^b) + 0b1 ;
        ov   = ( (^a<31>) & ( b<31>) & ( out<31>) )
             | ( ( a<31>) & (^b<31>) & (^out<31>) ) ;
        z    = ^(/| out<31:0>) ;
    }
    instruct and out = a & b ;
    instruct or out = a | b ;
    instruct xor out = a @ b ;
}
