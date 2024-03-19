/* Unicorn Emulator Engine */
/* Sample code to demonstrate how to emulate RISCV code */

#include <unicorn/unicorn.h>
#include <string.h>


static void test_riscv_andn(void)
{
    #define RISCV_CODE_ANDN "\x33\xf5\xa5\x40"    // 0011 0011 1111 0101 1010 0101 0100 0000   ===>       andn       a0,a1,a0

    #define ADDRESS 0x10000
    uc_engine *uc;
    uc_err err;

    uint32_t a0 = 0xFFFFBDDD;
    uint32_t a1 = 0x0;
    uint32_t a2 = 0x0;

    printf("##########################\n");
    printf("A0 = 0x%x\n", a0);
    printf("A1 = 0x%x\n", a1);
    printf("A2 = 0x%x\n", a2);
    printf("##########################\n");
    printf("pack A2, A0, A1\n");

    // Initialize emulator in RISCV64 mode
    err = uc_open(UC_ARCH_RISCV, UC_MODE_RISCV32, &uc);
    if (err) {
        printf("Failed on uc_open() with error returned: %u (%s)\n", err,
               uc_strerror(err));
        return;
    }

    // map 2MB memory for this emulation
    uc_mem_map(uc, ADDRESS, 2 * 1024 * 1024, UC_PROT_ALL);

    // write machine code to be emulated to memory
    uc_mem_write(uc, ADDRESS, RISCV_CODE_ANDN, sizeof(RISCV_CODE_ANDN) - 1);

    // initialize machine registers
    uc_reg_write(uc, UC_RISCV_REG_A0, &a0);
    uc_reg_write(uc, UC_RISCV_REG_A1, &a1);
    uc_reg_write(uc, UC_RISCV_REG_A2, &a2);

    // emulate machine code in infinite time (last param = 0), or when
    // finishing all the code.
    err = uc_emu_start(uc, ADDRESS, ADDRESS + sizeof(RISCV_CODE_ANDN) - 1, 0, 0);
    if (err) {
        printf("Failed on uc_emu_start() with error returned: %u\n", err);
    }

    uc_reg_read(uc, UC_RISCV_REG_A2, &a2);
    printf("##########################\n");
    printf("A2 after  pack = 0x%x\n", a2);
    printf("##########################\n");

    uc_close(uc);
}


static void test_riscv_pack(void)
{
    #define RISCV_CODE_PACK "\x33\x46\xB5\x08"    // 0000 1000 0101 1101 0100 0110 0011 0011  ===> pack  a2, a0, a1 
    // #define RISCV_CODE_PACK "\x33\x45\x05\x08"    // 0000 1000 0101 1101 0100 0110 0011 0011  ===> pack  a0,a0,zero
    
   

    #define ADDRESS 0x10000
    uc_engine *uc;
    uc_err err;

    uint32_t a0 = 0xFFFFBDDD;
    uint32_t a1 = 0x0;
    uint32_t a2 = 0x0;

    printf("##########################\n");
    printf("A0 = 0x%x\n", a0);
    printf("A1 = 0x%x\n", a1);
    printf("A2 = 0x%x\n", a2);
    printf("##########################\n");
    printf("pack A2, A0, A1\n");

    // Initialize emulator in RISCV64 mode
    err = uc_open(UC_ARCH_RISCV, UC_MODE_RISCV32, &uc);
    if (err) {
        printf("Failed on uc_open() with error returned: %u (%s)\n", err,
               uc_strerror(err));
        return;
    }

    // map 2MB memory for this emulation
    uc_mem_map(uc, ADDRESS, 2 * 1024 * 1024, UC_PROT_ALL);

    // write machine code to be emulated to memory
    uc_mem_write(uc, ADDRESS, RISCV_CODE_PACK, sizeof(RISCV_CODE_PACK) - 1);

    // initialize machine registers
    uc_reg_write(uc, UC_RISCV_REG_A0, &a0);
    uc_reg_write(uc, UC_RISCV_REG_A1, &a1);
    uc_reg_write(uc, UC_RISCV_REG_A2, &a2);

    // emulate machine code in infinite time (last param = 0), or when
    // finishing all the code.
    err = uc_emu_start(uc, ADDRESS, ADDRESS + sizeof(RISCV_CODE_PACK) - 1, 0, 0);
    if (err) {
        printf("Failed on uc_emu_start() with error returned: %u\n", err);
    }

    uc_reg_read(uc, UC_RISCV_REG_A2, &a2);
    printf("##########################\n");
    printf("A2 after  pack = 0x%x\n", a2);
    printf("##########################\n");

    uc_close(uc);
}

static void test_riscv_sext(void)
{   
    #define RISCV_CODE_SEXT "\x13\x15\x55\x60"    // sext.h
    // #define RISCV_CODE_SEXT "\x13\x15\x45\x60" // sext.b


    uc_engine *uc;
    uc_err err;

    uint32_t a0 = 0x8000;
    printf("\n\n##########################\n");
    printf("A0 = 0x%x\n", a0);
    printf("##########################\n");
    printf("sext.h A0, A0\n");

    // Initialize emulator in RISCV64 mode
    err = uc_open(UC_ARCH_RISCV, UC_MODE_RISCV32, &uc);
    if (err) {
        printf("Failed on uc_open() with error returned: %u (%s)\n", err,
               uc_strerror(err));
        return;
    }

    // map 2MB memory for this emulation
    uc_mem_map(uc, ADDRESS, 2 * 1024 * 1024, UC_PROT_ALL);

    // write machine code to be emulated to memory
    uc_mem_write(uc, ADDRESS, RISCV_CODE_SEXT, sizeof(RISCV_CODE_SEXT) - 1);

    // initialize machine registers
    uc_reg_write(uc, UC_RISCV_REG_A0, &a0);

    // emulate machine code in infinite time (last param = 0), or when
    // finishing all the code.
    err = uc_emu_start(uc, ADDRESS, ADDRESS + sizeof(RISCV_CODE_SEXT) - 1, 0, 0);
    if (err) {
        printf("Failed on uc_emu_start() with error returned: %u\n", err);
    }

    uc_reg_read(uc, UC_RISCV_REG_A0, &a0);
    printf("##########################\n");
    printf("A0 after sext = 0x%x\n", a0);
    printf("##########################\n");

    uc_close(uc);
}


static void test_riscv_cpop(void)
{   
    #define RISCV_CODE_CPOP "\x13\x15\x25\x60"    // sext.h


    uc_engine *uc;
    uc_err err;

    uint32_t a0 = 0x70807080;
    printf("\n\n##########################\n");
    printf("A0 = 0x%x\n", a0);
    printf("##########################\n");
    printf("pcnt A0, A0\n");

    // Initialize emulator in RISCV64 mode
    err = uc_open(UC_ARCH_RISCV, UC_MODE_RISCV32, &uc);
    if (err) {
        printf("Failed on uc_open() with error returned: %u (%s)\n", err,
               uc_strerror(err));
        return;
    }

    // map 2MB memory for this emulation
    uc_mem_map(uc, ADDRESS, 2 * 1024 * 1024, UC_PROT_ALL);

    // write machine code to be emulated to memory
    uc_mem_write(uc, ADDRESS, RISCV_CODE_CPOP, sizeof(RISCV_CODE_CPOP) - 1);

    // initialize machine registers
    uc_reg_write(uc, UC_RISCV_REG_A0, &a0);

    // emulate machine code in infinite time (last param = 0), or when
    // finishing all the code.
    err = uc_emu_start(uc, ADDRESS, ADDRESS + sizeof(RISCV_CODE_CPOP) - 1, 0, 0);
    if (err) {
        printf("Failed on uc_emu_start() with error returned: %u\n", err);
    }

    uc_reg_read(uc, UC_RISCV_REG_A0, &a0);
    printf("##########################\n");
    printf("A0 after (pcnt/cpop) = 0x%x\n", a0);
    printf("##########################\n");

    uc_close(uc);
}


int main(int argc, char **argv, char **envp)
{
    test_riscv_andn();
    test_riscv_pack();
    test_riscv_sext();
    test_riscv_cpop();
    return 0;
}




