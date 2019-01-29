/******************************************
* (C)Copyright by N.T.T 1993(unpublished) *
* All rights are reserved.                *
******************************************/
declare alu16 {
    input       a<16> ;
    input       b<16> ;
    output      out<16> ;
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

circuit alu16 {
    input       a<16> ;
    input       b<16> ;
    output      out<16> ;
    output      ov ;
    output      z ;
    instrin     add ;
    instrin     sub ;
    instrin     and ;
    instrin     or ;
    instrin     xor ;
    instruct add par {
        out  = a + b ;
        ov   = ( (^a<15>) & (^b<15>) & ( out<15>) )
             | ( ( a<15>) & ( b<15>) & (^out<15>) ) ;
    }
    instruct sub par {
        out  = a + (^b) + 0b1 ;
        ov   = ( (^a<15>) & ( b<15>) & ( out<15>) )
             | ( ( a<15>) & (^b<15>) & (^out<15>) ) ;
        z    = ^(/| out<15:0>) ;
    }
    instruct and out = a & b ;
    instruct or out = a | b ;
    instruct xor out = a @ b ;
}