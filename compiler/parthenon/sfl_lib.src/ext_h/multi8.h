/******************************************
* (C)Copyright by N.T.T 1993(unpublished) *
* All rights are reserved.                *
******************************************/
declare multi8 {
    input       in1<8> ;
    input       in2<8> ;
    output      out<16> ;
    instrin     do ;
    instr_arg do(in1,in2) ;
}

circuit multi8 {
    input       in1<8> ;
    input       in2<8> ;
    output      out<16> ;
    sel_v       tmp0<16>, tmp1<16>, tmp2<16>, tmp3<16>;
    sel_v       tmp4<16>, tmp5<16>, tmp6<16>, tmp7<16>;
    instrin     do ;
    instruct do par {
        tmp0 = (0b00000000||in1    ) & (16 # in2<0>) ;
        tmp1 = (0b0000000||in1||0b0) & (16 # in2<1>) ;
        tmp2 = (0b000000||in1||0b00) & (16 # in2<2>) ;
        tmp3 = (0b00000||in1||0b000) & (16 # in2<3>) ;
        tmp4 = (0b0000||in1||0b0000) & (16 # in2<4>) ;
        tmp5 = (0b000||in1||0b00000) & (16 # in2<5>) ;
        tmp6 = (0b00||in1||0b000000) & (16 # in2<6>) ;
        tmp7 = (0b0||in1||0b0000000) & (16 # in2<7>) ;
        out = tmp0 + tmp1 + tmp2 + tmp3 + tmp4 + tmp5 + tmp6 + tmp7 ;
    }
}
