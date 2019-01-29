/******************************************
* (C)Copyright by N.T.T 1993(unpublished) *
* All rights are reserved.                *
******************************************/
declare cmp16 {
    input       in1<16> ;
    input       in2<16> ;
    output      same ;
    instrin     do ;
    instr_arg do(in1,in2) ;
}

circuit cmp16 {
    input       in1<16> ;
    input       in2<16> ;
    output      same ;
    instrin     do ;
    instruct do same = ^(/|(in1 @ in2)) ;
}
