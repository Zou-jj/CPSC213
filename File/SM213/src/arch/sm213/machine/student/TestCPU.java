package arch.sm213.machine.student;

import machine.AbstractCPU;
import machine.AbstractMainMemory;
import machine.RegisterSet;
import org.junit.Before;
import org.junit.Test;

public class TestCPU {
    CPU cpu;
    MainMemory mem = new MainMemory(12);

    @Before
    public void before() {
        byte[] ins = new byte[12];
        ins[0] = (byte) 0x01;
        ins[1] = (byte) 0x00;
        ins[2] = (byte) 0x12;
        ins[3] = (byte) 0x34;
        ins[4] = (byte) 0x56;
        ins[5] = (byte) 0x78;
        ins[6] = (byte) 0x71;
        ins[7] = (byte) 0xf4;
        ins[8] = (byte) 0xf0;
        ins[9] = (byte) 0x00;
        ins[10] = (byte) 0x00;
        ins[11] = (byte) 0x00;
        try {
            mem.set(0x0000, ins);
        } catch (AbstractMainMemory.InvalidAddressException e) {
            e.printStackTrace();
        }
        cpu = new CPU("cpu", mem);
    }

    @Test
    public void testShr() {
        before();
        try {
            cpu.fetch();
            cpu.execute();
            cpu.fetch();
            cpu.execute();
            cpu.fetch();
            cpu.execute();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}