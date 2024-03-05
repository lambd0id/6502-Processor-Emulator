#include <bitset>
#include <stdio.h>
#include <stdlib.h>

/*
Notes for noobs:
This machine is little endian
0x---- = numbers in hexadecimal
0b-------- = numbers in binary

0x00 - 0xFF => Zero Page Address
0x100 - 0x1FF => Stack Memory
Stack Pointer Starts at 0x1FF
0xFFFA - 0xFFFB => non-maskable interrupt handler
0xFFFC - 0xFFFD => power-on/reset location
0xFFFE - 0xFFFF => BRK/interrupt request handler

every memory access is 1 cycle
*/

using Byte = unsigned char;
using Word = unsigned short;    //2 bytes
using u32 = unsigned int;   //4 bytes

struct Mem
{
    static constexpr u32 MAX_MEM = 1024 * 64;   //64kB total memory
    Byte Data[MAX_MEM];

    void Initialize()
    {
        for (u32 i = 0; i < MAX_MEM; i++)
            Data[i] = 0;
    }

    Byte operator [](Word Address) const //done to access array outside the construct
    {
        if (0 <= Address < 0xFFFA)   //because oxFFFA and above are reserved
            return Data[Address];
        //else
            //pass (add some error handling here)
    }

    void SetMemory(Word Address, Byte Value)
    {
        Data[Address] = Value;
    }

};

struct CPU
{
    //reference: http://obelisk.me.uk/6502/

    Word PC;    //program counter
    Word SP;    //stack pointer (should be byte instead but for it to actually point to stack and be a byte, you have to add 0x100 everytime you access memory with it (which is a bit tedious))
    Byte A, X, Y;   //Index registers X & Y and accumulator

    std::bitset<7> StatusFlag;
    //0:Carry, 1:Zero, 2:Interrupt Disable, 3:Decimal Mode, 4:Break, 5:Overflow, 6:Negative

    void Reset(Mem& memory)
    {
        //reference: https://www.c64-wiki.com/wiki/Reset_(Process)
        PC = 0xFFFC;    //power-on/reset location
        SP = 0x01FF;    //from http://skilldrick.github.io/easy6502/#stack
        StatusFlag.reset();    //sets all flags to 0
        // check reference to confirm initial flag values

        memory.Initialize();
    }

    Byte FetchByte(Mem& memory)
    {
        Byte Data = memory[PC];
        PC++;
        return Data;
    }

    Word FetchWord(Mem& memory)
    {   //only for little endian platforms
        Word Data = memory[PC]; //takes the least significant byte (0000 ----)
        PC++;
        Data |= (memory[PC] << 8);  //adds most significant byte (Data | ---- 0000)
        PC++;
        return Data;
    } 

    Byte Read(Word Address, Mem& memory)
    {   //only for little endian platforms
        Word Data = memory[Address];
        return Data;
    }

    void SendtoStack(Byte Data, Mem& memory)
    {
        memory.SetMemory(SP, Data);
        SP--;
    }


    Byte ADDM_IM(Mem& memory)
    {
        return FetchByte(memory);
    }

    Byte ADDM_ZP(Mem& memory)
    {
        Byte ZeroPageAddress = FetchByte(memory);
        return Read(ZeroPageAddress, memory);
    }

    Byte ADDM_ZPX(Mem& memory)
    {
        Byte ZeroPageAddress = FetchByte(memory);
        ZeroPageAddress += X;
        return Read(ZeroPageAddress, memory);
    }

    Byte ADDM_ZPY(Mem& memory)
    {
        Byte ZeroPageAddress = FetchByte(memory);
        ZeroPageAddress += Y;
        return Read(ZeroPageAddress, memory);
    }

    Byte ADDM_ABS(Mem& memory)
    {
        Word AbsoluteAddress = FetchWord(memory);
        return Read(AbsoluteAddress, memory);
    }

    Byte ADDM_ABSX(Mem& memory)
    {
        Word AbsoluteAddress = FetchWord(memory);
        AbsoluteAddress += X;
        return Read(AbsoluteAddress, memory);
    }

    Byte ADDM_ABSY(Mem& memory)
    {
        Word AbsoluteAddress = FetchWord(memory);
        AbsoluteAddress += Y;
        return Read(AbsoluteAddress, memory);
    }

    Byte ADDM_IND(Mem& memory)
    {
        Word IndirectAddress = FetchWord(memory);
        IndirectAddress = (Read(IndirectAddress, memory) | (Read(IndirectAddress + 1, memory) << 8));
        return Read(IndirectAddress, memory);
    }

    Byte ADDM_INDX(Mem& memory)
    {
        Word IndirectAddress = FetchWord(memory) + X;
        IndirectAddress = (Read(IndirectAddress, memory) | (Read(IndirectAddress + 1, memory) << 8));
        return Read(IndirectAddress, memory);
    }

    Byte ADDM_INDY(Mem& memory)
    {
        Word IndirectAddress = FetchWord(memory);
        IndirectAddress = (Read(IndirectAddress, memory) | (Read(IndirectAddress + 1, memory) << 8)) + Y;
        return Read(IndirectAddress, memory);
    }

    void ZandN_SetStatus(Byte Value)
    {
        StatusFlag[1] = (Value == 0);
        StatusFlag[6] = (Value & 0b10000000) > 0;
    }


    void Execute(Mem& memory)
    {
    Byte Ins = FetchByte(memory);   //fetch opcode instuction

    //refer to: http://nparker.llx.com/a2/opcodes.html for pattern
    //opcode form: aaabbbcc
        switch(Ins & 0b11100000)    //aaa
        {
            case 0:
            {
                switch(Ins & 0b00011100)    //bbb
                {
                    case 0:
                    {
                        switch(Ins & 0b00000011)    //cc
                        {
                            case 0: //0b00000000 0x00 INS_BRK_IMP
                            {
                                SendtoStack(PC, memory);
                                unsigned char processor_status = static_cast<unsigned char>(StatusFlag.to_ulong());
                                //souce of black magic: https://stackoverflow.com/questions/11068204/is-it-possible-to-convert-bitset8-to-char-in-c
                                SendtoStack(processor_status, memory);
                                PC = Read(0xFFFE, memory);
                                StatusFlag[4] = 1;
                            } break;

                            case 1: //0b00000001 0x01 INS_ORA_INDX
                            {
                                A |= ADDM_INDX(memory);
                                ZandN_SetStatus(A);
                            } break;
                        }
                    } break;
                    
                    case 1:
                    {
                        switch(Ins & 0b00000011)
                        {
                            case 1: //0b00000101 0x05 INS_ORA_ZP
                            {
                                A |= ADDM_ZP(memory);
                                ZandN_SetStatus(A);
                            } break;

                            case 2: //0b00000110 0x06 INS_ASL_ZP
                            {
                                Byte Value = ADDM_ZP(memory);
                                StatusFlag[0] = ((Value & 0b10000000) >> 7);
                                Value = Value << 1;
                                memory.SetMemory(PC, Value);
                                ZandN_SetStatus(Value);
                            } break;
                        }
                    } break;

                    case 2:
                    {
                        switch(Ins & 0b00000011)
                        {
                            case 0: //0b00001000 0x08 INS_PHP_IMP
                            {
                                unsigned char processor_status = static_cast<unsigned char>(StatusFlag.to_ulong());
                                SendtoStack(processor_status, memory);
                            } break;

                            case 1: //0b00001001 0x09 INS_ORA_IM
                            {
                                A |= ADDM_IM(memory);
                                ZandN_SetStatus(A);
                            } break;
                            case 2: //0b0001010 0x0A INS_ASL_ACC
                            {
                                StatusFlag[0] = ((A & 0b10000000) >> 7);
                                A = A << 1;
                                ZandN_SetStatus(A);
                            } break;
                        }
                    } break;

                    case 3:
                    {
                        switch(Ins & 0b00000011) //0b00001101 0x0D INS_ORA_ABS
                        {
                            case 1:
                            {
                                A |= ADDM_IM(memory);
                                ZandN_SetStatus(A);
                            } break;

                            case 2: //0b00001110 0x0E INS_ASL_ABS
                            {
                                Byte Value = ADDM_ABS(memory);
                                StatusFlag[0] = ((Value & 0b10000000) >> 7);
                                Value = Value << 1;
                                memory.SetMemory(PC, Value);
                                ZandN_SetStatus(Value);
                            } break;
                        }
                    } break;

                    case 4:
                    {
                        switch(Ins & 0b00000011)
                        {
                            case 0: //0b00010000 0x10 INS_BPL_REL
                            {
                                PC += -(StatusFlag[6] - 1) * FetchByte(memory);
                                //add error handling when PC becomes negative
                            } break;

                            case 1: //0b00010001 0x11 INS_ORA_INDY
                            {
                                A |= ADDM_INDY(memory);
                                ZandN_SetStatus(A);
                            } break;
                        }
                    } break;

                    case 5:
                    {
                        switch(Ins & 0b00000011)
                        {
                            case 1: //0b00010101 0x15 INS_ORA_ZPX
                            {
                                A |= ADDM_ZPX(memory);
                                ZandN_SetStatus(A);
                            } break;

                            case 2: //0b00010110 0x16 INS_ASL_ZPX
                            {
                                Byte Value = ADDM_ZPX(memory);
                                StatusFlag[0] = ((Value & 0b10000000) >> 7);
                                Value = Value << 1;
                                memory.SetMemory(PC, Value);
                                ZandN_SetStatus(Value);
                            } break;
                        }
                    } break;

                    case 6:
                    {
                        switch(Ins & 0b00000011)
                        {
                            case 0: //0b00011000 0x18 INS_CLC_IMP
                            {
                                StatusFlag.reset(0);
                            } break;

                            case 1: //0b00011001 0x19 INS_ORA_ABSY
                            {
                                A |= ADDM_ABSY(memory);
                                ZandN_SetStatus(A);
                            } break;
                        }
                    } break;

                    case 7:
                    {
                        switch(Ins & 0b00000011)
                        {
                            case 1: //0b00011101 0x1D INS_ORA_ABSX
                            {
                                A |= ADDM_ABSX(memory);
                                ZandN_SetStatus(A);
                            } break;

                            case 2: //0b00011110 0x1E INS_ASL_ABSX
                            {
                                Byte Value = ADDM_ABSX(memory);
                                StatusFlag[0] = ((Value & 0b10000000) >> 7);
                                Value = Value << 1;
                                memory.SetMemory(PC, Value);
                                ZandN_SetStatus(Value);
                            } break;
                        }
                    } break;

                    default:
                    {
                        printf("Instruction not handled: %d", Ins);
                    } break;
                }
            } break;

            case 1:
            {
                switch(Ins & 0b00011100)
                {
                    case 0:
                    {
                        switch(Ins & 0b00000011)
                        {
                            case 0: //0b00100000 0x20 INS_JSR_ABS
                            {
                                SendtoStack(PC - 1, memory);
                                PC = ADDM_ABS(memory);
                            } break;

                            case 1: //0b00100001 0x21 INS_AND_INDX
                            {
                                A &= ADDM_INDX(memory);
                                ZandN_SetStatus(A);
                            } break;
                        }
                    } break;

                    case 1:
                    {
                        switch(Ins & 0b00000011)
                        {
                            case 0: //0b00100100 0x24 INS_BIT_ZP
                            {
                                Byte Value = ADDM_ZP(memory);
                                StatusFlag[5] = ((Value & 0b01000000) > 0);
                                StatusFlag[6] = ((Value & 0b10000000) > 0);
                                Value &= A;
                                StatusFlag[1] = (Value == 0);
                            } break;

                            case 1: //0b00100101 0x25 INS_AND_ZP
                            {
                                A &= ADDM_ZP(memory);
                                ZandN_SetStatus(A);
                            } break;

                            case 2: //0b00100110 0x26 INS_ROL_ZP
                            {
                                Byte Value = ADDM_ZP(memory);
                                Byte MSB = (Value & 0b10000000);
                                Value = Value << 1;
                                Value += StatusFlag[0];
                                StatusFlag[0] = (MSB > 0);
                                memory.SetMemory(PC--, Value);  //for Word, PC - 2 instead 
                                ZandN_SetStatus(Value);
                            } break;
                        }
                    } break;

                    case 2:
                    {
                        switch(Ins & 0b00000011)
                        {
                            case 0: //0b00101000 0x28 INS_PLP_IMP
                            {
                                StatusFlag = Read(SP, memory);
                                SP++;
                            } break;

                            case 1: //0b00101001 0x29 INS_AND_IM
                            {
                                A &= ADDM_IM(memory);
                                ZandN_SetStatus(A);
                            } break;

                            case 2: //0b00101010 0x2A INS_ROL_ACC
                            {
                                Byte MSB = (A & 0b10000000);
                                A = A << 1;
                                A += StatusFlag[0];
                                StatusFlag[0] = (MSB > 0);
                                ZandN_SetStatus(A);
                            } break;
                        }
                    } break;

                    case 3:
                    {
                        switch(Ins & 0b00000011)
                        {
                            case 0: //0b00101100 0x2C INS_BIT_ABS
                            {
                                Byte Value = ADDM_ABS(memory);
                                StatusFlag[5] = ((Value & 0b01000000) > 0);
                                StatusFlag[6] = ((Value & 0b10000000) > 0);
                                Value &= A;
                                StatusFlag[1] = (Value == 0);
                            } break;

                            case 1: //0b00101101 0x2D INS_AND_ABS
                            {
                                A &= ADDM_ABS(memory);
                                ZandN_SetStatus(A);
                            } break;

                            case 2: //0b00101110 0x2E INS_ROL_ABS
                            {
                                Byte Value = ADDM_ABS(memory);
                                Byte MSB = (Value & 0b10000000);
                                Value = Value << 1;
                                Value += StatusFlag[0];
                                StatusFlag[0] = (MSB > 0);
                                memory.SetMemory(PC - 2, Value);
                                ZandN_SetStatus(Value);
                            } break;
                        }
                    } break;

                    case 4:
                    {
                        //pass
                    } break;

                    case 5:
                    {
                        //pass
                    } break;

                    case 6:
                    {
                        //pass
                    } break;

                    case 7:
                    {
                        //pass
                    } break;
                }
            } break;

            case 2:
            {
                //pass
            } break;

            case 3:
            {
                //pass
            } break;

            case 4:
            {
                //pass
            } break;

            case 5:
            {
                //pass
            } break;

            case 6:
            {
                //pass
            } break;

            case 7:
            {
                //pass
            } break;
            default:
            {
                printf("Instruction not handled: %d", Ins);
            } break;
        }
    }
};


int main()
{
    Mem mem;
    CPU cpu;
    cpu.Reset(mem);
    cpu.Execute(mem);

    return 0;
}