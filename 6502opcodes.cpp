    using Byte = unsigned char;
    
    //Force Interrupt
    static constexpr Byte INS_BRK_IMP = 0x00;   //ok

    //Push Processor Status
    static constexpr Byte INS_PHP_IMP = 0x08;   //ok

    //Logical Inclusive OR
    static constexpr Byte INS_ORA_IM = 0x09;    //ok
    static constexpr Byte INS_ORA_ZP = 0x05;    //ok
    static constexpr Byte INS_ORA_ZPX = 0x15;   //ok
    static constexpr Byte INS_ORA_ABS = 0x0D;   //ok
    static constexpr Byte INS_ORA_ABSX = 0x1D;  //ok
    static constexpr Byte INS_ORA_ABSY = 0x19;  //ok
    static constexpr Byte INS_ORA_INDX = 0x01;  //ok
    static constexpr Byte INS_ORA_INDY = 0x11;  //ok

    //Arithmetic Shift Left
    static constexpr Byte INS_ASL_ACC = 0x0A;   //ok
    static constexpr Byte INS_ASL_ZP = 0x06;    //ok
    static constexpr Byte INS_ASL_ZPX = 0x16;   //ok
    static constexpr Byte INS_ASL_ABS = 0x0E;   //ok
    static constexpr Byte INS_ASL_ABSX = 0x1E;  //ok

    //Branch if positive
    static constexpr Byte INS_BPL_REL = 0x10;   //not complete!

    //Clear Carry Flag
    static constexpr Byte INS_CLC_IMP = 0x18;   //ok

//-----------------------------------------------

    //Logical AND 
    static constexpr Byte INS_AND_IM = 0x29;    //ok
    static constexpr Byte INS_AND_ZP = 0x25;    //ok
    static constexpr Byte INS_AND_ZPX = 0x35;
    static constexpr Byte INS_AND_ABS = 0x2D;   //ok
    static constexpr Byte INS_AND_ABSX = 0x3D;
    static constexpr Byte INS_AND_ABSY = 0x39;
    static constexpr Byte INS_AND_INDX = 0x21;  //ok
    static constexpr Byte INS_AND_INDY = 0x31;

    //Bit Test
    static constexpr Byte INS_BIT_ZP = 0x24;    //ok
    static constexpr Byte INS_BIT_ABS = 0x2C;   //ok

   //Jump to Subroutine
    static constexpr Byte INS_JSR_ABS = 0x20;   //not sure if ok

    //Pull Processor Status
    static constexpr Byte INS_PLP_IMP = 0x28;   //ok

    //Rotate Left
    static constexpr Byte INS_ROL_ACC = 0x2A;   //ok
    static constexpr Byte INS_ROL_ZP = 0x26;    //ok
    static constexpr Byte INS_ROL_ZPX = 0x36;
    static constexpr Byte INS_ROL_ABS = 0x2E;   //ok
    static constexpr Byte INS_ROL_ABSX = 0x3E;

    //Branch if Minus
    static constexpr Byte INS_BMI_REL = 0x30;

    //Set Carry Flag
    static constexpr Byte INS_SEC_IMP = 0x38;

//--------------------------------------------

    //Logical Shift Right
    static constexpr Byte INS_LSR_ACC = 0x4A;
    static constexpr Byte INS_LSR_ZP = 0x46;
    static constexpr Byte INS_LSR_ZPX = 0x56;
    static constexpr Byte INS_LSR_ABS = 0x4E;
    static constexpr Byte INS_LSR_ABSX = 0x5E;

    //Exclusive OR
    static constexpr Byte INS_EOR_IM = 0x49;
    static constexpr Byte INS_EOR_ZP = 0x45;
    static constexpr Byte INS_EOR_ZPX = 0x55;
    static constexpr Byte INS_EOR_ABS = 0x4D;
    static constexpr Byte INS_EOR_ABSX = 0x5D;
    static constexpr Byte INS_EOR_ABSY = 0x59;
    static constexpr Byte INS_EOR_INDX = 0x41;
    static constexpr Byte INS_EOR_INDY = 0x51;

   //Jump
    static constexpr Byte INS_JMP_ABS = 0x4C;
    static constexpr Byte INS_JMP_IND = 0x6C;

   //Push Accumulator
    static constexpr Byte INS_PHA_IMP = 0x48;

   //Return from Interrupt
    static constexpr Byte INS_RIT_IMP = 0x40;

    //Branch if Overflow CLear
    static constexpr Byte INS_BVC_REL = 0x50;

    //Clear Interrupt Disable
    static constexpr Byte INS_CLI_IMP = 0x58;

//---------------------------------------------

    //Add with Carry
    static constexpr Byte INS_ADC_IM = 0x69;
    static constexpr Byte INS_ADC_ZP = 0X65;
    static constexpr Byte INS_ADC_ZPX = 0x75;
    static constexpr Byte INS_ADC_ABS = 0x6D;
    static constexpr Byte INS_ADC_ABSX = 0x7D;
    static constexpr Byte INS_ADC_ABSY = 0x79;
    static constexpr Byte INS_ADC_INDX = 0x61;
    static constexpr Byte INS_ADC_INDY = 0x71;

    //Pull Accumulator
    static constexpr Byte INS_PLA_IMP = 0x68;

    //Rotate Right
    static constexpr Byte INS_ROR_ACC = 0x6A;
    static constexpr Byte INS_ROR_ZP = 0x66;
    static constexpr Byte INS_ROR_ZPX = 0x76;
    static constexpr Byte INS_ROR_ABS = 0x6E;
    static constexpr Byte INS_ROR_ABSX = 0x7E;

    //Return from Subroutine
    static constexpr Byte INS_RTS_IMP = 0x60;

    //Branch if Overflow Set
    static constexpr Byte INS_BVS_REL = 0x70;

    //Set Interrupt Disable
    static constexpr Byte INS_SEI_IMP = 0x78;

//----------------------------------------------

    //Store Accumulator
    static constexpr Byte INS_STA_ZP = 0x85;
    static constexpr Byte INS_STA_ZPX = 0x95;
    static constexpr Byte INS_STA_ABS = 0x8D;
    static constexpr Byte INS_STA_ABSX = 0x9D;
    static constexpr Byte INS_STA_ABSY = 0x99;
    static constexpr Byte INS_STA_INDX = 0x81;
    static constexpr Byte INS_STA_INDY = 0x91;

    //Store X Register
    static constexpr Byte INS_STX_ZP = 0x86;
    static constexpr Byte INS_STX_ZPY = 0x96;
    static constexpr Byte INS_STX_ABS = 0x8E;

    //Store Y Register
    static constexpr Byte INS_STY_ZP = 0x84;
    static constexpr Byte INS_STY_ZPX = 0x94;
    static constexpr Byte INS_STY_ABS = 0x8C;

    //Transfer X to Accumulator
    static constexpr Byte INS_TXA_IMP = 0x8A;

    //Decrement Y Register
    static constexpr Byte INS_DEY_IMP = 0x88;

    //Branch if Carry Clear
    static constexpr Byte INS_BCC_REL = 0x90;

    //Transfer X to Stack Pointer
    static constexpr Byte INS_TXS_IMP = 0x9A;

    //Transfer Y to Accumulator
    static constexpr Byte INS_TYA_IMP = 0x98;

//-------------------------------------------

    //Load Accumulator
    static constexpr Byte INS_LDA_IM = 0xA9;
    static constexpr Byte INS_LDA_ZP = 0xA5;
    static constexpr Byte INS_LDA_ZPX = 0xB5;
    static constexpr Byte INS_LDA_ABS = 0xAD;
    static constexpr Byte INS_LDA_ABSX = 0xBD;
    static constexpr Byte INS_LDA_ABSY = 0xB9;
    static constexpr Byte INS_LDA_INDX = 0xA1;
    static constexpr Byte INS_LDA_INDY = 0xB1;

    //Load X Register
    static constexpr Byte INS_LDX_IM = 0xA2;
    static constexpr Byte INS_LDX_ZP = 0xA6;
    static constexpr Byte INS_LDX_ZPY = 0xB6;
    static constexpr Byte INS_LDX_ABS = 0xAE;
    static constexpr Byte INS_LDX_ABSY = 0xBE;

    //Load Y Register
    static constexpr Byte INS_LDY_IM = 0xA0;
    static constexpr Byte INS_LDY_ZP = 0xA4;
    static constexpr Byte INS_LDY_ZPY = 0xB4;
    static constexpr Byte INS_LDY_ABS = 0xAC;
    static constexpr Byte INS_LDY_ABSY = 0xBC;

    //Transfer Accumulator to X
    static constexpr Byte INS_TAX_IMP = 0xAA;

    //Transfer Accumulator to Y
    static constexpr Byte INS_TAY_IMP = 0xA8;

    //Branch if Carry Set
    static constexpr Byte INS_BCS_REL = 0xB0;

    //Clear Overflow Flag
    static constexpr Byte INS_CLV_IMP = 0xB8;

    //Transfer Stack Pointer to X
    static constexpr Byte INS_TSX_IMP = 0xBA;

//---------------------------------------------

    //Compare
    static constexpr Byte INS_CMP_IM = 0xC9;
    static constexpr Byte INS_CMP_ZP = 0xC5;
    static constexpr Byte INS_CMP_ZPX = 0xD5;
    static constexpr Byte INS_CMP_ABS = 0xCD;
    static constexpr Byte INS_CMP_ABSX = 0xDD;
    static constexpr Byte INS_CMP_ABSY = 0xD9;
    static constexpr Byte INS_CMP_INDX = 0xC1;
    static constexpr Byte INS_CMP_INDY = 0xD1;

    //Compare Y Register
    static constexpr Byte INS_CPY_IM = 0xC0;
    static constexpr Byte INS_CPX_ZP = 0xC4;
    static constexpr Byte INS_CPX_ABS = 0xCC;

    //Decrement Memory
    static constexpr Byte INS_DEC_ZP = 0xC6;
    static constexpr Byte INS_DEC_ZPX = 0xD6;
    static constexpr Byte INS_DEC_ABS = 0xCE;
    static constexpr Byte INS_DEC_ABSX = 0xDE;

    //Decrement X Register
    static constexpr Byte INS_DEX_IMP = 0xCA;

    //INcrement Y Register
    static constexpr Byte INS_INY_IMP = 0xC8;

    //Branch if not equal
    static constexpr Byte INS_BNE_REL = 0xD0;

    //Clear Decimal Mode
    static constexpr Byte INS_CLD_IMP = 0xD8;

//------------------------------------------------

    //Compare X Register
    static constexpr Byte INS_CPX_IM = 0xE0;
    static constexpr Byte INS_CPX_ZP = 0xE4;
    static constexpr Byte INS_CPX_ABS = 0xEC;

    //Increment Memory
    static constexpr Byte INS_INC_ZP = 0xE6;
    static constexpr Byte INS_INC_ZPX = 0xF6;
    static constexpr Byte INS_INC_ABS = 0xEE;
    static constexpr Byte INS_INC_ABSX = 0xFE;

    //Increment X Register
    static constexpr Byte INS_INX_IMP = 0xE8;

    //No Operation
    static constexpr Byte INS_NOP_IMP = 0xEA;

    //Subtract with Carry
    static constexpr Byte INS_SBC_IM = 0xE9;
    static constexpr Byte INS_SBC_ZP = 0xE5;
    static constexpr Byte INS_SBC_ZPX = 0xF5;
    static constexpr Byte INS_SBC_ABS = 0xED;
    static constexpr Byte INS_SBC_ABSX = 0xFD;
    static constexpr Byte INS_SBC_ABSY = 0xF9;
    static constexpr Byte INS_SBC_INDX = 0xE1;
    static constexpr Byte INS_SBC_INDY = 0xF1;

    //Branch if Equal
    static constexpr Byte INS_BEQ_REL = 0xF0;

    //Set Decimal Flag
    static constexpr Byte INS_SED_IMP = 0xF8;